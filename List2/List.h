#pragma once
#include<iostream>
#include"List.cpp"
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"

template<typename T>class List
{
	class Element {}*Head, * Tail;
	unsigned int size;
	class ConstBaseIterator{};
public:
	class ConstIterator :public ConstBaseIterator{};
	class ConstReverseIterator :public ConstBaseIterator{};
	class Iterator :public ConstIterator{};
	ConstIterator cbegin()const;
	ConstIterator cend()const;
	ConstIterator begin()const;
	ConstIterator end()const;
	Iterator begin();
	Iterator end();

	ConstReverseIterator crbegin()const;
	ConstReverseIterator crend()const;
	ReverseIterator rbegin();
	ReverseIterator rend();

	List();
	List(const std::initializer_list<T>& il) :List();
	~List();

	//					Adding elements:
	void List<T>::push_front(T Data);
	void List<T>::push_back(T Data);
	void List<T>::insert(int Index, T Data);

	//				Removing elements:
	void List<T>::pop_front();
	void List<T>::pop_back();

	//				Methods:
	void List<T>::print()const;
	void List<T>::reverse_print()const;
};

template<typename T>void print(const List<T>& list);
template<typename T>void reverse_print(const List<T>& list);