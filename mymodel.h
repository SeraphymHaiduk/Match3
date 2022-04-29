#ifndef CPPMODEL_H
#define CPPMODEL_H
#include <QAbstractListModel>
#include <QModelIndex>
enum class ElementState{
    Pressed,
    NotPressed,
    Wrong,
    Deleted
};
struct Element{
    Element(QString color){
        m_color = color;
    }
    Element(QString color,ElementState state){
        m_color = color;
        m_state = state;
    }
    QString m_color;
    ElementState m_state = ElementState::NotPressed;
};


class MyModel: public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int rowsCount READ getRowsCount NOTIFY rowsCountChanged)
    Q_PROPERTY(int columnsCount READ getColumnsCount NOTIFY columnsCountChanged)
    Q_PROPERTY(int score READ getScore NOTIFY scoreChanged)
    Q_PROPERTY(int steps READ getSteps NOTIFY stepsChanged);
public:
    MyModel(QObject* parent = 0);
    enum Roles{
        ColorRole = Qt::UserRole+1,
        StateRole,
    };
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    QHash <int,QByteArray> roleNames() const override;
    bool setData(const QModelIndex& index, const QVariant& value,int role = Qt::EditRole) override;

    int getRowsCount() const;
    int getColumnsCount() const;
    int getScore() const;
    int getSteps() const;

    Q_INVOKABLE void populate();

    Q_INVOKABLE bool pressOn(int index);
    Q_INVOKABLE void setState(int index, QString state);

    Q_INVOKABLE void removeMatches();
    Q_INVOKABLE void checkNewMatches();

    Q_INVOKABLE bool isElementPressed(int index) const;
    Q_INVOKABLE bool isElementDeleted(int index) const;
signals:
    void rowsCountChanged();
    void columnsCountChanged();
    void scoreChanged();
    void stepsChanged();

    void wrongChoise(int firstChoise, int secondChoise);
    void rightChoise(int firstChoise, int secondChoise);
    void matchesHappened(QList<int> matchesToRemove);

    void gameOver();
private:
    QList<Element> m_data;
    int m_lastChoise = -1;
    QList<QString> m_availableColors;
    int m_rowsCount, m_columnsCount;

    int m_score, m_steps;

    void setState(int index, ElementState state);
    void setSteps(int steps);
    void setScore(int score);

    QList<int> swap(int a, int b);
    void clearMatches(QMap<QString,QList<QList<int>>> &matches);
    QList<QList<int>> hasMatches(int leftTop, int rightBottom, const QList<Element>& area);
    bool matchesIsPossible();
};

#endif // CPPMODEL_H
