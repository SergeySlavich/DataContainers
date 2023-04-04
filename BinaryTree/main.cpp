#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

//TODO:
//int minValue();	DONE
//int maxValue();	DONE
//int Count();		DONE
//int Sum();		DONE
//int Avg();		DONE
//int Depth();		//возвращает глубину дерева
//void Clear();		//Удаляет все элементы из Бинарного дерева
//void Erase();		//удаляет из дерева заданное значение

//Обеспечить вызов методов без необходимости передавать в них корень дерева
//tree.print(tree.GetRoot()) = > tree.print();

#define DEBUG

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
	Tree(const std::initializer_list<int>& il) :Tree()
	{
		for (int i : il)insert(i);
	}
	Tree(const Tree& other) :Tree()
	{
		Copy(other.Root);
	}
	~Tree()
	{
		Clear(Root);
		cout << "TDestructor:\t" << this << endl;
	}
	//Обеспечить вызов методов без необходимости передавать в них корень дерева
	//tree.print(tree.GetRoot()) = > tree.print();
	void insert(int Data)
	{
		insert(Data, Root);
	}
	void Clear()
	{
		Clear(Root);
	}
	void print()
	{
		print(this->getRoot());
	}
	int minValue()
	{
		return minValue(this->getRoot());
	}
	int maxValue()
	{
		return maxValue(this->getRoot());
	}
	int Count()
	{
		return Count(this->getRoot());
	}
	int Sum()
	{
		return Sum(this->getRoot());
	}
	int Depth()					//TODO (in progress)
	{
		return Depth(this->getRoot());
	}
	double Avg()
	{
		return (double)Sum(Root) / Count(Root);
	}
	void clear(int Data)
	{
		clear(Data, Root);
	}
protected:
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
	void Clear(Element* Root)
	{
		if (Root == nullptr) return;
		Clear(Root->pLeft);
		Clear(Root->pRight);
		delete Root;
	}
	void Copy(Element* Root)
	{
		if (Root == nullptr) return;
		insert(Root->Data, this->Root);
		Copy(Root->pLeft);
		Copy(Root->pRight);
	}
	void print(Element* Root)const
	{
		if (Root == nullptr)return;
		print(Root->pLeft);
		cout << Root->Data << '\t';
		print(Root->pRight);
	}
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
	int Depth(Element* Root)							//возвращает глубину дерева - TODO (in progress)
	{
		if (Root == nullptr) return 0;

		int l_depth = Depth(Root->pLeft) + 1;
		int r_depth = Depth(Root->pRight) + 1;
		return l_depth < r_depth ? r_depth : l_depth;
		/*return
			Root == nullptr ? 0 :
			Depth(Root->pLeft) + 1 >
			Depth(Root->pRight) + 1 ?
			Depth(Root->pLeft) + 1 :
			Depth(Root->pRight) + 1;*/
		/*if (Root == nullptr)return 0;
		if (Depth(Root->pLeft) + 1 > Depth(Root->pRight) + 1)return Depth(Root->pLeft) + 1;
		else return Depth(Root->pRight) + 1;*/
	}   
	void clear(int Data, Element* Root)
	{

	}
};

class UniqueTree :public Tree
{
protected:
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
public:
	void insert(int Data)
	{
		insert(Data, Root);
	}
};

#define BASE_CHECK
//#define DEPTH_CHECK

void main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK
	int n;
	cout << "Input size of tree: "; cin >> n;
	Tree tree;
	for (int i = 0; i < n; i++)
	{
		int value = rand() % 100;
		tree.insert(value);
		cout << value << ' ';
	}
	cout << endl;
	//cout << "method \"print(getRoot())\":" << endl;
	//tree.print(tree.getRoot());
	cout << "method \"print()\":\n";
	tree.print();
	cout << endl;
	//cout << "minimal value in tree by minValue(tree.getRoot()): " << tree.minValue(tree.getRoot()) << endl;
	cout << "minimal value in tree by minValue(): " << tree.minValue() << endl;
	//cout << "maximal value in tree by maxValue(tree.getRoot()): " << tree.maxValue(tree.getRoot()) << endl;
	cout << "maximal value in tree by maxValue(): " << tree.maxValue() << endl;
	//cout << "Count of elements of tree by Count(tree.getroot()): " << tree.Count(tree.getRoot()) << endl;
	cout << "Count of elements of tree by Count(): " << tree.Count() << endl;
	//cout << "Sum of elements of tree by Sum(tree.getRoot()): " << tree.Sum(tree.getRoot()) << endl;
	cout << "Sum of elements of tree by Sum(): " << tree.Sum() << endl;
	cout << "Avg of elements of tree: " << tree.Avg() << endl;
	//cout << "Depth of tree by Depth(tree.getRoot()): " << tree.Depth(tree.getRoot()) << endl;
	cout << "Depth of tree by Depth(): " << tree.Depth() << endl;

	UniqueTree tree2;
	for (int i = 0; i < n; i++)
	{
		tree2.insert(rand() % 100);
	}
	tree2.print();
	cout << "method \"print()\":\n";
	tree2.print();
	cout << "minimal value in tree: " << tree2.minValue() << endl;
	cout << "maximal value in tree: " << tree2.maxValue() << endl;
	cout << "Count of elements of tree: " << tree2.Count() << endl;
	cout << "Sum of elements of tree: " << tree2.Sum() << endl;
	cout << "Avg of elements of tree: " << tree2.Avg() << endl;
	cout << "Depth of tree by Depth(): " << tree2.Depth() << endl;
#endif

#ifdef DEPTH_CHECK
	Tree tree = { 50, 25, 75, 16, 32, 64, 80, 48, 49 };
	tree.print();
	cout << "\ndepth of tree: " << tree.Depth() << endl;

	Tree tree2 = tree;
	tree2.print();
#endif
}