#ifndef GROUP_H
#define GROUP_H

#include "student.h"

// Узел для хранения информации о группе студентов
struct GroupNode {
    int groupNumber; // Номер группы
    StudentHashTable students; // Хэш-таблица студентов группы
    GroupNode* next; // Указатель на следующий узел в списке
    GroupNode* prev; // Указатель на предыдущий узел в списке

    // Конструктор с инициализацией номера группы
    GroupNode(int num);

    // Функция для печати всех студентов группы
    void printStudents();

    // Функция для вычисления общей суммы стипендий в группе
    float calculateTotalScholarship() const;

    // Функция для сохранения данных группы в файл
    void saveToFile(ofstream& outFile) const;

    // Функция для загрузки данных группы из файла
    void loadFromFile(ifstream& inFile, int groupNumber);
};

// Двусвязный список групп
struct GroupList {
    GroupNode* head; // Указатель на первый узел списка
    GroupNode* tail; // Указатель на последний узел списка

    // Конструктор по умолчанию
    GroupList();

    // Функция для добавления новой группы
    void addGroup(int groupNumber);

    // Функция для удаления группы по номеру
    void removeGroup(int groupNumber);

    // Функция для поиска группы по номеру
    GroupNode* findGroup(int groupNumber) const;

    // Функция для добавления студента в группу
    void addStudentToGroup(int groupNumber, const char* studentName, const int* grades, float stipend, const char* phoneNumber);

    // Функция для удаления студента из группы
    void removeStudentFromGroup(int groupNumber, int studentId);

    // Функция для удаления всех групп и студентов
    void removeAllGroup();

    // Функция для печати номеров всех групп
    void printAllGroupNumbers() const;

    // Функция для печати всех групп и их студентов
    void printAllGroups() const;

    // Функция для вычисления общей суммы стипендий во всех группах
    float calculateTotalScholarship() const;

    // Функция для проверки, пуст ли список групп
    bool isEmpty() const;

    // Функция для печати процента стипендий по каждой группе
    void printGroupScholarshipPercentage() const;

    // Функция для сохранения данных всех групп в файл
    void saveToFile(const char* filename) const;

    // Функция для загрузки данных всех групп из файла
    void loadFromFile(const char* filename);

    // Функция для удаления всех студентов из группы
    void removeAllStudentsFromGroup(int groupNumber);
};

#endif
