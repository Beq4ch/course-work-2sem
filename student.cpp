#include "student.h"

// ������� ��� ���������� ���-�������� ����� ��������
unsigned int hashStudentName(const char* name) {
    unsigned int hash = 0;
    while (*name) {
        hash = (hash * 31) + static_cast<unsigned int>(*name);
        ++name;
    }
    return hash;
}

// ����������� ��������� Student
Student::Student(int studentId, const char* studentName, const int* studentGrades, float stipend, const char* extra, int group)
    : id(studentId), scholarship(stipend), groupNumber(group) {
    strncpy_s(name, studentName, MAX_NAME_LENGTH - 1);
    name[MAX_NAME_LENGTH - 1] = '\0';
    for (int j = 0; j < NUM_GRADES; ++j) {
        grades[j] = studentGrades ? studentGrades[j] : 0;
    }
    strncpy_s(phoneNumber, extra, PHONE_NUMBER_LENGTH - 1);
    phoneNumber[PHONE_NUMBER_LENGTH - 1] = '\0';
}


// ����������� ���-������� � ��������������
StudentHashTable::StudentHashTable(int initialSize)
    : tableSize(initialSize), numElements(0), nextId(1) {
    table = new StudentNode * [tableSize]();
}

// ���������� ��� ������������ ������ ���-�������
StudentHashTable::~StudentHashTable() {
    removeAllStudents();
    delete[] table;
}

// ���-������� ��� ���������� ������� �� ������ ����� ��������
unsigned int StudentHashTable::hashFunction(const char* name) const {
    return hashStudentName(name) % tableSize;
}

// ������� ��� ���������� �������� � ���-�������
void StudentHashTable::addStudent(const char* name, const int* grades, float stipend, const char* phoneNumber, int groupNumber) {
    if (numElements > tableSize * 0.75) {
        resizeTable();
    }
    unsigned int hash = hashFunction(name);
    Student newStudent(nextId++, name, grades, stipend, phoneNumber, groupNumber);
    StudentNode* newNode = new StudentNode(newStudent);

    if (!table[hash]) {
        table[hash] = newNode;
    }
    else {
        StudentNode* current = table[hash];
        while (current->next) {
            current = current->next;
        }
        current->next = newNode;
    }
    numElements++;
}

// ������� ��� ���������� ������� �������
void StudentHashTable::resizeTable() {
    int newSize = tableSize * 2;
    StudentNode** newTable = new StudentNode * [newSize]();

    for (int i = 0; i < tableSize; ++i) {
        StudentNode* current = table[i];
        while (current) {
            unsigned int newHash = hashStudentName(current->student.name) % newSize;
            StudentNode* next = current->next;
            current->next = newTable[newHash];
            newTable[newHash] = current;
            current = next;
        }
    }

    delete[] table;
    table = newTable;
    tableSize = newSize;
}

// ������� ��� ������ �������� �� ��������������
Student* StudentHashTable::findStudent(int id) const {
    for (int i = 0; i < tableSize; ++i) {
        StudentNode* current = table[i];
        while (current) {
            if (current->student.id == id) {
                return &current->student;
            }
            current = current->next;
        }
    }
    return nullptr;
}

// ������� ��� �������� �������� �� ��������������
void StudentHashTable::removeStudent(int id) {
    for (int i = 0; i < tableSize; ++i) {
        StudentNode* current = table[i];
        StudentNode* prev = nullptr;
        while (current) {
            if (current->student.id == id) {
                if (prev) {
                    prev->next = current->next;
                }
                else {
                    table[i] = current->next;
                }
                delete current;
                numElements--;
                cout << "������� � ID " << id << " ������.\n";
                return;
            }
            prev = current;
            current = current->next;
        }
    }
    cout << "������� � ID " << id << " �� ������.\n";
}

// ������� ��� �������� ���� ��������� �� �������
void StudentHashTable::removeAllStudents() {
    for (int i = 0; i < tableSize; ++i) {
        StudentNode* current = table[i];
        while (current) {
            StudentNode* toDelete = current;
            current = current->next;
            delete toDelete;
        }
        table[i] = nullptr;
    }
    numElements = 0;
    nextId = 1;
}

// ������� ��� ���������� ����� ����� ���������
float StudentHashTable::calculateTotalScholarship() const {
    float total = 0;
    for (int i = 0; i < tableSize; ++i) {
        StudentNode* current = table[i];
        while (current) {
            total += current->student.scholarship;
            current = current->next;
        }
    }
    return total;
}

// ������� ��� ������ ���� ���������
void StudentHashTable::printAllStudents() const {
    if (isEmpty()) {
        cout << "������ ��������� ����\n";
        return;
    }
    for (int i = 0; i < tableSize; ++i) {
        StudentNode* current = table[i];
        while (current) {
            cout << "ID: " << current->student.id << "\n";
            cout << "���: " << current->student.name << "\n";
            cout << "������: ";
            for (int j = 0; j < NUM_GRADES; ++j) {
                cout << current->student.grades[j] << " ";
            }
            cout << "\n���������: " << current->student.scholarship << "\n";
            cout << "����� ��������: " << current->student.phoneNumber << "\n";
            cout << "------------------------\n";
            current = current->next;
        }
    }
}

// ������� ��� ���������� ������ ������� � ����
void StudentHashTable::saveToFile(ofstream& outFile) const {
    for (int i = 0; i < tableSize; ++i) {
        StudentNode* current = table[i];
        while (current) {
            outFile << current->student.id << "\n";
            outFile << current->student.name << "\n";
            for (int j = 0; j < NUM_GRADES; ++j) {
                outFile << current->student.grades[j] << " ";
            }
            outFile << "\n";
            outFile << current->student.scholarship << "\n";
            outFile << current->student.phoneNumber << "\n";
            current = current->next;
        }
    }
    outFile << "#\n";
}

void StudentHashTable::filterStudents(const char* name, const char* phoneNumber, const int* grades, float scholarship, int groupNumber) const {
    for (int i = 0; i < tableSize; ++i) {
        StudentNode* current = table[i];
        while (current) {
            bool match = true;
            if (name && strcmp(current->student.name, name) != 0) {
                match = false;
            }
            if (phoneNumber && strcmp(current->student.phoneNumber, phoneNumber) != 0) {
                match = false;
            }
            if (grades) {
                for (int j = 0; j < NUM_GRADES; ++j) {
                    if (current->student.grades[j] != grades[j]) {
                        match = false;
                        break;
                    }
                }
            }
            if (scholarship >= 0 && current->student.scholarship != scholarship) {
                match = false;
            }
            if (groupNumber >= 0 && current->student.groupNumber != groupNumber) {
                match = false;
            }
            if (match) {
                cout << "������: " << current->student.groupNumber << "\n";
                cout << "ID: " << current->student.id << "\n";
                cout << "���: " << current->student.name << "\n";
                cout << "������: ";
                for (int j = 0; j < NUM_GRADES; ++j) {
                    cout << current->student.grades[j] << " ";
                }
                cout << "\n���������: " << current->student.scholarship << "\n";
                cout << "����� ��������: " << current->student.phoneNumber << "\n";
                cout << "------------------------\n";
            }
            current = current->next;
        }
    }
}



void StudentHashTable::moveStudentToGroup(int id, StudentHashTable& newGroupTable, int newGroupNumber) {
    Student* student = findStudent(id);
    if (student) {
        // ��������� �������� � ����� ������
        newGroupTable.addStudent(student->name, student->grades, student->scholarship, student->phoneNumber, newGroupNumber);
        // ������� �������� �� ������� ������
        removeStudent(id);
        cout << "������� � ID " << id << " ��������� � ������ " << newGroupNumber << ".\n";
    }
    else {
        cout << "������� � ID " << id << " �� ������.\n";
    }
}


// ������� ��� �������� ������ ������� �� �����
void StudentHashTable::loadFromFile(ifstream& inFile, int groupNumber) {
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

        addStudent(studentName, grades, stipend, phoneNumber, groupNumber);
        if (id >= nextId) {
            nextId = id + 1;
        }
    }
}


// ������� ��� ��������, ����� �� �������
bool StudentHashTable::isEmpty() const {
    return numElements == 0;
}
