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

template<typename T>class Element
{
	T Data;		//значение элемента
	Element<T>* pNext;	//адрес следующего элемента
	static int count;
public:
	Element(T Data, Element<T>* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		count++;
#ifdef DEBUG
		cout << "EConstructor:\t" << this << endl;
#endif // DEBUG
	}
	~Element()
	{
		count--;
#ifdef DEBUG
		cout << "EDestructor:\t" << this << endl;
#endif // DEBUG
	}
	friend class ForwardList<T>;
	friend class Iterator<T>;
	friend class ConstIterator;
};

template<typename T>int Element<T>::count = 0;

template<typename T>class ConstIterator
{
	Element<T>* Temp;
public:
	ConstIterator(Element<T>* Temp = nullptr) :Temp(Temp)
	{
#ifdef DEBUG
		cout << "ItConstructor:\t" << this << endl;
#endif // DEBUG
	}
	~ConstIterator()
	{
#ifdef DEBUG
		cout << "ItDestructor:\t" << this << endl;
#endif // DEBUG
	}

	ConstIterator<T>& operator++()
	{
		Temp = Temp->pNext;
		return *this;
	}

	bool operator==(const ConstIterator<T>& other)const
	{
		return this->Temp == other.Temp;
	}
	bool operator!=(const ConstIterator<T>& other)const
	{
		return this->Temp != other.Temp;
	}
	const T& operator*()const
	{
		return Temp->Data;
	}
};

template<typename T>class Iterator
{
	Element<T>* Temp;
public:
	Iterator<T>(Element<T>* Temp = nullptr) : Temp(Temp)
	{
#ifdef DEBUG
		cout << "ItConstructor:\t" << this << endl;
#endif // DEBUG
	}
	~Iterator<T>()
	{
#ifdef DEBUG
		cout << "ItDestructor:\t" << this << endl;
#endif // DEBUG
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

template<typename T>class ForwardList	//Forward - односвязный, однонаправленный
{
	Element<T>* Head;	//Голова списка - содержит указатель на нулевой элемент списка
	int size;
public:
	ConstIterator<T> cbegin()const
	{
		return Head;
	}
	Iterator<T> begin()
	{
		return Head;
	}
	ConstIterator<T> cend()const
	{
		return nullptr;
	}
	Iterator<T> end()
	{
		return nullptr;
	}
	ForwardList()
	{
		Head = nullptr;	//Если список пуст, то его Голова указывает на 0
		size = 0;
#ifdef DEBUG
		cout << "LConstructor:\t" << this << endl;
#endif // DEBUG
	}
	ForwardList(const std::initializer_list<T>& il) :ForwardList()
	{
		//il - initializer_list
		//initializer_list - это контейнер.
		//Контейнер - это объект, который организует хранение других объектов в памяти.
		//Как и у любого другого контейнера, у initilizer_list есть методы begin() и end()
		//begin() - возвращает итератор на начало контейнера.
		//end()   - возвращает итератор на конец контейнера.
		cout << typeid(il.begin()).name() << endl;
		for (T const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
	}
	ForwardList(const ForwardList<T>& other)
	{
		for (Element<T>* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_front(Temp->Data);
		reverse();
		cout << "CopyConstructor:" << this << endl;
	}
	~ForwardList()
	{
		while (Head)pop_front();
#ifdef DEBUG
		cout << "LDestructor:\t" << this << endl;
#endif // DEBUG
	}

	//					Adding elements:
	void push_front(T Data)
	{
		/*		//1) Создаем новый элемент:
		Element* New = new Element(Data);
		//2) Новый элемент должен указывать на начало списка:
		New->pNext = Head;
		//3) Голову списка "переводим" на новый элемент:
		Head = New;		*/
		Head = new Element<T>(Data, Head);
		size++;
	}
	void push_back(T Data)
	{
		if (Head == nullptr)return push_front(Data);
		//1) Создаем новый элемент:
		//Element<T>* New = new Element<T>(Data);
		//2) Доходим до конца списка:
		Element<T>* Temp = Head;
		while (Temp->pNext)
			Temp = Temp->pNext;
		//3) Добавляем элемент в конец списка:
		Temp->pNext = new Element<T>(Data);
		size++;
	}
	void insert(int Index, T Data)
	{
		if (Index == 0)return push_front(Data);
		if (Index > size)return;

		//Element* New = new Element(Data);		//1) Создаем новый элемент

		Element<T>* Temp = Head;				//2) Доходим до нужного элемента
		for (int i = 0; i < Index - 1; i++)Temp = Temp->pNext;

		
		//New->pNext = Temp->pNext;				//3) Вставляем новый элемент в список
		//Temp->pNext = New;
		Temp->pNext = new Element<T>(Data, Temp->pNext);
		size++;
	}

	//					Erasing Elements
	void pop_front()
	{
		Element<T>* Erased = Head;			//1) запоминаем адрес удаляемого элемента
		Head = Head->pNext;					//2) исключаем элемент из стписка
		delete Erased;						//3) удаляем элемент из памяти
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
	void reverse()
	{
		ForwardList<T> buffer;
		while (Head)
		{
			buffer.push_front(Head->Data);	//Начальный элемент добавляет в начало буфера
			pop_front();					//удаляем начальный элемент из исходного списка
		}
		Head = buffer.Head;
		buffer.Head = nullptr;
	}
	ForwardList<T> reverse()
	{
		ForwardList<T> result{};
		for (int i : *this)
			result.push_front(i);
		return result;
	}
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
		cout << "Count of all elements: " << Element::count << endl;
	}
	
	//					Operators:
	ForwardList<T> operator+(ForwardList<T>& other)
	{
		ForwardList<T> result = {};
		for (int i : *this)
			result.push_back(i);
		for (int i : other)
			result.push_back(i);
		return result;
	}
};
template<typename T>ForwardList<T> operator+(const ForwardList<T>& left, const ForwardList<T>& right)
{
	ForwardList<T> cat;
	for (ConstIterator<T> it = left.cbegin(); it != left.cend(); ++it)
		cat.push_back(*it);
	for (ConstIterator<T> it = right.cbegin(); it != right.cend(); ++it)
		cat.push_back(*it);
	return cat;
}

//#define BASE_CHECK
//#define RANGE_BASED_FOR_ARRAY
//#define RANGE_BASED_FOR_LIST
#define HOME_WORK_1
//#define PREFORMANCE_CHECK

void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
		//list.push_back(rand() % 100);
	}
	list.print();
	//list.push_back(123);

	int value;
	int index;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list.insert(index, value);
	list.print();

	ForwardList list2;
	list2.push_back(3);
	list2.push_back(5);
	list2.push_back(8);
	list2.print();
#endif // BASE_CHECK

#ifdef RANGE_BASED_FOR_ARRAY
	int arr[] = { 3,5,8,13,21 };
	/*for (int i = 0; i < sizeof(arr)/sizeof(int); i++)
	{
		cout << arr[i] << tab;
	}
	cout << endl;*/

	//Range-based for
	//https://legacy.cplusplus.com/doc/tutorial/control/#:~:text=equal%20to%2050.-,Range%2Dbased%20for%20loop,-The%20for%2Dloop
	for (int i : arr)
	{
		cout << i << tab;
	}
	cout << endl;
#endif // RANGE_BASED_FOR_ARRAY

#ifdef RANGE_BASED_FOR_LIST
	ForwardList list = { 3, 5, 8, 13, 21 };
	for (int i : list)cout << i << tab; cout << endl;
#endif // RANGE_BASED_FOR_LIST


#ifdef HOME_WORK_1
	ForwardList<int> list = { 3, 5, 8, 13, 21 };
	//list.print();
	for (int i : list)
	{
		cout << i << tab;
	}
	cout << endl;

	ForwardList<int> list2 = { 34, 55, 89 };
	for (int i : list2)cout << i << tab; cout << endl;

	ForwardList<int> list3 = list + list2;
	for (int i : list3)cout << i << tab; cout << endl;

	for (int i : list)cout << i << tab; cout << endl;
#endif // HOME_WORK_1

#ifdef PREFORMANCE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
	}
	cout << "Список заполнен" << endl;
	ForwardList list2 = list;
	//for (int i : list)cout << i << tab; cout << endl;
	//for (int i : list2)cout << i << tab; cout << endl;  
#endif // PREFORMANCE_CHECK

}