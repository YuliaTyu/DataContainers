#include<iostream>
#include<time.h>
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"

//#define DEBUG

class Tree
{
protected:
	class Element
	{
		int Data;
		Element* pLeft;
		Element* pRight;
	public:
		Element(int Data, Element* pLeft = nullptr, Element* pRight = nullptr) :
			Data(Data), pLeft(pLeft), pRight(pRight)
		{
#ifdef DEBUG
			cout << "EConstructor:\t" << this << endl;
#endif // DEBUG
		}
		~Element()
		{
#ifdef DEBUG
			cout << "EDestructor:\t" << this << endl;
#endif // DEBUG
		}
		friend class Tree;
		friend class UniqueTree;
	}*Root;
public:
	Element* getRoot()const
	{
		return Root;
	}
	Tree() :Root(nullptr)
	{
		cout << "TConstructor:\t" << this << endl;
	}
	Tree(const std::initializer_list<int>& il) :Tree()
	{
		for (int const* it = il.begin(); it != il.end(); ++it)
			insert(*it, Root);
		cout << "ILConstructor:\t" << this << endl;
	}
	~Tree()
	{
		clear();
		cout << "TDestructor:\t" << this << endl;
	}
	void clear()
	{
		clear(Root);
	}
	void insert(int Data)
	{
		insert(Data, Root);
	}
	void erase(int Data)
	{
		erase(Data, Root);
	}
	int minValue()const
	{
		return minValue(Root);
	}
	int maxValue()const
	{
		return maxValue(Root);
	}
	int sum()const
	{
		return sum(Root);
	}
	int count()const
	{
		return count(Root);
	}
	double avg()const
	{
		return (double)sum(Root) / count(Root);
	}
	void print()const
	{
		print(Root);
		cout << endl;
	}
private:
	void clear(Element*& Root)
	{
		if (Root == nullptr)return;
		clear(Root->pLeft);
		clear(Root->pRight);
		delete Root;
		Root = nullptr;
	}
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr) this->Root = new Element(Data);
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}
	void erase(int Data, Element*& Root)
	{
		if (Root == nullptr)return;
		erase(Data, Root->pLeft);
		erase(Data, Root->pRight);
		if (Data == Root->Data)
		{
			if (Root->pLeft == Root->pRight)
			{
				delete Root;
				Root = nullptr;
			}
			else
			{
				
				if (count(Root->pLeft) > count(Root->pRight))
				{
					Root->Data = maxValue(Root->pLeft);
					erase(maxValue(Root->pLeft), Root->pLeft);
				}
				else
				{
					Root->Data = minValue(Root->pRight);
					erase(minValue(Root->pRight), Root->pRight);
				}
			}
		}
	}
	int minValue(Element* Root)const
	{
		return Root == nullptr ? INT_MIN : Root->pLeft == nullptr ? Root->Data : minValue(Root->pLeft);
		/*if (Root->pLeft == nullptr)return Root->Data;
		else return minValue(Root->pLeft);*/
	}
	int maxValue(Element* Root)const
	{
		return !Root ? INT_MIN : Root->pRight ? maxValue(Root->pRight) : Root->Data;
		/*if (Root->pRight == nullptr)return Root->Data;
		else return maxValue(Root->pRight);*/
	}
	int count(Element* Root)const
	{
		return !Root ? 0 : count(Root->pLeft) + count(Root->pRight) + 1;
		/*if (Root == nullptr)return 0;
		else return count(Root->pLeft) + count(Root->pRight) + 1;*/
	}
	int sum(Element* Root)const
	{
		return Root == nullptr ? 0 : sum(Root->pLeft) + sum(Root->pRight) + Root->Data;
	}


	void print(Element* Root)const
	{
		if (Root == nullptr)return;
		print(Root->pLeft);
		cout << Root->Data << tab;
		print(Root->pRight);
	}
};
class UniqueTree :public Tree
{
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr) this->Root = new Element(Data);
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else if (Data > Root->Data)
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}
public:
	void insert(int Data)
	{
		insert(Data, Root);
	}
};

template<typename T> void measure_performance(const char message[], T(Tree::*function)()const, const Tree& tree)//функция которая показаывает за какое время выполняется программа
{
	//int (*function)() - указатель на ф-ию ничег не принимает возвращает значение типа INT
	clock_t start = clock();
	T result = (tree.*function)();
	clock_t end = clock();

	cout << message << result << " , вычеслено за" << double(end - start) / CLOCKS_PER_SEC << "секунд\n";

}

//#define BASE_CHECK
//#define ERASE_CHECK

void main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK
	int n;
	cout << "введите количесвто элементов : "; cin >> n;
	Tree tree;
	cout << "Мин: " << tree.minValue() << endl;
	cout << "Макс: " << tree.maxValue() << endl;
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100);
	}
	tree.print();
	cout << endl;
	cout << "Мин: " << tree.minValue() << endl;
	cout << "Макс: " << tree.maxValue() << endl;
	cout << "Кол-во элементов: " << tree.count() << endl;
	cout << "Сумма: " << tree.sum() << endl;
	cout << "Среднеарифметическое: " << tree.avg() << endl;

	UniqueTree u_tree;
	for (int i = 0; i < n; i++)
	{
		u_tree.insert(rand() % 100);
	}
	u_tree.print();
	cout << "Мин: " << u_tree.minValue() << endl;
	cout << "Макс: " << u_tree.maxValue() << endl;
	cout << "Кол-во: " << u_tree.count() << endl;
	cout << "Сумма: " << u_tree.sum() << endl;
	cout << "Среднеарифметическое: " << u_tree.avg() << endl;
#endif // BASE_CHECK

#ifdef ERASE_CHECK

	Tree tree =
	{
					50,

			25,				75,

		16,		32,		58,		85
	};
	tree.print();

	int value;
	
	tree.erase(25);
	tree.erase(32);
	tree.erase(50);
	tree.erase(75);
	tree.print();
#endif // ERASE_CHECK

	int n;
	cout << "введите количесвто элементов : "; cin >> n;
	Tree tree;
	//cout << "Мин: " << tree.minValue() << endl;
	//cout << "Макс: " << tree.maxValue() << endl;
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100);
	}
	/*tree.print();
	cout << endl;
	cout << "Мин: " << tree.minValue() << endl;
	cout << "Макс: " << tree.maxValue() << endl;
	cout << "Кол-во элементов: " << tree.count() << endl;
	cout << "Сумма: " << tree.sum() << endl;
	cout << "Среднеарифметическое: " << tree.avg() << endl;*/

	measure_performance("мин знач ", &Tree::minValue,tree);
	measure_performance("макс знач ", &Tree::maxValue,tree);
	measure_performance("сумма знач ", &Tree::sum,tree);
	measure_performance("кол-во ", &Tree::count,tree);
	measure_performance("сред-ариф знач ", &Tree::avg,tree);

}