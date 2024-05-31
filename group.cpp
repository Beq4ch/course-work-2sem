#include "group.h"

// Конструктор GroupNode с инициализацией номера группы
GroupNode::GroupNode(int num) : groupNumber(num), next(nullptr), prev(nullptr) {}

// Функция для печати всех студентов группы
void GroupNode::printStudents() {
    cout << "Группа " << groupNumber << ":\n";
    students.printAllStudents();
}

// Функция для вычисления общей суммы стипендий в группе
float GroupNode::calculateTotalScholarship() const {
    return students.calculateTotalScholarship();
}

// Функция для сохранения данных группы в файл
void GroupNode::saveToFile(ofstream& outFile) const {
    outFile << groupNumber << "\n";
    students.saveToFile(outFile);
}

// Функция для загрузки данных группы из файла
void GroupNode::loadFromFile(ifstream& inFile, int groupNumber) {
    students.loadFromFile(inFile, groupNumber);
}

// Конструктор GroupList по умолчанию
GroupList::GroupList() : head(nullptr), tail(nullptr) {}

GroupList::~GroupList() {
    removeAllGroup();
}

// Функция для добавления новой группы
void GroupList::addGroup(int groupNumber) {
    GroupNode* newNode = new GroupNode(groupNumber);
    if (tail) {
        tail->next = newNode;
        newNode->prev = tail;
    }
    else {
        head = newNode;
    }
    tail = newNode;
}

// Функция для удаления группы по номеру
void GroupList::removeGroup(int groupNumber) {
    for (GroupNode* current = head; current; current = current->next) {
        if (current->groupNumber == groupNumber) {
            if (current->prev) {
                current->prev->next = current->next;
            }
            else {
                head = current->next;
            }
            if (current->next) {
                current->next->prev = current->prev;
            }
            else {
                tail = current->prev;
            }
            delete current;
            cout << "Группа " << groupNumber << " удалена.\n";
            return;
        }
    }
    cout << "Группа с номером " << groupNumber << " не найдена.\n";
}

// Функция для поиска группы по номеру
GroupNode* GroupList::findGroup(int groupNumber) const {
    for (GroupNode* current = head; current; current = current->next) {
        if (current->groupNumber == groupNumber) {
            return current;
        }
    }
    return nullptr;
}

// Функция для добавления студента в группу
void GroupList::addStudentToGroup(int groupNumber, const char* studentName, const int* grades, float stipend, const char* phoneNumber) {
    if (GroupNode* group = findGroup(groupNumber)) {
        group->students.addStudent(studentName, grades, stipend, phoneNumber, groupNumber);
    }
    else {
        cout << "Группа с номером " << groupNumber << " не найдена.\n";
    }
}

// Функция для удаления студента из группы
void GroupList::removeStudentFromGroup(int groupNumber, int studentId) {
    if (GroupNode* group = findGroup(groupNumber)) {
        group->students.removeStudent(studentId);
    }
    else {
        cout << "Группа с номером " << groupNumber << " не найдена.\n";
    }
}

// Функция для удаления всех студентов из группы
void GroupList::removeAllStudentsFromGroup(int groupNumber) {
    if (GroupNode* group = findGroup(groupNumber)) {
        group->students.removeAllStudents();
        cout << "Все студенты из группы " << groupNumber << " удалены.\n";
    }
    else {
        cout << "Группа с номером " << groupNumber << " не найдена.\n";
    }
}

// Функция для удаления всех групп и студентов
void GroupList::removeAllGroup() {
    GroupNode* current = head;
    while (current != nullptr) {
        GroupNode* toDelete = current;
        current = current->next;
        delete toDelete;
    }
    head = tail = nullptr;
    cout << "Все студенты из группы удалены.\n";
}

// Функция для печати номеров всех групп
void GroupList::printAllGroupNumbers() const {
    cout << "Список всех групп потока:\n";
    for (GroupNode* current = head; current; current = current->next) {
        cout << current->groupNumber << "\n";
    }
}

// Функция для печати всех групп и их студентов
void GroupList::printAllGroups() const {
    for (GroupNode* current = head; current; current = current->next) {
        current->printStudents();
    }
}

// Функция для вычисления общей суммы стипендий во всех группах
float GroupList::calculateTotalScholarship() const {
    float total = 0;
    for (GroupNode* current = head; current; current = current->next) {
        total += current->calculateTotalScholarship();
    }
    return total;
}

// Функция для проверки, пуст ли список групп
bool GroupList::isEmpty() const {
    return head == nullptr;
}

// Функция для печати процента стипендий по каждой группе
void GroupList::printGroupScholarshipPercentage() const {
    float totalScholarship = calculateTotalScholarship();
    for (GroupNode* current = head; current; current = current->next) {
        float groupTotal = current->calculateTotalScholarship();
        float percentage = (totalScholarship == 0) ? 0 : (groupTotal / totalScholarship) * 100;
        cout << "Группа " << current->groupNumber << ": " << percentage << "%\n";
    }
}

// Функция для сохранения данных всех групп в файл
void GroupList::saveToFile(const char* filename) const {
    string fullFilename = filename;
    if (fullFilename.find(".txt") == string::npos) {
        fullFilename += ".txt"; // Добавляем .txt, если не указано
    }

    ofstream outFile(fullFilename);
    if (outFile) {
        for (GroupNode* current = head; current; current = current->next) {
            current->saveToFile(outFile);
        }
        cout << "Данные сохранены в файл " << fullFilename << ".\n";
    }
    else {
        cout << "Ошибка при открытии файла " << fullFilename << ".\n";
    }
}

// Функция для загрузки данных всех групп из файла
void GroupList::loadFromFile(const char* filename) {
    string fullFilename = filename;
    if (fullFilename.find(".txt") == string::npos) {
        fullFilename += ".txt"; // Добавляем .txt, если не указано
    }

    ifstream inFile(fullFilename);
    if (inFile) {
        removeAllGroup(); // Очистка всех текущих данных перед загрузкой
        while (!inFile.eof()) {
            int groupNumber;
            inFile >> groupNumber;
            if (inFile.fail()) break; // Проверка на ошибки ввода
            inFile.ignore(); // Пропуск символа новой строки

            GroupNode* newGroup = new GroupNode(groupNumber);
            if (tail) {
                tail->next = newGroup;
                newGroup->prev = tail;
            }
            else {
                head = newGroup;
            }
            tail = newGroup;

            newGroup->loadFromFile(inFile, groupNumber);
        }
        cout << "Данные загружены из файла " << fullFilename << ".\n";
    }
    else {
        cout << "Ошибка при открытии файла " << fullFilename << ".\n";
    }
}

