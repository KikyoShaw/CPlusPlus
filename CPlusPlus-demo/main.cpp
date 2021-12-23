#include <iostream>
#include "Polymorphism.h"
#include "Copy.h"
#include "Sort.h"
#include <chrono>	// ͳ������ʱ����Ҫ

#include <bitset>

using namespace std;

using namespace chrono;

/*
* �ṹ��ռ�����ܽ�
* 1.������ȷ���ṹ��������Ա������ռ�ֽڴ�С���������СNΪ��׼������ռ���N����������
* 2.�ֽڶ���ԭ�򣬽ṹ���ڴ�ռ䰴�ճ�Ա���Ⱥ�˳�����У����ŵ�һ����Ա��ʱ�����������ʹ�СΪn������Ŀռ��С��ΪN��
*   ������һ����Ա��ʱ������ó�Ա������ռ��С С�� N-n�������ռ�õ�N�ռ��У�ƫ����ΪN-n��
*   ������������£�����������N��С�ռ䣬����������ơ�
* 
* �ṹ���к����ӽṹ��ʱ�ռ�����ܽ�
* 1.������ȷ���ӽṹ��͸��ṹ��������Ա������ռ�ֽڴ�С���������СNΪ��׼������ռ���N����������
* 2.�ֽڶ���ԭ�򣬸��ṹ���ڴ�ռ䰴�ճ�Ա���Ⱥ�˳�����У����ŵ�һ����Ա��ʱ�����������ʹ�СΪn������Ŀռ��С��ΪN��
*   ������һ����Ա��ʱ������ó�Ա������ռ��С С�� N-n�������ռ�õ�N�ռ��У�ƫ����ΪN-n��
*   ������������£�����������N��С�ռ䣬����������ơ�
*   ���ŵ��ӽṹ���Աʱ�����СΪ�ýṹ����ռ�ֽڴ�С���ô�С����Ӱ�츸�ṹ��ڷŴ�СN��
* 
* �ܽ�
* 1.�ڶ���ṹ���ʱ�����ѡ�����ų�Ա����˳���Խ�ʡ�ռ����ġ�
* 2.��ν�����Ǹ����͵����ݰ���һ���Ĺ����ڿռ�������򣬴˴���������˵����һ����һ����˳���������
* 3.�����и�ǰ�������������͵����ݵ�ַ�ܱ������ݳ�������������˵����1�ֽ��Ƕ���ģ�2�ֽڵ����ݵ�ַҪ��2�������Դ����ơ�
* 4.linux����ϵͳĬ�϶�������4�ֽڶ��룬��linux�£��ṹ��Ŀռ�����У�������Ա������ռ�ֽ�������4��������ռ���4�ı������ɡ�
	��windows���������������Ͷ��룬��32λ����ϵͳ��Ĭ��4�ֽڶ��룬64λ����Ĭ��8�ֽڶ��룬Ҳ����4�ֽڶ��롣
* 5.struct�ṹ��C��C++�ǲ�ͬ�ģ�C��structֻ������������û���ڴ�ռ�ķ��䣬static��������Ҫ�����ڴ棬��˲��ܶ��徲̬������C++���ԡ�
* 6.�������ʹ��#pragma pack(N) ȡN�ֽڴ�С������롣#pragma pack(1),����������
* ȡ pack �趨�ġ�ϵͳĬ�ϵġ��ṹ���г�Ա��ռ�ֽ����ֵ, ��������֮�����С���Ǹ���
*/

//���²��Ծ���x86�����£�32λ
//#pragma pack(4)
//struct STU
//{
//	char s1; //1
//	int s2; //4  
//	double s3; //8 
//	char s4; //1
//	//�����ֽڶ���,�ֽڴ�СΪ1+4+8+1 = 14
//};
//
//struct STU2
//{
//	char s1; //1 
//	STU s2; //14 
//	char s3; //1 
//	int s4; //4  
//	//�����ֽڶ���,�ֽڴ�СΪ1+14+1+4 = 20
//};
//#pragma pack(pop)   //�ָ�����״̬

struct STU
{
	//��׼Ϊ8�������ռ�ֽڿռ䣩
	char s1; //1 ��ռ�ռ�Ϊ1������ռ�Ϊ8����ʱ����ռ�Ϊ8 ƫ����Ϊ0��ʣ��ռ�Ϊ7
	int s2; //4  ��ռ�ռ�Ϊ4��4+1<8, �������ռ仹��8��ƫ����Ϊ1�� ʣ��ռ�Ϊ3
	double s3; //8 ��ռ�ռ�Ϊ8�� 4+1+8>8����˼�������8�ֽڿռ䣬��ʱ����ռ�Ϊ16��ƫ����Ϊ0�� ʣ��ռ�Ϊ0
	char s4; //1  ��ռ�ռ�Ϊ1�� 8+1>8, ��˼�������8�ֽڿռ䣬��ʱ����ռ�Ϊ24��ƫ����Ϊ0��ʣ��ռ�Ϊ7
	//��ˣ��ṹ��STU��ռ�ֽڴ�СΪ24
};

struct STU2
{
	//��׼Ϊ8�����ṹ����ӽṹ���������ռ�ֽڿռ䣩
	char s1; //1 ��ռ�ռ�Ϊ1������ռ�Ϊ8����ʱ����ռ�Ϊ8 ƫ����Ϊ0��ʣ��ռ�Ϊ7
	STU s2; //24 ��ռ�ռ�Ϊ24�� STU�ṹ����ռ��С����Ӱ�����ռ�, ����ռ�Ϊ32
	char s3; //1 ��ռ�ռ�Ϊ1������ռ�Ϊ8����ʱ����ռ�Ϊ40 ƫ����Ϊ0��ʣ��ռ�Ϊ7
	int s4; //4  ��ռ�ռ�Ϊ4��4+1<8, �������ռ仹��40��ƫ����Ϊ1�� ʣ��ռ�Ϊ3
	//��ˣ��ṹ��STU2��ռ�ֽڴ�СΪ40
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
	cout << "��ʱ: " << tCost.count() << " ns(����)." << endl;	\
}

int main()
{
	#pragma region ��̬&&�麯��&&���麯�� ʾ��
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

	#pragma region ���&&ǳ���� ʾ��
	//Student s1;
	////Student s2(s1);
	//Student s2;
	//s1 = s2;
	#pragma endregion

	#pragma region �ֽڶ���

	//cout << sizeof(STU) << endl;
	//cout << sizeof(STU2) << endl;

	#pragma endregion

	#pragma region ����ָ��
	
	//unique_ptr<string> p1(new string("hello"));
	//unique_ptr<string> p2(new string("world"));

	//unique_ptr<string> p3;

	///*p3 = p1;*/

	//p3 = unique_ptr<string>(new string("Hello World!"));

	//cout << p1->data() << endl;

	//cout << p3->data() << endl;

	#pragma endregion

	#pragma region �����㷨

	int a[6] = {13, 6, 8, 4, 9, 5};
	int n = sizeof(a) / sizeof(int);
	cout << "����ǰ��";
	for (int i = 0; i < n; i++) {
		cout << a[i] << " ";
	}
	cout << endl;
	//BubbleSort(a, n);
	 //CocktailSort(a, n);
	//SelectionSort(a, n);
	//QuickSort(a, 0, n -1);
	//InsertionSort(a, n);
	 //ShellSort(a, n);
	 //InsertionSortDichotomy(a, n);
	//MergeSort(a, 0, n-1);
	//HeapSort(a, n);

	RUN_SORT(BucketSort(a, n));

	cout << "�����";
	for (int i = 0; i < n; i++) {
		cout << a[i] << " ";
	}

	cout << endl;

	#pragma endregion

	#pragma region DOUBLE

	/*
	* �������ڴ��ʾ
ĿǰC/C++��������׼������IEEE�ƶ��ĸ�������ʾ��������float,double���㡣���ֽṹ��һ�ֿ�ѧ��������
�÷��š�ָ����β��(���λ��1��д���ڴ�)����ʾ��������Ϊ2��������һ����������ʾΪβ������2��ָ���η������Ϸ��š������Ǿ���Ĺ��
	  ����λ ���� β�� ����
float   1      8    23   32
double  1     11   52   64

������-12.5תΪ�����ȶ����Ʊ�ʾ

12.5:
1. ��������12��������Ϊ1100; С������0.5, ��������.1���Ȱ��������������ӵ�һ��1����ȡ24λ�����油0����
1100.10000000000000000000
�ⲿ������Ч���֡�����С����ǰ����������������ȡ��ͷǰ��1������β����
2. ��С�����Ƶ���һ��1�ĺ��棬��Ҫ����3λ��1.10010000000000000000000*2^3��, ����ƫ����127��127+3=130����������10000010�����ǽ��롣
3. -12.5�Ǹ��������Է���λ��1���ѷ���λ�������β����������ע�⣬β���ĵ�һλ����1�����Թ涨������һλ��1��ֻȡ��23λ��
1 10000010 10010000000000000000000
����32λ��8λһ������һ�£��ã�
11000001 01001000 00000000 00000000
����ʮ�����Ƶ� C1480000.
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
	////if (!isBigEndian())//����Ǹ��ֽ������ַ�������
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

