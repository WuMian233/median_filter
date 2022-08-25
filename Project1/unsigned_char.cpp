#include<iostream>
#include<time.h>
#include<chrono>
#include<stdlib.h>
#include<algorithm>
#include<vector>
#include<set>
//#include<>
using namespace std;
using namespace std::chrono;
/**
template<int T>//模板类 为数组传参时不会丢失长度信息，按引用传递时数组不会被拷贝，退化为指针
void print(int(&arr)[T])
{
	for (auto i : arr)
	{
		std::cout << i << " ";
	}
};
*/

void print_arr(unsigned char* arr, int col, int row)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			cout << (int)arr[i * col + j] << " ";
		}
		cout << endl;
	}
	
}


void random(unsigned char *arr, int total,int a, int b)//{[a,b]的随机数
{
	system_clock::time_point now = system_clock::now();
	unsigned seed = now.time_since_epoch().count();
	srand(seed);
	for (int i = 0; i < total; i++)
	{
		unsigned char num = (rand() % (b - a + 1)) + a;
		arr[i] = num;
	}
};

/**
template<int A,int B>
double multi(double (&a)[A],double (&b)[B])//
{
	if (A <= 0 || B <= 0 || A & B != 0)
	{
		throw"something is wrong";
		//return 0;//处理错误
	}
	int max_digit_a = 0;
	int max_digit_b = 0;
	for (int i = 0; i < A; i++)
	{
		max_digit_a = max(max_digit, get_digit(a[i]));
		max_digit_b = max(max_digit, get_digit(b[i]));
	}
	

	int sum = 0;
	for (int i = 0; i < A; i++)
	{
		sum += (int)pow(a[i], max_digit_a) * (int)pow(b[i], max_digit_b);
	}
}
int get_digit(double num)
{
	int count = 0;
	while (num - (int)num != 0)
	{
		count++;
		num = 10 * num;
	}
	return count;
}
*/
/**
gray=0.299*R+0.587*G+0.114*B
gray=(299*R+587*G+114*B)/1000
gray=(1024*299*R+1024*587*G+1024*114*B)/(1024*1000)
gray=(306176*R+601088*G+116736*B)/(1024*1000)
gray=(306176/1000*R+601088/1000*G+116736/1000*B)/(1024)//截断误差
gray=(306*R+601*G+116*B)>>10
*/
/**
void funarr(int(&arr)[10])//函数 按引用传参
{
	std::cout << &arr << std::endl;
	std::cout << arr << std::endl;
	std::cout << sizeof(arr) << std::endl;
}
*/

void combline(unsigned char* big_array, unsigned char* small_array, int big_col, int big_row, int small_col,int small_row,int positionx,int positiony)
{
	for (int i = 0; i < small_row; i++)
	{
		for (int j = 0; j < small_col; j++)
		{
			big_array[(positiony + i)*big_col + positionx + j] = small_array[i * small_col + j];
		}
	}
	//print_arr(big_array, big_col, big_row);
}

void reflection_pad(unsigned char* origin_arr,int col,int row,int length)
{
	for (int i = length; i < row - length; i++)
	{
		for (int j = 0; j < length; j++)
		{
			int pos1 = i * col + j;
			unsigned char num1 = origin_arr[i * col + 2 * length - j];
			int pos2 = (i + 1) * col - j-1;
			unsigned char num2 = origin_arr[(i + 1) * col - (2 * length - j)-1];
			//cout << "pos2" << pos2 << "num2" << num2 << endl;
			origin_arr[pos1] = num1;
			origin_arr[pos2] = num2; 
		}
	}
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < col; j++)
		{
			int pos1 = i * col + j;
			unsigned char num1 = origin_arr[(2 * length - i) * col + j];
			int pos2 = (row - i-1) * col + j;
			unsigned char num2 = origin_arr[(row - (2 * length - i)-1) * col + j];
			origin_arr[pos1] = num1;
			origin_arr[pos2] = num2;
			//cout << "pos2" << pos2 << "num2" << num2 << endl;
		}
	}
	cout << "reflecion"<<endl;
	print_arr(origin_arr,col,row);
}
/*****
unsigned char* median_filter(unsigned char* reflection_arr,int col,int row,int n)//
{
	int origin_row = row - 2 * (n - 2);
	int origin_col = col - 2 * (n - 2);
	unsigned char* processing_arr = new unsigned char[origin_col * row];
	for (int i = 0; i < row; i++)
	{
		//朴素算法 但是实际用起来会出问题
		static unsigned char* window = new unsigned char[n];
		
		for (int iter = 0; iter < n; iter++)
		{
			window[iter] = reflection_arr[i * col + iter];
			//cout << (int)window[iter] << " ";
		}
		//cout << endl;

		static unsigned char* copy_window = new unsigned char[n];

		

		for (int j = 0; j < origin_col; j++)
		{
			window[j % n] = reflection_arr[i * col + j + n];

			copy_window = std::copy(window, window + n, copy_window);
			print_arr(copy_window,n,1);
			std::sort(copy_window, copy_window + n);
			processing_arr[i * origin_col+j] = copy_window[n / 2];

		}
		
		/**
		delete []window;
		delete []copy_window;
		*/ /**
	}
	cout << "processing" << endl;
	print_arr(processing_arr, origin_col, row);
	unsigned char* median_arr = new unsigned char[origin_col * origin_row];
	cout << " " << endl;
	for (int j = 0; j < origin_col; j++)
	{
		static unsigned char* window2 = new unsigned char[n];
		for (int iter = 0; iter < n; iter++)
		{
			window2[iter] = processing_arr[iter*origin_col+j];
			//cout << (int)window2[iter] << " ";
		}
		static unsigned char* copy_window2 = new unsigned char[n];

		for (int i = 0; i < origin_row; i++)
		{
			window2[i % n] = processing_arr[i * origin_col + j];

			copy_window2 = std::copy(window2, window2 + n, copy_window2);
			std::sort(copy_window2, copy_window2 + n);
			median_arr[i * origin_col + j] = copy_window2[n / 2];
		}
	}
	cout << "copy" << endl;
	print_arr(median_arr, origin_col, origin_row);
	return median_arr;
}
*****/
unsigned char* median_filter1(unsigned char* reflection_arr, int col, int row, int n)//
{//中值算法来自https://blog.51cto.com/u_15302258/3086800
	int origin_row = row - 2 * (n - 2);
	int origin_col = col - 2 * (n - 2);
	
	unsigned char* processing_arr = new unsigned char[origin_col * row];//C26451警告 算术溢出
	multiset<unsigned char> st;
	
	for (int i = 0; i < row; i++)
	{
		
		
		for (int j = 0; j < origin_col;j++)
		{
			
			if (st.size() >= n)
			{
				st.erase(st.find(reflection_arr[i * col + j - n]));
			}
			st.insert(reflection_arr[i * col + j]);
			if (i >= n - 1)
			{
				auto mid = st.begin();
				std::advance(mid, n / 2);
				processing_arr[i *origin_col + j] = (*mid + *prev(mid, (static_cast<std::_Iter_diff_t<std::_Tree<std::_Tset_traits<unsigned char, std::less<unsigned char>, std::allocator<unsigned char>, true>>::iterator>>(1) - n % 2))) / 2;//这里有问题
				cout << "median:" << (*mid + *prev(mid, (static_cast<std::_Iter_diff_t<std::_Tree<std::_Tset_traits<unsigned char, std::less<unsigned char>, std::allocator<unsigned char>, true>>::iterator>>(1) - n % 2))) / 2 << endl;
			}
		}
		cout << "嗯哼" << endl;

		st.clear();//第三次就会崩溃
	}
	multiset<unsigned char> st1;
	cout << "processing" << endl;
	print_arr(processing_arr, origin_col, row);
	unsigned char* median_arr = new unsigned char[origin_col * origin_row];
	
	for (int j = 0; j < origin_col; j++)
	{
		
		for (int i = 0; i < origin_row; j++)
		{
			if (st1.size() >= n)
			{
				st1.erase(st1.find(reflection_arr[(i-n) * col + j]));
			}
			st1.insert(reflection_arr[i * col + j]);
			if (i >= n - 1)
			{
				auto mid = st1.begin();
				std::advance(mid, n / 2);
				median_arr[i  * origin_col + j] = (*mid + *prev(mid, (static_cast<std::_Iter_diff_t<std::_Tree<std::_Tset_traits<unsigned char, std::less<unsigned char>, std::allocator<unsigned char>, true>>::iterator>>(1) - n % 2))) / 2;//C6386 写入到数组时缓冲区溢出
			}
		}
		st1.clear();
	}
	cout << "copy" << endl;
	print_arr(median_arr, origin_col, origin_row);
	return median_arr;
}

unsigned char* get_median_filter(unsigned char* arr, int origin_col, int origin_row,int n)
{
	int col = origin_col + 2 * (n - 2);
	int row = origin_row + 2 * (n - 2);
	unsigned char* big_arr = new unsigned char[col * row];
	combline(big_arr, arr, col, row, origin_col, origin_row, n - 2, n - 2);
	reflection_pad(big_arr, col, row, n - 2);
	unsigned char* median_arr = median_filter1(big_arr, col, row, n);
	return median_arr;
}
/**
int main()
{
	
	unsigned char zero = 0;
	unsigned char* array = new unsigned char[35]{ zero };
	random(array,35,0,255);
	print_arr(array,7,5);
	unsigned char* median_arr = get_median_filter(array, 7, 5, 3);//5行7列 3*3中值滤波
	/**unsigned char* big_arr = new unsigned char[9 * 7];
	combline(big_arr, array, 9, 7, 7, 5, 1, 1);
	reflection_pad(big_arr, 9, 7, 1);
	unsigned char* median_arr = median_filter1(big_arr, 9, 7, 3);
	*//**
	print_arr(median_arr, 7, 5);

	getchar();
	
	return 0;
}
*/