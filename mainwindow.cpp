#include "mainwindow.h"
#include <QVBoxLayout>
#include <QString>

mainwindow::mainwindow(QWidget* parent)
    : QMainWindow(parent), lastDeletedTask(nullptr), lastDeletedIndex(-1) {
    // Main layout
    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(centralWidget);

    // Task Display
    taskDisplay = new QTextEdit(this);
    taskDisplay->setReadOnly(true);
    layout->addWidget(taskDisplay);

    // Input Fields
    taskInput = new QLineEdit(this);
    taskInput->setPlaceholderText("Enter task description");
    dateInput = new QLineEdit(this);
    dateInput->setPlaceholderText("Enter due date (YYYY-MM-DD)");

    layout->addWidget(taskInput);
    layout->addWidget(dateInput);

    // Buttons
    QPushButton* addTaskButton = new QPushButton("Add Task", this);
    QPushButton* deleteTaskButton = new QPushButton("Delete Task", this);
    QPushButton* markDoneButton = new QPushButton("Mark as Done", this);
    QPushButton* undoButton = new QPushButton("Undo Last Deletion", this);

    layout->addWidget(addTaskButton);
    layout->addWidget(deleteTaskButton);
    layout->addWidget(markDoneButton);
    layout->addWidget(undoButton);

    // Set main widget and layout
    setCentralWidget(centralWidget);

    // Connect buttons to slots
    connect(addTaskButton, &QPushButton::clicked, this, &mainwindow::addTask);
    connect(deleteTaskButton, &QPushButton::clicked, this, &mainwindow::deleteTask);
    connect(markDoneButton, &QPushButton::clicked, this, &mainwindow::markTaskAsDone);
    connect(undoButton, &QPushButton::clicked, this, &mainwindow::undo);

    updateTaskDisplay();
}

void mainwindow::addTask() {
    QString task = taskInput->text();
    QString date = dateInput->text();

    if (!task.isEmpty() && !date.isEmpty()) {
        taskList.addTask(task.toStdString(), date.toStdString());
        taskInput->clear();
        dateInput->clear();
        updateTaskDisplay();
    }
}

void mainwindow::deleteTask() {
    bool ok;
    int index = taskInput->text().toInt(&ok) - 1; // Adjust for 1-based indexing
    if (ok) {
        Node* deletedNode = taskList.deleteTaskAndReturn(index);
        if (deletedNode) {
            lastDeletedTask = deletedNode;
            lastDeletedIndex = index;
            taskInput->clear();
            updateTaskDisplay();
        }
    }
}

void mainwindow::markTaskAsDone() {
    bool ok;
    int index = taskInput->text().toInt(&ok) - 1; // Adjust for 1-based indexing
    if (ok && taskList.markTaskAsDone(index)) {
        taskInput->clear();
        updateTaskDisplay();
    }
}

void mainwindow::undo() {
    if (lastDeletedTask) {
        taskList.restoreDeletedTask(lastDeletedTask, lastDeletedIndex);
        lastDeletedTask = nullptr;
        lastDeletedIndex = -1;
        updateTaskDisplay();
    }
}

void mainwindow::updateTaskDisplay() {
    taskDisplay->setText(QString::fromStdString(taskList.getTasks()));
}
