#include "mymodel.h"
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <random>
#include <QFile>
MyModel::MyModel(QObject* parent) : QAbstractListModel(parent)
{
    qDebug() << "Model created";
    populate();
    qDebug() << "data size: " << m_data.size();

}

int MyModel::rowCount(const QModelIndex& parent) const{
    if(parent.isValid()){
        return 0;
    }

    return m_data.length();
}
QVariant MyModel::data(const QModelIndex& index, int role) const{
    if(!index.isValid()){
        return QVariant();
    }
    switch (role){
    case ColorRole: return m_data.at(index.row()).m_color;
    case StateRole: return m_data.at(index.row()).m_state;
    default: return QVariant();
    }
}

bool MyModel::setData(const QModelIndex &index, const QVariant& value, int role){
    if(!index.isValid()){
        return false;
    }
    switch(role){
    case StateRole: m_data[index.row()].m_state = value.toString();
        dataChanged(index,index,QVector<int>() << StateRole);
        return true;
    default: return false;
    }
}
QHash <int,QByteArray> MyModel::roleNames() const{
    QHash<int,QByteArray> roles = QAbstractListModel::roleNames();
    roles[ColorRole] = "colorName";
    roles[StateRole] = "state";
    return roles;
}


void MyModel::populate(){
    QFile file("config.json");
    if(!file.open(QIODevice::ReadOnly)){
       qDebug() << "Cannot open config.json";
    }
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll().data());
    QJsonObject obj = doc.object();
    QJsonArray list = obj.value("colors").toArray();
    int tmp = obj.value("height").toInt();
    if(tmp < 5 || tmp > 50){
        tmp = 5;
    }
    m_rowsCount = tmp;
    tmp = obj.value("width").toInt();
    if(tmp < 5 || tmp > 50){
        tmp = 5;
    }
    m_columnsCount = tmp;
    qDebug() << m_rowsCount << m_columnsCount;
    int count = m_rowsCount*m_columnsCount;
    beginInsertRows(QModelIndex(),0,count-1);
    srand(time(NULL));
    for(int i = 0; i < count; i++){
        m_data.append(list[std::rand()%list.count()].toString());
    }
    endInsertRows();
    QList<QList<int>> matchList;
    QMap<QString,QList<QList<int>>> map;
    for(auto& a: matchList){
        map[m_data[a.first()].m_color].append(a);
    }
    qDebug() << map;
    matchList = hasMatches(0,m_data.size()-1,m_data);
    while(matchList.size() != 0){
        for(auto& a: matchList){
            map[m_data[a.first()].m_color].append(a);
        }
        clearMatches(map);
        matchList = hasMatches(0,m_data.size()-1,m_data);
    }
}

void MyModel::clearMatches(QMap<QString, QList<QList<int>>> &matches){
    QList<QString> keys = matches.keys();
    QString newColor;
    for(QString& colorKey: keys){
        for(QList<int>& match: matches[colorKey]){
            int i = 2;
            while(i < match.length()){
                do{
                    newColor = m_data[std::rand()%m_data.size()].m_color;
                }while(newColor == colorKey);
                m_data[match[i]] = newColor;
                i+=3;
            }
        }
    }
}

void MyModel::removeMatches(){
    if(m_matchesToRemove.size() == 0){
        return;
    }
    QSet<int> set;
    for(auto& a: m_matchesToRemove){
        for(int index: a){
            set.insert(index);
        }
    }
    qDebug() << set;
    QList<int> matches = set.values();
    for(int i = 0; i < matches.size()-1; i++){
        int min = i;
        for(int j = i+1; j < matches.size();j++){
            if(matches[j] < matches[min]){
               min = j;
            }
        }
        int tmp = matches[i];
        matches[i] = matches[min];
        matches[min] = tmp;
    }
    qDebug() << matches;
    for(int i = 0; i < matches.count(); i++){
        beginRemoveRows(QModelIndex(),matches[i]-i,matches[i]-i);
        m_data.removeAt(matches[i]-i);
        endRemoveRows();
    }
}

bool MyModel::swap(int a, int b){
    if(a >= m_data.size() || b >= m_data.size())
        return false;
    int j = a% m_columnsCount;
    int i = a/m_columnsCount;
    int first, second;
    auto matchIsPossible = [this](int first,int second) -> bool{
        QList<Element> tmpData = m_data;
        QString tmp = tmpData[first].m_color;
        tmpData[first] = tmpData[second];
        tmpData[second] = tmp;
        m_matchesToRemove = hasMatches(0,tmpData.size()-1,tmpData);
        if(m_matchesToRemove.size() == 0){
            return false;
        }
        return true;
    };
    if(b == a-m_columnsCount && i>0){                   //up+
            first = j+i*m_columnsCount;
            second = j+((i-1)*m_columnsCount);
            if(!matchIsPossible(first,second)){
                return false;
            }
            beginMoveRows(QModelIndex(), first,first,QModelIndex(),second);
                m_data.move(first,second);
            endMoveRows();
            first = (j+1)+(i-1)*m_columnsCount;
            second = j+((i)*m_columnsCount)+1;
            beginMoveRows(QModelIndex(),first,first,QModelIndex(),second);
                m_data.move(first,second-1);
            endMoveRows();
            return true;
    }
    if(b == a-1 && j>0){                                //left+
            first = j+(i*m_columnsCount);
            second = (j-1)+i*m_columnsCount;
            if(!matchIsPossible(first,second)){
                return false;
            }
            beginMoveRows(QModelIndex(),first,first,QModelIndex(),second);
                m_data.move(first,second);
            endMoveRows();
            return true;
    }

    if(b == a+1 && j<m_columnsCount-1){                 //right+
            first = j+i*m_columnsCount;
            second = j+1+i*m_columnsCount+1;
            if(!matchIsPossible(first,second-1)){
                return false;
            }
            beginMoveRows(QModelIndex(),first,first,QModelIndex(),second);
                m_data.move(first,second-1);
            endMoveRows();
            return true;
    }
    if(b == a+m_columnsCount && i<m_columnsCount-1){     //down+
            first = j+i*m_columnsCount;
            second = j+((i+1)*m_columnsCount);
            if(!matchIsPossible(first,second)){
                return false;
            }
            beginMoveRows(QModelIndex(),first,first,QModelIndex(),second);
                m_data.move(first,second-1);
            endMoveRows();
            first = (j)+(i+1)*m_columnsCount;
            second = j+(i*m_columnsCount);
            beginMoveRows(QModelIndex(),first,first,QModelIndex(),second);
                m_data.move(first,second);
            endMoveRows();
            return true;
    }
    return false;
}

bool MyModel::pressOn(int index){
    if(index != m_lastChoise){
        if(m_lastChoise == -1){
            m_lastChoise = index;
        }
        else{
            if(swap(m_lastChoise,index)){
                emit rightChoise(m_lastChoise,index,m_matchesToRemove);
            }
            else{
                emit wrongChoise(m_lastChoise,index);
            }
            m_lastChoise = -1;
        }
        return true;
    }
    return false;
}

QList<QList<int>> MyModel::hasMatches(int leftTop, int rightBottom, const QList<Element>& area){
    QList<QList<int>> list;
    if(leftTop < 0 || rightBottom >= area.size() ){
        qDebug() << "uncorrect params: " << "leftTop: " << leftTop << " rightBottom: " << rightBottom
        << " m_columnsCount: " << m_columnsCount << " m_rowsCount " << m_rowsCount;
        return list;
    }
    int i1,j1,i2,j2;
    i1 = leftTop/m_columnsCount;
    j1 = leftTop%m_columnsCount;
    i2 = rightBottom/m_columnsCount;
    j2 = rightBottom%m_columnsCount;
    QList<int> tmpList;
    if((j2 - j1) >= 2){
        for(int i = i1; i <= i2; i++){      //find horizontal matches
            tmpList.clear();
            tmpList.push_back(j1+i*m_columnsCount);
            for(int j = j1+1; j <= j2; j++){
                int currentIndex = i*m_columnsCount+j;
                if(area[tmpList.last()].m_color == area[currentIndex].m_color){
                    tmpList.push_back(currentIndex);
                }
                else{
                    if(tmpList.length() >= 3){
                        list.append(tmpList);
                    }
                    tmpList.clear();
                    tmpList.push_back(currentIndex);
                }
            }
            if(tmpList.length() >= 3){
                list.append(tmpList);
            }
        }
    }
    if((i2 - i1) >= 2){
        for(int j = j1; j <= j2; j++){      //find vertical matches
            tmpList.clear();
            tmpList.push_back(j+i1*m_columnsCount);
            for(int i = i1+1; i <= i2; i++){
                int currentIndex = i*m_columnsCount+j;
                if(area[tmpList.last()].m_color == area[currentIndex].m_color){
                    tmpList.push_back(currentIndex);
                }
                else{
                    if(tmpList.length() >= 3){
                        list.append(tmpList);
                    }
                    tmpList.clear();
                    tmpList.push_back(currentIndex);
                }
            }
            if(tmpList.length() >= 3){
                list.append(tmpList);
            }
        }
    }
    return list;
}

int MyModel::getRowsCount() const{
    return m_rowsCount;
}

int MyModel::getColumnsCount()const{
    return m_columnsCount;
}

void MyModel::setState(int index, QString state){
    setData(this->index(index),state,StateRole);
}
