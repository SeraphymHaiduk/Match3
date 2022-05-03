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
    QObject::connect(this,&MyModel::readyToDisappear,[this](){
        for(auto& element: m_matchesToRemove){
            setState(element,ElementState::Deleted);
        }
        m_matchesToRemove.clear();
    });
    QObject::connect(this,&MyModel::readyToRemove,this,&MyModel::removeMatches);
}

int MyModel::rowCount(const QModelIndex& parent) const{
    if(parent.isValid()){
        return 0;
    }

    return m_data.length();
}

QString MyModel::stateToString(ElementState state){
    switch (state) {
    case ElementState::Pressed: return "pressed";
    case ElementState::NotPressed: return "notpressed";
    case ElementState::Wrong: return "wrong";
    case ElementState::Deleted: return "deleted";
    default: qDebug() << QString("%1 state case not implemented in this function").arg(int(state));
        return QString();
    }
}

QVariant MyModel::data(const QModelIndex& index, int role) const{
    if(!index.isValid()){
        return QVariant();
    }
    switch (role){
    case ColorRole: return m_data.at(index.row()).m_color;
    case StateRole: {
        return int(m_data.at(index.row()).m_state);
        }
    default: return QVariant();
    }
}

QHash <int,QByteArray> MyModel::roleNames() const{
    QHash<int,QByteArray> roles = QAbstractListModel::roleNames();
    roles[ColorRole] = "colorName";
    roles[StateRole] = "state";
    return roles;
}


void MyModel::populate(){
    do{
        beginResetModel();
        m_data.clear();
        endResetModel();
        int m_lastChoise = -1;
        setScore(0);
        setSteps(0);
        setRowsCount(0);
        setColumnsCount(0);

        auto defaultInit = [this](){
            m_availableColors = {"red","green","blue"};
            setRowsCount(5);
            setColumnsCount(5);
        };

        auto initFromConfig = [this]() -> bool{
            QFile file("config.json");
            if(!file.open(QIODevice::ReadOnly)){
               qDebug() << "Cannot open config.json";
               return false;
               //run initialization by default
            }
            QJsonDocument doc = QJsonDocument::fromJson(file.readAll().data());
            qDebug() << 1;
            QJsonObject obj = doc.object();
            qDebug() << 2;
            QJsonArray list = obj.value("colors").toArray();
            qDebug() << 3;
            if(m_availableColors.size() > 0)
                m_availableColors.clear();
            for(auto color: list){
                m_availableColors.append(color.toString());
            }
            qDebug() << m_availableColors;
            if(m_availableColors.size() < 3)
                return false;
            int tmp = obj.value("height").toInt();
            if(tmp < 5 || tmp > 50){
                tmp = 5;
            }
            setRowsCount(tmp);
            tmp = obj.value("width").toInt();
            if(tmp < 5 || tmp > 50){
                tmp = 5;
            }
            setColumnsCount(tmp);
            return true;
        };

        if(!initFromConfig())
            defaultInit();

        int count = m_rowsCount*m_columnsCount;

        beginInsertRows(QModelIndex(),0,count-1);
        srand(time(NULL));
        for(int i = 0; i < count; i++){
            m_data.append(m_availableColors[std::rand()%m_availableColors.count()]);
        }
        QList<QList<int>> matchList;
        QMap<QString,QList<QList<int>>> map;
        for(auto& a: matchList){
            map[m_data[a.first()].m_color].append(a);
        }
        matchList = hasMatches(m_data);
        while(matchList.size() != 0){
            for(auto& a: matchList){
                map[m_data[a.first()].m_color].append(a);
            }
            clearMatches(map);
            matchList = hasMatches(m_data);
        }
        endInsertRows();

    }while(!matchesIsPossible());
}

void MyModel::clearMatches(QMap<QString, QList<QList<int>>> &matches){
    QList<QString> keys = matches.keys();
    QString newColor;
    for(QString& colorKey: keys){
        for(QList<int>& match: matches[colorKey]){
            int i = 2;
            while(i < match.length()){
                do{
                    newColor = m_availableColors[std::rand()%m_availableColors.size()];
                }while(newColor == colorKey);
                m_data[match[i]] = newColor;
                i+=3;
            }
        }
    }
}


void MyModel::removeMatches(){
    qDebug() << "remove Matches";
    QList<int> arr;
    for(auto& element: m_data){
        arr << int(element.m_state);
    }

    auto elementIsEmpty = [this](int index){
        return m_data[index].m_state == ElementState::Deleted;
    };

    int scoreIncrease = 0;
    for(int j = 0; j < m_columnsCount;j++){
        int deletedCount = 0;
        int i;
        int first;
        for(i = m_rowsCount-1;i >= 0; i--){
            first = i*m_columnsCount+j;
            if(elementIsEmpty(first)){
                deletedCount++;
                beginRemoveRows(QModelIndex(),first,first);
                m_data.removeAt(first);
                endRemoveRows();
            }
            else if(deletedCount != 0){
                int second = (i+deletedCount)*m_columnsCount+j-deletedCount;
                beginMoveRows(QModelIndex(),first,first,QModelIndex(),second+1);
                m_data.move(first,second);
                endMoveRows();
            }
        }
        for(i = 0;i < deletedCount; i++){
            first = i*m_columnsCount+j;

            beginInsertRows(QModelIndex(),first,first);
            m_data.insert(first,Element{m_availableColors[std::rand()%m_availableColors.size()],ElementState::NotPressed});
            endInsertRows();
        }
        scoreIncrease += deletedCount;
    }
    setScore(m_score+scoreIncrease);
    checkNewMatches();
}

void MyModel::checkNewMatches(){
    qDebug() << "check new matches";
    QList<QList<int>> listOfLists = hasMatches(m_data);
    if(listOfLists.size() > 0){
        for(auto& list: listOfLists){
            for(auto match: list){
                m_matchesToRemove.append(match);
            }
        }
        qDebug() << "new matches: " << m_matchesToRemove;
        emit matchesHappened();
    }
    else{
       qDebug() << "hasn't matches"    ;
       if(!matchesIsPossible()){
           emit gameOver();
       }
    }
}

QList<int> MyModel::swap(int a, int b){
    if(a >= m_data.size() || b >= m_data.size() || a == b)
        return QList<int>();
    int j = a% m_columnsCount;
    int i = a/m_columnsCount;
    int first, second;
    auto possibleMatches = [this](int first,int second) -> QList<int>{
        QList<Element> tmpData = m_data;
        QString tmp = tmpData[first].m_color;
        tmpData[first] = tmpData[second];
        tmpData[second] = tmp;
        QList<QList<int>> listOfMatchLists = hasMatches(tmpData);
        QList<int> matches;
        for(auto& list: listOfMatchLists){
            for(int index: list){
                if(matches.contains(index) == false){
                    matches.append(index);
                }
            }
        }
        return matches;
    };
    QList<int> matchesToRemove;
    if(b == a-m_columnsCount && i>0){                   //up+
            first = j+i*m_columnsCount;
            second = j+((i-1)*m_columnsCount);
            matchesToRemove = possibleMatches(first,second);
            if(matchesToRemove.size() == 0){
                return matchesToRemove;
            }
            beginMoveRows(QModelIndex(), first,first,QModelIndex(),second);
                m_data.move(first,second);
            endMoveRows();
            first = (j+1)+(i-1)*m_columnsCount;
            second = j+((i)*m_columnsCount)+1;
            beginMoveRows(QModelIndex(),first,first,QModelIndex(),second);
                m_data.move(first,second-1);
            endMoveRows();
            return matchesToRemove;
    }
    if(b == a-1 && j>0){                                //left+
            first = j+(i*m_columnsCount);
            second = (j-1)+i*m_columnsCount;
            matchesToRemove = possibleMatches(first,second);
            if(matchesToRemove.size() == 0){
                return matchesToRemove;
            }
            beginMoveRows(QModelIndex(),first,first,QModelIndex(),second);
                m_data.move(first,second);
            endMoveRows();
            return matchesToRemove;
    }
    if(b == a+1 && j<m_columnsCount-1){                 //right+
            first = j+i*m_columnsCount;
            second = j+1+i*m_columnsCount+1;
            matchesToRemove = possibleMatches(first,second-1);
            if(matchesToRemove.size() == 0){
                return matchesToRemove;
            }
            beginMoveRows(QModelIndex(),first,first,QModelIndex(),second);
                m_data.move(first,second-1);
            endMoveRows();
            return matchesToRemove;
    }
    if(b == a+m_columnsCount && i<m_columnsCount-1){     //down+
            first = j+i*m_columnsCount;
            second = j+((i+1)*m_columnsCount);
            matchesToRemove = possibleMatches(first,second);
            if(matchesToRemove.size() == 0){
                return matchesToRemove;
            }
            beginMoveRows(QModelIndex(),first,first,QModelIndex(),second);
                m_data.move(first,second-1);
            endMoveRows();
            first = (j)+(i+1)*m_columnsCount;
            second = j+(i*m_columnsCount);
            beginMoveRows(QModelIndex(),first,first,QModelIndex(),second);
                m_data.move(first,second);
            endMoveRows();
            return matchesToRemove;
    }
    return matchesToRemove;
}

bool MyModel::pressOn(int index){
    qDebug() << "pressOn";
    if(index != m_lastChoise){
        if(m_lastChoise == -1){
            m_lastChoise = index;
            setState(index,ElementState::Pressed);
        }
        else{
            setSteps(m_steps+1);
            m_matchesToRemove = swap(m_lastChoise,index);
            if(m_matchesToRemove.size() > 0){
                setState(m_lastChoise,ElementState::NotPressed);
                setState(index,ElementState::NotPressed);
                emit matchesHappened();
            }
            else{
                setState(m_lastChoise,ElementState::Wrong);
                setState(index,ElementState::Wrong);
            }
            m_lastChoise = -1;
        }
        return true;
    }
    else{
        setState(index,ElementState::NotPressed);
    }
    return false;
}

QList<QList<int>> MyModel::hasMatches(const QList<Element>& area){
    int leftTop = 0;
    int rightBottom = area.size()-1;
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

void MyModel::setState(int index, ElementState state){
    setData(this->index(index),int(state),StateRole);
}

bool MyModel::setData(const QModelIndex &index, const QVariant &value, int role){
    if(!index.isValid()){
        return false;
    }
    switch(role){
    case StateRole: {
        m_data[index.row()].m_state = ElementState(value.toInt());
        emit dataChanged(index,index,QVector<int>() << StateRole);
        return true;
    }
    default: return false;
    }
}


int MyModel::getScore() const{
    return m_score;
}


int MyModel::getSteps() const{
    return m_steps;
}

void MyModel::setScore(int score){
   m_score = score;
   emit scoreChanged();
}

void MyModel::setSteps(int steps){
    m_steps = steps;
    emit stepsChanged();
}

bool MyModel::matchesIsPossible(){
    auto possibleIfSwap = [this](int first, int second)->bool{
        m_data.swapItemsAt(first,second);
        QList<QList<int>> matches = hasMatches(m_data); //add finding in limited area
        m_data.swapItemsAt(first,second);
        if(matches.size() > 0){
            return true;
        }
        else{
            return false;
        }
    };

    auto possibleAt = [this, possibleIfSwap](unsigned int i,unsigned int j) -> bool{
        qDebug() << "possibleAt i: " << i  << "j: "<< j;
        if(i >= m_rowsCount || j >= m_columnsCount)
            return false;
        if(i > 0){
            if(possibleIfSwap(j+i*m_columnsCount,j+(i-1)*m_columnsCount))
                return true;
        }
        if(j < m_columnsCount-1){
            if(possibleIfSwap(j+i*m_columnsCount,j+1+i*m_columnsCount))
                return true;
        }
        if(i < m_rowsCount-1){
            if(possibleIfSwap(j+i*m_columnsCount,j+(i+1)*m_columnsCount))
                return true;
        }
        if(j > 0){
            if(possibleIfSwap(j+i*m_columnsCount,j-1+i*m_columnsCount))
                return true;
        }
        return false;
    };
    for(int vertical = 0; vertical <= 1; vertical++){
        int count1,count2;
        if(vertical){
            count1 = m_rowsCount;
            count2 = m_columnsCount;
        }
        else{
            count1 = m_columnsCount;
            count2 = m_rowsCount;
        }
        for(int i = 0; i < count1; i++){
            for(int j = 0; j < count2-2; j++){
                if(vertical){
                    if(m_data[i+j*count2].m_color == m_data[i+(j+1)*count2].m_color){ //[ ][|][|][ ][ }
                        if(possibleAt(j+2,i) || possibleAt(j-1,i)){
                            return true;
                        }
                    }
                    else if(m_data[i+j*count2].m_color == m_data[i+(j+2)*count2].m_color){ //[ ][|][ ][|][ }
                        if(possibleAt(j+1,i)){
                            return true;
                        }
                    }
                }
                else{
                    if(m_data[j+i*count2].m_color == m_data[j+1+i*count2].m_color){ //[ ][|][|][ ][ }
                        if(possibleAt(i,j+2) || possibleAt(i,j-1)){
                            return true;
                        }
                    }
                    else if(m_data[j+i*count2].m_color == m_data[j+2+i*count2].m_color){ //[ ][|][ ][|][ }
                        if(possibleAt(i,j+1)){
                            return true;
                        }
                    }
                }

            }
        }
    }
    return false;
}

void MyModel::setRowsCount(int value){
    m_rowsCount = value;
    emit rowsCountChanged();
}

void MyModel::setColumnsCount(int value){
    m_columnsCount = value;
    emit columnsCountChanged();
}
