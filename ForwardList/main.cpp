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
	static int count;
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		count++;
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		count--;
		cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList;
};

int Element::count = 0; // инициализируем статическую переменную,
						//объявленнную в классе Element

class ForwardList	//Forward - односвязный, однонаправленный
{
	Element* Head;	//Голова списка, содержит указатель на нулевой элемент списка
	int size;
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
		Head = new Element(Data, Head);
		//Element* New = new Element(Data);//1) Создаем новый элемент:
		//New->pNext = Head;//2) Новый элемент должен указывать на начало списка:
		//Head = New;//3) Голову списка "переводим" на новый элемент:
		size++;
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
		size++;
	}
	void insert(int Index, int Data)
	{
		if (Index == 0)return push_front(Data);
		if (Index > size)return;

		//1) Создаем новый элемент
		Element* New = new Element(Data);
		//2) Доходим до нужного элемента
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++) Temp = Temp->pNext;
		//3) 
		New->pNext = Temp->pNext;
		Temp->pNext = New;
		size++;
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
		cout << "Количество элементов списка: " << size << endl;
		cout << "Общее количество элементов: " << Element::count << endl;
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
	int value;
	int index;
	cout << "Введите инлекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list.insert(index, value);
	list.print();

	ForwardList list2;
	list2.push_back(3);
	list2.push_back(5);
	list2.push_back(8);
	list2.print();
}