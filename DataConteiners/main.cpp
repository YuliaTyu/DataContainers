#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"

class Element
{
	int Data;
	Element* pNext;// новый элемент
	static int count;
public:
	Element(int Data, Element* pNext = nullptr)
	{
		this->Data = Data;
		this->pNext = pNext;
		count++;
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		count--;
		cout << "EDectructor:\t" << this << endl;
	}
	friend class ForwardList;//Дружим два класса!!!!
};
int Element::count = 0;

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
	//создание эдемента в конец списка
	void push_back(int Data)
	{
		if (Head == nullptr)return push_front(Data);//список не пуст //return прерывает функцию
		Element* New = new Element(Data);
		Element* Temp = Head;
		while(Temp->pNext)Temp = Temp->pNext;
		Temp->pNext = New;
	}
	//удаляем первый элемент из списка
	void pop_front()
	{
		//запоминаем адрес удаляемого элемента
		Element* Erased = Head;

		//переносим Head на второой элемент
		Head = Head->pNext;

		//удаляем первый элемент из памяти 
		delete Erased;
	}
	//удаляем последний элемент из списка
	void pop_back()
	{
		Element* Temp = Head;
		while (Temp->pNext->pNext != nullptr)Temp = Temp->pNext;//предыдущий элемент имеет 0 !
		delete Temp->pNext;
		Temp->pNext = nullptr;//показываем что это последний элемент списка
	}
	//всатвляем параметры по индексу
	void insert(int Data, int index)
	{
		if (index == 0)return push_front(Data);
		if (Element::count <= index)return push_back(Data);
		//1 доходим до нужного элемента(элемент перед добавляемым)
		Element* Temp = Head;
		for (int i = 0; i < index - 1; i++)Temp = Temp->pNext;

		//2 создаем добавляемый элемент
		Element* New = new Element(Data);
		
		//цепляем добавляемый элемент к следующим за ним в списке
		New->pNext = Temp->pNext;

		//пристыковываем к новому элементу
		Temp->pNext = New;
	}
	//удаляем элемент по индексу
	//void erase(int index)

	//Methods
	void print()const
	{
		Element* Temp = Head;//Temp - это итератор -указатель при помощи котрого можно перебирать элементы структуры данных
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;
		}
		Temp;
	}
};

//#define BASE_CHECK

void main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK


	int n;
	cout << "Введите размер списка: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
		//list.push_front(rand() % 100);
	}
	//list.push_back(123);
	//list.print();
	//list.pop_front();
	//list.print();
	//list.pop_back();
	//list.print();
	int index;
	int value;
	cout << "Введите индекс доб элемента"; cin >> index;
	cout << "Введите значение доб элемента"; cin >> value;
	list.insert(value,index);
	list.print();

#endif // BASE_CHECK

	ForwardList list1;
	list1.push_back(0);
	list1.push_back(1);
	list1.push_back(1);
	list1.push_back(2);
	list1.print();
	
	ForwardList list2;
	list2.push_back(3);
	list2.push_back(5);
	list2.push_back(8);
	list2.push_back(13);
	list2.push_back(21);
	list2.push_back(34);
	list2.push_back(55);
	list2.push_back(89);
	list2.print();

	int index;
	int value;
	cout << "Введите индекс добавляемого значения"; cin >> index;
	cout << "Введите значение добавляемого значения"; cin >> value;
	list1.insert(value, index);
	list1.print();
}