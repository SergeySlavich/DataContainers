#include"List.h"

//TODO:
//От ветки 'TemplatedList2' создать ветку 'SeparatedList2' и в ней разделить класс 'List' на файлы.



//#define BASE_CHECK

void main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK
	int n;
	cout << "Ââåäèòå ðàçìåð ñïèñêà: "; cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
	}
	list.print();
	list.reverse_print();

	int index;
	int value;
	cout << "Ââåäèòå èíäåêñ äîáàâëÿåìîãî ýëåìåíòà: "; cin >> index;
	cout << "Ââåäèòå çíà÷åíèå äîáàâëÿåìîãî ýëåìåíòà: "; cin >> value;
	list.insert(index, value);
	list.print();
	list.reverse_print();
#endif // BASE_CHECK

	List<double> list = { 3.2, 5.6, 8.7, 13.4, 21.3 };

	//list.print();
	for (int i : list)
	{
		cout << i << tab;
	}
	cout << endl;

	for (double& i : list)i *= 10;

	print(list);
	for (List<double>::ReverseIterator rit = list.rbegin(); rit != list.rend(); rit++)*rit /= 10;
	reverse_print(list);
}

