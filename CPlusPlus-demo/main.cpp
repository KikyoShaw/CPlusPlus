#include <iostream>
#include "Polymorphism.h"
#include "Copy.h"
#include "Sort.h"
#include "Matching.h"
#include <chrono>	// 统计运行时间需要

#include <bitset>

using namespace chrono;

/*
* 结构体空间计算总结
* 1.首先先确定结构体中最大成员类型所占字节大小，以这个大小N为基准，整体空间是N的整数倍。
* 2.字节对齐原则，结构体内存空间按照成员的先后顺序排列，当排第一个成员的时候，其数据类型大小为n，申请的空间大小即为N，
*   当排下一个成员的时候，如果该成员类型所占大小 小于 N-n，则继续占用到N空间中，偏移量为N-n，
*   不成立的情况下，则会继续申请N大小空间，依次向后类推。
* 
* 结构体中含有子结构体时空间计算总结
* 1.首先先确定子结构体和父结构体中最大成员类型所占字节大小，以这个大小N为基准，整体空间是N的整数倍。
* 2.字节对齐原则，父结构体内存空间按照成员的先后顺序排列，当排第一个成员的时候，其数据类型大小为n，申请的空间大小即为N，
*   当排下一个成员的时候，如果该成员类型所占大小 小于 N-n，则继续占用到N空间中，偏移量为N-n，
*   不成立的情况下，则会继续申请N大小空间，依次向后类推。
*   当排到子结构体成员时，其大小为该结构体所占字节大小，该大小不会影响父结构体摆放大小N。
* 
* 总结
* 1.在定义结构体的时候最好选择最优成员定义顺序，以节省空间的损耗。
* 2.所谓对齐是各类型的数据按照一定的规则在空间进行排序，此处的排序不是说按照一个接一个的顺序进行排序。
* 3.对齐有个前提条件：该类型的数据地址能被其数据长度整除。举例说明：1字节是对齐的，2字节的数据地址要被2整除，以此类推。
* 4.linux操作系统默认对齐是以4字节对齐，在linux下，结构体的空间计算中，若最大成员类型所占字节数超过4，则整体空间是4的倍数即可。
	而windows是以最大的内置类型对齐，在32位操作系统下默认4字节对齐，64位则是默认8字节对齐，也可能4字节对齐。
* 5.struct结构在C和C++是不同的，C中struct只是类型声明，没有内存空间的分配，static变量是需要分配内存，因此不能定义静态变量，C++可以。
* 6.对齐可以使用#pragma pack(N) 取N字节大小参与对齐。#pragma pack(1),变量紧缩。
* 取 pack 设定的、系统默认的、结构体中成员所占字节最大值, 它们三个之间的最小的那个。
*/

//以下测试均在x86环境下，32位
//#pragma pack(4)
//struct STU
//{
//	char s1; //1
//	int s2; //4  
//	double s3; //8 
//	char s4; //1
//	//由于字节对齐,字节大小为1+4+8+1 = 14
//};
//
//struct STU2
//{
//	char s1; //1 
//	STU s2; //14 
//	char s3; //1 
//	int s4; //4  
//	//由于字节对齐,字节大小为1+14+1+4 = 20
//};
//#pragma pack(pop)   //恢复对齐状态

struct STU
{
	//基准为8（最大所占字节空间）
	char s1; //1 所占空间为1，分配空间为8，此时整体空间为8 偏移量为0，剩余空间为7
	int s2; //4  所占空间为4，4+1<8, 因此整体空间还是8，偏移量为1， 剩余空间为3
	double s3; //8 所占空间为8， 4+1+8>8，因此继续分配8字节空间，此时整体空间为16，偏移量为0， 剩余空间为0
	char s4; //1  所占空间为1， 8+1>8, 因此继续分配8字节空间，此时整体空间为24，偏移量为0，剩余空间为7
	//因此，结构体STU所占字节大小为24
};

struct STU2
{
	//基准为8（父结构体和子结构体中最大所占字节空间）
	char s1; //1 所占空间为1，分配空间为8，此时整体空间为8 偏移量为0，剩余空间为7
	STU s2; //24 所占空间为24， STU结构体所占大小，不影响分配空间, 整体空间为32
	char s3; //1 所占空间为1，分配空间为8，此时整体空间为40 偏移量为0，剩余空间为7
	int s4; //4  所占空间为4，4+1<8, 因此整体空间还是40，偏移量为1， 剩余空间为3
	//因此，结构体STU2所占字节大小为40
};

int isBigEndian()
{
	unsigned short t = 1;
	unsigned char* m = (unsigned char*)&t;
	return m[1];
}

string c2b(char* cp, int n)
{
	string tmpStr = "";
	for (int i = 0; i < n; i++)
	{
		char ch = cp[i];
		char shift = ch >> 1;
		for (int j = 0; j < 8; j++)
		{
			if (ch == (shift << 1))
				tmpStr += "0";
			else if (ch != (shift << 1))
				tmpStr += "1";
			ch = shift;
			shift = shift >> 1;
		}
	}
	return tmpStr;
}

void PrintfBinary(unsigned char cData)
{
	for (int i = 7; i >= 0; i--)
	{
		if (cData & (1 << i))
		{
			cout << "1";
		}
		else
		{
			cout << "0";
		}
	}
}


#define RUN_SORT(FUNC)	\
{	\
	auto tStart = system_clock::now();	\
	FUNC;	\
	auto tEnd = system_clock::now();	\
	auto tCost = duration_cast<nanoseconds>(tEnd - tStart);	\
	cout << "耗时: " << tCost.count() << " ns(纳秒)." << endl;	\
}

int main()
{
	#pragma region 多态&&虚函数&&纯虚函数 示例
	//Animal* pAn = new Tiger();
	//pAn->eat();
	//cout << sizeof(Animal) << endl;
	//Animal animal;
	//Animal* pAn = new Animal();
	//Tiger tiger;
	//Animal* pAn = &tiger;
	//pAn->run();
	//delete pAn;
	//pAn = nullptr;
	#pragma endregion

	#pragma region 深拷贝&&浅拷贝 示例
	//Student s1;
	////Student s2(s1);
	//Student s2;
	//s1 = s2;
	#pragma endregion

	#pragma region 字节对齐

	//cout << sizeof(STU) << endl;
	//cout << sizeof(STU2) << endl;

	#pragma endregion

	#pragma region 智能指针
	
	//unique_ptr<string> p1(new string("hello"));
	//unique_ptr<string> p2(new string("world"));

	//unique_ptr<string> p3;

	///*p3 = p1;*/

	//p3 = unique_ptr<string>(new string("Hello World!"));

	//cout << p1->data() << endl;

	//cout << p3->data() << endl;

	#pragma endregion

	#pragma region 排序算法

	////int a[6] = {1314, 696, 856, 4, 956, 52};
	//int a[6] = {13, 6, 8, 4, 9, 5};
	//int n = sizeof(a) / sizeof(int);
	//cout << "排序前：";
	//for (int i = 0; i < n; i++) {
	//	cout << a[i] << " ";
	//}
	//cout << endl;
	////BubbleSort(a, n);
	// //CocktailSort(a, n);
	////SelectionSort(a, n);
	////QuickSort(a, 0, n -1);
	////InsertionSort(a, n);
	// //ShellSort(a, n);
	// //InsertionSortDichotomy(a, n);
	////MergeSort(a, 0, n-1);
	////HeapSort(a, n);

	//RUN_SORT(BucketSort(a, n));
	////RUN_SORT(LsdRadixSort(a, n));

	//cout << "排序后：";
	//for (int i = 0; i < n; i++) {
	//	cout << a[i] << " ";
	//}

	//cout << endl;

	#pragma endregion

	#pragma region 匹配算法
	string s1 = "kkikkikkyk";
	string s2 = "kkikky";
	//string s1 = "kikykyo";
	//string s2 = "kyk";
	
	auto tStart = system_clock::now();

	//int index = BruteForce(s1, s2);
	//int index = BoyerMoore(s1, s2);
	//int index = RobinKarp(s1, s2);
	//int index = KnuthMorrisPratt(s1, s2);
	int index = Sunday(s1, s2);

	auto tEnd = system_clock::now();
	auto tCost = duration_cast<nanoseconds>(tEnd - tStart);
	if (index == -1)
		cout << "s1与s2不匹配" << endl;
	else
		cout << "s1与s2匹配成功,字符开始匹配位置：" << index << endl;
	cout << "耗时: " << tCost.count() << " ns(纳秒)." << endl;
	#pragma endregion

	#pragma region DOUBLE

	/*
	* 浮点数内存表示
目前C/C++编译器标准都遵照IEEE制定的浮点数表示法来进行float,double运算。这种结构是一种科学计数法，
用符号、指数和尾数(最高位的1不写入内存)来表示，底数定为2——即把一个浮点数表示为尾数乘以2的指数次方再添上符号。下面是具体的规格：
	  符号位 阶码 尾数 长度
float   1      8    23   32
double  1     11   52   64

举例：-12.5转为单精度二进制表示

12.5:
1. 整数部分12，二进制为1100; 小数部分0.5, 二进制是.1，先把他们连起来，从第一个1数起取24位（后面补0）：
1100.10000000000000000000
这部分是有效数字。（把小数点前后两部分连起来再取掉头前的1，就是尾数）
2. 把小数点移到第一个1的后面，需要左移3位（1.10010000000000000000000*2^3）, 加上偏移量127：127+3=130，二进制是10000010，这是阶码。
3. -12.5是负数，所以符号位是1。把符号位，阶码和尾数连起来。注意，尾数的第一位总是1，所以规定不存这一位的1，只取后23位：
1 10000010 10010000000000000000000
把这32位按8位一节整理一下，得：
11000001 01001000 00000000 00000000
就是十六进制的 C1480000.
	*/
	//int index = 1;

	//float ind = 12.5;

	//float ind1;
	//ind1 = 154.07815;

	//float ind2 = ind;

	//unsigned char* pChar = reinterpret_cast<unsigned char*>(&ind);

	//for (int i = sizeof(float) - 1; i >= 0; --i)
	//{
	//	PrintfBinary(pChar[i]);
	//}
	//cout<<endl;

	////cout<<bitset<8>(ind)<<endl;

	///*cout<<isBigEndian()<<endl;*/

	////char* cp = (char*)&ind;
	////cout << isBigEndian() << endl;
	////string ret;
	////ret = c2b(cp, 4);
	////if (!isBigEndian())//如果是高字节序，则将字符串逆序
	////{
	////	for (int i = 3; i > 0; i--)
	////	{
	////		for (int j = 0; j < 8; j++)
	////			cout << ret[8 * i + j];
	////	}
	////}
	////cout<<ret<<endl;
	///*scanf("%.8f", &ind);*/

	////cout << ind << endl;

	#pragma endregion

	system("pause");

	return 0;
}

