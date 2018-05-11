#include "student.h"
#include <QDebug>

Student::Student(QObject *parent) : QObject(parent)
{
    firstName = QString("none");
    familyName = QString("none");
    matricNumber = 0;
    choiceAllocated = 0;
    GPA = 10.0;
    firstChoice = QString("none");
    secondChoice = QString("none");
    thirdChoice = QString("none");
    fourthChoice = QString("none");
    fifthChoice = QString("none");
    planCode = QString("none");
    personalProject = QString("none");
    requestedBySupervisor = QString("none");
    allocatedProject = nullptr;
    projectAssigned = false;
}

void Student::displayStudentData()
{
//    qDebug() << " Name \t" << this->firstName << " " << this->familyName << "\n"
//             << "Matric# \t" << this->matricNumber << "\n"
//             << "GPA \t" << this->GPA << "\n"
//             << "First \t" << this->firstChoice << "\n"
//             << "Second \t" << this->secondChoice << "\n"
//             << "Third \t" << this->thirdChoice << "\n"
//             << "Fourth \t" << this->fourthChoice << "\n"
//             << "Fifth \t" << this->fifthChoice << "\n";
    if(allocatedProject){
        qDebug() << " Name \t" << this->firstName << " " << this->familyName << "\n"
                 << "Matric# \t" << this->matricNumber << "\n"
                 << "GPA \t" << this->GPA << "\n"
                 << "Allocated \t" << this->allocatedProject->getProjectTitle();
    }
    else{
        qDebug() << " Name \t" << this->firstName << " " << this->familyName << "\n"
                 << "Matric# \t" << this->matricNumber << "\n"
                 << "GPA \t" << this->GPA << "\n"
                 << "Allocated \t" << "No project allocated\n\n";
    }

}


int Student::getMatricNumber() const
{
    return matricNumber;
}

void Student::setMatricNumber(const int &value)
{
    matricNumber = value;
}

float Student::getGPA() const
{
    return GPA;
}

void Student::setGPA(float value)
{
    GPA = value;
}

QString Student::getFirstChoice() const
{
    return firstChoice;
}

void Student::setFirstChoice(const QString &value)
{
    firstChoice = value;
}

QString Student::getSecondChoice() const
{
    return secondChoice;
}

void Student::setSecondChoice(const QString &value)
{
    secondChoice = value;
}

QString Student::getThirdChoice() const
{
    return thirdChoice;
}

void Student::setThirdChoice(const QString &value)
{
    thirdChoice = value;
}

QString Student::getFourthChoice() const
{
    return fourthChoice;
}

void Student::setFourthChoice(const QString &value)
{
    fourthChoice = value;
}

QString Student::getFifthChoice() const
{
    return fifthChoice;
}

void Student::setFifthChoice(const QString &value)
{
    fifthChoice = value;
}

QString Student::getPersonalProject() const
{
    return personalProject;
}

void Student::setPersonalProject(const QString &value)
{
    personalProject = value;
}

QString Student::getRequestedBySupervisor() const
{
    return requestedBySupervisor;
}

void Student::setRequestedBySupervisor(const QString &value)
{
    requestedBySupervisor = value;
}


QString Student::getFirstName() const
{
    return firstName;
}

void Student::setFirstName(const QString &value)
{
    firstName = value;
    if(value.isEmpty())
        firstName = QString(" ");
}

QString Student::getFamilyName() const
{
    return familyName;
}

void Student::setFamilyName(const QString &value)
{
    familyName = value;
    if(value.isEmpty())
        firstName = QString(" ");
}

int Student::getChoiceAllocated() const
{
    return choiceAllocated;
}

void Student::setChoiceAllocated(int value)
{
    choiceAllocated = value;
}

Project *Student::getAllocatedProject() const
{
    return allocatedProject;
}

void Student::setAllocatedProject(Project *value)
{
    allocatedProject = value;
}

bool Student::getProjectAssigned() const
{
    return projectAssigned;
}

void Student::setProjectAssigned(bool value)
{
    projectAssigned = value;
}

QString Student::getPlanCode() const
{
    return planCode;
}

void Student::setPlanCode(const QString &value)
{
    planCode = value;
}
