#include<iostream>
using namespace std;

void elevator(int floor);

void main()
{
	setlocale(LC_ALL, "");
	int n;
	cout << "Введите номер этажа:"; cin >> n;
	elevator(n);

}
void elevator(int floor)
{
	if (floor == 0)
	{
		cout << "Вы в подвале" << endl;
		return;                         //прерывание ОБЯЗАТЕЛЬНО в рекурсии!
	} 
	cout << "Вы на " << floor << " Этаже " << endl;//вниз
	elevator(floor-1);                  //завершение ВЫЗОВА -1 идем на дно отталкиваемся и идем наверх
	cout << "Вы на " << floor << " Этаже " << endl;//вверх
	

}