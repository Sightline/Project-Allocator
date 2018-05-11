#ifndef STUDENT_H
#define STUDENT_H

#include <QObject>
#include "project.h"

class Student : public QObject
{
    Q_OBJECT
public:
    explicit Student(QObject *parent = 0);
    void displayStudentData();

    int getMatricNumber() const;
    void setMatricNumber(const int &value);

    float getGPA() const;
    void setGPA(float value);

    QString getFirstChoice() const;
    void setFirstChoice(const QString &value);

    QString getSecondChoice() const;
    void setSecondChoice(const QString &value);

    QString getThirdChoice() const;
    void setThirdChoice(const QString &value);

    QString getFourthChoice() const;
    void setFourthChoice(const QString &value);

    QString getFifthChoice() const;
    void setFifthChoice(const QString &value);

    QString getPersonalProject() const;
    void setPersonalProject(const QString &value);

    QString getRequestedBySupervisor() const;
    void setRequestedBySupervisor(const QString &value);

    QString getFirstName() const;
    void setFirstName(const QString &value);

    QString getFamilyName() const;
    void setFamilyName(const QString &value);

    int getChoiceAllocated() const;
    void setChoiceAllocated(int value);

    Project *getAllocatedProject() const;
    void setAllocatedProject(Project *value);

    bool getProjectAssigned() const;
    void setProjectAssigned(bool value);

    QString getPlanCode() const;
    void setPlanCode(const QString &value);

private:
    QString firstName;
    QString familyName;
    int matricNumber;
    float GPA;
    QString firstChoice;
    QString secondChoice;
    QString thirdChoice;
    QString fourthChoice;
    QString fifthChoice;
    QString personalProject;
    QString requestedBySupervisor;
    QString planCode;
    Project *allocatedProject;
    int choiceAllocated;
    bool projectAssigned;

signals:

public slots:
};

#endif // STUDENT_H
