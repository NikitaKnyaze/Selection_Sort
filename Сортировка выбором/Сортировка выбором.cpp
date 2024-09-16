// Сортировка выбором.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <future>
#include <thread>

void min_index(int* arr, int start, const int size, std::promise<int>& prom)
{
	int min = start;

	for (int i = start + 1; i < size; ++i) {
		if (arr[i] < arr[min]) {
			min = i;
		}
	}
	prom.set_value(min);
}

void sortSelect(int* arr, const int size)
{
	for (int i = 0; i < size - 1; i++) {
		std::promise<int> myPromise{};

		std::future<int> myFuture{ myPromise.get_future() };
	
		std::thread t(min_index, std::ref(arr), i, size, std::ref(myPromise));

		t.detach();

		int min_index = myFuture.get();

		if(i != min_index)
		{
			int temp = arr[i];
			arr[i] = arr[min_index];
			arr[min_index] = temp;
		}
	}
}

int main()
{
	int arr[]{ 4, 22, 56, 88, 2, 45, 56, 5 };
	int size{ sizeof(arr) / sizeof(arr[0]) };

	sortSelect(arr, size);

	for (const auto a : arr)
	{
		std::cout << a << " ";
	}

	std::cout << std::endl;

	return EXIT_SUCCESS;
}