//ForwardList
#include<iostream>
using namespace std;

//TODO:
//Оптимизировать методы

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

#define tab "\t"
class ForwardList	//Forward - односвязный, однонаправленный
{
	Element* Head;	//Голова списка, содержит указатель на нулевой элемент списка
public:
	ForwardList()
	{
		Head = nullptr;		//Если список пуст, то его голова указывает на 0.
		cout << "LConstructor:\t" << this << endl;
	}
	//Деструктор дожен очищать список перед удалением
	~ForwardList()
	{
		while (Head->pNext != nullptr) pop_front();
		cout << "LDestructor:\t" << this << endl;
	}
	//				Methods:

	//		Adding elements:
	void push_front(int Data)
	{
		Head = new Element(Data, Head);
		//Element* New = new Element(Data);				//1) Создаем новый элемент
		//New->pNext = Head;							//2) Новый элемент должен указывать на начало списка
		//Head = New;									//3) Голову списка "переводим" на новый элемент
	}
	void push_back(int Data)
	{
		if (Head == nullptr)return push_front(Data);
		//Element* New = new Element(Data);			//1) Создаем новый элемент:
		Element* Temp = Head;						//2) Доходим до конца списка:
		while (Temp->pNext != nullptr)
			Temp = Temp->pNext;
		//Temp->pNext = New;						//3) Добавляем элемент в конец списка:
		Temp->pNext = new Element(Data);
	}
	//void insert(int Data, int Index);		//вставляет элемент в список по заданному индексу
	void insert(int Index, int Data)		//вставляет элемент в список по заданному индексу
	{
		if (!(Index))
		{
			push_front(Data);
			return;
		}
		Element* Temp = Head;				//Итератор
		for (int i = 0; i < Index - 1; i++)	//Переходим до элемента перед нужным
		{
			Temp = Temp->pNext;
			if (!(Temp->pNext->pNext))
			{
				push_back(Data);
				return;
			}
			if (!(Temp->pNext))return;
		}
		Temp->pNext = new Element(Data,Temp->pNext);
		//Element* New = new Element(Data);	//Создаем новый элемент
		//New->pNext = Temp->pNext;			//Перепривязываем хвост списка к новому элементу
		//Temp->pNext = New;					//Привязываем элемент к списку
	}

	//		Deleting elements:
	//В класс ForwardList добавить следующие методы :
	//void pop_front();	//удаляет элемент c начала списка
	
	void pop_front()	//удаляет элемент c начала списка
	{
		Element* Temp = Head;				//Создаем итератор
		Temp = Temp->pNext;				//Переходим на второй элемент
		Head = Temp;						//Голову списка "переводим" на второй элемент
	}

	//void pop_back();	//удаляет элемент c конца списка
	void pop_back()		//удаляет элемент c конца списка
	{
		if (Head == nullptr)return;			//Если список пуст, прерываем выполнение программы
		Element* Temp = Head;				//Создаем итератор
		while (Temp->pNext->pNext)			//
			Temp = Temp->pNext;				//Доходим до предпоследнего элемента списка
		delete Temp->pNext;					//удаляем последний элемент
		Temp->pNext = nullptr;
	}
	//void erase(int Index);				//удаляет элемент из списка по заданному индексу
	void erase(int Index)				//удаляет элемент из списка по заданному индексу
	{
		if (!(Index))
		{
			pop_front();
			return;
		}
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)
		{
			Temp = Temp->pNext;
		}
		Element* buffer = Temp->pNext->pNext;
		delete Temp->pNext;
		Temp->pNext = buffer;
	}

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
	Element* read_front()
	{
		Element* Temp = Head;
		Temp = Temp->pNext;
		return Temp;
	}
	Element* read(int Index)
	{
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++) Temp = Temp->pNext;
		return Temp;
	}
	//CopyMethods;
	void copy_ForwardList(ForwardList& original)
	{
		Element* Temp = Head;
		for (int i = 0; original.read(i)->pNext = nullptr; i++)
		{
			push_back(original.read(i)->Data);
		}
	}
};

void main()
{
	setlocale(LC_ALL, "");
	int n;
	cout << "Input size of list: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	list.print();

	////		CHECK push_front()
	//cout << "Using push_front()" << endl;
	//list.push_front(123);
	//list.print();

	////		CHECK push_back()
	/*cout << "Using push_back()" << endl;
	list.push_back(123);
	list.print();*/
	
	//		CHECK pop_front()
	cout << "using pop_front()" << endl;
	list.pop_front();
	list.print();

	////		CHECK pop_back()
	/*cout << "using pop_back()" << endl;
	list.pop_back();
	list.print();*/

	////		CHECK insert(Index, Data)
	//int Index, Data;
	//cout << "using insert(Index, Data)" << endl;
	//cout << "Input Index: "; cin >> Index;
	//cout << "Input Data: "; cin >> Data;
	//list.insert(Index, Data);
	//list.print();

	////		CHECK erase(I`ndex)
	/*int Index;
	cout << "Using erase(Index)" << endl;
	cout << "Input Index: "; cin >> Index;
	list.erase(Index);
	list.print();*/
	
	//////		CHECK copy_method()
	//cout << "Using copy_method()" << endl;
	//cout << list.read(0) << endl;
	//cout << list.read(1) << endl;
	//cout << list.read(2) << endl;
	//cout << list.read(3) << endl;
	//cout << list.read(4) << endl;
	//ForwardList list2;
	//list2.copy_ForwardList(list);
	//list2.print();
}