#include "group.h"

GroupNode::GroupNode(int num) : groupNumber(num), next(nullptr), prev(nullptr) {}

void GroupNode::printStudents() {
    cout << "������ " << groupNumber << ":\n";
    students.printAllStudents();
}

float GroupNode::calculateTotalScholarship() const {
    return students.calculateTotalScholarship();
}

void GroupNode::saveToFile(ofstream& outFile) const {
    outFile << groupNumber << "\n";
    students.saveToFile(outFile);
}

void GroupNode::loadFromFile(ifstream& inFile) {
    students.loadFromFile(inFile);
}

GroupList::GroupList() : head(nullptr), tail(nullptr) {}

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
            cout << "������ " << groupNumber << " �������.\n";
            return;
        }
    }
    cout << "������ � ������� " << groupNumber << " �� �������.\n";
}

GroupNode* GroupList::findGroup(int groupNumber) const {
    for (GroupNode* current = head; current; current = current->next) {
        if (current->groupNumber == groupNumber) {
            return current;
        }
    }
    return nullptr;
}

void GroupList::addStudentToGroup(int groupNumber, const char* studentName, const int* grades, float stipend, const char* phoneNumber) {
    if (GroupNode* group = findGroup(groupNumber)) {
        group->students.addStudent(studentName, grades, stipend, phoneNumber);
    }
    else {
        cout << "������ � ������� " << groupNumber << " �� �������.\n";
    }
}

void GroupList::removeStudentFromGroup(int groupNumber, int studentId) {
    if (GroupNode* group = findGroup(groupNumber)) {
        group->students.removeStudent(studentId);
    }
    else {
        cout << "������ � ������� " << groupNumber << " �� �������.\n";
    }
}

void GroupList::removeAllStudentsFromGroup(int groupNumber) {
    if (GroupNode* group = findGroup(groupNumber)) {
        group->students.removeAllStudents();
        cout << "��� �������� �� ������ " << groupNumber << " �������.\n";
    }
    else {
        cout << "������ � ������� " << groupNumber << " �� �������.\n";
    }
}

void GroupList::removeAllGroup() {
    GroupNode* current = head;
    while (current != nullptr) {
        GroupNode* toDelete = current;
        current = current->next;
        delete toDelete;
    }
    head = tail = nullptr;
    cout << "��� �������� �� ������ �������.\n";
}

void GroupList::editStudentInGroup(int groupNumber, int studentId, const char* studentName, const int* grades, float stipend, const char* phoneNumber) {
    if (GroupNode* group = findGroup(groupNumber)) {
        group->students.editStudent(studentId, studentName, grades, stipend, phoneNumber);
    }
    else {
        cout << "������ � ������� " << groupNumber << " �� �������.\n";
    }
}

void GroupList::printAllGroupNumbers() const {
    cout << "������ ���� ����� ������:\n";
    for (GroupNode* current = head; current; current = current->next) {
        cout << current->groupNumber << "\n";
    }
}

void GroupList::printAllGroups() const {
    for (GroupNode* current = head; current; current = current->next) {
        current->printStudents();
    }
}

float GroupList::calculateTotalScholarship() const {
    float total = 0;
    for (GroupNode* current = head; current; current = current->next) {
        total += current->calculateTotalScholarship();
    }
    return total;
}

bool GroupList::isEmpty() const {
    return head == nullptr;
}

void GroupList::printGroupScholarshipPercentage() const {
    float totalScholarship = calculateTotalScholarship();
    for (GroupNode* current = head; current; current = current->next) {
        float groupTotal = current->calculateTotalScholarship();
        float percentage = (totalScholarship == 0) ? 0 : (groupTotal / totalScholarship) * 100;
        cout << "������ " << current->groupNumber << ": " << percentage << "%\n";
    }
}

void GroupList::saveToFile(const char* filename) const {
    string fullFilename = filename;
    if (fullFilename.find(".txt") == string::npos) {
        fullFilename += ".txt"; // ��������� .txt, ���� �� �������
    }

    ofstream outFile(fullFilename);
    if (outFile) {
        for (GroupNode* current = head; current; current = current->next) {
            current->saveToFile(outFile);
        }
        cout << "������ ��������� � ���� " << fullFilename << ".\n";
    }
    else {
        cout << "������ ��� �������� ����� " << fullFilename << ".\n";
    }
}

void GroupList::loadFromFile(const char* filename) {
    string fullFilename = filename;
    if (fullFilename.find(".txt") == string::npos) {
        fullFilename += ".txt"; // ��������� .txt, ���� �� �������
    }

    ifstream inFile(fullFilename);
    if (inFile) {
        while (true) {
            int groupNumber;
            inFile >> groupNumber;
            if (inFile.eof()) {
                break; // ����� �����
            }
            inFile.ignore(); // ������� ������� ����� ������

            GroupNode* newGroup = new GroupNode(groupNumber);
            if (tail) {
                tail->next = newGroup;
                newGroup->prev = tail;
            }
            else {
                head = newGroup;
            }
            tail = newGroup;

            newGroup->loadFromFile(inFile);
        }
        cout << "������ ��������� �� ����� " << fullFilename << ".\n";
    }
    else {
        cout << "������ ��� �������� ����� " << fullFilename << ".\n";
    }
}
