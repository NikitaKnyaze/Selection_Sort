// Сортировка выбором.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <future>
#include <thread>

void sortSelect(int arr[], int size, std::promise<int*>& prom)
{
	for (int i = 0; i < size - 1; ++i)
	{
		int min{ i };

		for (int j = i + 1; j < size; ++j)
		{
			if (arr[j] < arr[min])
			{
				min = j;
			}
		}

		if (min != i)
		{
			int temp = arr[i];
			arr[i] = arr[min];
			arr[min] = temp;
		}
	}
	prom.set_value(arr); 
}

int main()
{
	int arr[]{ 4, 22, 56, 88, 2, 45, 56, 7 };
	int size{ sizeof(arr) / sizeof(arr[0]) };

	std::promise<int*> myPromise{};

	std::future<int*> myFuture{ myPromise.get_future() };

	std::thread myThread(sortSelect, arr, size, std::ref(myPromise));

	myFuture.get();

	for (int i = 0; size > i; ++i)
	{
		std::cout << arr[i] << " ";
	}

	std::cout << std::endl;

	myThread.join();

	return EXIT_SUCCESS;
}