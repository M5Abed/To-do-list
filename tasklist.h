#ifndef TASKLIST_H
#define TASKLIST_H

#include <string>
using namespace std;

// Node structure
struct Node {
    string task;
    string date;  // Date in YYYY-MM-DD format
    bool isDone;
    Node* next;

    Node(string t, string d) : task(t), date(d), isDone(false), next(nullptr) {}
};

// Linked List for managing tasks
class LinkedList {
private:
    Node* head;

public:
    LinkedList();
    void addTask(const string& task, const string& date);
    Node* deleteTaskAndReturn(int index);
    void restoreDeletedTask(Node* node, int index);
    bool markTaskAsDone(int index);
    void sortTasksByDate();
    string getTasks();
    ~LinkedList();

private:
    bool compareDates(const string& date1, const string& date2);
};

#endif // TASKLIST_H
