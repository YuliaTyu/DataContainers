#include<iostream>
using namespace std;

#define tab "\t"

class Element
{
	int Data;
	Element* pNext;
public:
	Element(int Data, Element* pNext = nullptr)
	{
		this->Data = Data;
		this->pNext = pNext;
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		cout << "EDectructor:\t" << this << endl;
	}
	friend class ForwardList;//Дружим два класса!!!!
};

class ForwardList
{
	Element* Head;
public:
	ForwardList()
	{
		//к-р по умолчанию создает пустой список
		Head = nullptr;//если список пуст то голова указывает на ноль
		cout << "FLConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		cout << "FLDestructor:\t" << this << endl;
	}

	//создание элеменента в начало списка
	void push_front(int Data)
	{
		//1 создаем элемент и сохраняем в него добавляемое значение
		Element* New = new Element(Data);
		//2 привязываем новый созданный элемент к началу списка
		New->pNext = Head;
		//3 переносим голову на новый элемент
		Head = New;

	}

	//Methods
	void print()const
	{
		Element* Temp = Head;//Temp - это итератор -указатель при помощи котрого можно перебирать элементы структуры данных
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;
		}
	}
};


void main()
{
	setlocale(LC_ALL, "");

	int n;
	cout << "Введите размер списка: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
	}
	list.print();

}