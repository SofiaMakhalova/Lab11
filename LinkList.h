#include <fstream>
#include <iostream>
#include "Abiturients.h"
using namespace std;

void showMenu() {
    cout << "\n========== MENU ==========" << endl;
    cout << "1. Show all abiturients" << endl;
    cout << "2. Add abiturient" << endl;
    cout << "3. Delete abiturient by ID" << endl;
    cout << "4. Show abiturients with unsatisfactory grades" << endl;
    cout << "5. Show abiturients with score above specified" << endl;
    cout << "6. Show abiturients with highest score" << endl;
    cout << "7. Show abiturients by phone prefix" << endl;
    cout << "0. Exit" << endl;
    cout << "Your choice: ";
}
void loadFromFile(const char* filename, Abiturient*& arr, int &size, int &capacity) {
    ifstream file(filename, ios::binary);
    if (!file) {
        cout << "File was not found. Create new file!" << endl;
        size = 0;
        return;
    }
    file.read((char*)&size, sizeof(size));
    if (size > capacity) {
        capacity = size;
        delete[] arr;
        arr = new Abiturient[capacity];
    }
    cout << "Loaded " << size << " records from file" << endl;
    for (int i = 0; i < size; i++) {
        file >> arr[i].id;
        file.ignore(1000, '\n');
        file.getline(arr[i].fullname, 150);
        file >> arr[i].email;
        file >> arr[i].telephone;
        for (int j = 0; j < 4; j++) {
            file >> arr[i].marks[j];
        }
        file.ignore(1000, '\n');
    }
    file.close();
}

void saveToFile(const char* filename, Abiturient* arr, int size) {
    ofstream file(filename, ios::binary);
    file.write((char*)&size, sizeof(size));
    for (int i = 0; i < size; i++) {
        file.write((char*)&arr[i], sizeof(Abiturient));
    }
    file.close();
    cout << "Saved file"<< endl;
}

void addAbit(Abiturient*& arr, const Abiturient& newAbiturient, int &size, int &capacity) {
    if (size == capacity) {
        capacity *= 2;
        Abiturient* newArr = new Abiturient[capacity];
        for (int i = 0; i < size; i++) {
            newArr[i] = arr[i];
        }
        delete[] arr;
        arr = newArr;
    }
    arr[size] = newAbiturient;
    size++;
}

void deleteById(Abiturient*& arr, int id, int &size) {
    int index = -1;
    for (int i = 0; i < size; i++) {
        if (arr[i].id == id) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        cout << "Abiturient with ID " << id << " not found!" << endl;
        return;
    }
    for (int i = index; i < size - 1; i++) {
        arr[i] = arr[i + 1];
    }
    size--;
    cout << "Abiturient with ID " << id << " deleted successfully!" << endl;
}

void printAbiturient(const Abiturient& arr) {
    cout << arr.id << " " << arr.fullname<< " " << arr.email << " " << arr.telephone << endl;
}

bool unsatisfactory_grades(const Abiturient& arr) {
    for (int j = 0; j < 4; j++) {
        if (arr.marks[j] < 100)
            return true;
    }
    return false;
}

int Total_Score(const Abiturient& arr) {
    int sum = 0;
    for (int j = 0; j < 4; j++)
        sum += arr.marks[j];
    return sum;
}

int Highest_Score(Abiturient arr[], int size) {
    if (size == 0) return 0;
    int maxSum = Total_Score(arr[0]);
    for (int i = 1; i < size; i++) {
        int sum = Total_Score(arr[i]);
        if (sum > maxSum)
            maxSum = sum;
    }
    return maxSum;
}

bool phoneStartsWith(const char* phone, const char* prefix) {
    for (int i = 0; prefix[i] != '\0'; i++) {
        if (phone[i] != prefix[i]) {
            return false;
        }
    }
    return true;
}