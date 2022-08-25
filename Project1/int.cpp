#include<iostream>
#include<time.h>
#include<chrono>
#include<stdlib.h>
#include<algorithm>
#include<vector>
#include<set>
//#include<iterator>
//#include<>
using namespace std;
using namespace std::chrono;
/**
template<int T>//ģ���� Ϊ���鴫��ʱ���ᶪʧ������Ϣ�������ô���ʱ���鲻�ᱻ�������˻�Ϊָ��
void print(int(&arr)[T])
{
	for (auto i : arr)
	{
		std::cout << i << " ";
	}
};
*/

void print_arr(int* arr, int col, int row)
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


void random(int* arr, int total, int a, int b)//{[a,b]�������
{
	system_clock::time_point now = system_clock::now();
	unsigned seed = now.time_since_epoch().count();
	srand(seed);
	for (int i = 0; i < total; i++)
	{
		int num = (rand() % (b - a + 1)) + a;
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
		//return 0;//�������
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
gray=(306176/1000*R+601088/1000*G+116736/1000*B)/(1024)//�ض����
gray=(306*R+601*G+116*B)>>10
*/
/**
void funarr(int(&arr)[10])//���� �����ô���
{
	std::cout << &arr << std::endl;
	std::cout << arr << std::endl;
	std::cout << sizeof(arr) << std::endl;
}
*/

void combline(int* big_array, int* small_array, int big_col, int big_row, int small_col, int small_row, int positionx, int positiony)
{
	for (int i = 0; i < small_row; i++)
	{
		for (int j = 0; j < small_col; j++)
		{
			big_array[(positiony + i) * big_col + positionx + j] = small_array[i * small_col + j];
		}
	}
	//print_arr(big_array, big_col, big_row);
}

void reflection_pad(int* origin_arr, int col, int row, int length)
{
	for (int i = length; i < row - length; i++)
	{
		for (int j = 0; j < length; j++)
		{
			int pos1 = i * col + j;
			int num1 = origin_arr[i * col + 2 * length - j];
			int pos2 = (i + 1) * col - j - 1;
			int num2 = origin_arr[(i + 1) * col - (2 * length - j) - 1];
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
			int num1 = origin_arr[(2 * length - i) * col + j];
			int pos2 = (row - i - 1) * col + j;
			int num2 = origin_arr[(row - (2 * length - i) - 1) * col + j];
			origin_arr[pos1] = num1;
			origin_arr[pos2] = num2;
			//cout << "pos2" << pos2 << "num2" << num2 << endl;
		}
	}
	cout << "reflecion" << endl;
	print_arr(origin_arr, col, row);
	cout << endl;
}

int* median_filter(int* reflection_arr,int col,int row,int n)//
{
	int origin_row = row - 2 * (n - 2);
	int origin_col = col - 2 * (n - 2);
	int* processing_arr = new int[origin_col * row];
	for (int i = 0; i < row; i++)
	{
		//�����㷨 
		static int* window = new int[n];

		for (int iter = 0; iter < n; iter++)
		{
			window[iter] = reflection_arr[i * col + iter];
			//cout << (int)window[iter] << " ";
		}
		//cout << endl;

		static int* copy_window = new int[n];



		for (int j = 0; j < origin_col; j++)
		{
			window[j % n] = reflection_arr[i * col + j + n];

			for (int k = 0; k < n; k++)
			{
				copy_window[k] = window[k];
			}
			//cout << "copy" << endl;
			/**
			for (int k = 0; k < n; k++)
			{
				cout << copy_window[k] <<" ";
			}
			*/
			//cout << endl;
			//print_arr(copy_window,n,1);
			std::sort(copy_window, copy_window + n);
			processing_arr[i * origin_col+j] = copy_window[n / 2];

		}

		/**
		delete []window;
		delete []copy_window;
		*/ 
	}
	cout << "processing" << endl;
	print_arr(processing_arr, origin_col, row);
	int* median_arr = new int[origin_col * origin_row];
	cout << " " << endl;
	for (int j = 0; j < origin_col; j++)
	{
		static int* window2 = new int[n];
		for (int iter = 0; iter < n; iter++)
		{
			window2[iter] = processing_arr[iter*origin_col+j];
			//cout << (int)window2[iter] << " ";
		}
		static int* copy_window2 = new int[n];

		for (int i = 0; i < origin_row; i++)
		{
			window2[i % n] = processing_arr[i * origin_col + j];
			for (int k = 0; k < n; k++)
			{
				copy_window2[k] = window2[k];
			}
			
			std::sort(copy_window2, copy_window2 + n);
			median_arr[i * origin_col + j] = copy_window2[n / 2];
		}
	}
	
	return median_arr;
}

int* median_filter1(int* reflection_arr, int col, int row, int n)//
{//��ֵ�㷨����https://blog.51cto.com/u_15302258/3086800
	int origin_row = row - 2 * (n - 2);
	int origin_col = col - 2 * (n - 2);

	int* processing_arr = new int[origin_col * row];//C26451���� �������
	multiset<int> st;

	for (int i = 0; i < row; i++)
	{


		for (int j = 0; j < origin_col; j++)
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
				processing_arr[i * origin_col + j] = (*mid + *prev(mid, (static_cast<std::_Iter_diff_t<std::_Tree<std::_Tset_traits<int, std::less<int>, std::allocator<int>, true>>::iterator>>(1) - n % 2))) / 2;//����������
				cout << "median:" << (*mid + *prev(mid, (static_cast<std::_Iter_diff_t<std::_Tree<std::_Tset_traits<int, std::less<int>, std::allocator<int>, true>>::iterator>>(1) - n % 2))) / 2 << endl;
			}
		}
		cout << "�ź�" << endl;

		st.clear();//�����ξͻ����
	}
	multiset<int> st1;
	cout << "processing" << endl;
	print_arr(processing_arr, origin_col, row);
	int* median_arr = new int[origin_col * origin_row];

	for (int j = 0; j < origin_col; j++)
	{

		for (int i = 0; i < origin_row; j++)
		{
			if (st1.size() >= n)
			{
				st1.erase(st1.find(reflection_arr[(i - n) * col + j]));
			}
			st1.insert(reflection_arr[i * col + j]);
			if (i >= n - 1)
			{
				auto mid = st1.begin();
				std::advance(mid, n / 2);
				median_arr[i * origin_col + j] = (*mid + *prev(mid, (static_cast<std::_Iter_diff_t<std::_Tree<std::_Tset_traits<int, std::less<int>, std::allocator<int>, true>>::iterator>>(1) - n % 2))) / 2;//C6386 д�뵽����ʱ���������
			}
		}
		st1.clear();
	}
	cout << "copy" << endl;
	print_arr(median_arr, origin_col, origin_row);
	return median_arr;
}

int* get_median_filter(int* arr, int origin_col, int origin_row, int n)
{
	int col = origin_col + 2 * (n - 2);
	int row = origin_row + 2 * (n - 2);
	int* big_arr = new int[col * row];
	combline(big_arr, arr, col, row, origin_col, origin_row, n - 2, n - 2);
	reflection_pad(big_arr, col, row, n - 2);
	int* median_arr = median_filter(big_arr, col, row, n);
	return median_arr;
}
int main()
{

	
	int* array = new int[81]{ 0 };
	random(array, 81, 0, 99);
	print_arr(array, 9, 9);
	int* median_arr = get_median_filter(array, 9, 9, 3);//5��7�� 3*3��ֵ�˲�
	/**int* big_arr = new int[9 * 7];
	combline(big_arr, array, 9, 7, 7, 5, 1, 1);
	reflection_pad(big_arr, 9, 7, 1);
	int* median_arr = median_filter1(big_arr, 9, 7, 3);
	*/
	cout << "res:" << endl;
	print_arr(median_arr, 9, 9);

	getchar();

	return 0;
}