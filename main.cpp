#include <fstream>
#include <iostream>
#include "Abiturients.h"
#include "LinkList.h"
using namespace std;

int main() {
    int size = 0;
    int capacity = 2;
    Abiturient* arr = new Abiturient[capacity];
    loadFromFile("data.dat", arr, size, capacity);
    int choice;
    do {
        showMenu();
        cin >> choice;
        switch(choice) {
            case 1: {
                cout << "\nAll abiturients:" << endl;
                for (int i = 0; i < size; i++) {
                    printAbiturient(arr[i]);
                }
                break;
            }
            case 2: {
                Abiturient newAbiturient;
                cout << "\nEnter abiturient data:" << endl;
                cout << "Id:";
                cin >> newAbiturient.id;
                cout << "Full name:";
                cin.ignore();
                cin.getline(newAbiturient.fullname, 150);
                cout << "Email:";
                cin >> newAbiturient.email;
                cout << "Telephone:";
                cin >> newAbiturient.telephone;
                cout << "Marks:";
                for (int j = 0; j < 4; j++) {
                    cin >> newAbiturient.marks[j];
                }
                addAbit(arr, newAbiturient, size, capacity);
                cout << "Abiturient added successfully!" << endl << endl;
                break;
            }
            case 3: {
            }
            case 4: {
                cout << "Abiturients, who have unsatisfactory grades:" << endl;
                for (int i = 0; i < size; i++) {
                    if (unsatisfactory_grades(arr[i])) {
                        printAbiturient(arr[i]);
                    }
                }
                cout << " " << endl;
                break;
            }
            case 5: {
                int specified_score;
                cout << "The specified score:";
                cin >> specified_score;
                cout << "Abiturients whose total score is above the specified score: " << endl;
                for (int i = 0; i < size; i++) {
                    int sum = Total_Score(arr[i]);
                    if (sum > specified_score) {
                        printAbiturient(arr[i]);
                    }
                }
            }
            case 6: {
                cout << "Abiturients with the highest total score: " << endl;
                int maxScore = Highest_Score(arr, size);
                for (int i = 0; i < size; i++) {
                    if (Total_Score(arr[i]) == maxScore) {
                        printAbiturient(arr[i]);
                    }
                }
            }
            case 7: {
                char prefix[20];
                cout << "Enter phone prefix (example: 380): ";
                cin >> prefix;
                cout << "\nAbiturients whose phone number starts with " << prefix << ":" << endl;
                bool found = false;
                for (int i = 0; i < size; i++) {
                    if (phoneStartsWith(arr[i].telephone, prefix)) {
                        printAbiturient(arr[i]);
                        found = true;
                    }
                }
                if (!found) {
                    cout << "No abiturients found with prefix " << prefix << "!" << endl;
                }
                break;
            }
        }
    } while (choice != 0);
    saveToFile("data.dat", arr, size);
    delete[] arr;
    return 0;
}