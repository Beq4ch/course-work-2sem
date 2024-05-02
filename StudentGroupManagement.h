#pragma once
#include <iostream>
#include <string>
#include <clocale>
#include <windows.h>
#include <fstream>

using namespace std;

struct Student {
    Student* next; // Следующий
    string name; // ФИО
    int grades[5]{}; // Оценки
    int scholarship; // Размер стипендии

    Student() : next(nullptr), name(""), scholarship(0) {}
};

struct Group {
    Group* next; // Следующий
    int number; // Номер группы
    Student* head; // Первый элемент списка студентов
    Group() : next(nullptr), number(0), head(nullptr) {};
};

// ОСНОВНЫЕ ФУНКЦИИ
Group* addGroup(); // Добавление группы

void addStudent(Group* Group); // Функция добавления студента

void insertStudentSorted(Group* Group, Student* Student); // Добавление студента в группу (в алфавитном порядке)

Group* selectGroup(Group* Group); // Выбор группы

void editStudent(Group* Group); // Редактирование студента

void deleteAllStudents(Group* Group); // Удаление всех студентов в группе

void deleteStudent(Group* Group, int position); // Удаление студента (по номеру позиции)

void printAllGroups(Group* Group); // Вывод информации о всех группах

void printGroup(Group* Group); // Вывод информации о выбранной группе

void readStudentsFromFile(Group* Group, const string& filename); // Чтение студентов из файла

void writeGroupsToFile(Group* Group); // Вывод информации о группах в файл

void printGroupWithHighestAverage(Group* Group); // Вывод группы с максимальным средним баллом

void outputGroup(Group* g); //Вывод группы

// ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ
bool isGroupExists(Group* Group); // Проверка наличия группы

bool isGroupDuplicate(Group* head, Group* Group); // Проверка на дублирование группы
