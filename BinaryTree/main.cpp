#include<iostream>
using namespace std;

//TODO:
//1. Выяснить, почему в дереве не появляются элементы;
// Ответ: в методе insert() два входящих аргумента: добавляемое_значение и указатель_на_корневой_элемент.
//  В новом созданном дереве (еще пустом) корневой элемент равен nullptr.
// А в самом методе первым делом происходит проверка if (Root == nullptr)return; и выполняется возврат из метода.
//2. В классе Tree написать метод print();

class Tree
{
	class Element
	{
		int Data;
		Element* pLeft;
		Element* pRight;
	public:
		Element(int Data, Element* pLeft = nullptr, Element* pRight = nullptr)
			:Data(Data), pLeft(pLeft), pRight(pRight)
		{
			cout << "EConstructor:\t" << this << endl;
		}
		~Element()
		{
			cout << "EDestructor:\t" << this << endl;
		}
		friend class Tree;
	}*Root;
public:
	Element* getRoot()
	{
		return Root;
	}
	Tree() :Root(nullptr)
	{
		cout << "TConstructor:\t" << this << endl;
	}
	~Tree()
	{
		cout << "TDestructor:\t" << this << endl;
	}
	//1. Выяснить, почему в дереве не появляются элементы;
	void insert(int Data, Element* Root)
	{
		if (Root == nullptr)
		{
			Root = new Element(Data);
			return;
		}
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr) Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}
//2. В классе Tree написать метод print();
	void print()
	{
		Element* Temp = new Element(0);
		cout << "PRINTING" << Temp->Data << endl;
		for (Temp->Data; Temp->pRight != nullptr && Temp->pLeft != nullptr; Temp->Data++)
		{
			cout << Temp->Data << '\t';
		}
	}
};

void main()
{
	setlocale(LC_ALL, "");

	int n;
	cout << "Введите размер дерева: "; cin >> n;
	Tree tree;
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100, tree.getRoot());
	}
	tree.print();
}