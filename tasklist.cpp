#include "tasklist.h"

LinkedList::LinkedList() : head(nullptr) {}

void LinkedList::addTask(const string& task, const string& date) {
    Node* newNode = new Node(task, date);
    newNode->next = head;
    head = newNode;
    sortTasksByDate(); // Automatically sort tasks after adding
}

Node* LinkedList::deleteTaskAndReturn(int index) {
    if (!head) return nullptr;
    if(index<0)return nullptr; // To not Crash if the given index is less than 1

    Node* temp = head;
    if (index == 0) {// the entered value already - 1 in the GUI code, So this is the (1) case
        head = head->next;
        temp->next = nullptr; // Isolate the node to be witout next
        return temp;
    }

    Node* prev = nullptr;
    for (int i = 0; temp && i < index; ++i) {
        prev = temp;
        temp = temp->next;
    }

    if (!temp) return nullptr;
//else
    prev->next = temp->next; // skipping the target node
    temp->next = nullptr; // make it point to null
    return temp; // return the deleted one to can be resotred later
}

void LinkedList::restoreDeletedTask(Node* node, int index) {
    if (!node) return;

    if (index == 0) {
        node->next = head;
        head = node;
        return;
    }

    Node* temp = head;
    for (int i = 0; temp && i < index - 1; ++i) {
        temp = temp->next;
    }

    if (!temp) return;

    node->next = temp->next;
    temp->next = node;

    sortTasksByDate(); // Re-sort after restoring
}

bool LinkedList::markTaskAsDone(int index) {
    Node* temp = head;
    for (int i = 0; temp && i < index; ++i) {//afrer this loop, temp may point to the target task or point to null if the Enterd index incorrect
        temp = temp->next;
    }

    if (!temp) return false;
//else
    temp->isDone = true;
    return true;
}

void LinkedList::sortTasksByDate() {
    if (!head || !head->next) return;  // No need to sort if the list has 0 or 1 node

    Node* ptr1 = head;
    while (ptr1 != nullptr) {
        Node* ptr2 = ptr1->next;

        while (ptr2 != nullptr) {
            if (compareDates(ptr1->date, ptr2->date)) { // this function (mentioned bellow) return true if first>second
                // Swap task data
                string tempTask = ptr1->task; //stoirng the first pointer data
                string tempDate = ptr1->date;
                bool tempIsDone = ptr1->isDone;

                ptr1->task = ptr2->task; //changing the first task's data with the second one's
                ptr1->date = ptr2->date;
                ptr1->isDone = ptr2->isDone;

                ptr2->task = tempTask; //changing the second task's data with the first one's
                ptr2->date = tempDate;
                ptr2->isDone = tempIsDone;
            }
            ptr2 = ptr2->next;
        }
        ptr1 = ptr1->next;
    }
}

bool LinkedList::compareDates(const string& date1, const string& date2) {// Swap nodes if the first date is greater
    return date1 > date2;
}

string LinkedList::getTasks() {// printing tasks
    string result = "";
    Node* temp = head;
    int index = 1;  // Start indexing from 1

    while (temp) {
        result += to_string(index) + ". " + temp->task + " (Due: " + temp->date + ")";
        if (temp->isDone) {
            result += " [DONE]";
        }
        result += "\n"; // Add a newline after each task
        temp = temp->next;
        ++index;
    }

    return result.empty() ? "No tasks available.\n" : result;
}

LinkedList::~LinkedList() { // Default Distractor
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}
