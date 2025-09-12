#include<iostream>
using namespace std;

#define tab "\t"
#define delimiter "\n--------------------------\n"

class List
{
	class Element             //класс в классе !!!!!
	{
		int Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr)
			:Data(Data), pNext(pNext), pPrev(pPrev)
		{
			cout << "EConsrtuctor\t " << this << endl;
		}
		~Element()
		{
			cout << "EDesrtuctor\t " << this << endl;
		}
		friend class List;
	}*Head, * Tail;    //объекты классов и структур и указатели и указатели на эти объекты можно объявлять непосредст
	//после описания класса и структур

	size_t size; //размер списка size_t  
public:
	List()
	{
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstructor\t" << this << endl;
	}
	~List()
	{
		//while (Head)pop_front();
		while (Tail)pop_back();
		cout << "LDestructor\t" << this << endl;
	}

	void push_front(int Data)
	{
		//1 создаем элемент в котором будет сохранено добавляемое значение
		Element* New = new Element(Data);
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data);
		}
		else
		{
			//2 Пристыковываем элемент к списку
			New->pNext = Head;
			//3 пристыковываем начальный элемент списка к новому элементу
			Head->pPrev = New;
			//4 Делаем новый элемент начальным элементом спсика
			Head = New;
		}

		//увеличиваем кол-во элементов в списке
		size++;
	}
	void push_back(int Data)
	{
		//1 создаем элемент в котором будет сохранено добавляемое значение
		Element* New = new Element(Data);
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = New;
		}
		else
		{
			//2 Пристыковываем элемент к списку
			New->pPrev = Tail;
			//3 пристыковываем конечный элемент списка к новому элементу
			Tail->pNext = New;
			//4 Делаем новый элемент хвостом списка 
			Tail = New;
		}
		size++;
	}
	void pop_front()
	{
		if (Head == nullptr && Tail == nullptr)return;
		if (Head == Tail) //если голова и хвост равны, значит они указывают либо на ноль либо на один и тот же
			              //элемент. Ситуацию с пустым списком обрабытывает предыдущее условие .
			              // ситуацию с вырожденным списком обрабатывает текущее условие и в этом if удаляется один 
			              //единственный элемент
		{
			delete Head;
			Head = Tail = nullptr;
		}
		else
		{
			//ОБЩИЙ СЛУЧАЙ
			//1 смещаем голову на следующий элемент
			Head = Head->pNext;
			//2 удаляем элемент из памяти 
			delete Head->pPrev;
			//обнуляем указатель на удаленный элемент(делаем Head последним элементом спсика)
			Head->pPrev = nullptr;
		}
		size--;

	}
	void pop_back()
	{
		if (Head == nullptr && Tail == nullptr)return;
		if (Head == Tail) //если голова и хвост равны, значит они указывают либо на ноль либо на один и тот же
			//элемент. Ситуацию с пустым списком обрабытывает предыдущее условие .
			// ситуацию с вырожденным списком обрабатывает текущее условие и в этом if удаляется один 
			//единственный элемент
		{
			delete Tail;
			Head = Tail = nullptr;
		}
		else
		{
			//ОБЩИЙ СЛУЧАЙ
			//1 смещаем голову на следующий элемент
			Tail = Tail->pPrev;
			//2 удаляем элемент из памяти 
			delete Tail->pNext;
			//обнуляем указатель на удаленный элемент(делаем Head последним элементом спсика)
			Tail->pNext = nullptr;
		}
		size--;
	}
	void insert(int Data, int Index)
	{
		if(Index < 0)return;
		if(Index == 0 || size == 0)return push_front(Data);
		if(Index>=size)return push_back(Data);

		//ОБЩИЙ СЛУЧАЙ
		//1 доходим до нужного элемента - выбираем с какой стороны зайти к элементу 
		Element* Temp;
		if (Index < size / 2)
		{
			Temp = Head;
			for (int i = 0; i < Index; i++)Temp = Temp->pNext;

		}
		else
		{
			Temp = Tail;
			for (int i = 0; i < size - Index - 1; i++)Temp = Temp->pPrev;
		}
		//не зависисо от того каким образом мы дошли до нужного элемента с начала или конца спсика
		//процедура добавления элемент будет идентичной
		//2 создаем новый элемент 
		Element* New = new Element(Data);
		//3 пристыковываем новый элемент к списку
		New->pNext = Temp;
		New->pPrev = Temp->pPrev;
		//4 вклиниваем новый элемен в список 
		Temp->pPrev->pNext = New;
		Temp->pPrev = New;
		size++;

	}
	//Метод
	void Print()const
	{
		cout << delimiter << endl;
		cout <<"Head" << Head << endl;
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout <<"Tail"<< Tail << endl;
		cout << "Кол-во элементов списка" << size;
		cout << delimiter << endl;
    }
	void Reverse_Print()const
	{
		cout << delimiter << endl;
		cout << "Head"<< Head << endl;
		for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Tail"<< Tail << endl;
		cout << "Кол-во элементов списка" << size;
		cout << delimiter << endl;
	}
};

//#define BASE_CHECK


void main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK

	int n;
	cout << "Введите размер списка"; cin >> n;
	List list;
	list.pop_front();
	list.Print();
	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	list.Print();
	list.Reverse_Print();

	//list.pop_back();
	//list.Print();
	//list.Reverse_Print();

	int Index;
	int value;
	cout << "Введите индекс добавляемого элемента:"; cin >> Index;
	cout << "Введите значение добавляемого элемента:"; cin >> value;
	list.insert(value,Index);
	list.Print();
	list.Reverse_Print();
#endif // BASE_CHECK

}