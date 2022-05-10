#ifndef CPPMODEL_H
#define CPPMODEL_H
#include <QAbstractListModel>
#include <QModelIndex>
#include <QList>




class MyModel: public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int rowsCount READ getRowsCount NOTIFY rowsCountChanged)
    Q_PROPERTY(int columnsCount READ getColumnsCount NOTIFY columnsCountChanged)
    Q_PROPERTY(int score READ getScore NOTIFY scoreChanged)
    Q_PROPERTY(int steps READ getSteps NOTIFY stepsChanged);
public:
    MyModel(QObject* parent = 0);
    enum Roles : unsigned short int{
        ColorRole = Qt::UserRole+1,
        StateRole,
    };
    enum class ElementState : unsigned char{
        Pressed,
        NotPressed,
        Wrong,
        Deleted
    };
    Q_ENUM(ElementState)
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    QHash <int,QByteArray> roleNames() const override;

    int getRowsCount() const;
    int getColumnsCount() const;
    int getScore() const;
    int getSteps() const;

    Q_INVOKABLE void populate();
    Q_INVOKABLE bool pressOn(int index);
    Q_INVOKABLE void setState(int index, int state);
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

signals:
    void rowsCountChanged();
    void columnsCountChanged();
    void scoreChanged();
    void stepsChanged();

    void wrongChoise();
    void rightChoise();
    void matchesHappened();
    void matchesNotHappened();

    void readyToDisappear();
    void readyToRemove();

    void gameOver();
private:
    QList<Element> m_data;
    int m_lastChoise = -1;
    QList<QString> m_availableColors;
    QList<int> m_matchesToRemove;
    int m_rowsCount, m_columnsCount;

    int m_score, m_steps;

    void setRowsCount(int value);
    void setColumnsCount(int value);
    void setSteps(int steps);
    void setScore(int score);
    void setState(int index, ElementState state);
    void removeMatches();
    void checkNewMatches();

    QList<int> swap(int a, int b);
    void clearMatches(QMap<QString,QList<QList<int>>> &matches);
    QList<QList<int>> hasMatches(const QList<Element>& area);
    bool matchesIsPossible();
};

#endif // CPPMODEL_H
