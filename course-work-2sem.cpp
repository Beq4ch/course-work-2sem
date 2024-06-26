﻿#include <iostream>
#include <windows.h>
#include "group.h"

using namespace std;

// Функция для безопасного чтения строки из ввода
void safeReadString(char* buffer, int maxLength) {
    cin.get(buffer, maxLength);
    while (cin.get() != '\n') {} // Чтение и игнорирование всех оставшихся символов в строке ввода
}

void filterMenu(GroupList& groupList) {
    int choice;
    do {
        system("cls");
        cout << "\nФильтрация студентов:\n";
        cout << "1. Фильтрация по ФИО\n";
        cout << "2. Фильтрация по номеру телефона\n";
        cout << "3. Фильтрация по оценкам\n";
        cout << "4. Фильтрация по стипендии\n";
        cout << "5. Фильтрация по номеру группы\n";
        cout << "6. Назад\n";
        cout << "Выберите пункт: ";
        cin >> choice;

        char studentName[MAX_NAME_LENGTH];
        char phoneNumber[PHONE_NUMBER_LENGTH];
        int grades[NUM_GRADES];
        float scholarship;
        int groupNumber;

        switch (choice) {
        case 1:
            cout << "Введите ФИО студента: ";
            cin.ignore();
            safeReadString(studentName, MAX_NAME_LENGTH);
            for (GroupNode* group = groupList.head; group; group = group->next) {
                group->students.filterStudents(studentName);
            }
            system("pause");
            break;
        case 2:
            cout << "Введите номер телефона: ";
            cin.ignore();
            safeReadString(phoneNumber, PHONE_NUMBER_LENGTH);
            for (GroupNode* group = groupList.head; group; group = group->next) {
                group->students.filterStudents(nullptr, phoneNumber);
            }
            system("pause");
            break;
        case 3:
            cout << "Введите " << NUM_GRADES << " оценок: ";
            for (int i = 0; i < NUM_GRADES; ++i) {
                cin >> grades[i];
            }
            for (GroupNode* group = groupList.head; group; group = group->next) {
                group->students.filterStudents(nullptr, nullptr, grades);
            }
            system("pause");
            break;
        case 4:
            cout << "Введите размер стипендии: ";
            cin >> scholarship;
            for (GroupNode* group = groupList.head; group; group = group->next) {
                group->students.filterStudents(nullptr, nullptr, nullptr, scholarship);
            }
            system("pause");
            break;
        case 5:
            cout << "Введите номер группы: ";
            cin >> groupNumber;
            for (GroupNode* group = groupList.head; group; group = group->next) {
                group->students.filterStudents(nullptr, nullptr, nullptr, -1, groupNumber);
            }
            system("pause");
            break;
        case 6:
            return;
        default:
            cout << "Неверный ввод, попробуйте снова.\n";
            break;
        }
    } while (choice != 6);
}

void editStudentMenu(GroupList& groupList, int groupNumber, int studentId) {
    GroupNode* group = groupList.findGroup(groupNumber);
    if (!group) {
        cout << "Группа с номером " << groupNumber << " не найдена.\n";
        return;
    }

    Student* student = group->students.findStudent(studentId);
    if (!student) {
        cout << "Студент с ID " << studentId << " не найден\n";
        return;
    }

    int choice;
    do {
        system("cls");
        cout << "Редактирование студента (ID: " << studentId << ")\n";
        cout << "1. Изменить ФИО\n";
        cout << "2. Изменить оценки\n";
        cout << "3. Изменить стипендию\n";
        cout << "4. Изменить номер телефона\n";
        cout << "5. Переместить в другую группу\n";
        cout << "6. Назад\n";
        cout << "Выберите пункт: ";
        cin >> choice;
        cin.ignore(); // Пропуск символа новой строки

        switch (choice) {
        case 1: {
            char studentName[MAX_NAME_LENGTH];
            cout << "Введите новое ФИО: ";
            safeReadString(studentName, MAX_NAME_LENGTH);
            strncpy_s(student->name, studentName, MAX_NAME_LENGTH);
            cout << "ФИО изменено.\n";
            system("pause");
            break;
        }
        case 2: {
            int grades[NUM_GRADES];
            cout << "Введите новые оценки (" << NUM_GRADES << " оценок): ";
            for (int i = 0; i < NUM_GRADES; ++i) {
                cin >> grades[i];
            }
            for (int i = 0; i < NUM_GRADES; ++i) {
                student->grades[i] = grades[i];
            }
            cout << "Оценки изменены.\n";
            system("pause");
            break;
        }
        case 3: {
            float stipend;
            cout << "Введите новый размер стипендии: ";
            cin >> stipend;
            student->scholarship = stipend;
            cout << "Стипендия изменена.\n";
            system("pause");
            break;
        }
        case 4: {
            char phoneNumber[PHONE_NUMBER_LENGTH];
            cout << "Введите новый номер телефона: ";
            safeReadString(phoneNumber, PHONE_NUMBER_LENGTH);
            strncpy_s(student->phoneNumber, phoneNumber, PHONE_NUMBER_LENGTH);
            cout << "Номер телефона изменен.\n";
            system("pause");
            break;
        }
        case 5: {
            int newGroupNumber;
            cout << "Введите новый номер группы: ";
            cin >> newGroupNumber;
            cin.ignore(); // Пропуск символа новой строки

            GroupNode* newGroup = groupList.findGroup(newGroupNumber);
            if (!newGroup) {
                cout << "Группа с номером " << newGroupNumber << " не найдена. Создаем новую группу.\n";
                groupList.addGroup(newGroupNumber);
                newGroup = groupList.findGroup(newGroupNumber);
            }
            group->students.moveStudentToGroup(studentId, newGroup->students, newGroupNumber);
            return; // Выходим из меню редактирования, так как студент перемещен
        }
        case 6:
            return;
        default:
            cout << "Неверный ввод, попробуйте снова.\n";
            system("pause");
            break;
        }
    } while (choice != 6);
}

// Меню для взаимодействия с пользователем
void menu(GroupList& groupList) {
    SetConsoleCP(1251); // Установка кодировки консоли для ввода
    SetConsoleOutputCP(1251); // Установка кодировки консоли для вывода
    int choice;
    do {
        system("cls");
        cout << "\n\tРАБОТА С ГРУППАМИ\n";
        cout << "1. Добавить группу\n";
        cout << "2. Удалить группу\n";
        cout << "3. Удалить всех студентов группы\n";
        cout << "4. Показать проценты стипендии по группам\n";
        cout << "5. Удалить все группы\n";
        cout << "\n\tРАБОТА СО СТУДЕНТАМИ\n";
        cout << "6. Добавить студента в группу\n";
        cout << "7. Удалить студента из группы\n";
        cout << "8. Редактировать данные студента\n";
        cout << "9. Показать все группы и студентов\n";
        cout << "10. Фильтрация студентов\n";
        cout << "\n\tРАБОТА С ФАЙЛАМИ\n";
        cout << "11. Сохранить данные в файл\n";
        cout << "12. Загрузить данные из файла\n";
        cout << "\n\tЗАВЕРШЕНИЕ РАБОТЫ\n";
        cout << "13. Выйти\n";
        cout << "Выберите пункт: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            int groupNumber;
            cout << "Введите номер группы: ";
            cin >> groupNumber;
            if (groupList.findGroup(groupNumber)) {
                cout << "Группа с номером " << groupNumber << " уже существует\n";
            }
            else {
                groupList.addGroup(groupNumber);
                cout << "Группа успешно добавлена\n";
            }
            system("pause");
            break;
        }
        case 2: {
            if (groupList.isEmpty()) {
                cout << "Список групп пуст!\n";
            }
            else {
                system("cls");
                int groupNumber;
                groupList.printAllGroupNumbers();
                cout << "Введите номер группы для удаления: ";
                cin >> groupNumber;
                groupList.removeGroup(groupNumber);
            }
            system("pause");
            break;
        }
        case 3: {
            if (groupList.isEmpty()) {
                cout << "Список групп пуст!\n";
            }
            else {
                int groupNumber;

                system("cls");
                groupList.printAllGroupNumbers();

                cout << "Введите номер группы: ";
                cin >> groupNumber;
                cin.ignore(); // Пропуск символа новой строки

                GroupNode* group = groupList.findGroup(groupNumber);

                if (!group) {
                    cout << "Группа с номером " << groupNumber << " не найдена.\n";
                }
                else {
                    group->printStudents();
                    if (!(group->students.isEmpty())) {
                        groupList.removeAllStudentsFromGroup(groupNumber);
                    }
                }
            }
            system("pause");
            break;
        }
        case 4:
            if (groupList.isEmpty()) {
                cout << "Список групп пуст!\n";
            }
            else {
                system("cls");
                groupList.printGroupScholarshipPercentage();
            }
            system("pause");
            break;
        case 5: {
            if (groupList.isEmpty()) {
                cout << "Список групп пуст!\n";
            }
            else {
                groupList.removeAllGroup();
            }
            system("pause");
            break;
        }
        case 6: {
            if (groupList.isEmpty()) {
                cout << "Список групп пуст!\n";
            }
            else {
                int groupNumber, grades[NUM_GRADES];
                char studentName[MAX_NAME_LENGTH];
                char phoneNumber[PHONE_NUMBER_LENGTH];
                float stipend;

                system("cls");
                groupList.printAllGroupNumbers();

                cout << "Введите номер группы: ";
                cin >> groupNumber;
                cin.ignore(); // Пропуск символа новой строки

                if (!groupList.findGroup(groupNumber)) {
                    cout << "Группа с номером " << groupNumber << " не найдена.\n";
                }
                else {
                    cout << "Введите ФИО студента (до 50 символов): ";
                    safeReadString(studentName, MAX_NAME_LENGTH);

                    cout << "Введите " << NUM_GRADES << " оценок: ";
                    for (int i = 0; i < NUM_GRADES; ++i) {
                        cin >> grades[i];
                    }

                    cout << "Введите размер стипендии: ";
                    cin >> stipend;
                    cin.ignore();

                    cout << "Введите номер телефона (в формате +7XXXXXXXXX): ";
                    safeReadString(phoneNumber, PHONE_NUMBER_LENGTH);

                    groupList.addStudentToGroup(groupNumber, studentName, grades, stipend, phoneNumber);
                    cout << "Студент успешно добавлен\n";
                }
            }
            system("pause");
            break;
        }
        case 7: {
            if (groupList.isEmpty()) {
                cout << "Список групп пуст!\n";
            }
            else {
                int groupNumber, studentId;

                system("cls");

                groupList.printAllGroupNumbers();

                cout << "Введите номер группы: ";
                cin >> groupNumber;
                cin.ignore(); // Пропуск символа новой строки

                GroupNode* group = groupList.findGroup(groupNumber);

                if (!group) {
                    cout << "Группа с номером " << groupNumber << " не найдена.\n";
                }
                else {
                    group->printStudents();
                    if (!(group->students.isEmpty())) {
                        cout << "Введите идентификационный номер студента: ";
                        cin >> studentId;
                        cin.ignore(); // Пропуск символа новой строки

                        groupList.removeStudentFromGroup(groupNumber, studentId);
                    }
                }
            }
            system("pause");
            break;
        }
        case 8: {
            if (groupList.isEmpty()) {
                cout << "Список групп пуст!\n";
            }
            else {
                int groupNumber, studentId;

                system("cls");

                groupList.printAllGroupNumbers();

                cout << "Введите номер группы: ";
                cin >> groupNumber;
                cin.ignore(); // Пропуск символа новой строки

                GroupNode* group = groupList.findGroup(groupNumber);
                if (!group) {
                    cout << "Группа с номером " << groupNumber << " не найдена.\n";
                }
                else {
                    group->printStudents();
                    if (!(group->students.isEmpty())) {
                        cout << "Введите идентификационный номер студента: ";
                        cin >> studentId;
                        cin.ignore(); // Пропуск символа новой строки

                        if (!group->students.findStudent(studentId)) {
                            cout << "Студент с ID " << studentId << " не найден";
                        }
                        editStudentMenu(groupList, groupNumber, studentId);
                    }
                }
            }
            system("pause");
            break;
        }
        case 9:
            if (groupList.isEmpty()) {
                cout << "Список групп пуст!\n";
            }
            else {
                system("cls");
                groupList.printAllGroups();
            }
            system("pause");
            break;
        case 10: {
            if (groupList.isEmpty()) {
                cout << "Список групп пуст!\n";
            }
            else {
                filterMenu(groupList);
            }
            system("pause");
            break;
        }
        case 11: {
            if (groupList.isEmpty()) {
                cout << "Список групп пуст!\n";
            }
            else {
                char filename[MAX_NAME_LENGTH];
                cout << "Введите имя файла для сохранения: ";
                cin.ignore();
                safeReadString(filename, MAX_NAME_LENGTH);
                groupList.saveToFile(filename);
            }
            system("pause");
            break;
        }
        case 12: {
            char filename[MAX_NAME_LENGTH];
            cout << "Введите имя файла для загрузки: ";
            cin.ignore();
            safeReadString(filename, MAX_NAME_LENGTH);
            groupList.loadFromFile(filename);
            system("pause");
            break;
        }
        case 13:
            cout << "Выход из программы.\n";
            break;
        default:
            cout << "Неверный ввод, попробуйте снова.\n";
            break;
        }
    } while (choice != 13);
}


// Основная функция программы
int main() {
    GroupList groupList;
    menu(groupList);
    return 0;
}
