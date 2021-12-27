#include "Matching.h"
#include <iostream>

/*
* BFƥ���㷨
* ����(����)ƥ���㷨,�ֱ���Ϊ����ƥ��ģʽ�㷨
* ԭ��: �����ַ���s1���ַ���s2�ĳ��ȷֱ�Ϊm��n��
* ˫ѭ������ƥ��s1��s2����s2��������������s2��ÿ���ַ�����s1��ĳһ���ֵ�һ��ƥ��ɹ���������˴��㷨
* ���ʱ�临�Ӷȣ�O(m*n)
* ����ʱ�临�Ӷȣ�O(m+n)
*/
int BruteForce(const string& s1, const string& s2)
{
	int index = 0;
	int i = 0; 
	int j = 0;
	while (s1[i] != '\0' && s2[j] != '\0'){
		if (s1[i] == s2[j]) { //�ҵ����λ�ú�Ƚ�˫����һ���ַ�
			i++;
			j++;
		}
		else { //����ȵ�ʱ��
			index++; //��¼��һ��λ��
			i = index; //s1�ַ����Ƶ���һ��λ��
			j = 0; //s2�ַ������׸���ʼƥ��
		}
	}
	if (s2[j] == '\0')
		return index;
	return 0;
}

/*
* BMƥ���㷨
* ��ģʽƥ����ַ��������㷨,Ч�ʿ���KMP�㷨��
* �����ص㣺��ģʽ�����ҿ�ʼ����ƥ�䣬���ַ����ú�׺��
* ԭ������������������ַ�ƥ�䣬���ַ���ƥ���ʱ�򣬾ʹӻ��ַ���ͺ��ַ�����һ���������ֵ������ģʽ�����Ƽ���ƥ�䡣
* ���ַ���Ե����������ú�׺��Ե���ģʽ����
* ���ַ�������λ�� = ���ַ����ֵ�λ�� �C ���ַ���ģʽ������һ�γ��ֵ�λ�á�
* �ú�׺������λ�� = �ú�׺���ֵ�λ�� �C �ú�׺��ģʽ������һ�γ��ֵ�λ�á�
* ʵ�����ù����У��������ַ��ĸ���ҪԶԶ���ںú�׺���������˴󲿷����ֻ��Ҫ�õ����ַ����ɣ���Ҳ��BM�㷨����Ľ��汾BMH��˼��
* https://www.ruanyifeng.com/blog/2013/05/boyer-moore_string_search_algorithm.html
* ʱ�临�Ӷ�O(n/m)
* �ʱ�临�Ӷȣ�O(m*n)
* �ռ临�Ӷ�O(k) ���ַ���ռ��Сk
*/

int *CreatPreBmGS(const string& str)
{
	int* BmGS = new int[256]; //Ϊ���ַ��������ڴ�ռ�
	for (int i = 0; i < 256; i++) //��ʼ����
		BmGS[i] = 0;
	for (int i = 0; i < str.size(); i++) //Ѱ������
	{
		int index = str[i];
		BmGS[index] = i;
	}
	return BmGS;
}

int BoyerMoore(const string& s1, const string& s2)
{
	int s1_len = s1.size();
	int s2_len = s2.size();
	int *BmGS = CreatPreBmGS(s2); //�������ַ���
	int skipIndex = 0; //������������
	for (int i = 0; i < s1_len - s2_len; i += skipIndex) {
		skipIndex = 0; //���¸�ֵ����
		for (int j = s2_len - 1; j >= 0; j--) { //�����������
			if (s1[i + j] != s2[j]) {
				int _skipIndex = j = BmGS[s1[i + j]]; //���û��ַ�������������ֵ������λ�� = ���ַ����ֵ�λ�� �C ���ַ���ģʽ������һ�γ��ֵ�λ�á�
				skipIndex = _skipIndex > 1 ? _skipIndex : 1;//�������Ȳ���С��1
				break;
			}
		}
		if (0 == skipIndex)
			return i;
	}
	return 0;
}

//��ģʽ���ַ�ʹ��hash��ʾ
void generateBC(const string& b, int m, int bc[]) {
	//b��ģʽ���� m��ģʽ���ĳ��ȣ� bc��ɢ�б�
	//bc���±����ַ�����ASCII�룬����ֵ��ÿ���ַ���ģʽ���г��ֵ�λ�á�
	for (int i = 0; i < 256; i++) {
		bc[i] = -1;
	}
	for (int i = 0; i < m; i++) {
		int ascii = (int)b[i];
		bc[ascii] = i;
	}
}
/*
��suffix�����prefix����
suffix������±�K��ʾ��׺�ִ��ĳ��ȣ�����ֵ��Ӧ�洢���ǣ���ģʽ���и��ú�׺{u}��ƥ����Ӵ�{u*}
����ʼ�±�ֵ��
prefix�����ǲ����͡�����¼ģʽ���ĺ�׺�ִ��Ƿ���ƥ��ģʽ����ǰ׺�Ӵ���

*/
void generateGS(const string& b, int m, int suffix[], bool prefix[]) {
	for (int i = 0; i < m; i++) {
		suffix[i] = -1;
		prefix[i] = false;
	}
	for (int i = 0; i < m - 1; ++i) {
		int j = i;
		int k = 0; //������׺�ִ�����
		while (j >= 0 && b[j] == b[m - 1 - k]) {
			//��b[0, m-1]�󹫹���׺�ִ�
			--j;
			++k;
			suffix[k] = j + 1; //j+1��ʾ������׺�ִ���b[0,i]�е���ʼ�±�
		}
		if (j == -1) prefix[k] = true;//���������׺�ִ�Ҳ��ģʽ����ǰ׺�ִ�

	}
}

//j��ʾ���ַ���Ӧ��ģʽ���е��ַ��±꣬m��ģʽ���ĳ���
//�����ںú�׺������ģʽ������ƶ��ĸ��� 
int moveByGS(int j, int m, int suffix[], bool prefix[]) {
	int k = m - 1 - j; //�ú�׺�ĳ���
	if (suffix[k] != -1) return j - suffix[k] + 1;
	for (int r = j + 2; r <= m - 1; ++r) {
		if (prefix[m - r] == true) {
			return r;
		}
	}
	return m;
}

//BM�㷨
int BM(const string& a, const string& b) 
{
	const int n = a.size();
	const int m = b.size();
	int *suffix = new int[m];
	bool *prefix = new bool[m];

	int bc[256];//bc��¼ģʽ����ÿ���ַ������ֵ�λ��

	generateBC(b, m, bc); //�����ַ���hash��
	//generateGS(b, m, suffix, prefix); //����ú�׺�ͺ�ǰ׺����

	int i = 0; //��ʾ������ģʽ������ĵ�һ���ַ�
	while (i <= n - m) {
		int j;
		for (j = m - 1; j >= 0; j--) { //ģʽ���Ӻ���ǰƥ��
			if (a[i + j] != b[j]) break; //���ַ���Ӧ��ģʽ���±���j,��i+j λ���ǻ��ַ���λ��si        
		}
		if (j < 0) {
			return i; //ƥ��ɹ�������������ģʽ����һ��ƥ����ַ���λ��
		}
		//����x��ͬ�ڽ�ģʽ�����󻬶�j-bc[(int)a[i+j]]λ
		//bc[(int)a[i+j]]��ʾ�����л��ַ���ģʽ���г��ֵ�λ��xi
		int x = i + (j - bc[(int)a[i + j]]);

		int y = 0;
		if (j < m - 1) {//����кú�׺�Ļ�,�����ڴ����������ƶ���λ��y
			y = moveByGS(j, m, suffix, prefix);
		}
		i = i + max(x, y); //i����λ���Ժ��ƽ϶��λ��

	}
	return -1;
}