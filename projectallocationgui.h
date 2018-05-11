#ifndef PROJECTALLOCATIONGUI_H
#define PROJECTALLOCATIONGUI_H

#include <QMainWindow>
#include <QHash>
#include <QHashIterator>
#include <QMap>
#include <QMapIterator>
#include <QList>
#include <QListIterator>
#include <QStringList>
#include <QStringListIterator>
#include <QStandardItemModel>
#include <QSortFilterProxyModel>
#include <QLabel>
#include <QProgressBar>
#include "student.h"
#include "project.h"


namespace Ui {
class ProjectAllocationGUI;
}

class ProjectAllocationGUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit ProjectAllocationGUI(QWidget *parent = 0);
    ~ProjectAllocationGUI();
    /*!
     * \brief allocateProjects: This function is used to allocate projects to students
     * based on their GPA and preferences.
     */
    void allocateProjects();
    /*!
     * \brief loadStudentList:
     */
    void loadStudentList();
    void createModels();
    void loadProjectList();
    void loadEligibleStaff();
    int loadStudentGPAList();
    void processStudentLine(QString line);
    void processProjectLine(QString line);
    void processStudentGPALine(QString line);
    void processEligibleStaffLine(QString line);
    //
    void processStudentLineModel(QString line);
    void processProjectLineModel(QString line);
    void processStudentGPALineModel(QString line);
    void processEligibleStaffLineModel(QString line);
    bool checkManualAllocation(int row);
    //
    Student *maxGPA(QList<Student*> students);
    void saveAllocation();
    void saveStaffData();
    void displayProjectData();
    QList<Project *> getUnallocatedProjects();
    QList<Student *> getUnallocatedStudents();
    //
    QVariant getModelData(QStandardItemModel* model, int row, int col);
    QVariant getModelData(QSortFilterProxyModel *model, int row, int col);


public slots:
    void updateTotalLoad();
    void updateStaffLoad(int row);
    void updateStaffLoadProxy(QSortFilterProxyModel *staffProxyModel, int row);


private slots:
    void on_assigProjectsButton_clicked();

    void on_actionLoad_Student_List_triggered();

    void on_actionAdd_GPA_List_triggered();

    void on_actionAdd_Project_List_triggered();

    void on_actionExport_triggered();
    
    void on_randomAllocationPushButton_clicked();

    void on_pushButtonRankGPA_clicked();

    void on_actionClear_All_triggered();

    void on_viewAllButton_clicked();

    void on_viewUnallocatedBitton_clicked();

    void on_courseCodeComboBox_currentIndexChanged(const QString &arg1);

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionAdd_Student_triggered();

    void on_actionAdd_Project_triggered();

    void on_actionRemove_Student_triggered();

    void on_actionRemove_Project_triggered();

    void on_assignSupervisorsButton_clicked();

    void on_actionRemove_Staff_triggered();

private:
    enum studentHeadersEnum{
        MATRIC,
        SURNAME,
        FIRSTNAME,
        COURSE,
        GPA,
        ALLOCATEDPROJECT,
        SUPERVISOR,
        SECONDSUPERVISOR,
        CHOICEALLOCATED,
        FIRST,
        SECOND,
        THIRD,
        FOURTH,
        FIFTH
    };
    enum projectsHeadersEnum{
        TITLE,
        STAFFMEMBER,
        STUDENTALLOCATED,
        APPLICABLECOURSES
    };
    enum staffHeadersEnum{
        NAME,
        NUMPROJECTSOFFERED,
        NUMPROJECTSALLOCATED,
        DIVISION,
        NUMSECONDSUPERVISOR,
        NUMPDSUPERVISOR,
        TOTALLOAD
    };
    enum divisionsEnum{
        AS,
        ENE,
        IE,
        SPE,
        BENG
    };
    enum coursesEnum{
        AE,
        AEM,
        BE,
        CE,
        CEM,
        CSE,
        EEE,
        EEEM,
        ME,
        MEM,
        MECH,
        NN,
        SE
    };

    Ui::ProjectAllocationGUI *ui;
    QString studentListFileLocation;
    QString projectListFileLocation;
    QHash<int,Student*> studentList;
    QList<Project*> projectList;
    QList<Project*> allocatedProjectsList;
    QMap<QString,Project*> projectTitleList;
    QHash<QString,QString> projectTitlesHash;
    QMap<float,int> sortedStudentList;
    QList<QStringList> studentsOmitted;
    QList<Student*> studentsWithGPA;
    QStringList coursesRunning;
    QStringList divisions;
    QMap<QString,QString> coursesRunningMap;
    QMap<QString,QString> divisionsMap;
    QStandardItemModel *studentModel;
    QStandardItemModel *projectModel;
    QStandardItemModel *staffModel;
    QStandardItemModel *projectTitleModel;
    QStandardItemModel *coursesModel;
    QLabel *statusLabel;
    QProgressBar *statusProgressBar;
};

#endif // PROJECTALLOCATIONGUI_H
