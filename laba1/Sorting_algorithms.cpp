

#include <iostream>
#include <chrono>

#include "Sorting_algorithms.h"


Sorting_algorithms::Sorting_algorithms() {
	Dialog_Loop();
}

void Sorting_algorithms::Dialog_Loop() {
	while (true) {
		Console_User_Dialog();
	}
}

void Sorting_algorithms::Console_User_Dialog()
{
	// Выбор пользователем размера массива
	if (Array_to_Sort != nullptr)
	{
		delete[] Array_to_Sort;
	}
	std::cout << "Hello!\nPlease, enter the array size from 2 to 1000: \n";		//
	Array_Size = Valid_Input(2, 1000);
	Array_to_Sort = new int[Array_Size];

	// Выбор пользователем метода заливки алгорима
	std::cout << "\nChoose the method of the array filling :\n"
		<< "1)Increasing \n2)Decreasing\n3)Random\n";

	int Choice_of_fill = Valid_Input(1, 3);

	Function_Call("fill", Choice_of_fill);

	Print_Array();

	//  Контрольная сумма и серии до сортировки
	int cont_sum_1 = Control_Sum();
	int num_ser_1 = Series();
	std::cout << "\nControl sum before sort: " << cont_sum_1
		<< "\nSeries before sort: " << num_ser_1 << "\n";

	// Выбор пользователем метода сортировки
	std::cout << "\nChoose the method of the array sort :\n"
		<< "1)Selection_Sort \n2)Shell_Sort \n3)HeapSort\n";

	int Choice_of_sort = Valid_Input(1, 3);

	Function_Call("sort", Choice_of_sort);

	Print_Array();

	//  Контрольная сумма и серии после сортировки
	int cont_sum_2 = Control_Sum();
	int num_ser_2 = Series();
		
	std::cout << "\nControl sum after sort: " << cont_sum_2 
		<< "\nSeries after sort: " << num_ser_2 << "\n";

	// Проверка контрольных сумм и кол-ва серий
	if (cont_sum_1 != cont_sum_2)
		std::cout << "Control sums doesn't match!\n";
	else
		std::cout << "Control sums is match!\n";

	if (num_ser_1 != num_ser_2)
		std::cout << "Series doesn't match!\n";
	else
		std::cout << "Series is match!\n";

	/* */
	std::cout << "C = " << Num_C << ", M = " << Num_M << "\n\n";

	Num_C = Num_M = 0;

	delete[] Array_to_Sort;
	Array_to_Sort = nullptr;

}

int Sorting_algorithms::Valid_Input(int min_range, int max_range)
{
	int result;
	while (!(std::cin >> result) || (result < min_range)
		|| (result > max_range)) {
		std::cout << "Incorrect input! Please, try again!\n";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	return result;
}

void Sorting_algorithms::Function_Call(const char operation[], int num)
{
	
	if(operation == "fill")
	{	// Для заполнения массива
		switch (num) 
		{
		case 1: Increasing_Fillage_of_Array(); break;
		case 2: Descreasing_Fillage_of_Array(); break;
		case 3: Random_Fillage_of_Array(); break;
		}
	}

	if (operation == "sort")
	{	// Для сортировки массива
		switch (num)
		{
		case 1: Benchmark(&Sorting_algorithms::Selection_Sort); break;
		case 2: Benchmark(&Sorting_algorithms::Shell_Sort); break;
		case 3: Benchmark(&Sorting_algorithms::HeapSort); break;
		}
	}
}

void Sorting_algorithms::Random_Fillage_of_Array()
{
	for (int i = 0; i < Array_Size; i++)
		Array_to_Sort[i] = (rand() % Array_Size);
}

void Sorting_algorithms::Descreasing_Fillage_of_Array()
{
	int j = 0;
	for (int i = Array_Size - 1; i >= 0; i--)
		Array_to_Sort[j++] = i;

}

void Sorting_algorithms::Increasing_Fillage_of_Array()
{
	for (int i = 0; i < Array_Size; i++)
		Array_to_Sort[i] = i;
}

inline void Sorting_algorithms::Swap_method(int i, int j)
{
	Num_C++;
	Array_to_Sort[i] = Array_to_Sort[i] + Array_to_Sort[j];
	Array_to_Sort[j] = Array_to_Sort[i] - Array_to_Sort[j];
	Array_to_Sort[i] = Array_to_Sort[i] - Array_to_Sort[j];
}

void Sorting_algorithms::Selection_Sort()
{
	for (int i = 0; i < Array_Size - 1; i++)
	{
		int min_i = i;

		for (int j = i + 1; j < Array_Size; j++)
		{
			Num_M++;
			if (Array_to_Sort[j] < Array_to_Sort[min_i])
				min_i = j;
		}
		Num_M++;
		if (min_i != i)
			Swap_method(i, min_i);
	}
}

void Sorting_algorithms::Shell_Sort()
{
	for (int step = Array_Size / 2; step > 0; step /= 2) {
		for (int i = step; i < Array_Size; i++) {
			Num_M++;
			for (int j = i - step; (j >= 0)
				&& (Array_to_Sort[j] > Array_to_Sort[j + step]); j -= step) {
				Swap_method(j, j + step);
			}
		}
	}
}

void Sorting_algorithms::HeapSort()
{
	for (int i = 0; i < Array_Size; i++) {
		for (int j = Array_Size / 2 - i / 2 - 1; j > -1; j--) {
			Num_M++;
			if (j * 2 + 2 <= Array_Size - 1 - i){
				Num_M++;
				if (Array_to_Sort[2 * j + 1] > Array_to_Sort[2 * j + 2]){
					Num_M++;
					if (Array_to_Sort[j] < Array_to_Sort[2 * j + 1])
						Swap_method(j, 2 * j + 1);
				}
				else{
					Num_M++;
					if (Array_to_Sort[j] < Array_to_Sort[2 * j + 2])
						Swap_method(j, 2 * j + 2);
				}
			}
			else{
				Num_M++;
				if (j * 2 + 1 <= Array_Size - 1 - i){
					Num_M++;
					if (Array_to_Sort[j] < Array_to_Sort[2 * j + 1])
						Swap_method(j, 2 * j + 1);
				}
			}
		}
		Swap_method(0, Array_Size - i - 1);
	}
}

int Sorting_algorithms::Control_Sum()
{
	int sum = 0;
	for (int i = 0; i < Array_Size; i++)
		sum += Array_to_Sort[i];
	return sum;
}

int Sorting_algorithms::Series()
{
	int num = 0;
	for (int i = 1; i < Array_Size; i++)
		if (Array_to_Sort[i] < Array_to_Sort[i - 1])
			num++;
	
	return num;
}

void Sorting_algorithms::Benchmark(void (Sorting_algorithms::* f)()) 
{
	auto begin = std::chrono::steady_clock::now();
	(this->*f)();
	auto end = std::chrono::steady_clock::now();
	auto elapsed_ms 
		= std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
	std::cout << "Time Elapsed: " << elapsed_ms.count() << " ns\n";
}

void Sorting_algorithms::Print_Array() 
{
	for (int i = 0; i < Array_Size; i++)
	{
		std::cout << Array_to_Sort[i] << "  ";
		if ((i != 0) && (i % 15 == 0))
			std::cout << "\n";
	}
	std::cout << "\n";
}

Sorting_algorithms::~Sorting_algorithms()
{
	if (Array_to_Sort != nullptr)
	{
		delete[] Array_to_Sort;
	}
}

