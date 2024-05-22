#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

constexpr int MAX_NAME_LENGTH = 50;
constexpr int PHONE_NUMBER_LENGTH = 13; // Максимальная длина номера телефона, включая код страны
constexpr int NUM_GRADES = 5;

unsigned int hashStudentName(const char* name);

struct Student {
    int id; // Идентификационный номер студента
    char name[MAX_NAME_LENGTH];
    int grades[NUM_GRADES];
    float scholarship;
    char phoneNumber[PHONE_NUMBER_LENGTH];

    Student(int studentId = 0, const char* studentName = "", const int* studentGrades = nullptr, float stipend = 0.0, const char* extra = "");
};

struct StudentHashTable {
    Student* table;
    bool* isOccupied; // Массив для отслеживания занятых ячеек
    int tableSize;
    int numElements;
    int nextId;

    StudentHashTable(int initialSize = 50);

    ~StudentHashTable();

    void addStudent(const char* name, const int* grades, float stipend, const char* phoneNumber);

    Student* findStudent(int id) const;

    void removeStudent(int id);

    void editStudent(int id, const char* name, const int* grades, float stipend, const char* phoneNumber);

    float calculateTotalScholarship() const;

    void printAllStudents() const;

    void saveToFile(ofstream& outFile) const;

    void loadFromFile(ifstream& inFile);

    bool isEmpty() const;

    void removeAllStudents();

    void resizeTable();

private:
    unsigned int hashFunction(const char* name) const;

    int linearProbe(int hash, int i) const; // Линейное пробирование
};

#endif
