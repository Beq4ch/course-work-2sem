#include "StudentGroupManagement.h"
void menu()
{
	cout << "1) Добавить группу" << endl;
	cout << "2) Добавить студента" << endl;
	cout << "3) Редактировать группу" << endl;
	cout << "---" << endl;
	cout << "4) Вывести все группы" << endl;
	cout << "5) Вывести выбранную группу" << endl;
	cout << "---" << endl;
	cout << "6) Добавить группы из файла" << endl;
	cout << "7) Вывести группы в файла" << endl;
	cout << "---" << endl;
	cout << "8) Вывести в алфавитном порядке список той группы, в которой средний балл является максимальным по потоку" << endl;
	cout << "---" << endl;
	cout << "0) Выход" << endl;
}

int main()
{
	SetConsoleCP(1251); // Для русского языка
	SetConsoleOutputCP(1251); // Для русского языка
	Group* head = nullptr;
	Group* tail = nullptr;

	int selection; // Переменная для меню

	do {
		system("cls");
		menu();
		cin >> selection;
		switch (selection) {
		case 1:
		{
			Group* p = addGroup();
			if (p->head == nullptr) // Создание первой группы
			{
				head = p;
				tail = p;
				cout << "Группа № " << p->number << " успешно добавлена" << endl;
				system("pause");
				break;
			}
			if (isGroupDuplicate(head, p)) // Проверка на повторяющуюся группу
			{
				cout << "Группа № " << p->number << " уже существует" << endl;
				system("pause");
				break;
			}
			if (p->number > head->number) // Если вводимое число больше первого эл-та в списке
			{
				if (p->number < tail->number) // Если меньше последнего числа в списке возрастания
				{
					Group* temp = head;
					while (temp->next != nullptr) // Идём от начало списка возрастания и ищем место куда должен встать элемент
					{
						if (p->number > temp->next->number)// Идём по списку и сравниваем
							temp = temp->next;
						else
						{
							Group* temp2 = temp->next;
							temp->next = p;
							temp = temp->next;
							temp->next = temp2;
							break;
						}
					}
				}
				else //Если число больше предыдущего то просто добавляем его
				{
					tail->next = p;
					tail = tail->next;
					tail->next = nullptr;
				}
			}
			else // Если число меньше первого эл-та, ставим его в начало
			{
				Group* temp = head;
				head = p;
				head->next = temp;
			}
			cout << "Группа № " << p->number << " успешно добавлена" << endl;
			system("pause");
			break;
		}
		case 2:
		{
			if (isGroupExists(head))
				addStudent(head);
			break;
		}
		case 3:
		{
			if (isGroupExists(head))
			{
				Group* edit = selectGroup(head);
				if (edit == nullptr) // Если выбранная не сущ. группа
					break;
				cout << "1) Редактировать студентов" << endl;
				cout << "0) Удалить группу" << endl;
				int k;
				cin >> k;
				switch (k)
				{
				case 0:
				{
					cout << "Вы точно хотите удалить группу № " << edit->number << endl;
					cout << " 1) Да" << endl;
					cout << " 2) Нет" << endl;
					int l;	cin >> l;
					if (l == 2)
						break;
					else if (l == 1)
					{
						deleteAllStudents(edit); // Удаляем всех студентов в группе
						if (edit == head) // Изменение первого элемента потока
						{
							if (head->next == nullptr) // Проверка ,если группа только одна
							{
								delete head;
								head = nullptr;
							}
							else
							{
								Group* temp = head->next;
								delete head;
								head = temp;
							}
						}
						else if (edit == tail) // Изменение последнего элемента потока
						{
							Group* temp = head;
							while (temp->next != tail)
								temp = temp->next;
							delete tail;
							tail = temp;
							tail->next = nullptr;
						}
					}
					else
						break;
					break;
				}
				case 1:
				{
					if (edit->head == nullptr)
					{
						cout << "В группе нет студентов" << endl;
						system("pause");
						break;
					}
					editStudent(edit);
					break;
				}
				default:
					break;
				}
			}
			break;
		}
		case 4:
		{
			if (isGroupExists(head))
				printAllGroups(head);
			break;
		}
		case 5:
		{
			if (isGroupExists(head))
				printGroup(head);
			break;
		}
		case 6:
		{
			string filename;
			cout << "Имя файла должно содержать только номер группы(без .txt)" << endl;
			cout << "Введите название файла:" << endl;

			cin >> filename;
			Group* p = new Group;
			p->number = atoi(filename.c_str());
			p->head = nullptr;
			p->next = nullptr;
			if (head == nullptr) // Создание первой группы
			{
				head = p;
				tail = p;
				readStudentsFromFile(p, filename);
				if (p->head == nullptr)
					break;
				cout << "Группа № " << p->number << " успешно добавлена" << endl;
				system("pause");
				break;
			}
			if (isGroupDuplicate(head, p)) // Проверка на повторяющуюся группу
			{
				cout << "Группа № " << p->number << " уже существует" << endl;
				system("pause");
				delete p;
				break;
			}
			if (p->number > head->number) // Если вводимое число больше первого эл-та в списке
			{
				if (p->number < tail->number) // Если меньше последнего числа в списке возрастания
				{
					Group* temp = head;
					while (temp->next != nullptr) // Идём от начало списка возрастания и ищем место куда должен встать элемент
					{
						if (p->number > temp->next->number)// Идём по списку и сравниваем
							temp = temp->next;
						else
						{
							Group* temp2 = temp->next;
							temp->next = p;
							temp = temp->next;
							temp->next = temp2;
							break;
						}
					}
				}
				else //Если число больше предыдущего то просто добавляем его
				{
					tail->next = p;
					tail = tail->next;
					tail->next = nullptr;
				}
			}
			else // Если число меньше первого эл-та, ставим его в начало
			{
				Group* temp = head;
				head = p;
				head->next = temp;
			}
			readStudentsFromFile(p, filename);
			if (p->head == nullptr)
				break;

			cout << "Группа № " << p->number << " успешно добавлена" << endl;
			system("pause");
			break;
		}
		case 7:
		{
			if (isGroupExists(head))
				writeGroupsToFile(head);
			break;
		}
		case 8:
		{
			if (isGroupExists(head))
				printGroupWithHighestAverage(head);
			break;
		}
		default:
			break;
		}
	} while (selection != 0);
}