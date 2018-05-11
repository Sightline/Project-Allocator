#include "projectallocationgui.h"
#include "ui_projectallocationgui.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QDebug>
#include <QMessageBox>
#include <QStringListIterator>
#include <QRegularExpression>
#include <QRegularExpressionMatch>



ProjectAllocationGUI::ProjectAllocationGUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ProjectAllocationGUI)
{
    ui->setupUi(this);
    connect(ui->primaryLineEdit,&QLineEdit::editingFinished,this,&ProjectAllocationGUI::updateTotalLoad);
    connect(ui->secondaryLineEdit,&QLineEdit::editingFinished,this,&ProjectAllocationGUI::updateTotalLoad);
    connect(ui->productLineEdit,&QLineEdit::editingFinished,this,&ProjectAllocationGUI::updateTotalLoad);

    // create objects for the label and progress bar
    statusLabel = new QLabel(this);
    statusProgressBar = new QProgressBar(this);

    // set text for the label
    statusLabel->setText("Status...");
    statusLabel->setMinimumWidth(250);

    // make progress bar text invisible
    statusProgressBar->setTextVisible(false);

    // add the two controls to the status bar
    ui->statusBar->addPermanentWidget(statusLabel);
    ui->statusBar->addPermanentWidget(statusProgressBar,1);

    createModels();

    // Divisions in the School of Engineering
    divisions << "Aerospace Sciences"
              << "Electronic and Nanoscale Engineering"
              << "Infrastructure and Environment"
              << "Systems, Power and Energy"
              << "Biomedical Engineering";

    // Define the running course names
    coursesRunning << "Aerospace Engineering [MSc]"
                   << "Aerospace Engineering & Management [MSc]"
                   << "Biomedical Engineering [MSc]"
                   << "Civil Engineering [MSc]"
                   << "Civil Engineering & Management [MSc]"
                   << "Computer Systems Engineering [MSc]"
                   << "Electronic & Electrical Engineering [MSc]"
                   << "Electronic & Electrical Engineering & Management [MSc]"
                   << "Mechanical Engineering [MSc]"
                   << "Mechanical Engineering & Management [MSc]"
                   << "Mechatronics [MSc]"
                   << "Nanoscience and Nanotechnology [MSc]"
                   << "Sustainable Energy [MSc]";

    // and the course code map
    coursesRunningMap.insert(QString("H400-5200"),coursesRunning[AE]);
    coursesRunningMap.insert(QString("H4N1-5200"),coursesRunning[AEM]);
    coursesRunningMap.insert(QString("H160-5200"),coursesRunning[BE]);
    coursesRunningMap.insert(QString("H200-5200"),coursesRunning[CE]);
    coursesRunningMap.insert(QString("H2N1-5200"),coursesRunning[CEM]);
    coursesRunningMap.insert(QString("HG55-5200"),coursesRunning[CSE]);
    coursesRunningMap.insert(QString("HH56-5200"),coursesRunning[EEE]);
    coursesRunningMap.insert(QString("H6N1-5200"),coursesRunning[EEEM]);
    coursesRunningMap.insert(QString("H300-5200"),coursesRunning[ME]);
    coursesRunningMap.insert(QString("H3N1-5200"),coursesRunning[MEM]);
    coursesRunningMap.insert(QString("H313-5200"),coursesRunning[MECH]);
    coursesRunningMap.insert(QString("H620-5200"),coursesRunning[NN]);
    coursesRunningMap.insert(QString("H213-5200"),coursesRunning[SE]);

    // Finally map MSc programmes to the divisions
    divisionsMap.insertMulti(coursesRunning[AE],divisions[AS]);
    divisionsMap.insertMulti(coursesRunning[AEM],divisions[AS]);
    divisionsMap.insertMulti(coursesRunning[BE],divisions[BENG]);
    divisionsMap.insertMulti(coursesRunning[CE],divisions[IE]);
    divisionsMap.insertMulti(coursesRunning[CEM],divisions[IE]);
    divisionsMap.insertMulti(coursesRunning[CSE],divisions[ENE]);
    divisionsMap.insertMulti(coursesRunning[EEE],divisions[ENE]);
    divisionsMap.insertMulti(coursesRunning[EEEM],divisions[ENE]);
    divisionsMap.insertMulti(coursesRunning[ME],divisions[SPE]);
    divisionsMap.insertMulti(coursesRunning[ME],divisions[BENG]);
    divisionsMap.insertMulti(coursesRunning[MEM],divisions[SPE]);
    divisionsMap.insertMulti(coursesRunning[MECH],divisions[SPE]);
    divisionsMap.insertMulti(coursesRunning[NN],divisions[ENE]);
    divisionsMap.insertMulti(coursesRunning[SE],divisions[ENE]);
    divisionsMap.insertMulti(coursesRunning[SE],divisions[SPE]);
    divisionsMap.insertMulti(coursesRunning[SE],divisions[IE]);
    divisionsMap.insertMulti(coursesRunning[SE],divisions[BENG]);

    coursesModel = new QStandardItemModel(0,1);
    QList<QStandardItem*> items;
    items << new QStandardItem(QString("H400-5200"));
    items << new QStandardItem(QString("H4N1-5200"));
    items << new QStandardItem(QString("H160-5200"));
    items << new QStandardItem(QString("H200-5200"));
    items << new QStandardItem(QString("H2N1-5200"));
    items << new QStandardItem(QString("HG55-5200"));
    items << new QStandardItem(QString("HH56-5200"));
    items << new QStandardItem(QString("H6N1-5200"));
    items << new QStandardItem(QString("H300-5200"));
    items << new QStandardItem(QString("H3N1-5200"));
    items << new QStandardItem(QString("H313-5200"));
    items << new QStandardItem(QString("H620-5200"));
    items << new QStandardItem(QString("H213-5200"));
    for(int ic = 0; ic<items.count();ic++)
    {
        coursesModel->appendRow(items[ic]);
    }

    ui->courseCodeComboBox->setModel(coursesModel);

    // Load in the list of eligible staff
    loadEligibleStaff();
}

ProjectAllocationGUI::~ProjectAllocationGUI()
{
    delete ui;
}


void ProjectAllocationGUI::allocateProjects()
{
    // The logic behind project allocation is that students
    // with a higher GPA should have the most chance of getting the
    // project they want.

    // Ensure that the studentModel is sorted by GPA
    studentModel->sort(GPA,Qt::DescendingOrder);

    // Use a regular expression to filter the text.
    QRegularExpression re("[^a-z^A-z^0-9](Confidential)*",QRegularExpression::CaseInsensitiveOption);

    // We need to populate a local hash table with the titles filtered
    // by the regular expression above. This is to ensure comparison
    // can be achieved even in the presence of some local differences
    // between the project name .xlsx file and the student choice .xlsx file.
    int numProjects = projectModel->rowCount();
    for(int project = 0; project < numProjects; project++)
    {
        // Check if the project has been allocated
        QModelIndex index = projectModel->index(project,2);
        QVariant selected = projectModel->data(index);
        if(QString("No student allocated").compare(selected.toString()))
        {
            continue;
        }
        index = projectModel->index(project,TITLE);
        QVariant titleV = projectModel->data(index);
        QString title = titleV.toString();
        title.replace(re,"");
        QList<QStandardItem*> list;
        QStandardItem *titleItem = new QStandardItem(title);
        QStandardItem *fullTitle = new QStandardItem(titleV.toString());
        list << titleItem << fullTitle;
        projectTitleModel->appendRow(list);
    }

    // Loop over all students in the model
    int ii = 0;
    statusLabel->setText("Allocating GPA Supervisors....");
    statusProgressBar->setMaximum(studentModel->rowCount());
    while(ii < studentModel->rowCount())
    {
        statusProgressBar->setValue(ii);
        // Try to assign each students their top choice. Working through
        // the studentModel, first entry will have the top GPA and so on
        // down.
        // First check if the student has already been manually allocated
        QModelIndex index = studentModel->index(ii,CHOICEALLOCATED);
        QVariant choiceV = studentModel->data(index);
        int choice = choiceV.toInt();
        if(choice != 0)
        {
            // Break out and continue on to the next student
            ii++;
            continue;
        }
        // First, get the student choices from the model
        index = studentModel->index(ii,FIRST);
        QVariant firstChoiceV = studentModel->data(index);
        QString firstChoice = firstChoiceV.toString();
        index = studentModel->index(ii,SECOND);
        QVariant secondChoiceV = studentModel->data(index);
        QString secondChoice = secondChoiceV.toString();
        index = studentModel->index(ii,THIRD);
        QVariant thirdChoiceV = studentModel->data(index);
        QString thirdChoice = thirdChoiceV.toString();
        index = studentModel->index(ii,FOURTH);
        QVariant fourthChoiceV = studentModel->data(index);
        QString fourthChoice = fourthChoiceV.toString();
        index = studentModel->index(ii,FIFTH);
        QVariant fifthChoiceV = studentModel->data(index);
        QString fifthChoice = fifthChoiceV.toString();
        // Filter to take out everything but the letters.
        firstChoice.replace(re,"");
        secondChoice.replace(re,"");
        thirdChoice.replace(re,"");
        fourthChoice.replace(re,"");
        fifthChoice.replace(re,"");
        // Now allocate
        QList<QStandardItem*> titleList = projectTitleModel->findItems(firstChoice);
        if(!titleList.isEmpty())
        {
            // Get the full title string
            index = projectTitleModel->indexFromItem(titleList[0]);
            int projectTitleRow = index.row();
            index = projectTitleModel->index(projectTitleRow,1);
            QVariant fullTitle = projectTitleModel->data(index);
            //Update student model data
            index = studentModel->index(ii,ALLOCATEDPROJECT);
            studentModel->setData(index,fullTitle.toString());
            index = studentModel->index(ii,CHOICEALLOCATED);
            studentModel->setData(index,QString::number(1));
            // Now update the project model
            QList<QStandardItem*> item = projectModel->findItems(fullTitle.toString());
            // Multiplicity is implemented by having several instances of the same project.
            // To ensure the student is allocated to the correct instance, we need to
            // go through the list and check if a studnent has already been allocated to
            // that instance.
            int instance = 0;
            foreach(QStandardItem* i, item)
            {
                // Get the student allocated
                index = projectModel->indexFromItem(i);
                int projectRow = index.row();
                index = projectModel->index(projectRow,STUDENTALLOCATED);
                QVariant currentAllocation = projectModel->data(index);
                if(!(currentAllocation.toString() == QString("No student allocated")))
                {
                    instance++;
                }
            }
            index = projectModel->indexFromItem(item[instance]);
            int projectRow = index.row();
            index = projectModel->index(projectRow,STUDENTALLOCATED);
            QModelIndex studInd = studentModel->index(ii,MATRIC);
            projectModel->setData(index,studentModel->data(studInd));
            index = projectModel->index(projectRow,STAFFMEMBER);
            studInd = studentModel->index(ii,SUPERVISOR);
            studentModel->setData(studInd,projectModel->data(index));
            // Update the staffModel data
            index = projectModel->index(projectRow,STAFFMEMBER);
            QVariant staffName = projectModel->data(index);
            item.clear();
            item = staffModel->findItems(staffName.toString());
            index = staffModel->indexFromItem(item[0]);
            int staffRow = index.row();
            index = staffModel->index(staffRow,NUMPROJECTSALLOCATED);
            QVariant npv = staffModel->data(index);
            int np = npv.toInt();
            np += 1;
            staffModel->setData(index,np);
//            updateStaffLoad(staffRow);
            // Remove project from model
            projectTitleModel->removeRow(projectTitleRow);
            ii++;
            continue;
        }
        titleList.clear();
        titleList = projectTitleModel->findItems(secondChoice);
        if(!titleList.isEmpty())
        {
            // Get the full title string
            index = projectTitleModel->indexFromItem(titleList[0]);
            int projectTitleRow = index.row();
            index = projectTitleModel->index(projectTitleRow,1);
            QVariant fullTitle = projectTitleModel->data(index);
            //Update student model data
            index = studentModel->index(ii,ALLOCATEDPROJECT);
            studentModel->setData(index,fullTitle.toString());
            index = studentModel->index(ii,CHOICEALLOCATED);
            studentModel->setData(index,QString::number(2));
            // Now update the project model
            QList<QStandardItem*> item = projectModel->findItems(fullTitle.toString());
            int instance = 0;
            foreach(QStandardItem* i, item)
            {
                // Get the student allocated
                index = projectModel->indexFromItem(i);
                int projectRow = index.row();
                index = projectModel->index(projectRow,STUDENTALLOCATED);
                QVariant currentAllocation = projectModel->data(index);
                if(!(currentAllocation.toString() == QString("No student allocated")))
                {
                    instance++;
                }
            }
            index = projectModel->indexFromItem(item[instance]);
            int projectRow = index.row();
            index = projectModel->index(projectRow,STUDENTALLOCATED);
            QModelIndex studInd = studentModel->index(ii,MATRIC);
            projectModel->setData(index,studentModel->data(studInd));
            index = projectModel->index(projectRow,STAFFMEMBER);
            studInd = studentModel->index(ii,SUPERVISOR);
            studentModel->setData(studInd,projectModel->data(index));
            // Update the staffModel data
            index = projectModel->index(projectRow,STAFFMEMBER);
            QVariant staffName = projectModel->data(index);
            item.clear();
            item = staffModel->findItems(staffName.toString());
            index = staffModel->indexFromItem(item[0]);
            int staffRow = index.row();
            index = staffModel->index(staffRow,NUMPROJECTSALLOCATED);
            QVariant npv = staffModel->data(index);
            int np = npv.toInt();
            np += 1;
            staffModel->setData(index,np);
//            updateStaffLoad(staffRow);
            // Remove project from model
            projectTitleModel->removeRow(projectTitleRow);
            ii++;
            continue;
        }
        titleList.clear();
        titleList = projectTitleModel->findItems(thirdChoice);
        if(!titleList.isEmpty())
        {
            // Get the full title string
            index = projectTitleModel->indexFromItem(titleList[0]);
            int projectTitleRow = index.row();
            index = projectTitleModel->index(projectTitleRow,1);
            QVariant fullTitle = projectTitleModel->data(index);
            //Update student model data
            index = studentModel->index(ii,ALLOCATEDPROJECT);
            studentModel->setData(index,fullTitle.toString());
            index = studentModel->index(ii,CHOICEALLOCATED);
            studentModel->setData(index,QString::number(3));
            // Now update the project model
            QList<QStandardItem*> item = projectModel->findItems(fullTitle.toString());
            int instance = 0;
            foreach(QStandardItem* i, item)
            {
                // Get the student allocated
                index = projectModel->indexFromItem(i);
                int projectRow = index.row();
                index = projectModel->index(projectRow,STUDENTALLOCATED);
                QVariant currentAllocation = projectModel->data(index);
                if(!(currentAllocation.toString() == QString("No student allocated")))
                {
                    instance++;
                }
            }
            index = projectModel->indexFromItem(item[instance]);
            int projectRow = index.row();
            index = projectModel->index(projectRow,STUDENTALLOCATED);
            QModelIndex studInd = studentModel->index(ii,MATRIC);
            projectModel->setData(index,studentModel->data(studInd));
            index = projectModel->index(projectRow,STAFFMEMBER);
            studInd = studentModel->index(ii,SUPERVISOR);
            studentModel->setData(studInd,projectModel->data(index));
            // Update the staffModel data
            index = projectModel->index(projectRow,STAFFMEMBER);
            QVariant staffName = projectModel->data(index);
            item.clear();
            item = staffModel->findItems(staffName.toString());
            index = staffModel->indexFromItem(item[0]);
            int staffRow = index.row();
            index = staffModel->index(staffRow,NUMPROJECTSALLOCATED);
            QVariant npv = staffModel->data(index);
            int np = npv.toInt();
            np += 1;
            staffModel->setData(index,np);
//            updateStaffLoad(staffRow);
            // Remove project from model
            projectTitleModel->removeRow(projectTitleRow);
            ii++;
            continue;
        }
        titleList.clear();
        titleList = projectTitleModel->findItems(fourthChoice);
        if(!titleList.isEmpty())
        {
            // Get the full title string
            index = projectTitleModel->indexFromItem(titleList[0]);
            int projectTitleRow = index.row();
            index = projectTitleModel->index(projectTitleRow,1);
            QVariant fullTitle = projectTitleModel->data(index);
            //Update student model data
            index = studentModel->index(ii,ALLOCATEDPROJECT);
            studentModel->setData(index,fullTitle.toString());
            index = studentModel->index(ii,CHOICEALLOCATED);
            studentModel->setData(index,QString::number(4));
            // Now update the project model
            QList<QStandardItem*> item = projectModel->findItems(fullTitle.toString());
            int instance = 0;
            foreach(QStandardItem* i, item)
            {
                // Get the student allocated
                index = projectModel->indexFromItem(i);
                int projectRow = index.row();
                index = projectModel->index(projectRow,STUDENTALLOCATED);
                QVariant currentAllocation = projectModel->data(index);
                if(!(currentAllocation.toString() == QString("No student allocated")))
                {
                    instance++;
                }
            }
            index = projectModel->indexFromItem(item[instance]);
            int projectRow = index.row();
            index = projectModel->index(projectRow,STUDENTALLOCATED);
            QModelIndex studInd = studentModel->index(ii,MATRIC);
            projectModel->setData(index,studentModel->data(studInd));
            index = projectModel->index(projectRow,STAFFMEMBER);
            studInd = studentModel->index(ii,SUPERVISOR);
            studentModel->setData(studInd,projectModel->data(index));
            // Update the staffModel data
            index = projectModel->index(projectRow,STAFFMEMBER);
            QVariant staffName = projectModel->data(index);
            item.clear();
            item = staffModel->findItems(staffName.toString());
            index = staffModel->indexFromItem(item[0]);
            int staffRow = index.row();
            index = staffModel->index(staffRow,NUMPROJECTSALLOCATED);
            QVariant npv = staffModel->data(index);
            int np = npv.toInt();
            np += 1;
            staffModel->setData(index,np);
//            updateStaffLoad(staffRow);
            // Remove project from model
            projectTitleModel->removeRow(projectTitleRow);
            ii++;
            continue;
        }
        titleList.clear();
        titleList = projectTitleModel->findItems(fifthChoice);
        if(!titleList.isEmpty())
        {
            // Get the full title string
            index = projectTitleModel->indexFromItem(titleList[0]);
            int projectTitleRow = index.row();
            index = projectTitleModel->index(projectTitleRow,1);
            QVariant fullTitle = projectTitleModel->data(index);
            //Update student model data
            index = studentModel->index(ii,ALLOCATEDPROJECT);
            studentModel->setData(index,fullTitle.toString());
            index = studentModel->index(ii,CHOICEALLOCATED);
            studentModel->setData(index,QString::number(5));
            // Now update the project model
            QList<QStandardItem*> item = projectModel->findItems(fullTitle.toString());
            int instance = 0;
            foreach(QStandardItem* i, item)
            {
                // Get the student allocated
                index = projectModel->indexFromItem(i);
                int projectRow = index.row();
                index = projectModel->index(projectRow,STUDENTALLOCATED);
                QVariant currentAllocation = projectModel->data(index);
                if(!(currentAllocation.toString() == QString("No student allocated")))
                {
                    instance++;
                }
            }
            index = projectModel->indexFromItem(item[instance]);
            int projectRow = index.row();
            index = projectModel->index(projectRow,STUDENTALLOCATED);
            QModelIndex studInd = studentModel->index(ii,MATRIC);
            projectModel->setData(index,studentModel->data(studInd));
            index = projectModel->index(projectRow,STAFFMEMBER);
            studInd = studentModel->index(ii,SUPERVISOR);
            studentModel->setData(studInd,projectModel->data(index));
            // Update the staffModel data
            index = projectModel->index(projectRow,STAFFMEMBER);
            QVariant staffName = projectModel->data(index);
            item.clear();
            item = staffModel->findItems(staffName.toString());
            index = staffModel->indexFromItem(item[0]);
            int staffRow = index.row();
            index = staffModel->index(staffRow,NUMPROJECTSALLOCATED);
            QVariant npv = staffModel->data(index);
            int np = npv.toInt();
            np += 1;
            staffModel->setData(index,np);
//            updateStaffLoad(staffRow);
            // Remove project from model
            projectTitleModel->removeRow(projectTitleRow);
            ii++;
            continue;
        }
        ii++;
        continue;
    }
    // Update the UI
    int count =0;
    QModelIndex index;
    for(int iter=0; iter < studentModel->rowCount();iter++)
    {
        index = studentModel->index(iter,CHOICEALLOCATED);
        QVariant choice = studentModel->data(index);
        if(choice.toInt() != 0)
        {
            count++;
        }
    }
    ui->numAllocatedLineEdit->setText(QString::number(count));
    ui->studentsTableView->setModel(studentModel);
    ui->projectsTableView->setModel(projectModel);
    statusLabel->setText("Status...");
    statusProgressBar->setValue(0);
    updateTotalLoad();
}


void ProjectAllocationGUI::loadStudentList()
{
    // Open File for reading
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Student List"), "./", tr("CSV Files (*.csv)"));
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Couldn't open file";
        int ret = QMessageBox::warning(this,tr("File Issue"),
                    tr("The student list database file could not be opened. Do you wish to try again?"),
                    QMessageBox::Cancel,QMessageBox::Open);
        switch(ret){
        case QMessageBox::Cancel:
            break;
        case QMessageBox::Open:
            loadStudentList();
        }

        return;
    }

    QTextStream in(&file);
    int counter = 0;
    while (!in.atEnd()) {
        QString line = in.readLine();
        if(counter > 0)
        {
            processStudentLineModel(line);
        }
        counter++;
    }

    // Now add the GPA data
    if(!loadStudentGPAList())
    {
        return;
    }

    // Sort the student model in increasing GPA
    studentModel->sort(4,Qt::DescendingOrder);

    // Update the UI
    ui->studentLineEdit->setText(fileName);
    ui->numStudentsLineEdit->setText(QString::number(studentModel->rowCount()));
}

void ProjectAllocationGUI::createModels()
{
    // Set-up the models
    // Student Model
    studentModel = new QStandardItemModel(0,14);
    studentModel->setHorizontalHeaderItem(0,new QStandardItem("Matric #"));
    studentModel->setHorizontalHeaderItem(1,new QStandardItem("Surname"));
    studentModel->setHorizontalHeaderItem(2,new QStandardItem("First Name(s)"));
    studentModel->setHorizontalHeaderItem(3,new QStandardItem("Course"));
    studentModel->setHorizontalHeaderItem(4,new QStandardItem("GPA"));
    studentModel->setHorizontalHeaderItem(5,new QStandardItem("Allocated Project"));
    studentModel->setHorizontalHeaderItem(6,new QStandardItem("Supervisor"));
    studentModel->setHorizontalHeaderItem(7,new QStandardItem("Second Supervisor"));
    studentModel->setHorizontalHeaderItem(8,new QStandardItem("Choice Allocated"));
    studentModel->setHorizontalHeaderItem(9,new QStandardItem("First Choice"));
    studentModel->setHorizontalHeaderItem(10,new QStandardItem("Second Choice"));
    studentModel->setHorizontalHeaderItem(11,new QStandardItem("Third Choice"));
    studentModel->setHorizontalHeaderItem(12,new QStandardItem("Fourth Choice"));
    studentModel->setHorizontalHeaderItem(13,new QStandardItem("Fifth Choice"));
    ui->studentsTableView->setModel(studentModel);
    ui->studentsTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->studentsTableView->horizontalHeader()->setSectionResizeMode(5,QHeaderView::Interactive);
    ui->studentsTableView->horizontalHeader()->setSectionResizeMode(8,QHeaderView::Interactive);
    ui->studentsTableView->horizontalHeader()->setSectionResizeMode(9,QHeaderView::Interactive);
    ui->studentsTableView->horizontalHeader()->setSectionResizeMode(10,QHeaderView::Interactive);
    ui->studentsTableView->horizontalHeader()->setSectionResizeMode(11,QHeaderView::Interactive);
    ui->studentsTableView->horizontalHeader()->setSectionResizeMode(12,QHeaderView::Interactive);
    ui->studentsTableView->horizontalHeader()->setSectionsMovable(true);

    // Project model
    projectModel = new QStandardItemModel(0,4);
    projectModel->setHorizontalHeaderItem(0,new QStandardItem("Title"));
    projectModel->setHorizontalHeaderItem(1,new QStandardItem("Staff Member"));
    projectModel->setHorizontalHeaderItem(2,new QStandardItem("Student Allocated"));
    projectModel->setHorizontalHeaderItem(3,new QStandardItem("Applicable Courses"));
    ui->projectsTableView->setModel(projectModel);
    ui->projectsTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->projectsTableView->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Interactive);
    ui->projectsTableView->horizontalHeader()->setSectionsMovable(true);

    // Project title model
    projectTitleModel = new QStandardItemModel(0,2);

    // Staff model
    staffModel = new QStandardItemModel(0,6);
    staffModel->setHorizontalHeaderItem(0,new QStandardItem("Name"));
    staffModel->setHorizontalHeaderItem(1,new QStandardItem("# Projects Offered"));
    staffModel->setHorizontalHeaderItem(2,new QStandardItem("# Projects Allocated"));
    staffModel->setHorizontalHeaderItem(3,new QStandardItem("Division"));
    staffModel->setHorizontalHeaderItem(4,new QStandardItem("# Second Supervisor"));
    staffModel->setHorizontalHeaderItem(5,new QStandardItem("# PD Supervisor"));
    staffModel->setHorizontalHeaderItem(6,new QStandardItem("Total Load"));
    ui->staffTableView->setModel(staffModel);
    ui->staffTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->staffTableView->horizontalHeader()->setSectionsMovable(true);
}


void ProjectAllocationGUI::loadProjectList()
{
    // Get filename from GUI.
    // Open File for reading
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Project List"), "./", tr("CSV Files (*.csv)"));
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Couldn't open file";
        int ret = QMessageBox::warning(this,tr("File Issue"),
                    tr("The project list database file could not be opened. Do you wish to try again?"),
                    QMessageBox::Cancel,QMessageBox::Open);
        switch(ret){
        case QMessageBox::Cancel:
            break;
        case QMessageBox::Open:
            loadProjectList();
        }
        return;
    }

    QTextStream in(&file);
    int counter = 0;
    while (!in.atEnd()) {
        QString line = in.readLine();
        if(counter > 0)
        {
            processProjectLineModel(line);
        }
        counter++;
    }

    // Update the UI
    ui->projectLineEdit->setText(fileName);
    ui->numProjectsLineEdit->setText(QString::number(projectModel->rowCount()));
    updateTotalLoad();
}

void ProjectAllocationGUI::loadEligibleStaff()
{
    // Open File for reading
    QFile file(QString("EligibleStaff.csv"));
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Couldn't open file";
        int ret = QMessageBox::warning(this,tr("File Issue"),
                    tr("The eligible staff list database file could not be opened. Do you wish to try again?"),
                    QMessageBox::Cancel,QMessageBox::Open);
        switch(ret){
        case QMessageBox::Cancel:
            break;
        case QMessageBox::Open:
            loadEligibleStaff();
        }
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        processEligibleStaffLineModel(line);
    }
}


int ProjectAllocationGUI::loadStudentGPAList()
{
    int ret = QMessageBox::warning(this,tr("GPA Required..."),
                         tr("To perform project allocation, a student GPA list must be supplied. "
                            "Do you wish to load one at this time?"),QMessageBox::Ok | QMessageBox::Cancel);
    switch (ret)
    {
        case QMessageBox::Cancel:
        {
            // Abort
            return 0;
        }
        case QMessageBox::Ok:
        {
            // Open File for reading
            QString fileName = QFileDialog::getOpenFileName(this,
                tr("Open Student GPA file"), "./", tr("CSV Files (*.csv)"));
            QFile file(fileName);
            if (!file.open(QIODevice::ReadOnly))
            {
                qDebug() << "Couldn't open file";
                int ret = QMessageBox::warning(this,tr("File Issue"),
                            tr("The student GPA list database file could not be opened. Do you wish to try again?"),
                            QMessageBox::Cancel,QMessageBox::Open);
                switch(ret){
                case QMessageBox::Cancel:
                    break;
                case QMessageBox::Open:
                    loadStudentGPAList();
                }
                return 0;
            }

            QTextStream in(&file);
            int count = 0;
            while (!in.atEnd()) {
                QString line = in.readLine();
                processStudentGPALineModel(line);
                count++;
            }
            // Update the UI
            ui->gpsLineEdit->setText(fileName);
            return 1;
        }
    }
    return 0;
}


void ProjectAllocationGUI::processStudentLineModel(QString line)
{
    QStringList list;
    list = line.split(',');
    // Create a studentModel row
    QStandardItem *matric = new QStandardItem(QString::number(list[0].toInt()));
    // Check if this matric number os already listed in the model
    QList<QStandardItem*> items = studentModel->findItems(QString::number(list[0].toInt()));
    if(!items.isEmpty())
    {
        return;
    }
    QStandardItem *family = new QStandardItem(list[1]);
    QStandardItem *first = new QStandardItem(list[2]);
    QStandardItem *code = new QStandardItem(list[3]);
    code->setTextAlignment(Qt::AlignCenter);
    QStandardItem *GPA = new QStandardItem(QString("10.0"));
    GPA->setTextAlignment(Qt::AlignCenter);
    QStandardItem *allocated = new QStandardItem(QString("..No project allocated"));
    QStandardItem *staff = new QStandardItem(QString("..No Supervisor Assigned"));
    QStandardItem *secondStaff = new QStandardItem(QString("..No Supervisor Assigned"));
    QStandardItem *choice = new QStandardItem(QString::number(0));
    choice->setTextAlignment(Qt::AlignCenter);
    QStandardItem *firstChoice = new QStandardItem(list[4]);
    QStandardItem *second = new QStandardItem(list[5]);
    QStandardItem *third = new QStandardItem(list[6]);
    QStandardItem *fourth = new QStandardItem(list[7]);
    QStandardItem *fifth = new QStandardItem(list[8]);

    // Allocate to model
    QList<QStandardItem*> rowData;
    rowData << matric << family << first << code << GPA << allocated << staff
            << secondStaff << choice << firstChoice << second << third
            << fourth << fifth;
    studentModel->appendRow(rowData);
}

void ProjectAllocationGUI::processProjectLineModel(QString line)
{
    QStringList list;
    QStringList staffList;
    QStringList courseList;
    list = line.split(',');
    staffList = list[1].split(' ');
    courseList = list[4].split('|');
    QStringList tmp;
    foreach(QString course, courseList)
    {
        foreach(QString running,coursesRunning)
        {
            if(course == running)
            {
                tmp.append(course);
            }
        }
    }

    // Create a projectModel row
    QStandardItem *title = new QStandardItem(list[0]);
    QStandardItem *staff = new QStandardItem(QString(staffList[1] + " " + staffList[2]));
    QStandardItem *allocatedStudent = new QStandardItem(QString("No student allocated"));
    // Allocate to model
    QList<QStandardItem*> rowData;
    rowData << title << staff << allocatedStudent;
    QStringList courses = tmp;
    foreach(QString course, courses)
    {
        QStandardItem *courseItm = new QStandardItem(course);
        rowData << courseItm;
    }
    projectModel->appendRow(rowData);

    // Create or update a staffModel row
    QString firstName = staffList[1];
    QString secondName = staffList[2];
    // Use a regular expression to filter the text.
    QRegularExpression re("[^a-z^A-z^0-9^-](Dr|Professor|Mr|Mrs)*");
    firstName.replace(re,"");
    secondName.replace(re,"");
    QString staffName = QString(firstName + " " + secondName);
    // Check if this staff member has already been added to the staffModel
    QList<QStandardItem*> item = staffModel->findItems(staffName);
    if(item.isEmpty())
    {
        QStandardItem *name = new QStandardItem(staffName);
        QStandardItem *numP = new QStandardItem(QString::number(1));
        numP->setTextAlignment(Qt::AlignCenter);
        QStandardItem *numA = new QStandardItem(QString::number(0));
        numA->setTextAlignment(Qt::AlignCenter);
        QStandardItem *division = new QStandardItem(QString(""));
        QStandardItem *secondSup = new QStandardItem(QString::number(0));
        secondSup->setTextAlignment(Qt::AlignCenter);
        QStandardItem *supPD = new QStandardItem(QString::number(0));
        supPD->setTextAlignment(Qt::AlignCenter);
        QStandardItem *totalLoad = new QStandardItem(QString::number(0));
        totalLoad->setTextAlignment(Qt::AlignCenter);
        rowData.clear();
        rowData << name << numP << numA << division << secondSup << supPD << totalLoad;
        staffModel->appendRow(rowData);
    }
    else
    {
        QModelIndex index = staffModel->indexFromItem(item[0]);
        int staffRow = index.row();
        index = staffModel->index(staffRow,NUMPROJECTSOFFERED);
        QVariant npv = staffModel->data(index);
        int np = npv.toInt();
        np += 1;
        staffModel->setData(index,np);
    }
}

void ProjectAllocationGUI::processStudentGPALineModel(QString line)
{
    QStringList list;
    list = line.split(',');
    QStringList secondList;
    secondList = list[0].split(' ');
    int matricNumber = secondList[0].mid(1,7).toInt();
    float GPA = list[2].toFloat();
    if(GPA == 0.0f)
        GPA = 10.0f;

    QList<QStandardItem*> items = studentModel->findItems(QString::number(matricNumber));
    if(items.isEmpty())
    {
        qDebug() << "Ommited student (from model) - " << list;
    }
    else
    {
        QString str;
        str.sprintf("%04.1f",GPA);
        QModelIndex matricIndex = studentModel->indexFromItem(items[0]);
        int row = matricIndex.row();
        QModelIndex index = studentModel->index(row,4);
        studentModel->setData(index,str);
    }
}

void ProjectAllocationGUI::processEligibleStaffLineModel(QString line)
{
    QStringList list;
    list = line.split(',');
    QString firstName = list[1];
    QString secondName = list[0];
    QString divisionName = list[2];
    // Use a regular expression to filter the text.
    QRegularExpression re("[^a-z^A-z^0-9^-](Dr|Professor|Mr|Mrs)*");
    firstName.replace(re,"");
    secondName.replace(re,"");

    // Create or update a staffModel row
    QList<QStandardItem*> rowData;
    QString staffName = QString(firstName + " " + secondName);
    // Check if this staff member has already been added to the staffModel
    QList<QStandardItem*> item = staffModel->findItems(staffName);
    if(item.isEmpty())
    {
        QStandardItem *name = new QStandardItem(staffName);
        QStandardItem *numP = new QStandardItem(QString::number(0));
        numP->setTextAlignment(Qt::AlignCenter);
        QStandardItem *numA = new QStandardItem(QString::number(0));
        numA->setTextAlignment(Qt::AlignCenter);
        QStandardItem *division = new QStandardItem(divisionName);
        QStandardItem *secondSup = new QStandardItem(QString::number(0));
        secondSup->setTextAlignment(Qt::AlignCenter);
        QStandardItem *supPD = new QStandardItem(QString::number(0));
        supPD->setTextAlignment(Qt::AlignCenter);
        QStandardItem *totalLoad = new QStandardItem(QString::number(0));
        totalLoad->setTextAlignment(Qt::AlignCenter);
        rowData.clear();
        rowData << name << numP << numA << division << secondSup << supPD << totalLoad;
        staffModel->appendRow(rowData);
    }
    else
    {
        QModelIndex index = staffModel->indexFromItem(item[0]);
        int staffRow = index.row();
        index = staffModel->index(staffRow,DIVISION);
        QVariant npv = QVariant(divisionName);
        staffModel->setData(index,npv);
    }
}

bool ProjectAllocationGUI::checkManualAllocation(int row)
{
    // Check if project has been manually allocated (choice = 7)
    QModelIndex index = studentModel->index(row,CHOICEALLOCATED);
    QVariant choice = studentModel->data(index);
    if(choice.toInt() == 7)
    {
        QModelIndex index2 = studentModel->index(row,MATRIC);
        QVariant matric = studentModel->data(index2);
        qDebug() << "Manual allocation on " << matric.toString();
        return true;
    }
    return false;
}

Student *ProjectAllocationGUI::maxGPA(QList<Student *> students)
{
    // Find the student with the maximum GPA
    Student *student;
    QListIterator<Student*> iter(students);
    iter.toFront();
    int maxGPA = 0;
    while(iter.hasNext())
    {
        if(iter.peekNext()->getGPA() >= maxGPA)
        {
            maxGPA = iter.peekNext()->getGPA();
            student = iter.next();
        }
        else
        {
            iter.next();
        }
    }
    return student;
}


void ProjectAllocationGUI::saveAllocation()
{
    // Open File for reading
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Export Student Allocation"), "./", tr("CSV Files (*.csv)"));
    QFile studentFile(fileName);
    if (!studentFile.open(QIODevice::WriteOnly))
    {
        qDebug() << "Couldn't open file";
        int ret = QMessageBox::warning(this,tr("File Issue"),
                    tr("The student allocation list database file could not be opened. Do you wish to try again?"),
                    QMessageBox::Cancel,QMessageBox::Open);
        switch(ret){
        case QMessageBox::Cancel:
            break;
        case QMessageBox::Open:
            saveAllocation();
        }
        return;
    }

    // Write to file
    QTextStream outStudent(&studentFile);
    outStudent << "Matric#" << "," << "Family name" << "," << "First name" << ","
               << "Plan Code" << ","
               << "Allocated project" << "," << "Supervisor" << ","
               << "Second Supervisor" << "," << "Choice Allocated" << "\n";
    // Model-based data
    for(int row = 0; row < studentModel->rowCount();row++)
    {
        for(int col=0; col < 9;col++)
        {
            if(col == GPA) continue;
            QStandardItem *item = studentModel->item(row,col);
            outStudent << item->text() << ",";
        }
        outStudent << "\n";
    }
}

void ProjectAllocationGUI::saveStaffData()
{
    // Open File for writing
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Export Staff Loading"), "./", tr("CSV Files (*.csv)"));
    QFile staffFile(fileName);
    if (!staffFile.open(QIODevice::WriteOnly))
    {
        qDebug() << "Couldn't open file";
        int ret = QMessageBox::warning(this,tr("File Issue"),
                    tr("The staff loading database file could not be opened. Do you wish to try again?"),
                    QMessageBox::Cancel,QMessageBox::Open);
        switch(ret){
        case QMessageBox::Cancel:
            break;
        case QMessageBox::Open:
            saveStaffData();
        }
        return;
    }

    // Write to file
    QTextStream outStaff(&staffFile);
    outStaff << "Name" << "," << "# Projects Offered" << "," << "# Projects Allocated" << ","
               << "Division" << ","
               << "# Second Supervisor" << "," << "# PD Supervisor" << ","
               << "Total Load" << "\n";
    for(int row = 0; row < staffModel->rowCount();row++)
    {
        for(int col=0; col < staffModel->columnCount();col++)
        {
            QStandardItem *item = staffModel->item(row,col);
            if(item)
            {
                outStaff << item->text() << ",";
            }
            else
            {
                QStandardItem *emptyItem = new QStandardItem(QString(" "));
                outStaff << emptyItem->text() << ",";
            }

        }
        outStaff << "\n";
    }
}


void ProjectAllocationGUI::displayProjectData()
{
    // Display data
    QListIterator<Project*> iter(projectList);
    iter.toFront();
    while(iter.hasNext())
    {
        Project *project = iter.next();
        if(project->getProjectAssigned())
        {
            qDebug() << project->getProjectTitle() << "\t"
                 << project->getAllocatedStudent()->getFamilyName() << " "
                 << project->getAllocatedStudent()->getFirstName();
        }
        else
        {
            qDebug() << project->getProjectTitle() << "\t"
                     << "Project unassigned";
        }
    }
}


QList<Project *> ProjectAllocationGUI::getUnallocatedProjects()
{
    QList<Project*> list;
    QListIterator<Project*> iter(projectList);
    while(iter.hasNext())
    {
        Project *proj = iter.next();
        if( !proj->getProjectAssigned() )
        {
            list.append(proj);
        }
    }
    return list;
}

QList<Student *> ProjectAllocationGUI::getUnallocatedStudents()
{
    QList<Student*> list;
    QHashIterator<int,Student*> iter(studentList);
    while(iter.hasNext())
    {
        Student *student = iter.next().value();
        if( !student->getProjectAssigned() )
        {
            list.append(student);
        }
    }
    return list;
}

QVariant ProjectAllocationGUI::getModelData(QStandardItemModel *model, int row, int col)
{
    QModelIndex index = model->index(row,col);
    return model->data(index);
}

QVariant ProjectAllocationGUI::getModelData(QSortFilterProxyModel *model, int row, int col)
{
    QModelIndex index = model->index(row,col);
    return model->data(index);
}

void ProjectAllocationGUI::updateTotalLoad()
{
    // As there has been a change somewhere in the staff model, update the total load.
    // There needs to be a relative weighting between primary and secondary supervision.
    float primaryWeight = ui->primaryLineEdit->text().toFloat();
    float secondaryWeight = ui->secondaryLineEdit->text().toFloat();
    float productWeight = ui->productLineEdit->text().toFloat();
    // Now loop over each entry in the staffModel
    int numRows = staffModel->rowCount();
    float total;
    QModelIndex index;
    QVariant data;
    statusLabel->setText("Updating Staff Load....");
    statusProgressBar->setMaximum(numRows);
    for(int ii=0; ii<numRows;ii++)
    {
        statusProgressBar->setValue(ii);
        total = 0.0f;
        // get number of projects allocated as primary supervisor
        index = staffModel->index(ii,NUMPROJECTSALLOCATED);
        data = staffModel->data(index);
        total += primaryWeight * data.toFloat();
        // get number of projects allocated as secondary supervisor
        index = staffModel->index(ii,NUMSECONDSUPERVISOR);
        data = staffModel->data(index);
        if(data.toInt() != -1)
        {
            total += secondaryWeight * data.toFloat();
        }
        // get number of projects allocated as product design supervisor
        index = staffModel->index(ii,NUMPDSUPERVISOR);
        data = staffModel->data(index);
        total += productWeight * data.toFloat();
        // update the total load
        index = staffModel->index(ii,TOTALLOAD);
        staffModel->setData(index,QVariant(total));
    }
    statusLabel->setText("Status...");
    statusProgressBar->setValue(0);
}

void ProjectAllocationGUI::updateStaffLoad(int row)
{
    // Update the total load for the staff member in row.
    // There needs to be a relative weighting between primary and secondary supervision.
    float primaryWeight = ui->primaryLineEdit->text().toFloat();
    float secondaryWeight = ui->secondaryLineEdit->text().toFloat();
    float productWeight = ui->productLineEdit->text().toFloat();
    float total;
    QModelIndex index;
    QVariant data;
    total = 0.0f;
    // get number of projects allocated as primary supervisor
    index = staffModel->index(row,NUMPROJECTSALLOCATED);
    data = staffModel->data(index);
    total += primaryWeight * data.toFloat();
    // get number of projects allocated as secondary supervisor
    index = staffModel->index(row,NUMSECONDSUPERVISOR);
    data = staffModel->data(index);
    if(data.toInt() != -1)
    {
        total += secondaryWeight * data.toFloat();
    }
    // get number of projects allocated as product design supervisor
    index = staffModel->index(row,NUMPDSUPERVISOR);
    data = staffModel->data(index);
    total += productWeight * data.toFloat();
    // update the total load
    index = staffModel->index(row,TOTALLOAD);
    staffModel->setData(index,QVariant(total));
}

void ProjectAllocationGUI::updateStaffLoadProxy(QSortFilterProxyModel *staffProxyModel, int row)
{
    // Update the total load for the staff member in row.
    // There needs to be a relative weighting between primary and secondary supervision.
    float primaryWeight = ui->primaryLineEdit->text().toFloat();
    float secondaryWeight = ui->secondaryLineEdit->text().toFloat();
    float productWeight = ui->productLineEdit->text().toFloat();
    float total;
    QModelIndex index;
    QVariant data;
    total = 0.0f;
    // get number of projects allocated as primary supervisor
    index = staffProxyModel->index(row,NUMPROJECTSALLOCATED);
    data = staffProxyModel->data(index);
    total += primaryWeight * data.toFloat();
    // get number of projects allocated as secondary supervisor
    index = staffProxyModel->index(row,NUMSECONDSUPERVISOR);
    data = staffProxyModel->data(index);
    total += secondaryWeight * data.toFloat();
    // get number of projects allocated as product design supervisor
    index = staffProxyModel->index(row,NUMPDSUPERVISOR);
    data = staffProxyModel->data(index);
    total += productWeight * data.toFloat();
    // update the total load
    index = staffProxyModel->index(row,TOTALLOAD);
    staffProxyModel->setData(index,total);
}


void ProjectAllocationGUI::on_assigProjectsButton_clicked()
{
    allocateProjects();
}


void ProjectAllocationGUI::on_actionLoad_Student_List_triggered()
{
    loadStudentList();
}

void ProjectAllocationGUI::on_actionAdd_GPA_List_triggered()
{
    loadStudentGPAList();
}

void ProjectAllocationGUI::on_actionAdd_Project_List_triggered()
{
    loadProjectList();
}

void ProjectAllocationGUI::on_actionExport_triggered()
{
    saveAllocation();
    saveStaffData();
}



void ProjectAllocationGUI::on_randomAllocationPushButton_clicked()
{
    /* Algorithm is as follows:
     * Create a model of students without allocated projects
     * Sort this model using GPA
     * Create a model of unallocated projects
     * Sort the staff model using number of projects allocated
     * Loop over all students in the ordered list
     *      Get students course code
     *      create filtered model of all projects containing that course title
     *      sort using ordered staff model (?)
     *      allocate project
     *      update staff model (projects allocated++)
     *
     */

    // Student-focused project assignment.
    QSortFilterProxyModel *unallocatedStudentModel = new QSortFilterProxyModel(this);
    unallocatedStudentModel->setSourceModel(studentModel);
    unallocatedStudentModel->setFilterFixedString(QString::number(0));
    unallocatedStudentModel->setFilterKeyColumn(CHOICEALLOCATED);
    unallocatedStudentModel->sort(GPA,Qt::DescendingOrder);
    ui->studentsTableView->setModel(unallocatedStudentModel);
    // project proxy model.
    QSortFilterProxyModel *unallocatedProjectModel = new QSortFilterProxyModel(this);
    unallocatedProjectModel->setSourceModel(projectModel);
    unallocatedProjectModel->setFilterFixedString(QString("No student allocated"));
    unallocatedProjectModel->setFilterKeyColumn(STUDENTALLOCATED);
    unallocatedProjectModel->sort(STUDENTALLOCATED);
    ui->projectsTableView->setModel(unallocatedProjectModel);
    // sort staff model.
    QSortFilterProxyModel *staffProxyModel = new QSortFilterProxyModel(this);
    staffProxyModel->setSourceModel(staffModel);
    staffProxyModel->sort(NUMPROJECTSALLOCATED);

    // Setup status bar
    statusLabel->setText("Allocating Course Supervisors....");
    statusProgressBar->setMaximum(unallocatedStudentModel->rowCount());

    // Now loop through all the students in the sorted list
    QList<int> rowsAllocated;
    QVariant courseCode;
    QString courseTitle;
    QMap<int,QString> validProjects;
    QList<int> sortedValidProjects;
    for(int istudent=0; istudent < unallocatedStudentModel->rowCount(); istudent++)
    {
        statusProgressBar->setValue(istudent);
        courseCode = getModelData(unallocatedStudentModel,istudent,COURSE);
        courseTitle = coursesRunningMap[courseCode.toString()];
        validProjects.clear();
        sortedValidProjects.clear();
        // Find all valid projects
        for(int iproject=0; iproject < unallocatedProjectModel->rowCount(); ++iproject)
        {
            QVariant supervisor = getModelData(unallocatedProjectModel,iproject,STAFFMEMBER);
            for(int icourse=0; icourse < unallocatedProjectModel->columnCount(); ++icourse)
            {
                QVariant itemData = getModelData(unallocatedProjectModel,iproject,icourse);
                if(courseTitle == itemData.toString())
                {
                    validProjects.insert(iproject,supervisor.toString());
                    break;
                }
            }
        }




        // Now need to sort the valid projects list using the number of projects currently
        // assigned to that supervisor.
        QMapIterator<int,QString> iter(validProjects);
        int minAllocated = 0;
        while(iter.hasNext())
        {
            auto vpi = iter.next();
            int vp = vpi.key();
            QString sup = vpi.value();
            staffProxyModel->setFilterFixedString(sup);
            QModelIndex index = staffProxyModel->index(0,NUMPROJECTSALLOCATED);
            QVariant numAllocated = staffProxyModel->data(index);
            // add to sorted list
            if(sortedValidProjects.isEmpty())
            {
                sortedValidProjects.append(vp);
                minAllocated = numAllocated.toInt();
            }
            else
            {

                if(numAllocated.toInt() <= minAllocated)
                {
                    sortedValidProjects.insert(0,vp);
                    minAllocated = numAllocated.toInt();
                }
                else
                {
                    sortedValidProjects.append(vp);
                }
            }
        }


        // If there are no valid projects left, continue on to next student
        if(sortedValidProjects.isEmpty())
        {
            QVariant name = getModelData(unallocatedStudentModel,istudent,SURNAME);
            qDebug() << "Couldn't allocate to student - " << name.toString();
            continue;
        }

        // Now allocate the first project in the sorted list to this student
        int projectRow = sortedValidProjects[0];
        rowsAllocated.append(projectRow);
        QModelIndex index = unallocatedProjectModel->index(projectRow,0);
        QVariant projectTitle = unallocatedProjectModel->data(index);
        index = unallocatedProjectModel->index(projectRow,STAFFMEMBER);
        QVariant supervisor = unallocatedProjectModel->data(index);
        //Update model data
        QModelIndex sindex = unallocatedStudentModel->index(istudent,ALLOCATEDPROJECT);
        unallocatedStudentModel->setData(sindex,projectTitle.toString());
        sindex = unallocatedStudentModel->index(istudent,SUPERVISOR);
        unallocatedStudentModel->setData(sindex,supervisor.toString());
        // Update the staffModel data
        staffProxyModel->setFilterFixedString(supervisor.toString());
        index = staffProxyModel->index(0,NUMPROJECTSALLOCATED);
        QVariant npa = staffProxyModel->data(index);
        int np = npa.toInt();
        np += 1;
        staffProxyModel->setData(index,np);
        updateStaffLoadProxy(staffProxyModel,index.row());
        // Need to change the data used to filter the proxy models last.
        QVariant allocation = getModelData(unallocatedStudentModel,istudent,MATRIC);
        sindex = unallocatedStudentModel->index(istudent,CHOICEALLOCATED);
        unallocatedStudentModel->setData(sindex,QString::number(6));
        QModelIndex pindex = unallocatedProjectModel->index(projectRow,STUDENTALLOCATED);
        unallocatedProjectModel->setData(pindex,allocation.toString());
        // If a project was allocated, its row is removed from the filtered proxy so we need the
        // iterator to decrease by one.
        istudent--;
    }
        int totalStudents = studentModel->rowCount();
        int unallocated = unallocatedStudentModel->rowCount();
        int numAllocated = totalStudents - unallocated;
        ui->numAllocatedLineEdit->setText(QString::number(numAllocated));
        statusLabel->setText("Status...");
        statusProgressBar->setValue(0);
}

void ProjectAllocationGUI::on_pushButtonRankGPA_clicked()
{
    // Sort the student model in increasing GPA
    studentModel->sort(GPA,Qt::DescendingOrder);
}

void ProjectAllocationGUI::on_actionClear_All_triggered()
{
    // Remove all the data from each model
    studentModel->clear();
    projectModel->clear();
    staffModel->clear();
    ui->studentLineEdit->setText(QString(" "));
    ui->projectLineEdit->setText(QString(" "));
    ui->gpsLineEdit->setText(QString(" "));
    ui->numStudentsLineEdit->setText(QString::number(0));
    ui->numAllocatedLineEdit->setText(QString::number(0));
    ui->numProjectsLineEdit->setText(QString::number(0));
    // Recreate the blank models
    createModels();
    // Load in the list of eligible staff
    loadEligibleStaff();
}

void ProjectAllocationGUI::on_viewAllButton_clicked()
{
    ui->studentsTableView->setModel(studentModel);
    ui->projectsTableView->setModel(projectModel);
}

void ProjectAllocationGUI::on_viewUnallocatedBitton_clicked()
{
    // Student-focused project assignment.
    QSortFilterProxyModel *unallocatedStudentModel = new QSortFilterProxyModel(this);
    unallocatedStudentModel->setSourceModel(studentModel);
    unallocatedStudentModel->setFilterFixedString(QString::number(0));
    unallocatedStudentModel->setFilterKeyColumn(CHOICEALLOCATED);
    unallocatedStudentModel->sort(GPA,Qt::DescendingOrder);
    ui->studentsTableView->setModel(unallocatedStudentModel);
    // project proxy model.
    QSortFilterProxyModel *unallocatedProjectModel = new QSortFilterProxyModel(this);
    unallocatedProjectModel->setSourceModel(projectModel);
    unallocatedProjectModel->setFilterFixedString(QString("No student allocated"));
    unallocatedProjectModel->setFilterKeyColumn(STUDENTALLOCATED);
    ui->projectsTableView->setModel(unallocatedProjectModel);
    // sort staff model.
    staffModel->sort(STUDENTALLOCATED);
}

void ProjectAllocationGUI::on_courseCodeComboBox_currentIndexChanged(const QString &arg1)
{
    ui->courseTitleEdit->setText(coursesRunningMap[arg1]);
}

void ProjectAllocationGUI::on_actionOpen_triggered()
{
    // Open File for reading
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Session"), "./", tr("Project Allocator Data Files (*.dat)"));
    QFile projectFile(fileName);
    if (!projectFile.open(QIODevice::ReadOnly))
    {
        qDebug() << "Couldn't open file";
        int ret = QMessageBox::warning(this,tr("File Issue"),
                    tr("The project allocation data file could not be opened. Do you wish to try again?"),
                    QMessageBox::Cancel,QMessageBox::Open);
        switch(ret){
        case QMessageBox::Cancel:
            break;
        case QMessageBox::Open:
            on_actionOpen_triggered();
        }
        return;
    }
    // Clear the current model data
    studentModel->clear();
    projectModel->clear();
    staffModel->clear();

    // Set-up the models
    createModels();

    // Read from file
    QDataStream in(&projectFile);
    // Need to write data in the exact order with which it will need to be read
    // First the file locations and model dimensions
    QString studentFileName;
    QString projectFileName;
    QString gpaFileName;
    QString studentRowCount;
    QString studentColumnCount;
    QString projectRowCount;
    QString projectColumnCount;
    QString staffRowCount;
    QString staffColumnCount;
    QString primaryWeighting;
    QString secondaryWeighting;
    QString productWeighting;
    QString numAllocated;

    in >> studentFileName
       >> projectFileName
       >> gpaFileName
       >> studentRowCount
       >> studentColumnCount
       >> projectRowCount
       >> projectColumnCount
       >> staffRowCount
       >> staffColumnCount
       >> primaryWeighting
       >> secondaryWeighting
       >> productWeighting
       >> numAllocated;

    // Now the student model data
    for(int row = 0; row < studentRowCount.toInt();row++)
    {
        QList<QStandardItem*> rowItems;
        for(int col=0; col < studentColumnCount.toInt();col++)
        {
            QStandardItem *item = new QStandardItem();
            item->read(in);
            rowItems.append(item);
        }
        studentModel->appendRow(rowItems);
    }
    // Project model data
    for(int row = 0; row < projectRowCount.toInt();row++)
    {
        QList<QStandardItem*> rowItems;
        for(int col=0; col < projectColumnCount.toInt();col++)
        {
            QStandardItem *item = new QStandardItem();
            item->read(in);
            rowItems.append(item);
        }
        projectModel->appendRow(rowItems);
    }
    // and finally staffModel data
    for(int row = 0; row < staffRowCount.toInt();row++)
    {
        QList<QStandardItem*> rowItems;
        for(int col=0; col < staffColumnCount.toInt();col++)
        {
            QStandardItem *item = new QStandardItem();
            item->read(in);
            rowItems.append(item);
        }
        rowItems[NUMSECONDSUPERVISOR]->setTextAlignment(Qt::AlignCenter);
        rowItems[NUMPDSUPERVISOR]->setTextAlignment(Qt::AlignCenter);
        rowItems[TOTALLOAD]->setTextAlignment(Qt::AlignCenter);
        staffModel->appendRow(rowItems);
    }

    // Clean-up and close the file
    ui->studentLineEdit->setText(studentFileName);
    ui->projectLineEdit->setText(projectFileName);
    ui->gpsLineEdit->setText(gpaFileName);
    ui->numStudentsLineEdit->setText(QString::number(studentModel->rowCount()));
    ui->numProjectsLineEdit->setText(QString::number(projectModel->rowCount()));
    ui->numAllocatedLineEdit->setText(numAllocated);
    ui->primaryLineEdit->setText(primaryWeighting);
    ui->secondaryLineEdit->setText(secondaryWeighting);
    ui->productLineEdit->setText(productWeighting);


    ui->studentsTableView->setModel(studentModel);
    ui->projectsTableView->setModel(projectModel);
    ui->staffTableView->setModel(staffModel);
    updateTotalLoad();
    loadEligibleStaff();
    projectFile.close();
}

void ProjectAllocationGUI::on_actionSave_triggered()
{
    // Save the current database and model state to file.
    // Open File for reading
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save Session"), "./", tr("Project Allocator Data Files (*.dat)"));
    QFile projectFile(fileName);
    if (!projectFile.open(QIODevice::WriteOnly))
    {
        qDebug() << "Couldn't open file";
        int ret = QMessageBox::warning(this,tr("File Issue"),
                    tr("The project allocation data file could not be opened. Do you wish to try again?"),
                    QMessageBox::Cancel,QMessageBox::Open);
        switch(ret){
        case QMessageBox::Cancel:
            break;
        case QMessageBox::Open:
            on_actionSave_triggered();
        }
        return;
    }

    // Write to file
    QDataStream out(&projectFile);
    // Need to write data in the exact order with which it will need to be read
    // First the file locations and model dimensions
    out << ui->studentLineEdit->text()
        << ui->projectLineEdit->text()
        << ui->gpsLineEdit->text()
        << QString::number(studentModel->rowCount())
        << QString::number(studentModel->columnCount())
        << QString::number(projectModel->rowCount())
        << QString::number(projectModel->columnCount())
        << QString::number(staffModel->rowCount())
        << QString::number(staffModel->columnCount())
        << ui->primaryLineEdit->text()
        << ui->secondaryLineEdit->text()
        << ui->productLineEdit->text()
        << ui->numAllocatedLineEdit->text();

    // Now the student model data
    for(int row = 0; row < studentModel->rowCount();row++)
    {
        for(int col=0; col < studentModel->columnCount();col++)
        {
            QStandardItem *item =  studentModel->item(row,col);
            if(item)
            {
                item->write(out);
            }
            else
            {
                QStandardItem *emptyItem = new QStandardItem(QString(" "));
                emptyItem->write(out);
            }
        }
    }
    // Project model data
    for(int row = 0; row < projectModel->rowCount();row++)
    {
        for(int col=0; col < projectModel->columnCount();col++)
        {
            // columnCount is the maximum number of columns in the projectModel
            // Not every row is populated with this number of columns.
            QStandardItem *item =  projectModel->item(row,col);
            if(item)
            {
                item->write(out);
            }
            else
            {
                QStandardItem *emptyItem = new QStandardItem(QString(" "));
                emptyItem->write(out);
            }
        }
    }
    // and finally staffModel data
    for(int row = 0; row < staffModel->rowCount();row++)
    {
        for(int col=0; col < staffModel->columnCount();col++)
        {
            QStandardItem *item =  staffModel->item(row,col);
            if(item)
            {
                item->write(out);
            }
            else
            {
                QStandardItem *emptyItem = new QStandardItem(QString::number(0));
                emptyItem->write(out);
            }
        }
    }

    // Clean-up and close the file
    projectFile.flush();
    projectFile.close();
}


void ProjectAllocationGUI::on_actionAdd_Student_triggered()
{
    // Add a row to the studentModel
    QList<QStandardItem*> list;
    for(int i=0; i < studentModel->columnCount(); i++)
    {
        QStandardItem *item = new QStandardItem();
        list << item;
    }
    studentModel->appendRow(list);
    ui->numStudentsLineEdit->setText(QString::number(studentModel->rowCount()));
}

void ProjectAllocationGUI::on_actionAdd_Project_triggered()
{
    // Add a row to the projectModel
    QList<QStandardItem*> list;
    for(int i=0; i < projectModel->columnCount(); i++)
    {
        QStandardItem *item = new QStandardItem();
        list << item;
    }
    projectModel->appendRow(list);
    ui->numProjectsLineEdit->setText(QString::number(projectModel->rowCount()));
}

void ProjectAllocationGUI::on_actionRemove_Student_triggered()
{
    QItemSelectionModel *select = ui->studentsTableView->selectionModel();
    if(select->hasSelection())
    {
        QModelIndexList row = select->selectedRows();
        studentModel->removeRow(row.at(0).row());
    }
}

void ProjectAllocationGUI::on_actionRemove_Project_triggered()
{
    QItemSelectionModel *select = ui->projectsTableView->selectionModel();
    if(select->hasSelection())
    {
        QModelIndexList row = select->selectedRows();
        QVariant supervisor = getModelData(projectModel,row.at(0).row(),STAFFMEMBER);
        QList<QStandardItem*> item = staffModel->findItems(supervisor.toString());
        QModelIndex index = staffModel->indexFromItem(item[0]);
        int staffRow = index.row();
        index = staffModel->index(staffRow,NUMPROJECTSOFFERED);
        QVariant numprojoffered = staffModel->data(index);
        int num = numprojoffered.toInt();
        num--;
        staffModel->setData(index,num);
        projectModel->removeRow(row.at(0).row());
    }
}

void ProjectAllocationGUI::on_assignSupervisorsButton_clicked()
{
    // Distribute the second supervisor load. This will be performed in the same manner
    // as the course allocation process, with staff loading and applicable research area
    // being included in the allocation process.

    // sort staff model.
    QSortFilterProxyModel *staffProxyModel = new QSortFilterProxyModel(this);
    staffProxyModel->setSourceModel(staffModel);
    QModelIndex index;
    // Clear all current second supervisor allocations
    statusLabel->setText("Clearing Secondary Supervisors....");
    statusProgressBar->setMaximum(staffProxyModel->rowCount());
    for(int ii=0; ii<staffProxyModel->rowCount();ii++)
    {
        statusProgressBar->setValue(ii);
        index = staffProxyModel->index(ii,NUMSECONDSUPERVISOR);
        QVariant currNum = staffProxyModel->data(index);
        if(currNum.toInt() != -1)
        {
            staffProxyModel->setData(index,0);
        }
    }
    statusLabel->setText("Status...");
    statusProgressBar->setValue(0);

    // Refresh total load calculations
    updateTotalLoad();

    // Use a regular expression to filter the text.
    QRegularExpression re("[^a-z^A-z]",QRegularExpression::CaseInsensitiveOption);

    // make certain the
    // proxymodel is sorted ascending
    staffProxyModel->sort(TOTALLOAD,Qt::AscendingOrder);

    // We need to loop over each student
    int numStudents = studentModel->rowCount();
    statusLabel->setText("Allocating Secondary Supervisors....");
    statusProgressBar->setMaximum(numStudents);
    for (int student=0; student < numStudents; student++)
    {
        statusProgressBar->setValue(student);
        // First check if this is a management student
        QVariant managementYN = getModelData(studentModel,student,FIRST);
        if(managementYN == QString("MANAGEMENT"))
        {
            continue;
        }
        // Get the students course code
        QVariant cCode = getModelData(studentModel,student,COURSE);
        QString courseCode = cCode.toString();
        QString courseTitle = coursesRunningMap.value(courseCode);
        // Now get the applicable divisions
        QList<QString> applicableDivisions = divisionsMap.values(courseTitle);
        bool allocated = false;
        int row = 0;
        while(!allocated)
        {
            // We now need to run through the staff data.
            // First, check if they are eligible for assigning second supervisor duties
            QVariant numSecondaryV = getModelData(staffProxyModel,row,NUMSECONDSUPERVISOR);
            int numSecondary = numSecondaryV.toInt();
            if(numSecondary == -1)
            {
                row++;
                continue;
            }
            // Now extract their associated research division
            QVariant researchDivisionV = getModelData(staffProxyModel,row,DIVISION);
            QString researchDivision = researchDivisionV.toString();
            researchDivision.replace(re,"");
            for(int id=0; id < applicableDivisions.count();id++)
            {
                // Check if the staff's division is applicable
                QString appDiv = applicableDivisions[id];
                appDiv.replace(re,"");
                if(appDiv == researchDivision)
                {
                    // Staff member can be allocated as second supervisor
                    QVariant sup = getModelData(staffProxyModel,row,NAME);
                    index = studentModel->index(student,SECONDSUPERVISOR);
                    studentModel->setData(index,sup);
                    index = staffProxyModel->index(row,NUMSECONDSUPERVISOR);
                    QVariant numSSv = getModelData(staffProxyModel,row,NUMSECONDSUPERVISOR);
                    int numSS = numSSv.toInt();
                    numSS++;
                    staffProxyModel->setData(index,numSS);
                    allocated = true;
                }
            }

            // Increment row
            if(row < staffProxyModel->rowCount())
            {
                row++;
            }
            else
            {
                break;
            }
        }
        updateStaffLoadProxy(staffProxyModel,row-1);
    }
    statusLabel->setText("Status...");
    statusProgressBar->setValue(0);
}

void ProjectAllocationGUI::on_actionRemove_Staff_triggered()
{
    QItemSelectionModel *select = ui->staffTableView->selectionModel();
    if(select->hasSelection())
    {
        QModelIndexList row = select->selectedRows();
        staffModel->removeRow(row.at(0).row());
    }
}
