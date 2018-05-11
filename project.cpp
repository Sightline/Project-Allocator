#include "project.h"
#include "student.h"

Project::Project(QObject *parent) : QObject(parent)
{
    projectAssigned = false;
}

QString Project::getProjectTitle() const
{
    return projectTitle;
}

void Project::setProjectTitle(const QString &value)
{
    projectTitle = value;
}

QString Project::getStaffName() const
{
    return staffName;
}

void Project::setStaffName(const QString &value)
{
    staffName = value;
}

int Project::getMultiplicity() const
{
    return multiplicity;
}

void Project::setMultiplicity(int value)
{
    multiplicity = value;
}

Student *Project::getAllocatedStudent() const
{
    return allocatedStudent;
}

void Project::setAllocatedStudent(Student *value, int choice)
{
    // First check this student doesn't already have a project assigned.
    if(value->getAllocatedProject()->getProjectTitle() == QString("none"))
    {
        allocatedStudent = value;
        projectAssigned = true;
        value->setAllocatedProject(this);
        value->setChoiceAllocated(choice);
    }

}

bool Project::getProjectAssigned() const
{
    return projectAssigned;
}

void Project::setProjectAssigned(bool value)
{
    projectAssigned = value;
}

QStringList Project::getApplicableCourses() const
{
    return applicableCourses;
}

void Project::setApplicableCourses(const QStringList &value)
{
    applicableCourses = value;
}

