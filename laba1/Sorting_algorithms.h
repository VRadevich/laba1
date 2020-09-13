#pragma once
class Sorting_algorithms // WARNING!! God Object!!
{

public:


	// ����������� ������
	Sorting_algorithms() {
		Dialog_Loop();
	}

	// ���������� ������ ��� ������� �������
	~Sorting_algorithms();

private:
	
	int Num_C = 0;  // ���������� ���������
	int Num_M = 0;	// ���������� ���������
	// ��������� �� ������, ������� �� ����� ��������� � �����������.
	int* Array_to_Sort;

	// ������������� �� ����, ������� ����� ���������� ������ �������
	int Array_Size;

	// ������� ��� ������������ ���������� ���������
	void Dialog_Loop();

	// ������� ����������� ������� � �������������, 
	// �� ������� ���������� ������� � ����������� �� ���������� �������.
	void Console_User_Dialog();
		

	// ������� ���������� ������� ��������� ������������������
	void Descreasing_Fillage_of_Array();

	// ������� ���������� ���������� �������
	void Random_Fillage_of_Array();		

	// ������� ���������� ������������ �������������������
	void Increasing_Fillage_of_Array();	

	// ������� ��� �������� ���� ���� ��������� � �������
	void Swap_method(int, int);


	// ������� ���������� �������
	void Selection_Sort();				

	// ������� ���������� ������� �����
	void Shell_Sort();					

	// ������� ������������� ����������
	void HeapSort();

	// ������� ����������� ����� �������
	int Control_Sum();

	// ������� ���������� ����� � �������
	int Series();

	// ��������� ������� ���������� ��� �������� � ������� ����� � ����������
	// ����� ��������������� � int Benchmark() ��� �������/�������������
	void Benchmark(void (Sorting_algorithms::*)());

	// ����� ������� �� ����� � ���� ������� 10�N(
	void Print_Array();

};

