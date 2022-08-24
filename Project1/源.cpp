#include<iostream>
#include<time.h>
#include<chrono>
#include<stdlib.h>
//#include<>
using namespace std;

template<int T>//模板类 为数组传参时不会丢失长度信息，按引用传递时数组不会被拷贝，退化为指针
void print(int(&arr)[T])
{
	for (auto i : arr)
	{
		std::cout << i << "";
	}
}

template<int T>
void random(int(&arr)[T])
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch();
	srand(seed);
	for (int i=0;i< T;i++)
	{
		arr[i] = （rand() % （b - a + 1）) + a;
	}
}

template<int A,int B>
double multi(double (&a)[A],double (&b)[B])
{
	if (A <= 0 || B <= 0 || A & B != 0)
	{
		throw"something is wrong";
		//return 0;//处理错误
	}

}

/**
gray=0.299*R+0.587*G+0.114*B
gray=(299*R+587*G+114*B)/1000
gray=(1024*299*R+1024*587*G+1024*114*B)/(1024*1000)
gray=(306176*R+601088*G+116736*B)/(1024*1000)
gray=(306176/1000*R+601088/1000*G+116736/1000*B)/(1024)//截断误差
gray=(306*R+601*G+116*B)>>10
*/
void funarr(int(&arr)[10])//函数 按引用传参
{
	std::cout << &arr << std::endl;
	std::cout << arr << std::endl;
	std::cout << sizeof(arr) << std::endl;
}

void combline(unsigned int* big_array, unsigned int* small_array, int big_col, int big_row, int small_col,int small_row,int positionx,int positiony)
{
	for (int i = 0; i < small_row; i++)
	{
		for (int j = 0; j < small_col; j++)
		{
			big_array[(positiony)*big_col + positionx + j] = small_array[i * small_col + j];
		}
	}
}

void reflection_pad(unsigned int* origin_arr,int col,int row,int length)
{
	for (int i = length; i < row - length; i++)
	{
		for (int j = 0; j < length; j++)
		{
			int pos1 = i * col + j;
			int num1 = origin_arr[i * col + 2 * length - j];
			int pos2 = (i + 1) * col - j;
			int num2 = origin_arr[(i + 1) * col - (2 * length - j)];
			origin_arr[pos1] = num1;
			origin_arr[pos2] = num2;
		}
	}
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < col; j++)
		{
			int pos1 = i * col + j;
			int num1 = origin_arr[(2 * length - i) * col + j];
			int pos2 = (row - i) * col + j;
			int num2 = origin_arr[(row - (2 * length - i)) * col + j];
			origin_arr[pos1] = num1;
			origin_arr[pos2] = num2;
		}
	}
		

}

int* median_filter(int* reflection_arr,int col,int row,int length)
{

}

int main()
{
	

	return 0;
}