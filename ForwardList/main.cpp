//ForwardList
#include<iostream>
using namespace std;

//TODO:
//1. Проверочный код в секции HOME_WORK_1 должен заработать :
//https://github.com/okovtun/PV_225/blob/e27ac0456e5ae4235e83725eac11cf455de28748/DataContainers/ForwardList/main.cpp#L245


//2. В классе ForwardList написать метод reverse(), 
//который меняет порядок следования элементов на противоположный.


#define tab "\t"

template<typename T>class ForwardList;
template<typename T>class Iterator;

template<typename T>
class Element
{
	T Data;		//значение элемента
	Element<T>* pNext;	//адрес следующего элемента
	static int count;
public:
	Element(T Data, Element<T>* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		count++;
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		count--;
		cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList<T>;
	friend class Iterator<T>;
};

template<typename T>
int Element<T>::count = 0;

template<typename T>
class Iterator
{
	Element<T>* Temp;
public:
	Iterator<T>(Element<T>* Temp = nullptr) : Temp(Temp)
	{
		cout << "ItConstructor:\t" << this << endl;
	}
	~Iterator<T>()
	{
		cout << "ItDestructor:\t" << this << endl;
	}

	Iterator<T>& operator++()
	{
		Temp = Temp->pNext;
		return *this;
	}
	bool operator==(const Iterator<T>& other)const
	{
		return this->Temp == other.Temp;
	}
	bool operator!=(const Iterator<T>& other)const
	{
		return this->Temp != other.Temp;
	}
	T& operator*()
	{
		return Temp->Data;
	}
};

template<typename T>
class ForwardList	//Forward - односвязный, однонаправленный
{
	Element<T>* Head;	//Голова списка - содержит указатель на нулевой элемент списка
	int size;
public:

	Iterator<T> begin()
	{
		return Head;
	}
	Iterator<T> end()
	{
		return nullptr;
	}
	ForwardList()
	{
		Head = nullptr;	//Если список пуст, то его Голова указывает на 0
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	ForwardList(const std::initializer_list<T>& il) :ForwardList()
	{
		//il - initializer_list
		cout << typeid(il.begin()).name() << endl;
		for (T const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
	}
	~ForwardList()
	{
		while (Head)pop_front();
		cout << "LDestructor:\t" << this << endl;
	}

	//					Adding elements:
	void push_front(T Data)
	{
		/*
		//1) Создаем новый элемент:
		Element* New = new Element(Data);
		//2) Новый элемент должен указывать на начало списка:
		New->pNext = Head;
		//3) Голову списка "переводим" на новый элемент:
		Head = New;
		*/

		Head = new Element<T>(Data, Head);

		size++;
	}
	void push_back(T Data)
	{
		if (Head == nullptr)return push_front(Data);
		//1) Создаем новый элемент:
		Element<T>* New = new Element<T>(Data);
		//2) Доходим до конца списка:
		Element<T>* Temp = Head;
		while (Temp->pNext)
			Temp = Temp->pNext;
		//3) Добавляем элемент в конец списка:
		Temp->pNext = New;
		size++;
	}
	void insert(int Index, T Data)
	{
		if (Index == 0)return push_front(Data);
		if (Index > size)return;

		//1) Создаем новый элемент:
		//Element* New = new Element(Data);

		//2) Доходим до нужного элемента
		Element<T>* Temp = Head;
		for (int i = 0; i < Index - 1; i++)Temp = Temp->pNext;

		//3) Вставляем новый элемент в список:
		//New->pNext = Temp->pNext;
		//Temp->pNext = New;
		Temp->pNext = new Element<T>(Data, Temp->pNext);
		size++;
	}

	//					Erasing Elements
	void pop_front()
	{
		Element<T>* Erased = Head;	//1) запоминаем адрес удаляемого элемента
		Head = Head->pNext;		//2) исключаем элемент из стписка
		delete Erased;			//3) удаляем элемент из памяти

		size--;
	}

	void pop_back()
	{
		Element<T>* Temp = Head;
		while (Temp->pNext->pNext)
		{
			Temp = Temp->pNext;
		}
		delete Temp->pNext;
		Temp->pNext = nullptr;
		size--;
	}

	//					Methods:
	void print()const
	{
		//Element* Temp = Head;	//Temp - это итератор
		//Итератор - это указатель, при помощи которого можно получить доступ
		//к элементам структуры данных
		//while (Temp)
		//{
		//	cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		//	Temp = Temp->pNext;	//Переход на следующий элемент
		//}
		for (Element<T>* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Count of elements' list:" << size << endl;
		//cout << "Count all elements: " << Element::count << endl;
	}
	ForwardList<T> reverse()
	{
		ForwardList<T> result{};
		for (int i : *this)
			result.push_front(i);
		return result;
	}
	//					Operators:
	ForwardList<T> operator+(ForwardList<T>& other)
	{
		ForwardList result = *this;
		for (int i : other)
			push_back(i);
		return result;
	}
	friend class Iterator<T>;
};

#define HOME_WORK_1

void main()
{
	setlocale(LC_ALL, "");

#ifdef HOME_WORK_1
	ForwardList<int> list = { 3, 5, 8, 13, 21 };
	//list.print();
	cout << "list:\n";
	for (int i : list)cout << i << tab;cout << endl;

	ForwardList<int> list2 = { 34, 55, 89 };
	cout << "list2:\n";
	for (int i : list2)cout << i << tab; cout << endl;

	/*ForwardList<int> list3 = list + list2;
	cout << "list3:\n";
	for (int i : list3)cout << i << tab; cout << endl;*/

	cout << "Reverse list:\n";
	ForwardList<int> list4 = list.reverse();
	for (int i : list4)cout << i << tab; cout << endl;
#endif // HOME_WORK_1
}