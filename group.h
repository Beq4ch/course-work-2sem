#ifndef GROUP_H
#define GROUP_H

#include "student.h"

// ���� ��� �������� ���������� � ������ ���������
struct GroupNode {
    int groupNumber; // ����� ������
    int studentCount; // ���������� ��������� � ������
    StudentHashTable students; // ���-������� ��������� ������
    GroupNode* next; // ��������� �� ��������� ���� � ������
    GroupNode* prev; // ��������� �� ���������� ���� � ������

    // ����������� � �������������� ������ ������
    GroupNode(int num);

    // ������� ��� ������ ���� ��������� ������
    void printStudents();

    // ������� ��� ���������� ����� ����� ��������� � ������
    float calculateTotalScholarship() const;

    // ������� ��� ���������� ������ ������ � ����
    void saveToFile(ofstream& outFile) const;

    // ������� ��� �������� ������ ������ �� �����
    void loadFromFile(ifstream& inFile, int groupNumber);
};

// ���������� ������ �����
struct GroupList {
    GroupNode* head; // ��������� �� ������ ���� ������
    GroupNode* tail; // ��������� �� ��������� ���� ������

    // ����������� �� ���������
    GroupList();

    // ���������� ��� ������������ ������
    ~GroupList();

    // ������� ��� ���������� ����� ������
    void addGroup(int groupNumber);

    // ������� ��� �������� ������ �� ������
    void removeGroup(int groupNumber);

    // ������� ��� ������ ������ �� ������
    GroupNode* findGroup(int groupNumber) const;

    // ������� ��� ���������� �������� � ������
    void addStudentToGroup(int groupNumber, const char* studentName, const int* grades, float stipend, const char* phoneNumber);

    // ������� ��� �������� �������� �� ������
    void removeStudentFromGroup(int groupNumber, int studentId);

    // ������� ��� �������� ���� ����� � ���������
    void removeAllGroup();

    // ������� ��� ������ ������� ���� �����
    void printAllGroupNumbers() const;

    // ������� ��� ������ ���� ����� � �� ���������
    void printAllGroups() const;

    // ������� ��� ���������� ����� ����� ��������� �� ���� �������
    float calculateTotalScholarship() const;

    // ������� ��� ��������, ���� �� ������ �����
    bool isEmpty() const;

    // ������� ��� ������ �������� ��������� �� ������ ������
    void printGroupScholarshipPercentage() const;

    // ������� ��� ���������� ������ ���� ����� � ����
    void saveToFile(const char* filename) const;

    // ������� ��� �������� ������ ���� ����� �� �����
    void loadFromFile(const char* filename);

    // ������� ��� �������� ���� ��������� �� ������
    void removeAllStudentsFromGroup(int groupNumber);
};

#endif
