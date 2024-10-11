#include <iostream>
#include <string>
#include <fstream>

using namespace std;

const int MAX_TASKS = 1000; 
string tasks[MAX_TASKS];  
int taskCount = 0;        

void loadTasksFromFile() {
    ifstream inputFile("tasks.txt");
    if (inputFile.is_open()) {
        while (getline(inputFile, tasks[taskCount]) && taskCount < MAX_TASKS) {
            taskCount++;
        }
        inputFile.close();
    } else {
        cout << "No saved tasks found. Starting fresh.\n";
    }
}

void saveTasksToFile() {
    ofstream outputFile("tasks.txt");
    for (int i = 0; i < taskCount; i++) {
        outputFile << tasks[i] << endl;
    }
    outputFile.close();
}

void displayTasks() {
    if (taskCount == 0) {
        cout << "No tasks available.\n";
        return;
    }
    cout << "Tasks:\n";
    for (int i = 0; i < taskCount; i++) {
        cout << i + 1 << ". " << tasks[i] << endl;
    }
}

void addTask(const string& task) {
    if (taskCount < MAX_TASKS) {
        tasks[taskCount] = task;
        taskCount++;
        cout << "Task added successfully.\n";
    } else {
        cout << "Task limit reached. Cannot add more tasks.\n";
    }
}

void removeTask(int taskNum) {
    if (taskNum > 0 && taskNum <= taskCount) {
        for (int i = taskNum - 1; i < taskCount - 1; i++) {
            tasks[i] = tasks[i + 1]; 
        }
        taskCount--;
        cout << "Task removed successfully.\n";
    } else {
        cout << "Invalid task number.\n";
    }
}

int main() {
    int choice = 0; // Initialize choice
    string task;

    loadTasksFromFile(); 

    do {
        cout << "\nTo-Do List Application\n";
        cout << "1. Add Task\n";
        cout << "2. Remove Task\n";
        cout << "3. View Tasks\n";
        cout << "4. Save and Exit\n";
        cout << "Enter your choice: ";
        
        cin >> choice;
        cin.ignore(); 

        switch (choice) {
            case 1:
                cout << "Enter task: ";
                getline(cin, task);
                addTask(task);
                break;
            case 2:
                displayTasks();
                if (taskCount > 0) {
                    int taskNum;
                    cout << "Enter task number to remove: ";
                    cin >> taskNum;
                    removeTask(taskNum);
                }
                break;
            case 3:
                displayTasks();
                break;
            case 4:
                cout << "Exiting application...\n";
                saveTasksToFile(); 
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;  
        }
    } while (choice != 4); // Loop until the user chooses to exit

    return 0;
}

