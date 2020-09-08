#include "Sorting_algorithms.h"
#include <iostream>
#include <chrono>
#include <functional>


void Sorting_algorithms::Dialog_Loop()
{
	while (true)
	{
		Console_User_Dialog();
	}
}

// Имплементация фнункции диалога
void Sorting_algorithms::Console_User_Dialog()
{
	// Выбор пользователем размера массива
	std::cout << "Hello!\nPlease, enter the array size from 2 to 1000: \n";
	
	while (!(std::cin >> Array_Size) || (Array_Size < 2) || (Array_Size > 1000))
	{	// Мини-валидация ввода
		std::cout << "Incorrect value!\n";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	Array_to_Sort = new int[Array_Size];

	// Выбор пользователем метода заливки алгорима
	std::cout << "Choose the method of the array filling :\n"
		<< "1)Increasing \n2)Decreasing\n3)Random\n";

	int Choice_of_fill;
	do
	{
		std::cin >> Choice_of_fill;

		switch (Choice_of_fill)
		{
		default: std::cout << "Incorrect input! Please, try again!\n";
		case 1: Increasing_Fillage_of_Array(); break;
		case 2: Descreasing_Fillage_of_Array(); break;
		case 3: Random_Fillage_of_Array(); break;
		}

	} while ((Choice_of_fill < 1) || (Choice_of_fill > 3));
	Print_Array();
	// Выбор пользователем метода сортировки
	std::cout << "Choose the method of the array sort :\n"
		<< "1)Selection_Sort \n2)Shell_Sort \n3)HeapSort\n";

	int Choice_of_sort;
	do
	{
		std::cin >> Choice_of_sort;
		// Вход в выбранную функцию сортировки
		switch (Choice_of_sort)
		{
		default: std::cout << "Incorrect input! Please, try again!\n";
		case 1: Benchmark(&Sorting_algorithms::Selection_Sort);break;
		case 2: Benchmark(&Sorting_algorithms::HeapSort);break;
		case 3: Benchmark(&Sorting_algorithms::HeapSort);break;
		}

	} while ((Choice_of_sort < 1) || (Choice_of_sort > 3));

	Print_Array();
	std::cout << Enumerator_of_Swaps << std::endl;;
	Enumerator_of_Swaps = 0;
	delete [] Array_to_Sort;
}

// Реализация функции заполнения массива случайными числами
void Sorting_algorithms::Random_Fillage_of_Array()
{
	for (int i = 0; i < Array_Size; i++)	
		Array_to_Sort[i] = (rand() % Array_Size);	
}

// Реализация функции заполнения массива убывающей последовательностью
void Sorting_algorithms::Descreasing_Fillage_of_Array()
{
	for (int i = Array_Size - 1; i >= 0; i--)
		Array_to_Sort[i] = i;
}

// Реализация функции заполнения массива возрастающей последовательностью
void Sorting_algorithms::Increasing_Fillage_of_Array()
{
	for (int i = 0; i < Array_Size; i++)	
		Array_to_Sort[i] = i;	
}

void Sorting_algorithms::Swap_method(int i, int j)
{
	Array_to_Sort[i] = Array_to_Sort[i] + Array_to_Sort[j];
	Array_to_Sort[j] = Array_to_Sort[i] - Array_to_Sort[j];
	Array_to_Sort[i] = Array_to_Sort[i] - Array_to_Sort[j];
	Enumerator_of_Swaps++;
}

// Реализация функции сортировки выбором
void Sorting_algorithms::Selection_Sort()
{
	for (int i = 0; i < Array_Size - 1; i++)
	{
		int min_i = i;

		for (int j = i + 1; j < Array_Size; j++)		
			if (Array_to_Sort[j] < Array_to_Sort[min_i])			
				min_i = j;	

		if (min_i != i)		
			Swap_method(i, min_i);		
	}
}

// Реализация функции сортировки методом Шелла
void Sorting_algorithms::Shell_Sort()
{
	for (int step = Array_Size / 2; step > 0; step /= 2)	
		for (int i = step; i < Array_Size; i++)		
			for (int j = i - step; (j >= 0) && (Array_to_Sort[j] > Array_to_Sort[j + step]); j -= step)		
				Swap_method(j, j + step);						
}

// Реализация функции пирамидальной сортировки
void Sorting_algorithms::HeapSort()
{
	for (int i = 0; i < Array_Size; i++)
	{
		for (int j = Array_Size / 2 - 1 - i / 2; j > -1; j--)
		{
			if (j * 2 + 2 <= Array_Size - 1 - i)
			{
				if (Array_to_Sort[2 * j + 1] > Array_to_Sort[2 * j + 2])
				{
					if (Array_to_Sort[j] < Array_to_Sort[2 * j + 1])
					{
						Swap_method(j, 2 * j + 1);
					}
				}
				else
					if (Array_to_Sort[j] < Array_to_Sort[2 * j + 2])
					{
						Swap_method(j, 2 * j + 2);
					}
			}
			else
				if (j * 2 + 1 <= Array_Size - 1 - i)
					if (Array_to_Sort[j] < Array_to_Sort[2 * j + 1])
					{
						Swap_method(j, 2 * j + 1);
					}
		}
		Swap_method(0, Array_Size - i - 1);
	}
}

void Sorting_algorithms::Benchmark(void (Sorting_algorithms::*f)())
{
	auto begin = std::chrono::steady_clock::now();
	(this->*f)();
	auto end = std::chrono::steady_clock::now();
	auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
	std::cout << "Time Elapsed: " << elapsed_ms.count() << " ms\n";
}

void Sorting_algorithms::Print_Array()
{
	for (int i = 0; i < Array_Size; i ++)
	{		
		std::cout << Array_to_Sort[i] << "  ";
		if((i!=0)&&(i % 15 == 0))
			std::cout << "\n";
	}
	std::cout << "\n";
}

Sorting_algorithms::~Sorting_algorithms()
{
	delete [] Array_to_Sort;
}

