#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include "tasklist.h"

class mainwindow : public QMainWindow {
    Q_OBJECT

private:
    LinkedList taskList;
    Node* lastDeletedTask;
    int lastDeletedIndex;
    QTextEdit* taskDisplay;
    QLineEdit* taskInput; // For task description
    QLineEdit* dateInput; // For task due date

public:
    explicit mainwindow(QWidget* parent = nullptr);

private slots:
    void addTask();
    void deleteTask();
    void markTaskAsDone();
    void undo();
    void updateTaskDisplay();
};

#endif // MAINWINDOW_H
