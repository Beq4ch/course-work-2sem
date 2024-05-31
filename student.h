#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

// ��������� ��� ������������ ����� �����, ������ �������� � ���������� ������
constexpr int MAX_NAME_LENGTH = 50;
constexpr int PHONE_NUMBER_LENGTH = 13; // ������������ ����� ������ ��������, ������� ��� ������
constexpr int NUM_GRADES = 5;

// ������� ��� ���������� ���-�������� �������������� ��������
unsigned int hashStudentId(int id);

// ��������� ��� �������� ���������� � ��������
struct Student {
    int id; // ����������������� ����� ��������
    char name[MAX_NAME_LENGTH]; // ��� ��������
    int grades[NUM_GRADES]; // ������ ��������
    float scholarship; // ��������� ��������
    char phoneNumber[PHONE_NUMBER_LENGTH]; // ����� �������� ��������
    int groupNumber; // ����� ������ ��������

    // ����������� � ����������� �� ���������
    Student(int studentId = 0, const char* studentName = "", const int* studentGrades = nullptr, float stipend = 0.0, const char* extra = "", int group = 0);
};

// ���� �������� ������ ��� ���������
struct StudentNode {
    Student student;
    StudentNode* next;

    StudentNode(const Student& stud, StudentNode* nextNode = nullptr)
        : student(stud), next(nextNode) {}
};

// ��������� ���-������� ��� �������� ���������
struct StudentHashTable {
    StudentNode** table; // ������ ���������� �� ����
    int tableSize; // ������ �������
    int numElements; // ���������� ��������� � �������
    int nextId; // ��������� ������������� ��� ������ ��������

    // ����������� � �������������� ������� �������
    StudentHashTable(int initialSize = 50);

    // ���������� ��� ������������ ������
    ~StudentHashTable();

    // ������� ��� ���������� �������� � ���-�������
    void addStudent(const char* name, const int* grades, float stipend, const char* phoneNumber, int groupNumber);

    // ������� ��� ������ �������� �� ��������������
    Student* findStudent(int id) const;

    // ������� ��� �������� �������� �� ��������������
    void removeStudent(int id);

    // ������� ��� ���������� ����� ����� ���������
    float calculateTotalScholarship() const;

    // ������� ��� ������ ���� ���������
    void printAllStudents() const;

    // ������� ��� ���������� ������ ������� � ����
    void saveToFile(ofstream& outFile) const;

    // ������� ��� �������� ������ ������� �� �����
    void loadFromFile(ifstream& inFile, int groupNumber);

    // ������� ��� ��������, ����� �� �������
    bool isEmpty() const;

    // ������� ��� �������� ���� ��������� �� �������
    void removeAllStudents();

    // ������� ��� ���������� ������� �������
    void resizeTable();

    // ������� ��� ���������� ��������� �� ����������
    void filterStudents(const char* name = nullptr, const char* phoneNumber = nullptr, const int* grades = nullptr, float scholarship = -1, int groupNumber = -1) const;

    // ��������� ����� ��� ����������� �������� � ������ ������
    void moveStudentToGroup(int id, StudentHashTable& newGroupTable, int newGroupNumber);

private:
    // ���-������� ��� ���������� ������� �� ������ ����� ��������
    unsigned int hashFunction(int id) const;
};

#endif
