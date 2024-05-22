#include <iostream>
#include <windows.h>
#include "group.h"

using namespace std;

void safeReadString(char* buffer, int maxLength) {
    cin.get(buffer, maxLength);
    while (cin.get() != '\n') {} // Чтение и игнорирование всех оставшихся символов в строке ввода
}

void menu(GroupList& groupList) {

    SetConsoleCP(1251); // Установка кодировки консоли для ввода
    SetConsoleOutputCP(1251); // Установка кодировки консоли для вывода

    int choice;
    do {
        system("cls");
        cout << "\nМеню:\n";
        cout << "1. Добавить группу\n";
        cout << "2. Удалить группу\n";
        cout << "3. Добавить студента в группу\n";
        cout << "4. Удалить студента из группы\n";
        cout << "5. Удалить всех студентов группы\n";
        cout << "6. Удалить все группы\n";
        cout << "7. Редактировать данные студента\n";
        cout << "8. Показать студентов группы\n";
        cout << "9. Показать все группы и студентов\n";
        cout << "10. Показать проценты стипендии по группам\n";
        cout << "11. Сохранить данные в файл\n";
        cout << "12. Загрузить данные из файла\n";
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
        case 4: {
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
        case 5: {
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
                        groupList.removeAllStudentsFromGroup(groupNumber);
                    }
                }
            }
            system("pause");
            break;
        }
        case 6: {
            if (groupList.isEmpty()) {
                cout << "Список групп пуст!\n";
            }
            else {
                groupList.removeAllGroup();
            }
            system("pause");
            break;
        }
        case 7: {
            if (groupList.isEmpty()) {
                cout << "Список групп пуст!\n";
            }
            else {
                int groupNumber, studentId, grades[NUM_GRADES];
                char studentName[MAX_NAME_LENGTH];
                char phoneNumber[PHONE_NUMBER_LENGTH];
                float stipend;

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

                        groupList.editStudentInGroup(groupNumber, studentId, studentName, grades, stipend, phoneNumber);
                    }
                }
            }
            system("pause");
            break;
        }
        case 8:
            if (groupList.isEmpty()) {
                cout << "Список групп пуст!\n";
            }
            else {
                system("cls");
                groupList.printAllGroupNumbers();

                int groupNumber;
                cout << "Введите номер группы: ";
                cin >> groupNumber;
                cin.ignore(); // Пропуск символа новой строки

                groupList.findGroup(groupNumber)->printStudents();
            }
            system("pause");
            break;
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
        case 10:
            if (groupList.isEmpty()) {
                cout << "Список групп пуст!\n";
            }
            else {
                system("cls");
                groupList.printGroupScholarshipPercentage();
            }
            system("pause");
            break;
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
