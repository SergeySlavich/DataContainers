//ForwardList
#include"ForwarfList.cpp"

//#define BASE_CHECK
//#define RANGE_BASED_FOR_ARRAY
#define HOME_WORK_1
//#define RANGE_BASED_FOR_LIST

//TODO:
//Проверочный код в секции HOME_WORK_1 должен заработать :
//https://github.com/okovtun/PV_225/blob/e27ac0456e5ae4235e83725eac11cf455de28748/DataContainers/ForwardList/main.cpp#L245

template<typename T>T operator+(const ForwardList<T>& left, const ForwardList<T>& right)
{
	ForwardList<T> result = left;
	for (right.Head; right.Temp->pNext == nullptr; right.Temp = right.Temp->pNext)
	{
		result.push_back(right->Data);
	}
	return result;
}

void main()
{
	setlocale(LC_ALL, "Russian");

#ifdef BASE_CHECK
	int n;
	cout << "Input size of list: "; cin >> n;
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
	cout << "Input index of adding element: "; cin >> index;
	cout << "Input data of adding element: "; cin >> value;
	list.insert(index, value);
	list.print();

	ForwardList list2;
	list2.push_back(3);
	list2.push_back(5);
	list2.push_back(8);
	list2.print();
#endif // BASE_CHECK

#ifdef RANGE_BASED_FOR_ARRAY
	int arr[] = { 3, 5, 8, 13, 21 };

	/*for (int i = 0; i < sizeof(arr)/sizeof(int); i++)
	{
		cout << arr[i] << tab;
	}
	cout << endl;*/
	//Range-based for
	for (int i : arr)
	{
		cout << i << tab;
	}
	cout << endl;
#endif

#ifdef RANGE_BASED_FOR_LIST
	ForwardList<int> list{ 3, 5, 8, 13, 21 };
	for (int i : list) std::cout << i << tab; std::cout << endl;
	
	ForwardList<double> d_list{ 2.7, 3.14, 8, 13, 21 };
	for (double i : d_list) std::cout << i << tab; std::cout << endl;
	
	ForwardList<std::string> s_list{ "Хорошо", "живет", "на", "свете", "Винни", "Пух"};
	for (std::string i : s_list) std::cout << i << tab; std::cout << endl;
#endif

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

	ForwardList<int> list3 = list;// +list2;
	for (int i : list3)cout << i << tab; cout << endl;
#endif // HOME_WORK_1
}