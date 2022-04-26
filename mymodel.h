#ifndef CPPMODEL_H
#define CPPMODEL_H
#include <QAbstractListModel>
#include <QModelIndex>
struct Element{
    Element(QString color){
        m_color = color;
    }
    QString m_color;
    QString m_state = "nonSqueezed";
};

class MyModel: public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int rowsCount READ getRowsCount NOTIFY rowsCountChanged)
    Q_PROPERTY(int columnsCount READ getColumnsCount NOTIFY columnsCountChanged)
public:
    MyModel(QObject* parent = 0);
    enum Roles{
        ColorRole = Qt::UserRole+1,
        StateRole,
    };
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    QHash <int,QByteArray> roleNames() const override;
    bool setData(const QModelIndex& index,const QVariant& value, int role = StateRole)override;

    int getRowsCount() const;
    int getColumnsCount() const;

    Q_INVOKABLE bool pressOn(int index);
    Q_INVOKABLE void setState(int index, QString state);
    Q_INVOKABLE void removeMatches();
signals:
    void rowsCountChanged() const;
    void columnsCountChanged() const;

    void wrongChoise(int firstChoise, int secondChoise);
    void rightChoise(QList<int> matchesToRemove);
private:
    QList<Element> m_data;
    int m_lastChoise = -1;

    int m_rowsCount;
    int m_columnsCount;

    void populate();
    QList<int> swap(int a, int b);
    void clearMatches(QMap<QString,QList<QList<int>>> &matches);
    QList<QList<int>> hasMatches(int leftTop, int rightBottom, const QList<Element>& area);
};

#endif // CPPMODEL_H
