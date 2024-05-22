#include "student.h"

// Функция для вычисления хэш-значения имени студента
unsigned int hashStudentName(const char* name) {
    unsigned int hash = 0;
    while (*name) {
        hash = (hash * 31) + static_cast<unsigned int>(*name);
        ++name;
    }
    return hash;
}

// Конструктор структуры Student
Student::Student(int studentId, const char* studentName, const int* studentGrades, float stipend, const char* extra)
    : id(studentId), scholarship(stipend) {
    strncpy_s(name, studentName, MAX_NAME_LENGTH - 1);
    name[MAX_NAME_LENGTH - 1] = '\0';
    for (int j = 0; j < NUM_GRADES; ++j) {
        grades[j] = studentGrades ? studentGrades[j] : 0;
    }
    strncpy_s(phoneNumber, extra, PHONE_NUMBER_LENGTH - 1);
    phoneNumber[PHONE_NUMBER_LENGTH - 1] = '\0';
}

// Конструктор хэш-таблицы с инициализацией
StudentHashTable::StudentHashTable(int initialSize)
    : tableSize(initialSize), numElements(0), nextId(1) {
    table = new Student[tableSize]();
    isOccupied = new bool[tableSize]();
}

// Деструктор для освобождения памяти хэш-таблицы
StudentHashTable::~StudentHashTable() {
    delete[] table;
    delete[] isOccupied;
}

// Хэш-функция для вычисления индекса на основе имени студента
unsigned int StudentHashTable::hashFunction(const char* name) const {
    return hashStudentName(name) % tableSize;
}

// Линейное пробирование для разрешения коллизий
int StudentHashTable::linearProbe(int hash, int i) const {
    return (hash + i) % tableSize;
}

// Функция для добавления студента в хэш-таблицу
void StudentHashTable::addStudent(const char* name, const int* grades, float stipend, const char* phoneNumber) {
    if (numElements > tableSize * 0.75) {
        resizeTable();
    }
    unsigned int hash = hashFunction(name);
    int i = 0;
    while (isOccupied[linearProbe(hash, i)]) {
        ++i;
    }
    int index = linearProbe(hash, i);
    table[index] = Student(nextId++, name, grades, stipend, phoneNumber);
    isOccupied[index] = true;
    numElements++;
}

// Функция для увеличения размера таблицы
void StudentHashTable::resizeTable() {
    int newSize = tableSize * 2;
    Student* newTable = new Student[newSize]();
    bool* newIsOccupied = new bool[newSize]();

    for (int i = 0; i < tableSize; ++i) {
        if (isOccupied[i]) {
            unsigned int hash = hashFunction(table[i].name);
            int j = 0;
            while (newIsOccupied[linearProbe(hash, j)]) {
                ++j;
            }
            int newIndex = linearProbe(hash, j);
            newTable[newIndex] = table[i];
            newIsOccupied[newIndex] = true;
        }
    }

    delete[] table;
    delete[] isOccupied;

    table = newTable;
    isOccupied = newIsOccupied;
    tableSize = newSize;
}

// Функция для поиска студента по идентификатору
Student* StudentHashTable::findStudent(int id) const {
    for (int i = 0; i < tableSize; ++i) {
        if (isOccupied[i] && table[i].id == id) {
            return &table[i];
        }
    }
    return nullptr;
}

// Функция для удаления студента по идентификатору
void StudentHashTable::removeStudent(int id) {
    for (int i = 0; i < tableSize; ++i) {
        if (isOccupied[i] && table[i].id == id) {
            isOccupied[i] = false;
            numElements--;
            table[i] = Student();
            cout << "Студент с ID " << id << " удален.\n";
            return;
        }
    }
    cout << "Студент с ID " << id << " не найден.\n";
}

// Функция для удаления всех студентов из таблицы
void StudentHashTable::removeAllStudents() {
    for (int i = 0; i < tableSize; ++i) {
        isOccupied[i] = false;
        table[i] = Student();
    }
    numElements = 0;
    nextId = 1;
}

// Функция для редактирования данных студента
void StudentHashTable::editStudent(int id, const char* name, const int* grades, float stipend, const char* phoneNumber) {
    Student* student = findStudent(id);
    if (student) {
        strncpy_s(student->name, name, MAX_NAME_LENGTH - 1);
        student->name[MAX_NAME_LENGTH - 1] = '\0';
        for (int i = 0; i < NUM_GRADES; ++i) {
            student->grades[i] = grades[i];
        }
        student->scholarship = stipend;
        strncpy_s(student->phoneNumber, phoneNumber, PHONE_NUMBER_LENGTH - 1);
        student->phoneNumber[PHONE_NUMBER_LENGTH - 1] = '\0';
        cout << "Данные студента с ID " << id << " обновлены.\n";
    }
    else {
        cout << "Студент с ID " << id << " не найден.\n";
    }
}

// Функция для вычисления общей суммы стипендий
float StudentHashTable::calculateTotalScholarship() const {
    float total = 0;
    for (int i = 0; i < tableSize; ++i) {
        if (isOccupied[i]) {
            total += table[i].scholarship;
        }
    }
    return total;
}

// Функция для печати всех студентов
void StudentHashTable::printAllStudents() const {
    if (isEmpty()) {
        cout << "Список студентов пуст\n";
        return;
    }
    for (int i = 0; i < tableSize; ++i) {
        if (isOccupied[i]) {
            cout << "ID: " << table[i].id << "\n";
            cout << "ФИО: " << table[i].name << "\n";
            cout << "Оценки: ";
            for (int j = 0; j < NUM_GRADES; ++j) {
                cout << table[i].grades[j] << " ";
            }
            cout << "\nСтипендия: " << table[i].scholarship << "\n";
            cout << "Номер телефона: " << table[i].phoneNumber << "\n";
            cout << "------------------------\n";
        }
    }
}

// Функция для сохранения данных таблицы в файл
void StudentHashTable::saveToFile(ofstream& outFile) const {
    for (int i = 0; i < tableSize; ++i) {
        if (isOccupied[i]) {
            outFile << table[i].id << "\n";
            outFile << table[i].name << "\n";
            for (int j = 0; j < NUM_GRADES; ++j) {
                outFile << table[i].grades[j] << " ";
            }
            outFile << "\n";
            outFile << table[i].scholarship << "\n";
            outFile << table[i].phoneNumber << "\n";
        }
    }
    outFile << "#\n";
}

// Функция для загрузки данных таблицы из файла
void StudentHashTable::loadFromFile(ifstream& inFile) {
    char line[MAX_NAME_LENGTH];
    nextId = 1;
    while (true) {
        inFile.getline(line, MAX_NAME_LENGTH);
        if (strcmp(line, "#") == 0 || inFile.eof()) {
            break;
        }

        int id = atoi(line);
        inFile.getline(line, MAX_NAME_LENGTH);
        char studentName[MAX_NAME_LENGTH];
        strncpy_s(studentName, line, MAX_NAME_LENGTH);

        int grades[NUM_GRADES];
        for (int i = 0; i < NUM_GRADES; ++i) {
            inFile >> grades[i];
        }
        inFile.ignore();

        float stipend;
        inFile >> stipend;
        inFile.ignore();

        inFile.getline(line, PHONE_NUMBER_LENGTH);
        char phoneNumber[PHONE_NUMBER_LENGTH];
        strncpy_s(phoneNumber, line, PHONE_NUMBER_LENGTH);

        addStudent(studentName, grades, stipend, phoneNumber);
        if (id >= nextId) {
            nextId = id + 1;
        }
    }
}

// Функция для проверки, пуста ли таблица
bool StudentHashTable::isEmpty() const {
    return numElements == 0;
}
