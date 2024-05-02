#include "StudentGroupManagement.h"

//ОСНОВНЫЕ ФУНКЦИИ//
Group* addGroup() // Создание структуры группа
{
	Group* group = new Group;
	cout << "Введите группу" << endl;
	int groupNumber;
	cin >> groupNumber;
	group->number = groupNumber;
	return group;
}

void addStudent(Group* group)
{
	Group* temp1 = group;
	Group* add = nullptr;
	cout << endl;
	while (temp1 != nullptr)
	{
		cout << "| " << temp1->number << " ";
		temp1 = temp1->next;
	}
	cout << "| " << endl;
	temp1 = group;
	cout << endl;
	cout << "Введите нужную группу для вывода" << endl;
	short gr; cin >> gr;
	while (temp1 != nullptr)
	{
		if (gr == temp1->number)
			add = temp1;
		temp1 = temp1->next;
	}
	if (add == nullptr)
	{
		cout << "Такой группы нет" << endl;
		system("pause");
		return;
	}
	system("cls");
	cout << "Добавляем в группу № " << add->number << endl << endl;
	cout << "Введите ФИО студента" << endl;
	string nam, s;
	for (int i = 0; i < 3; i++)
	{
		cin >> s;
		nam += " ";
		nam += s;
	}

	cout << "Введите оценки студента за сесcию (5 Оценок)" << endl;
	int arr[5];
	int check;
	for (int i = 0; i < 5; i++)
	{
		cin >> check;
		while (check > 5 || check < 1)
		{
			cout << "Неверная оценка (0 - 5)" << endl;
			cin >> check;
		}
		arr[i] = check;
	}

	cout << "Введите размер стипендии студента" << endl;
	int stipendia; cin >> stipendia;

	Student* st = new Student;
	st->name = nam;
	for (int i = 0; i < 5; i++)
		st->grades[i] = arr[i];
	st->scholarship = stipendia;
	insertStudentSorted(add, st);
	cout << "Студент успешно добавлен" << endl;
	system("pause");
}

void insertStudentSorted(Group* group, Student* st) // Функция добавления студента в группу(В алфавитном порядке)
{
	int i = 0, l = 0;
	Student* s = group->head; // Переменная s - начало списка студентов
	if (s == nullptr) // Добавляем первого человека
	{
		group->head = st;
		st->next = nullptr;
		return;
	}
	else
	{
		while (s->name[i] == st->name[i]) // Идём по строчками, если у фамилий одинаковые буквы
			i++;
		if (st->name[i] > s->name[i]) // Если первая буква меньше первой буквы первого,то вставляем в начало 
		{
			while (true) // Идём по списку
			{
				if (s->next == nullptr)// Если след nullptr, то мы дошли до конца списка и вставляем его в конец
				{
					s->next = st;
					st->next = nullptr;
					break;
				}
				else
				{
					while (s->next->name[l] == st->name[l]) // Идём по строчками, если у фамилий одинаковые буквы
						l++;
					if (st->name[l] < s->next->name[l]) // Если меньше, то мы вставляем студента
					{
						Student* temp2 = s->next;
						s->next = st;
						st->next = temp2;
					}
				}
				l = 0;
				s = s->next;
			}
		}
		else //Вставляем в начало
		{
			Student* temp1 = group->head;
			group->head = st;
			st->next = temp1;
		}
		i = 0;
	}
}

Group* selectGroup(Group* group) // Возвращает указатель на группу
{
	Group* temp1 = group;
	cout << endl;
	while (temp1 != nullptr)
	{
		cout << "| " << temp1->number << " ";
		temp1 = temp1->next;
	}
	cout << "| " << endl;
	temp1 = group;
	cout << "Введите нужную группу для редактирования" << endl;
	short gr; cin >> gr;
	while (temp1 != nullptr)
	{
		if (gr == temp1->number)
		{
			return temp1;
		}
		temp1 = temp1->next;
	}
	cout << "Такой группы нет" << endl;
	system("pause");
	return nullptr;
}

void editStudent(Group* group)
{
	Group* edit = group;
	Student* st = group->head;
	system("cls");
	cout << endl;
	outputGroup(edit);
	cout << endl;
	cout << "Введите номер студента:" << endl;
	int stu; cin >> stu;

	for (int i = 1; i < stu; i++) // Поиск студента
		st = st->next;

	cout << "1) Редактировать студента" << endl;
	cout << "0) Удалить студента" << endl;
	int p; cin >> p;
	switch (p)
	{
	case 0:
	{
		cout << "Вы точно хотите удалить студента № " << stu << endl;
		cout << " 1) Да" << endl;
		cout << " 2) Нет" << endl;
		int l;	cin >> l;
		if (l == 2)
			break;
		else if (l == 1)
			deleteStudent(group, stu);
		else
			break;
		cout << endl;
		outputGroup(edit);
		system("pause");
		break;
	}
	case 1:
	{
		cout << st->name << "  ";
		for (int i = 0; i < 5; i++)
			cout << st->grades[i] << " ";
		cout << " ";
		cout << st->scholarship << endl;

		cout << "Введите новые оценки студента за сесcию (5 Оценок)" << endl;
		int arr[5];
		for (int i = 0; i < 5; i++)
			cin >> arr[i];
		cout << "Введите новый размер стипендии студента" << endl;
		int stipendia; cin >> stipendia;

		for (int i = 0; i < 5; i++)
			st->grades[i] = arr[i];
		st->scholarship = stipendia;

		cout << "Студент успешно обновлен" << endl << endl;;
		cout << st->name << "  ";
		for (int i = 0; i < 5; i++)
			cout << st->grades[i] << " ";
		cout << " ";
		cout << st->scholarship << endl;
		system("pause");
		break;
	}

	default:
		break;
	}
}

void deleteAllStudents(Group* group)// Удаление всех студентов в группе
{
	Student* st = group->head;
	while (st != nullptr)
	{
		Student* del = st->next;
		st->next = nullptr;
		delete st;
		st = nullptr;
		st = del;
	}
}

void deleteStudent(Group* group, int pos) // Удаление студента (Группа и номер позиции студента)
{
	Student* st = group->head;
	if (pos == 1) // Удаление первого студента
	{
		group->head = group->head->next; //Делаем второй элемент первым
		delete st; // Удаляем первый элемент
		return;
	}
	for (int i = 1; i < pos - 1; i++) // Поиск эл-та который нужно удалить		
		st = st->next;
	if (st->next->next == nullptr) // Удаляемый элемент последний
	{
		delete (st->next); // Удаляем элемент
		st->next = nullptr;
	}
	else
	{
		Student* temp = st->next->next; // Сохраняем элемент после удаляемого
		delete (st->next); // Удаляем элемент
		st->next = temp; // Создаём связь
	}
}

void printAllGroups(Group* group)
{
	Group* temp1 = group;
	cout << endl;
	while (temp1 != nullptr)
	{
		cout << endl;
		outputGroup(temp1);
		temp1 = temp1->next;
	}
	system("pause");
}

void printGroup(Group* group)
{
	Group* temp1 = group;
	cout << endl;
	while (temp1 != nullptr)
	{
		cout << "| " << temp1->number << " ";
		temp1 = temp1->next;
	}
	cout << "| " << endl;
	cout << "Введите нужную группу для вывода" << endl;
	short gr; cin >> gr;
	temp1 = group;
	while (temp1 != nullptr)
	{
		if (gr == temp1->number)
		{
			system("cls");
			outputGroup(temp1);
			system("pause");
			return;
		}
		temp1 = temp1->next;
	}
	cout << "Такой группы нет" << endl;
}

void readStudentsFromFile(Group* group, const string& filename)
{
	string name, man, stip;
	string file = filename + ".txt";
	fstream stud;
	stud.open(file);
	if (!stud.is_open()) // Проверка на открытие файла
	{
		cout << "Ошибка открытия файла!" << endl;
		system("pause");
		return;
	}
	while (getline(stud, name))
	{
		Student* st = new Student;
		int k = 0;
		while (!isdigit(name[k]))// Обработка ФИО
		{
			man += name[k];
			k++;
		}
		k = 0;
		int lengths = man.length();
		man.erase(man.length() - 1, 2);
		st->name = man;// Присваиваем ФИО
		man.clear();
		for (int i = 0; i < 5; i++) // Обработка Оценок
		{
			st->grades[i] = name[lengths + k] - '0';
			k += 2;
		}
		lengths += k;
		k = 0;
		while (name[lengths] != '\0') // Обработка стипендию
		{
			stip += name[lengths];
			lengths++;
		}
		st->scholarship = atoi(stip.c_str());
		stip.clear();
		insertStudentSorted(group, st);
	}
	stud.close();
}


void writeGroupsToFile(Group* group)
{
	string txt = ".txt";
	string filename;
	cout << "Введите название файла" << endl;
	cin >> filename;
	filename += txt;

	ofstream students;
	students.open(filename);
	if (!students.is_open()) // Проверка на открытие файла
	{
		cout << "Ошибка открытия файла!" << endl;
		system("pause");
		return;
	}
	Group* temp1 = group;
	cout << endl;
	while (temp1 != nullptr)
	{
		students << endl;
		Student* st = temp1->head;
		students << temp1->number << endl;
		if (temp1->head == nullptr)
			students << "В группе нет студентов" << endl;

		students << endl;
		int k = 1;
		while (st != nullptr)
		{
			students << k << ") " << st->name << "  ";
			for (int i = 0; i < 5; i++)
				students << st->grades[i] << " ";
			students << " ";
			students << st->scholarship << endl;
			st = st->next;
			k++;
		}
		k = 0;
		students << endl;
		temp1 = temp1->next;
	}
	cout << "Весь поток выведен в файл " << filename << endl;
	students.close();
	system("pause");
}

void printGroupWithHighestAverage(Group* group)
{
	int averageall = 0;
	Group* temp = group;
	Group* averout = nullptr;
	while (temp != nullptr)
	{
		int k = 0;
		int avergroup = 0;
		Student* st = temp->head;
		while (st != nullptr)
		{
			k++;
			for (int i = 0; i < 5; i++)
				avergroup += st->grades[i];
			st = st->next;
		}
		if ((temp->head != nullptr) && ((avergroup / k) > averageall))
		{
			averageall = (avergroup / k);
			averout = temp;
		}
		temp = temp->next;
	}
	system("cls");
	if (averout == nullptr)
	{
		cout << "В группах нет студентов" << endl;
		system("pause");
		return;
	}

	outputGroup(averout);
	system("pause");
}

void outputGroup(Group* group) // Вывод группы
{
	Student* st = group->head;
	cout << group->number << endl;
	if (group->head == nullptr)
	{
		cout << "В группе нет студентов" << endl;
		return;
	}
	cout << endl;
	int k = 1;
	while (st != nullptr)
	{
		cout << k << ") " << st->name << "  ";
		for (int i = 0; i < 5; i++)
			cout << st->grades[i] << " ";
		cout << " ";
		cout << st->scholarship << endl;
		st = st->next;
		k++;
	}
	k = 0;
	cout << endl;
}

//ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ ДЛЯ УМЕНЬШЕНИЯ КОДА//

bool isGroupExists(Group* group) //Функция для проверки существования групп
{
	if (group == nullptr)
	{
		cout << "Групп нет, сначала добавьте их" << endl;
		system("pause");
		return false;
	}
	else
		return true;
}
bool isGroupDuplicate(Group* head, Group* p)
{
	Group* temp = head;
	while (temp != nullptr)
	{
		if (temp->number == p->number)
			return 1;
		temp = temp->next;
	}
	return 0;
}