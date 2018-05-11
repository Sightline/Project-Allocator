#ifndef PROJECT_H
#define PROJECT_H

#include <QObject>
#include <QVector>

QT_FORWARD_DECLARE_CLASS(Student)

class Project : public QObject
{
    Q_OBJECT
public:
    explicit Project(QObject *parent = 0);

    QString getProjectTitle() const;
    void setProjectTitle(const QString &value);

    QString getStaffName() const;
    void setStaffName(const QString &value);

    int getMultiplicity() const;
    void setMultiplicity(int value);

    Student *getAllocatedStudent() const;
    void setAllocatedStudent(Student *value, int choice);

    bool getProjectAssigned() const;
    void setProjectAssigned(bool value);

    QStringList getApplicableCourses() const;
    void setApplicableCourses(const QStringList &value);

private:
    QString projectTitle;
    QString staffName;
    int multiplicity;
    Student *allocatedStudent;
    bool projectAssigned;
    QStringList applicableCourses;

signals:

public slots:
};

#endif // PROJECT_H
