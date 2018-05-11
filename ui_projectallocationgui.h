/********************************************************************************
** Form generated from reading UI file 'projectallocationgui.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROJECTALLOCATIONGUI_H
#define UI_PROJECTALLOCATIONGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ProjectAllocationGUI
{
public:
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionExport;
    QAction *actionClose;
    QAction *actionLoad_Student_List;
    QAction *actionAdd_Project_List;
    QAction *actionInfo;
    QAction *actionAdd_GPA_List;
    QAction *actionClear_All;
    QAction *actionAdd_Student;
    QAction *actionAdd_Project;
    QAction *actionRemove_Student;
    QAction *actionRemove_Project;
    QAction *actionRemove_Staff;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_6;
    QGroupBox *databaseGroupBox;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QSpacerItem *horizontalSpacer_5;
    QLineEdit *studentLineEdit;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_6;
    QLineEdit *gpsLineEdit;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_7;
    QLineEdit *projectLineEdit;
    QGroupBox *assignmentGroupBox;
    QVBoxLayout *verticalLayout;
    QPushButton *assigProjectsButton;
    QPushButton *randomAllocationPushButton;
    QPushButton *assignSupervisorsButton;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_4;
    QLineEdit *numStudentsLineEdit;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_5;
    QLineEdit *numProjectsLineEdit;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_6;
    QLineEdit *numAllocatedLineEdit;
    QGroupBox *filtersGroupBox;
    QVBoxLayout *verticalLayout_7;
    QPushButton *pushButtonRankGPA;
    QPushButton *viewAllButton;
    QPushButton *viewAllocatedButton;
    QPushButton *viewUnallocatedBitton;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_9;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_7;
    QComboBox *courseCodeComboBox;
    QLineEdit *courseTitleEdit;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_8;
    QHBoxLayout *horizontalLayout_9;
    QLabel *primaryLabel;
    QLineEdit *primaryLineEdit;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_8;
    QLineEdit *secondaryLineEdit;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_9;
    QLineEdit *productLineEdit;
    QSpacerItem *horizontalSpacer;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QSplitter *splitter;
    QTabWidget *tabWidget;
    QWidget *tabStudent;
    QVBoxLayout *verticalLayout_2;
    QTableView *studentsTableView;
    QWidget *tabProject;
    QVBoxLayout *verticalLayout_4;
    QTableView *projectsTableView;
    QWidget *tabStaff;
    QVBoxLayout *verticalLayout_3;
    QTableView *staffTableView;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuAbout;
    QMenu *menuAbout_2;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ProjectAllocationGUI)
    {
        if (ProjectAllocationGUI->objectName().isEmpty())
            ProjectAllocationGUI->setObjectName(QStringLiteral("ProjectAllocationGUI"));
        ProjectAllocationGUI->resize(1273, 630);
        actionNew = new QAction(ProjectAllocationGUI);
        actionNew->setObjectName(QStringLiteral("actionNew"));
        actionOpen = new QAction(ProjectAllocationGUI);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionSave = new QAction(ProjectAllocationGUI);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionExport = new QAction(ProjectAllocationGUI);
        actionExport->setObjectName(QStringLiteral("actionExport"));
        actionClose = new QAction(ProjectAllocationGUI);
        actionClose->setObjectName(QStringLiteral("actionClose"));
        actionLoad_Student_List = new QAction(ProjectAllocationGUI);
        actionLoad_Student_List->setObjectName(QStringLiteral("actionLoad_Student_List"));
        actionAdd_Project_List = new QAction(ProjectAllocationGUI);
        actionAdd_Project_List->setObjectName(QStringLiteral("actionAdd_Project_List"));
        actionInfo = new QAction(ProjectAllocationGUI);
        actionInfo->setObjectName(QStringLiteral("actionInfo"));
        actionAdd_GPA_List = new QAction(ProjectAllocationGUI);
        actionAdd_GPA_List->setObjectName(QStringLiteral("actionAdd_GPA_List"));
        actionClear_All = new QAction(ProjectAllocationGUI);
        actionClear_All->setObjectName(QStringLiteral("actionClear_All"));
        actionAdd_Student = new QAction(ProjectAllocationGUI);
        actionAdd_Student->setObjectName(QStringLiteral("actionAdd_Student"));
        actionAdd_Project = new QAction(ProjectAllocationGUI);
        actionAdd_Project->setObjectName(QStringLiteral("actionAdd_Project"));
        actionRemove_Student = new QAction(ProjectAllocationGUI);
        actionRemove_Student->setObjectName(QStringLiteral("actionRemove_Student"));
        actionRemove_Project = new QAction(ProjectAllocationGUI);
        actionRemove_Project->setObjectName(QStringLiteral("actionRemove_Project"));
        actionRemove_Staff = new QAction(ProjectAllocationGUI);
        actionRemove_Staff->setObjectName(QStringLiteral("actionRemove_Staff"));
        centralWidget = new QWidget(ProjectAllocationGUI);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout_6 = new QVBoxLayout(centralWidget);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        databaseGroupBox = new QGroupBox(centralWidget);
        databaseGroupBox->setObjectName(QStringLiteral("databaseGroupBox"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(databaseGroupBox->sizePolicy().hasHeightForWidth());
        databaseGroupBox->setSizePolicy(sizePolicy);
        databaseGroupBox->setMinimumSize(QSize(0, 150));
        databaseGroupBox->setMaximumSize(QSize(600, 16777215));
        verticalLayout_5 = new QVBoxLayout(databaseGroupBox);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label = new QLabel(databaseGroupBox);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_2->addWidget(label);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_5);

        studentLineEdit = new QLineEdit(databaseGroupBox);
        studentLineEdit->setObjectName(QStringLiteral("studentLineEdit"));
        studentLineEdit->setMinimumSize(QSize(400, 0));

        horizontalLayout_2->addWidget(studentLineEdit);


        verticalLayout_5->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_2 = new QLabel(databaseGroupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_3->addWidget(label_2);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_6);

        gpsLineEdit = new QLineEdit(databaseGroupBox);
        gpsLineEdit->setObjectName(QStringLiteral("gpsLineEdit"));
        gpsLineEdit->setMinimumSize(QSize(400, 0));

        horizontalLayout_3->addWidget(gpsLineEdit);


        verticalLayout_5->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_3 = new QLabel(databaseGroupBox);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_4->addWidget(label_3);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_7);

        projectLineEdit = new QLineEdit(databaseGroupBox);
        projectLineEdit->setObjectName(QStringLiteral("projectLineEdit"));
        projectLineEdit->setMinimumSize(QSize(400, 0));

        horizontalLayout_4->addWidget(projectLineEdit);


        verticalLayout_5->addLayout(horizontalLayout_4);


        horizontalLayout_6->addWidget(databaseGroupBox);

        assignmentGroupBox = new QGroupBox(centralWidget);
        assignmentGroupBox->setObjectName(QStringLiteral("assignmentGroupBox"));
        sizePolicy.setHeightForWidth(assignmentGroupBox->sizePolicy().hasHeightForWidth());
        assignmentGroupBox->setSizePolicy(sizePolicy);
        assignmentGroupBox->setMinimumSize(QSize(0, 150));
        assignmentGroupBox->setMaximumSize(QSize(200, 16777215));
        verticalLayout = new QVBoxLayout(assignmentGroupBox);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        assigProjectsButton = new QPushButton(assignmentGroupBox);
        assigProjectsButton->setObjectName(QStringLiteral("assigProjectsButton"));

        verticalLayout->addWidget(assigProjectsButton);

        randomAllocationPushButton = new QPushButton(assignmentGroupBox);
        randomAllocationPushButton->setObjectName(QStringLiteral("randomAllocationPushButton"));

        verticalLayout->addWidget(randomAllocationPushButton);

        assignSupervisorsButton = new QPushButton(assignmentGroupBox);
        assignSupervisorsButton->setObjectName(QStringLiteral("assignSupervisorsButton"));

        verticalLayout->addWidget(assignSupervisorsButton);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_4 = new QLabel(assignmentGroupBox);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_5->addWidget(label_4);

        numStudentsLineEdit = new QLineEdit(assignmentGroupBox);
        numStudentsLineEdit->setObjectName(QStringLiteral("numStudentsLineEdit"));
        numStudentsLineEdit->setMaximumSize(QSize(75, 16777215));

        horizontalLayout_5->addWidget(numStudentsLineEdit);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        label_5 = new QLabel(assignmentGroupBox);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_7->addWidget(label_5);

        numProjectsLineEdit = new QLineEdit(assignmentGroupBox);
        numProjectsLineEdit->setObjectName(QStringLiteral("numProjectsLineEdit"));
        numProjectsLineEdit->setMaximumSize(QSize(75, 16777215));

        horizontalLayout_7->addWidget(numProjectsLineEdit);


        verticalLayout->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        label_6 = new QLabel(assignmentGroupBox);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_8->addWidget(label_6);

        numAllocatedLineEdit = new QLineEdit(assignmentGroupBox);
        numAllocatedLineEdit->setObjectName(QStringLiteral("numAllocatedLineEdit"));
        numAllocatedLineEdit->setMaximumSize(QSize(75, 16777215));

        horizontalLayout_8->addWidget(numAllocatedLineEdit);


        verticalLayout->addLayout(horizontalLayout_8);


        horizontalLayout_6->addWidget(assignmentGroupBox);

        filtersGroupBox = new QGroupBox(centralWidget);
        filtersGroupBox->setObjectName(QStringLiteral("filtersGroupBox"));
        verticalLayout_7 = new QVBoxLayout(filtersGroupBox);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        pushButtonRankGPA = new QPushButton(filtersGroupBox);
        pushButtonRankGPA->setObjectName(QStringLiteral("pushButtonRankGPA"));

        verticalLayout_7->addWidget(pushButtonRankGPA);

        viewAllButton = new QPushButton(filtersGroupBox);
        viewAllButton->setObjectName(QStringLiteral("viewAllButton"));

        verticalLayout_7->addWidget(viewAllButton);

        viewAllocatedButton = new QPushButton(filtersGroupBox);
        viewAllocatedButton->setObjectName(QStringLiteral("viewAllocatedButton"));

        verticalLayout_7->addWidget(viewAllocatedButton);

        viewUnallocatedBitton = new QPushButton(filtersGroupBox);
        viewUnallocatedBitton->setObjectName(QStringLiteral("viewUnallocatedBitton"));

        verticalLayout_7->addWidget(viewUnallocatedBitton);


        horizontalLayout_6->addWidget(filtersGroupBox);

        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setMinimumSize(QSize(250, 0));
        groupBox->setMaximumSize(QSize(300, 16777215));
        verticalLayout_9 = new QVBoxLayout(groupBox);
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setContentsMargins(11, 11, 11, 11);
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QStringLiteral("label_7"));

        horizontalLayout_12->addWidget(label_7);

        courseCodeComboBox = new QComboBox(groupBox);
        courseCodeComboBox->setObjectName(QStringLiteral("courseCodeComboBox"));
        courseCodeComboBox->setMinimumSize(QSize(200, 0));

        horizontalLayout_12->addWidget(courseCodeComboBox);


        verticalLayout_9->addLayout(horizontalLayout_12);

        courseTitleEdit = new QLineEdit(groupBox);
        courseTitleEdit->setObjectName(QStringLiteral("courseTitleEdit"));

        verticalLayout_9->addWidget(courseTitleEdit);

        groupBox_2 = new QGroupBox(groupBox);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        verticalLayout_8 = new QVBoxLayout(groupBox_2);
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setContentsMargins(11, 11, 11, 11);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        primaryLabel = new QLabel(groupBox_2);
        primaryLabel->setObjectName(QStringLiteral("primaryLabel"));
        primaryLabel->setMinimumSize(QSize(100, 0));

        horizontalLayout_9->addWidget(primaryLabel);

        primaryLineEdit = new QLineEdit(groupBox_2);
        primaryLineEdit->setObjectName(QStringLiteral("primaryLineEdit"));
        primaryLineEdit->setAlignment(Qt::AlignCenter);

        horizontalLayout_9->addWidget(primaryLineEdit);


        verticalLayout_8->addLayout(horizontalLayout_9);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setMinimumSize(QSize(100, 0));

        horizontalLayout_10->addWidget(label_8);

        secondaryLineEdit = new QLineEdit(groupBox_2);
        secondaryLineEdit->setObjectName(QStringLiteral("secondaryLineEdit"));
        secondaryLineEdit->setAlignment(Qt::AlignCenter);

        horizontalLayout_10->addWidget(secondaryLineEdit);


        verticalLayout_8->addLayout(horizontalLayout_10);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        label_9 = new QLabel(groupBox_2);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setMinimumSize(QSize(100, 0));

        horizontalLayout_11->addWidget(label_9);

        productLineEdit = new QLineEdit(groupBox_2);
        productLineEdit->setObjectName(QStringLiteral("productLineEdit"));
        productLineEdit->setAlignment(Qt::AlignCenter);

        horizontalLayout_11->addWidget(productLineEdit);


        verticalLayout_8->addLayout(horizontalLayout_11);


        verticalLayout_9->addWidget(groupBox_2);


        horizontalLayout_6->addWidget(groupBox);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer);


        verticalLayout_6->addLayout(horizontalLayout_6);

        frame = new QFrame(centralWidget);
        frame->setObjectName(QStringLiteral("frame"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy1);
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frame);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        splitter = new QSplitter(frame);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        tabWidget = new QTabWidget(splitter);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabStudent = new QWidget();
        tabStudent->setObjectName(QStringLiteral("tabStudent"));
        verticalLayout_2 = new QVBoxLayout(tabStudent);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        studentsTableView = new QTableView(tabStudent);
        studentsTableView->setObjectName(QStringLiteral("studentsTableView"));
        studentsTableView->setDragEnabled(true);
        studentsTableView->setAlternatingRowColors(true);
        studentsTableView->setSortingEnabled(true);

        verticalLayout_2->addWidget(studentsTableView);

        tabWidget->addTab(tabStudent, QString());
        tabProject = new QWidget();
        tabProject->setObjectName(QStringLiteral("tabProject"));
        verticalLayout_4 = new QVBoxLayout(tabProject);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        projectsTableView = new QTableView(tabProject);
        projectsTableView->setObjectName(QStringLiteral("projectsTableView"));
        projectsTableView->setSortingEnabled(true);

        verticalLayout_4->addWidget(projectsTableView);

        tabWidget->addTab(tabProject, QString());
        tabStaff = new QWidget();
        tabStaff->setObjectName(QStringLiteral("tabStaff"));
        verticalLayout_3 = new QVBoxLayout(tabStaff);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        staffTableView = new QTableView(tabStaff);
        staffTableView->setObjectName(QStringLiteral("staffTableView"));
        staffTableView->setDragEnabled(true);
        staffTableView->setAlternatingRowColors(true);
        staffTableView->setSortingEnabled(true);

        verticalLayout_3->addWidget(staffTableView);

        tabWidget->addTab(tabStaff, QString());
        splitter->addWidget(tabWidget);

        horizontalLayout->addWidget(splitter);


        verticalLayout_6->addWidget(frame);

        ProjectAllocationGUI->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ProjectAllocationGUI);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1273, 20));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuAbout = new QMenu(menuBar);
        menuAbout->setObjectName(QStringLiteral("menuAbout"));
        menuAbout_2 = new QMenu(menuBar);
        menuAbout_2->setObjectName(QStringLiteral("menuAbout_2"));
        ProjectAllocationGUI->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ProjectAllocationGUI);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        ProjectAllocationGUI->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(ProjectAllocationGUI);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ProjectAllocationGUI->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuAbout->menuAction());
        menuBar->addAction(menuAbout_2->menuAction());
        menuFile->addAction(actionNew);
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave);
        menuFile->addAction(actionExport);
        menuFile->addSeparator();
        menuFile->addAction(actionClose);
        menuAbout->addAction(actionLoad_Student_List);
        menuAbout->addAction(actionAdd_Project_List);
        menuAbout->addAction(actionAdd_GPA_List);
        menuAbout->addSeparator();
        menuAbout->addAction(actionClear_All);
        menuAbout->addSeparator();
        menuAbout->addAction(actionAdd_Student);
        menuAbout->addAction(actionAdd_Project);
        menuAbout->addAction(actionRemove_Student);
        menuAbout->addAction(actionRemove_Project);
        menuAbout->addAction(actionRemove_Staff);
        menuAbout_2->addAction(actionInfo);

        retranslateUi(ProjectAllocationGUI);

        tabWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(ProjectAllocationGUI);
    } // setupUi

    void retranslateUi(QMainWindow *ProjectAllocationGUI)
    {
        ProjectAllocationGUI->setWindowTitle(QApplication::translate("ProjectAllocationGUI", "ProjectAllocationGUI", 0));
        actionNew->setText(QApplication::translate("ProjectAllocationGUI", "New", 0));
        actionOpen->setText(QApplication::translate("ProjectAllocationGUI", "Open", 0));
        actionSave->setText(QApplication::translate("ProjectAllocationGUI", "Save", 0));
        actionExport->setText(QApplication::translate("ProjectAllocationGUI", "Export to CSV", 0));
        actionClose->setText(QApplication::translate("ProjectAllocationGUI", "Close", 0));
        actionLoad_Student_List->setText(QApplication::translate("ProjectAllocationGUI", "Add Student List", 0));
        actionAdd_Project_List->setText(QApplication::translate("ProjectAllocationGUI", "Add Project List", 0));
        actionInfo->setText(QApplication::translate("ProjectAllocationGUI", "Info", 0));
        actionAdd_GPA_List->setText(QApplication::translate("ProjectAllocationGUI", "Add GPA List", 0));
        actionClear_All->setText(QApplication::translate("ProjectAllocationGUI", "Clear All", 0));
        actionAdd_Student->setText(QApplication::translate("ProjectAllocationGUI", "Add Student", 0));
        actionAdd_Project->setText(QApplication::translate("ProjectAllocationGUI", "Add Project", 0));
        actionRemove_Student->setText(QApplication::translate("ProjectAllocationGUI", "Remove Student", 0));
        actionRemove_Project->setText(QApplication::translate("ProjectAllocationGUI", "Remove Project", 0));
        actionRemove_Staff->setText(QApplication::translate("ProjectAllocationGUI", "Remove Staff", 0));
        databaseGroupBox->setTitle(QApplication::translate("ProjectAllocationGUI", "Current Databases", 0));
        label->setText(QApplication::translate("ProjectAllocationGUI", "Student List Database", 0));
        label_2->setText(QApplication::translate("ProjectAllocationGUI", "Student GPS Database", 0));
        label_3->setText(QApplication::translate("ProjectAllocationGUI", "Project List Database", 0));
        assignmentGroupBox->setTitle(QApplication::translate("ProjectAllocationGUI", "Assignment Operations", 0));
        assigProjectsButton->setText(QApplication::translate("ProjectAllocationGUI", "Assign  Projects - GPA", 0));
        randomAllocationPushButton->setText(QApplication::translate("ProjectAllocationGUI", "Assign Projects - Code", 0));
        assignSupervisorsButton->setText(QApplication::translate("ProjectAllocationGUI", "Assign Second Supervisors", 0));
        label_4->setText(QApplication::translate("ProjectAllocationGUI", "# Students", 0));
        label_5->setText(QApplication::translate("ProjectAllocationGUI", "# Projects", 0));
        label_6->setText(QApplication::translate("ProjectAllocationGUI", "# Allocated", 0));
        filtersGroupBox->setTitle(QApplication::translate("ProjectAllocationGUI", "Filters", 0));
        pushButtonRankGPA->setText(QApplication::translate("ProjectAllocationGUI", "Rank by GPA", 0));
        viewAllButton->setText(QApplication::translate("ProjectAllocationGUI", "View All", 0));
        viewAllocatedButton->setText(QApplication::translate("ProjectAllocationGUI", "View Allocated", 0));
        viewUnallocatedBitton->setText(QApplication::translate("ProjectAllocationGUI", "View Unallocated", 0));
        groupBox->setTitle(QApplication::translate("ProjectAllocationGUI", "Data", 0));
        label_7->setText(QApplication::translate("ProjectAllocationGUI", "Course Code", 0));
        courseCodeComboBox->setCurrentText(QString());
        groupBox_2->setTitle(QApplication::translate("ProjectAllocationGUI", "Weightings", 0));
        primaryLabel->setText(QApplication::translate("ProjectAllocationGUI", "Primary", 0));
        primaryLineEdit->setText(QApplication::translate("ProjectAllocationGUI", "1", 0));
        label_8->setText(QApplication::translate("ProjectAllocationGUI", "Secondary", 0));
        secondaryLineEdit->setText(QApplication::translate("ProjectAllocationGUI", "1", 0));
        label_9->setText(QApplication::translate("ProjectAllocationGUI", "Product Design", 0));
        productLineEdit->setText(QApplication::translate("ProjectAllocationGUI", "1", 0));
        tabWidget->setTabText(tabWidget->indexOf(tabStudent), QApplication::translate("ProjectAllocationGUI", "Students", 0));
        tabWidget->setTabText(tabWidget->indexOf(tabProject), QApplication::translate("ProjectAllocationGUI", "Projects", 0));
        tabWidget->setTabText(tabWidget->indexOf(tabStaff), QApplication::translate("ProjectAllocationGUI", "Staff", 0));
        menuFile->setTitle(QApplication::translate("ProjectAllocationGUI", "File", 0));
        menuAbout->setTitle(QApplication::translate("ProjectAllocationGUI", "Edit", 0));
        menuAbout_2->setTitle(QApplication::translate("ProjectAllocationGUI", "About", 0));
    } // retranslateUi

};

namespace Ui {
    class ProjectAllocationGUI: public Ui_ProjectAllocationGUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROJECTALLOCATIONGUI_H
