#include<iostream>
using namespace std;

//TODO:
//1. Написать методы insert() и erase();
//2. Оптимизировать методы добавления элементов;

#define tab "\t"

class List
{
	class Element
	{
		int Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr) :Data(Data), pNext(pNext), pPrev(pPrev)
		{
			cout << "EConstructor:\t" << this << endl;
		}
		~Element()
		{
			cout << "EDestructor:\t" << this << endl;
		}
		friend class List;
	}*Head, *Tail;
	unsigned int size;
public:
	List()
	{
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	~List()
	{
		while (Tail)pop_back();
		cout << "LDestructor:\t" << this << endl;
	}
	//			Adding elements:
	void push_front(int Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data);
			
		}
		else
		{
			Element* New = new Element(Data);	//1)
			New->pNext = Head;					//2)
			Head->pPrev = New;					//3)
			Head = New;							//4)
		}
			size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data);
		}
		else
		{
			Element* New = new Element(Data);	//1)
			New->pPrev = Tail;					//2)
			Tail->pNext = New;					//3)
			Tail = New;							//4)
		}
		size++;
	}

//1. Написать методы insert() и erase();					******HOMEWORK******
	void insert(int index, int Data)
	{
		if (index > size - 1) return;
		if (!(index))
		{
			push_front(Data);
			return;
		}
		if (index == size - 1)
		{
			push_back(Data);
			return;
		}
		Element* New = new Element(Data);
		if (index <= size / 2)
		{
			Element* Temp = Head;
			for (int i = 0; i < index - 1; i++)Temp = Temp->pNext;
			/*New->pPrev = Temp;
			New->pNext = Temp->pNext;
			Temp->pNext = New;*/
			//2. Оптимизировать методы добавления элементов;			***HOMEWORK***
			Temp->pNext = new Element(Data, Temp->pNext, Temp->pPrev);
		}
		else
		{
			Element* Temp = Tail;
			for (int i = size; i > index - 1; i--)Temp = Temp->pPrev;
			/*New->pPrev = Temp;
			New->pNext = Temp->pNext;
			Temp->pNext = New;*/
			Temp = new Element(Data, Temp->pNext, Temp->pPrev);
		}
		size++;
	}
	//			Removing elements:
	void pop_front()
	{
		if (Head == nullptr && Tail == nullptr)return;
		if (Head == Tail)
		{
			delete Head;
			Head = Tail = nullptr;
			return;
		}
		// Исключаем элемент из списка
		Head = Head->pNext;
		// Удаляем элемент из памяти
		delete Head->pPrev;
		// Обнуляем адрес удаленного элемента
		Head->pPrev = nullptr;
		size--;
	}
	void pop_back()
	{
		if (Head ==  Tail)return pop_front();
		Tail = Tail->pPrev;
		delete Tail->pNext;
		Tail->pNext = nullptr;
		size--;
	}
//1. Написать методы insert() и erase();					******HOMEWORK******
	/*void erase(int index, int Data)
	{
		if (index <= size / 2)
		{
			Element* Temp = Head;
			for (int i = 0; i < index - 1; i++)Temp = Temp->pNext;
			Temp->pNext = 
		}
		else
		{
			Element* Temp = Tail;
			for (int i = size; i > index; i--)Temp = Temp->pPrev;

		}
		size--;
	}*/

	//			Methods:
	void print()const
	{
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
		{
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		}
		cout << "Count of size: " << size << endl;
	}
	void reverse_print()const
	{
		for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
		{
			cout << Temp->pNext << tab << Temp << tab << Temp->Data << tab << Temp->pPrev << endl;
		}
		cout << "Count of size: " << size << endl;
	}
};

void main()
{
	setlocale(LC_ALL, "Russian");

	int n;
	cout << "Input size of list: "; cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
	}
	//list.print();
	//list.reverse_print();
	//list.pop_back();
	list.insert(4, 777);
	list.print();
}