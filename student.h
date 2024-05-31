#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

// Константы для максимальной длины имени, номера телефона и количества оценок
constexpr int MAX_NAME_LENGTH = 50;
constexpr int PHONE_NUMBER_LENGTH = 13; // Максимальная длина номера телефона, включая код страны
constexpr int NUM_GRADES = 5;

// Функция для вычисления хэш-значения идентификатора студента
unsigned int hashStudentId(int id);

// Структура для хранения информации о студенте
struct Student {
    int id; // Идентификационный номер студента
    char name[MAX_NAME_LENGTH]; // Имя студента
    int grades[NUM_GRADES]; // Оценки студента
    float scholarship; // Стипендия студента
    char phoneNumber[PHONE_NUMBER_LENGTH]; // Номер телефона студента
    int groupNumber; // Номер группы студента

    // Конструктор с параметрами по умолчанию
    Student(int studentId = 0, const char* studentName = "", const int* studentGrades = nullptr, float stipend = 0.0, const char* extra = "", int group = 0);
};

// Узел связного списка для студентов
struct StudentNode {
    Student student;
    StudentNode* next;

    StudentNode(const Student& stud, StudentNode* nextNode = nullptr)
        : student(stud), next(nextNode) {}
};

// Структура хэш-таблицы для хранения студентов
struct StudentHashTable {
    StudentNode** table; // Массив указателей на узлы
    int tableSize; // Размер таблицы
    int numElements; // Количество элементов в таблице
    int nextId; // Следующий идентификатор для нового студента

    // Конструктор с инициализацией размера таблицы
    StudentHashTable(int initialSize = 50);

    // Деструктор для освобождения памяти
    ~StudentHashTable();

    // Функция для добавления студента в хэш-таблицу
    void addStudent(const char* name, const int* grades, float stipend, const char* phoneNumber, int groupNumber);

    // Функция для поиска студента по идентификатору
    Student* findStudent(int id) const;

    // Функция для удаления студента по идентификатору
    void removeStudent(int id);

    // Функция для вычисления общей суммы стипендий
    float calculateTotalScholarship() const;

    // Функция для печати всех студентов
    void printAllStudents() const;

    // Функция для сохранения данных таблицы в файл
    void saveToFile(ofstream& outFile) const;

    // Функция для загрузки данных таблицы из файла
    void loadFromFile(ifstream& inFile, int groupNumber);

    // Функция для проверки, пуста ли таблица
    bool isEmpty() const;

    // Функция для удаления всех студентов из таблицы
    void removeAllStudents();

    // Функция для увеличения размера таблицы
    void resizeTable();

    // Функция для фильтрации студентов по параметрам
    void filterStudents(const char* name = nullptr, const char* phoneNumber = nullptr, const int* grades = nullptr, float scholarship = -1, int groupNumber = -1) const;

    // Добавляем метод для перемещения студента в другую группу
    void moveStudentToGroup(int id, StudentHashTable& newGroupTable, int newGroupNumber);

private:
    // Хэш-функция для вычисления индекса на основе имени студента
    unsigned int hashFunction(int id) const;
};

#endif
