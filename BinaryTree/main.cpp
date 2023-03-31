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
	protected:
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
		friend class UniqueTree;
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
		if (this->Root == nullptr)this->Root = new Element(Data);
		if (Root == nullptr)return;
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
	void print(Element* Root)const
	{
		if (Root == nullptr)return;
		print(Root->pLeft);
		cout << Root->Data << '\t';
		print(Root->pRight);
	}
	/*int minValue()
	{
		int minValue;
		while (Root != nullptr)
		{
			minValue = Root->Data;
			Root = Root->pLeft;
		}
		return minValue;
	}*/
	int minValue(Element* Root)
	{
		if (Root == nullptr) return 0;
		/*if (Root->pLeft == nullptr) return Root->Data;
		return minValue(Root->pLeft);*/
		return Root->pLeft == nullptr ? Root->Data : minValue(Root->pLeft);
	}
	int maxValue(Element* Root)
	{
		if (Root == nullptr) 0;
		return Root->pRight ? maxValue(Root->pRight) : Root->Data;
	}
	int Count(Element* Root)
	{
		if (Root == nullptr) return 0;
		else return Count(Root->pLeft) + Count(Root->pRight) + 1;
	}
	int Sum(Element* Root)
	{
		if (Root == nullptr)return 0;
		else return Sum(Root->pLeft) + Sum(Root->pRight) + Root->Data;
	}
	double Avg()
	{
		return (double)Sum(Root) / Count(Root);
	}

};

class UniqueTree :public Tree
{
public:
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)this->Root = new Element(Data);
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr) Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else if (Data > Root->Data)
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}
};

void main()
{
	setlocale(LC_ALL, "");

	int n;
	cout << "Input size of tree: "; cin >> n;
	Tree tree;
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100, tree.getRoot());
	}		
	tree.print(tree.getRoot());
	cout << endl;
	//cout << "minValue = " << tree.minValue() << endl;
	cout << "minimal value in tree: " << tree.minValue(tree.getRoot()) << endl;
	cout << "maximal value in tree: " << tree.maxValue(tree.getRoot()) << endl;
	cout << "Count of elements of tree: " << tree.Count(tree.getRoot()) << endl;
	cout << "Sum of elements of tree: " << tree.Sum(tree.getRoot()) << endl;
	cout << "Avg of elements of tree: " << tree.Avg() << endl;

	UniqueTree tree2;
	for (int i = 0; i < n; i++)
	{
		tree2.insert(rand() % 100, tree2.getRoot());
	}
	tree2.print(tree2.getRoot());
	cout << "minimal value in tree: " << tree2.minValue(tree2.getRoot()) << endl;
	cout << "maximal value in tree: " << tree2.maxValue(tree2.getRoot()) << endl;
	cout << "Count of elements of tree: " << tree2.Count(tree2.getRoot()) << endl;
	cout << "Sum of elements of tree: " << tree2.Sum(tree2.getRoot()) << endl;
	cout << "Avg of elements of tree: " << tree2.Avg() << endl;

}