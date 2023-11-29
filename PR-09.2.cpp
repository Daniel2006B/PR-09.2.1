#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h> // забезпечення відображення кирилиці
using namespace std;
enum Speciality { COMPUTER_SCIENCE, INFORMATION, MATHEMATICS_AND_ECONOMICS, HANDICRAFT, PHYSICS_AND_INFORMATICS };
string specialityStr[] = { "Комп’ютерні науки", "Інформатика", "Математика та економіка", "Трудове навчання", "Фізика та інформатика" };
struct Student
{
	string prizv;
	unsigned kurs;
	Speciality speciality;

	int phys;
	int math;
	int info;
	

};
void Create(Student* p, const int N);
void Print(Student* p, const int N);
void Sort(Student* p, const int N);
int BinSearch(Student* p, const int N, const string prizv, const Speciality speciality, double ser_bal);
int* IndexSort(Student* p, const int N);
void PrintIndexSorted(Student* p, int* I, const int N);
int main()
{ // забезпечення відображення кирилиці:
	SetConsoleCP(1251); // встановлення сторінки win-cp1251 в потік вводу
	SetConsoleOutputCP(1251); // встановлення сторінки win-cp1251 в потік виводу

	int N;
	cout << "Введіть кількість студентів N: "; cin >> N;

	Student* p = new Student[N];
	double proc, ser_bal;
	int ispeciality;
	Speciality speciality;
	string prizv;
	int found;
	int menuItem;
	do {
		cout << endl << endl << endl;
		cout << "Виберіть дію:" << endl << endl;
		cout << " [1] - введення даних з клавіатури" << endl;
		cout << " [2] - вивід даних на екран" << endl;
		cout << " [3] - фізичне впорядкування даних" << endl;
		cout << " [4] - бінарний пошук студента за курсом та прізвищем" << endl;
		cout << " [5] - індексне впорядкування та вивід даних"
			<< endl << endl;
		cout << " [0] - вихід та завершення роботи програми" << endl << endl;
		cout << "Введіть значення: "; cin >> menuItem;
		cout << endl << endl << endl;
		switch (menuItem)
		{
		case 1:
			Create(p, N);
			break;
		case 2:
			Print(p, N);
			break;
		case 3:
			Sort(p, N);
			break;
		case 4:
			cout << "Введіть ключі пошуку:" << endl;
			cout << "спеціальність (0 - Комп’ютерні науки, 1 - Інформатика, 2 - Математика та економіка, 3 - Трудове навчання, 4 - Фізика та інформатика): ";
			cin >> ispeciality;
			speciality = (Speciality)ispeciality;
			cin.get(); // очищуємо буфер клавіатури – бо залишаються символи
			cin.sync(); // "кінець рядка", які не дають ввести наступний літерний рядок

			cout << " прізвище: "; getline(cin, prizv);
			cout << endl;
			cout << " середній бал: "; cin >> ser_bal;
			if ((found = BinSearch(p, N, prizv, speciality,ser_bal)) != -1)
				cout << "Знайдено студента в позиції " << found + 1 << endl;
			else
				cout << "Шуканого студента не знайдено" << endl;
			break;
		case 5:
			PrintIndexSorted(p, IndexSort(p, N), N);
			break;
		case 0:
			break;
		default:
			cout << "Ви ввели помилкове значення! "
				"Слід ввести число - номер вибраного пункту меню" << endl;
		}
	} while (menuItem != 0);
	return 0;
}
void Create(Student* p, const int N)
{
	int speciality;
	for (int i = 0; i < N; i++)
	{
		cout << "Студент № " << i + 1 << ":" << endl;
		cin.get(); // очищуємо буфер клавіатури – бо залишаються символи
		cin.sync(); // "кінець рядка", які не дають ввести наступний літерний рядок

		cout << " прізвище: ";
		getline(cin, p[i].prizv);
		cout << " курс: ";
		cin >> p[i].kurs;
		cout << " спеціальність (0 - Комп’ютерні науки, 1 - Інформатика, 2 - Математика та економіка, 3 - Трудове навчання, 4 - Фізика та інформатика): ";
		cin >> speciality;
		p[i].speciality = (Speciality)speciality;

		cout << "оцінка з фізики : ";
		cin >> p[i].phys;
		cout << "оцінка з математики : ";
		cin >> p[i].math;
		
		cout << " оцінка інформатики : ";
		cin >> p[i].info;
		

		cout << endl;
	}
}
void Print(Student* p, const int N)
{
	cout << "=================================================================================="
		<< endl;
	cout << "|  №  |   Прізвище   | курс |     спеціальність      | фізика | математика | інформатика |"
		<< endl;
	cout << "----------------------------------------------------------------------------------"
		<< endl;
	for (int i = 0; i < N; i++)
	{
		cout << "| " << setw(3) << right << i + 1 << " ";
		cout << "| " << setw(13) << left << p[i].prizv
			<< "| " << setw(4) << right << p[i].kurs << " "
			<< "| " << setw(14) << left << specialityStr[p[i].speciality] << " ";
		cout << " | " << setw(6) << right << p[i].phys << " "
			<< " | " << setw(10) << left << p[i].math << " "
			<< " | " << setw(11) << right << p[i].info << " |";
		cout << endl << "=================================================================================="
			<< endl;
	}
	cout << endl;
}


void Sort(Student* p, const int N)
{
	Student tmp;
	for (int i0 = 0; i0 < N - 1; i0++) // метод "бульбашки"
		for (int i1 = 0; i1 < N - i0 - 1; i1++)
			if ((p[i1].speciality > p[i1 + 1].speciality)
				||
				(p[i1].speciality == p[i1 + 1].speciality &&
					double(p[i1].math+p[i1].phys+p[i1].info)/3> double(p[i1+1].math + p[i1+1].phys + p[i1+1].info) / 3)
				||
				(p[i1].speciality == p[i1 + 1].speciality &&
					double(p[i1].math + p[i1].phys + p[i1].info) / 3 > double(p[i1 + 1].math + p[i1 + 1].phys + p[i1 + 1].info) / 3 &&
					p[i1].prizv<p[i1+1].prizv))
			{
				tmp = p[i1];
				p[i1] = p[i1 + 1];
				p[i1 + 1] = tmp;
			}

}
int BinSearch(Student* p, const int N, const string prizv, const Speciality speciality, double ser_bal)
{ 
	int L = 0, R = N - 1, m;
	do {
		m = (L + R) / 2;
		if (p[m].prizv == prizv && p[m].speciality == speciality&&ser_bal==double(p[m].math+p[m].phys+p[m].info)/3)
			return m;
		if ((p[m].speciality < speciality)
			||
			(p[m].speciality == speciality && double(p[m].math + p[m].phys + p[m].info) / 3<ser_bal)
			||
			(p[m].speciality == speciality && ser_bal == double(p[m].math + p[m].phys + p[m].info) / 3 &&
				p[m].prizv < prizv))
		{
			L = m + 1;
		}
		else
		{
			R = m - 1;
		}
	} while (L <= R);
	return -1;
}
int* IndexSort(Student* p, const int N)
{ 
	int* I = new int[N]; // створили індексний масив
	for (int i = 0; i < N; i++)
		I[i] = i; // заповнили його початковими даними
	int i, j, value; // починаємо сортувати масив індексів
	for (i = 1; i < N; i++)
	{
		value = I[i];
		for (j = i - 1;
			j >= 0 && ((p[I[j]].speciality > p[value].speciality) ||
				(p[j].speciality == p[value].speciality && double(p[j].math + p[j].phys + p[j].info) / 3 > double(p[value].math + p[value].phys + p[value].info) / 3 )
				||
				(p[j].speciality == p[value].speciality && double(p[j].math + p[j].phys + p[j].info) / 3 == double(p[value].math + p[value].phys + p[value].info) / 3 &&
					p[j].prizv > p[value].prizv));
			j--)
		{
			I[j + 1] = I[j];
		}
		I[j + 1] = value;
	}
	return I;
}
void PrintIndexSorted(Student* p, int* I, const int N)
{ // аналогічно функції Print(), але замість звертання p[i]...
 // використовуємо доступ за допомогою індексного масиву І: p[I[i]]...
	cout << "========================================================================="
		<< endl;
	cout << "| № | Прізвище | курс | спеціальність | фізика | математика | інформатика |"
		<< endl;
	cout << "-------------------------------------------------------------------------"
		<< endl;
	for (int i = 0; i < N; i++)
	{
		cout << "| " << setw(3) << right << i + 1 << " ";
		cout << "| " << setw(13) << left << p[I[i]].prizv
			<< "| " << setw(4) << right << p[I[i]].kurs << " "
			<< "| " << setw(11) << left << specialityStr[p[I[i]].speciality] << " ";
		cout << " | " << setw(4) << right << p[i].phys << " "
			<< " | " << setw(4) << left << p[i].math << " "
			<< " | " << setw(4) << right << p[i].info << " |";
		cout << endl << "========================================================================="
			<< endl;
		cout << endl;
	}
}

