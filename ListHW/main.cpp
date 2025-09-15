#include<iostream>
using std::cin;
using std::cout;
using std::endl;

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

	class ConstBaseIterator //этот класс обобщает св-ва разных итераторов
	{
	protected:
		Element* Temp;
	public:
		ConstBaseIterator(Element*Temp = nullptr): Temp(Temp){}
		~ConstBaseIterator(){}

		bool operator==(const ConstBaseIterator& other)const
		{
			return this->Temp == other.Temp;
		}
		bool operator!=(const ConstBaseIterator& other)const
		{
			return this->Temp != other.Temp;
		}
		int operator*()const//в конст итераторе должен быть ТОЛЬКО конст оператор разименования
			                //НИ В КОЕМ случае НЕ должно быть обычного оператора разименования
		{
			return Temp->Data;
		}
	};

public:
	class ConstIterator:public ConstBaseIterator
	{
	public:
		ConstIterator(Element* Temp=nullptr) : ConstBaseIterator(Temp) {}
		~ConstIterator() {}

		ConstIterator& operator++()
		{
			Temp = Temp->pNext;
			return *this;
		}
		ConstIterator operator++(int)
		{
			ConstIterator old = *this;
			Temp = Temp->pNext;
			return old;
		}
		ConstIterator& operator--()
		{
			Temp = Temp->pNext;
			return *this;
		}
		ConstIterator operator--(int)
		{
			ConstIterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}
	};

	class ConstReverseIterator:public ConstBaseIterator
	{
	public:
		ConstReverseIterator(Element* Temp = nullptr): ConstBaseIterator(Temp){}
		~ConstReverseIterator(){}

		ConstReverseIterator& operator++()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		ConstReverseIterator operator++(int)
		{
			ConstReverseIterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}
		ConstReverseIterator& operator--()
		{
			Temp = Temp->pNext;
			return *this;
		}
		ConstReverseIterator operator--(int)
		{
			ConstReverseIterator old = *this;
			Temp = Temp->pNext;
			return old;
		}
	};
	class Iterator :public ConstIterator
	{
	public:
		Iterator(Element* Temp): ConstIterator(Temp){}
		~Iterator(){}
		int& operator*()
		{
			return Temp->Data;
		}
	};
	class ReverseIterator : public ConstReverseIterator
	{
	public:
		    ReverseIterator(Element * Temp) :ConstReverseIterator(Temp) {}
			~ReverseIterator() {}
			int& operator*()
			{
				return Temp->Data;
			}
	};
	ConstIterator begin()const
	{
		return Head;
	}
	ConstIterator end()const
	{
		return nullptr;
	}
	ConstReverseIterator rbegin()const
	{
		return Tail;
	}
	ConstReverseIterator rend()const
	{
		return nullptr;
	}
	Iterator begin()
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;
	}
	ReverseIterator rbegin()
	{
		return Tail;
	}
	ReverseIterator rend()
	{
		return nullptr;
	}

	List()
	{
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstructor\t" << this << endl;
	}
	List(const std::initializer_list<int>& il) :List() //к-р с одним параметром для первода другого типа в наш тип данных
	{
		for (int const* it = il.begin(); it != il.end(); ++it)
		{
			push_back(*it);
		}
		cout << "ILConstructor\t" << this << endl;
	}
	List(const List& other) : List()
	{
		*this = other;
		cout << "LCOPYConstructor\t" << this << endl;
	}
	~List()
	{
		//while (Head)pop_front();
		while (Tail)pop_back();
		cout << "LDestructor\t" << this << endl;
	}

	List& operator =(const List& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);
		cout << "LCOPYAssignment\t" << this << endl;
		return *this;
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

List operator+(const List& left, const List& right)
{
	List fusion = left;
	for (List::ConstIterator it = right.begin(); it != right.end(); ++it)
		fusion.push_back(*it);//*=100 не должен метод изменять значение - нужен отдельный класс константного итератора
	return fusion;
}

//#define BASE_CHECK
#define HOME_WORK

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

#ifdef HOME_WORK

	List list1 = { 3, 5, 8, 13, 21 };
	List list2 = { 34, 55, 89 };
	//list1.Print();
	//list2.Print();
	//list1.Reverse_Print();
	//list2.Reverse_Print();
	List list3 = list1 + list2;
	for (int i : list1)cout << i << tab; cout << endl;
	for (int i : list2)cout << i << tab; cout << endl;
	for (int i : list3)cout << i << tab; cout << endl;
	for (List::ConstIterator it = list1.begin(); it != list1.end(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;
	for (List::Iterator it = list1.begin(); it != list1.end(); ++it)
	{
		*it *= 100;
	}
	for (List::ConstReverseIterator it = list1.rbegin(); it != list1.rend(); ++it)
	{
		//*it *= 100;
		cout << *it << tab;
	}
	cout << endl;

#endif // HOME_WORK

}