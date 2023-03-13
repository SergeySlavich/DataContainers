//ForwardList
#include<iostream>
using namespace std;

//TODO:
//В класс ForwardList добавить следующие методы :
//void pop_front();	//удаляет элемент c начала списка
//void pop_back();	//удаляет элемент c конца списка

//void insert(int Data, int Index);	//вставляет элемент в список по заданному индексу
//void erase(int Index);				//удаляет элемент из списка по заданному индексу

//Деструктор дожен очищать список перед удалением

//CopyMethods;
//MoveMethods;

class Element
{
	int Data;		//значение элемента
	Element* pNext;	//Адрес следующего элемента
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList;
};

class ForwardList	//Forward - односвязный, однонаправленный
{
	Element* Head;	//Голова списка, содержит указатель на нулевой элемент списка
public:
	ForwardList()
	{
		Head = nullptr;		//Если список пуст, то его голова указывает на 0.
		cout << "LConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		cout << "LDestructor:\t" << this << endl;
	}
	//		Adding elements:
	void push_front(int Data)
	{
		//1) Создаем новый элемент:
		Element* New = new Element(Data);
		//2) Новый элемент должен указывать на начало списка:
		New->pNext = Head;
		//3) Голову списка "переводим" на новый элемент:
		Head = New;
	}
#define tab "\t"
	void push_back(int Data)
	{
		if (Head == nullptr)return push_front(Data);
		//1) Создаем новый элемент:
		Element* New = new Element(Data);
		//2) Доходим до конца списка:
		Element* Temp = Head;
		while (Temp->pNext != nullptr)
			Temp = Temp->pNext;
		//3) Добавляем элемент в конец списка:
		Temp->pNext = New;
	}
	//				Methods:
	void print()const
	{
		Element* Temp = Head;	//Temp - Это итератор, при помощи 
		//которого можно получить доступ к элементам структуры данных
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;	//Переход на следующий элемент
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
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	list.print();
	//list.push_back(123);
	//list.print();
}