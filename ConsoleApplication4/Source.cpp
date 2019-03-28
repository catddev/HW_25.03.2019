#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include<math.h>
#include<Windows.h>
#include<ctime>
#include<cstring>
#include<fstream>
using namespace std;

int current_size = 0;
int buffer_size = 0;

//1.	Разработайте программу «Телефонный справочник».
//Создайте структуру «Запись»(номер телефона, ФИО).
//Номер телефона представлен битовыми полями(код города и три двузначных числа).
//Б)***Создайте массив экземпляров структуры «Запись» и реализуйте для него следующие функции :
//1	Добавить запись
//2	Отредактировать запись
//3	Удалить запись
//4	Печать всех телефонов
//5	Сортировка по ФИО
//6 Сортировка по номеру телефона

struct Record {
	char fio[100];
	int kod : 15; //14+1
	int part1 : 8; //7+1 иначе ошибка в считывании
	int part2 : 8;
	int part3 : 8;

	void print() {
		cout << fio << endl;
		cout << "(" << kod << ")" << part1 << "-" << part2 << "-" << part3 << endl;
	}
};

template<typename T>//1
void add(T*&rs, T r) {
	if (buffer_size == 0)
	{
		buffer_size = 4;
		rs = new T[buffer_size];
	}
	else
	{
		if (current_size == buffer_size)
		{
			buffer_size *= 2;
			T*tmp = new T[buffer_size];
			for (int i = 0; i < current_size; i++)
				tmp[i] = rs[i];
			delete[] rs;
			rs = tmp;
		}
	}
	rs[current_size++] = r;
}
void edit(Record *&rs, char flag) {//2
	char str[100];
	int nkod, p1, p2, p3;
	int index = -1;

	cout << endl << "EDITING" << endl;
	if (flag == 's')
	{
		cout << "Enter full name to search" << endl;
		cin.getline(str, '/n');
		for (int i = 0; i < current_size; i++)
			if (strcmp(rs[i].fio, str) == 0)
			{
				index = i;
				break;
			}
	}
	else if (flag == 'n')
	{
		cout << "Enter telephone number in the format XXXX XX XX XX" << endl;
		cin >> nkod >> p1 >> p2 >> p3;
		for (int i = 0; i < current_size; i++)
			if (rs[i].kod == nkod && rs[i].part1 == p1 && rs[i].part2 == p2 && rs[i].part3 == p3)
			{
				index = i;
				break;
			}
	}
	int choice;
	if (index != -1)
	{
		cout << "Enter 1 to change name" << endl;
		cin >> choice;
		if (choice == 1)
		{
			cout << "Enter full name" << endl;
			cin.ignore(); //обязательно, т.к. выше cin>>choice
			cin.getline(rs[index].fio, 100);
		}
		cout << "Enter 2 to change number" << endl;
		cin >> choice;
		if (choice == 2)
		{
			cout << "Enter telephone number in the format XXXX XX XX XX" << endl;
			int kk, pp1, pp2, pp3;
			cin >> kk >> pp1 >> pp2 >> pp3;
			rs[index].kod = kk;
			rs[index].part1 = pp1;
			rs[index].part2 = pp2;
			rs[index].part3 = pp3;
		}
	}
}
void erase(Record *&rs, char flag) {//3
	char str[100];
	int nkod, p1, p2, p3;
	int index = -1;

	if (flag == 's')
	{
		cout << "Enter full name to erase" << endl;
		cin.getline(str, '/n');
		for (int i = 0; i < current_size; i++)
			if (strcmp(rs[i].fio, str) == 0)
			{
				index = i;
				break;
			}
	}
	else if (flag == 'n')
	{
		cout << "Enter telephone number in the format XXXX XX XX XX to erase" << endl;
		cin >> nkod >> p1 >> p2 >> p3;
		for (int i = 0; i < current_size; i++)
			if (rs[i].kod == nkod && rs[i].part1 == p1 && rs[i].part2 == p2 && rs[i].part3 == p3)
			{
				index = i;
				break;
			}
	}
	if (index != -1)
	{
		for (int i = index; i < current_size - 1; i++)
		{
			rs[i] = rs[i + 1];
		}
		current_size--;
	}
}
void printAll(Record *rs) {
	cout << endl;
	for (int i = 0; i < current_size; i++)
		rs[i].print();
	cout << endl;
}
void printAllTelephone(Record *rs) {//4
	for (int i = 0; i < current_size; i++)
		cout << "(" << rs[i].kod << ")" << rs[i].part1 << "-" << rs[i].part2 << "-" << rs[i].part3 << endl << endl;
}
void sortByName(Record *&rs) {//5
	for (int i = 0; i < current_size; i++)
		for (int j = i; j > 0; j--)
			if (strcmp(rs[j].fio, rs[j - 1].fio) == -1)
				swap(rs[j], rs[j - 1]);
}
void sortByNumber(Record *&rs) {//6
	for (int i = 0; i < current_size; i++)
	{
		for (int j = i; j > 0; j--)
		{
			if (rs[j].kod < rs[j - 1].kod)
				swap(rs[j], rs[j - 1]);
			else if (rs[j].kod == rs[j - 1].kod)
				if (rs[j].part1 < rs[j - 1].part1)
					swap(rs[j], rs[j - 1]);
				else if (rs[j].part1 == rs[j - 1].part1)
					if (rs[j].part2 < rs[j - 1].part2)
						swap(rs[j], rs[j - 1]);
					else if (rs[j].part2 == rs[j - 1].part2)
						if (rs[j].part3 < rs[j - 1].part3)
							swap(rs[j], rs[j - 1]);
		}
	}
}
void sortByNumber_2(Record*&rs) {
	int *n = new int[current_size];
	for (int i = 0; i < current_size; i++)
		n[i] = rs[i].part1 * 10000 + rs[i].part2 * 100 + rs[i].part3;

	for (int i = 0; i < current_size; i++)
	{
		for (int j = i; j > 0; j--)
		{
			if (rs[j].kod < rs[j - 1].kod)
				swap(rs[j], rs[j - 1]);
			else if (rs[j].kod == rs[j - 1].kod)
			{
				if (n[j] > n[j - 1])
					swap(rs[j], rs[j - 1]);
			}
		}
	}

	delete[] n;
}

int main()
{
	srand(time(NULL));
	setlocale(LC_ALL, "Rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Record *rs = 0;
	Record tmp;
	int k, p1, p2, p3;
	char str[100];

	ifstream in_file("in.txt");
	if (!in_file)
		cerr << "File open error" << endl;
	else
	{
		while (!in_file.eof())
		{
			in_file.ignore();//со второй итерации корректно, а в первой итерации нужна пустая строка в текстовом файле чтобы что-то проигнорить
			in_file.getline(tmp.fio, 100, '#');
			in_file >> k >> p1 >> p2 >> p3;

			tmp.kod = k;
			tmp.part1 = p1;
			tmp.part2 = p2;
			tmp.part3 = p3;

			add(rs, tmp);
		}
	}
	//printAll(rs);

	int choose=-1;
	//bool f = true;
	while (choose!=0)
	{
		cout << "Enter 1 to add number" << endl;
		cout << "Enter 2 to edit" << endl;
		cout << "Enter 3 to erase" << endl;
		cout << "Enter 4 to print all numbers" << endl;
		cout << "Enter 5 to sort by telephone number" << endl;
		cout << "Enter 6 to sort by full name" << endl;
		cout << "Enter 0 to exit" << endl << endl;
		cin >> choose;
		char mode;
		switch (choose)
		{
		case 1:
		{
			Record tmp2;
			int rk, rp1, rp2, rp3;
			cout << "Enter full name and number of new abonent XXXX XX XX XX" << endl;
			cin.ignore();
			cin.getline(tmp2.fio, 100);
			cin >> rk >> rp1 >> rp2 >> rp3;
			tmp2.kod = rk;
			tmp2.part1 = rp1;
			tmp2.part2 = rp2;
			tmp2.part3 = rp3;

			add(rs, tmp2);
			printAll(rs);
		}
		break;
		case 2:
		{
			cout << "Enter 's' to search by name or 'n' to search by number and then to EDIT" << endl;
			cin >> mode;
			cin.ignore();
			edit(rs, mode);
			printAll(rs);
		}
		break;
		case 3:
		{
			cout << "Enter 's' to search by name or 'n' to search by number and then to ERASE" << endl;
			cin >> mode;
			cin.ignore();
			erase(rs, mode);
			printAll(rs);
		}
		break;
		case 4:
			printAllTelephone(rs);
		break;
		case 5:
		{
			sortByNumber(rs);
			//sortByNumber_2(rs);
			printAll(rs);
		}
		break;
		case 6:
		{
			sortByName(rs);
			printAll(rs);
		}
		}
	}

	//edit(rs, 's');
	//edit(rs, 'n');
	//erase(rs, 'n');
	//erase(rs, 's');
	//sortByNumber(rs);
	//sortByNumber_2(rs);
	//sortByName(rs);
	cout << endl << endl;
	//printAll(rs);
	//printAllTelephone(rs);

	delete[] rs;

	system("pause");
	return 0;
}