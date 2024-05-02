#pragma once
#include <iostream>
#include <string>
#include <clocale>
#include <windows.h>
#include <fstream>

using namespace std;

struct Student {
    Student* next; // ���������
    string name; // ���
    int grades[5]{}; // ������
    int scholarship; // ������ ���������

    Student() : next(nullptr), name(""), scholarship(0) {}
};

struct Group {
    Group* next; // ���������
    int number; // ����� ������
    Student* head; // ������ ������� ������ ���������
    Group() : next(nullptr), number(0), head(nullptr) {};
};

// �������� �������
Group* addGroup(); // ���������� ������

void addStudent(Group* Group); // ������� ���������� ��������

void insertStudentSorted(Group* Group, Student* Student); // ���������� �������� � ������ (� ���������� �������)

Group* selectGroup(Group* Group); // ����� ������

void editStudent(Group* Group); // �������������� ��������

void deleteAllStudents(Group* Group); // �������� ���� ��������� � ������

void deleteStudent(Group* Group, int position); // �������� �������� (�� ������ �������)

void printAllGroups(Group* Group); // ����� ���������� � ���� �������

void printGroup(Group* Group); // ����� ���������� � ��������� ������

void readStudentsFromFile(Group* Group, const string& filename); // ������ ��������� �� �����

void writeGroupsToFile(Group* Group); // ����� ���������� � ������� � ����

void printGroupWithHighestAverage(Group* Group); // ����� ������ � ������������ ������� ������

void outputGroup(Group* g); //����� ������

// ��������������� �������
bool isGroupExists(Group* Group); // �������� ������� ������

bool isGroupDuplicate(Group* head, Group* Group); // �������� �� ������������ ������
