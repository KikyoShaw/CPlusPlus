#include "Matching.h"
#include <iostream>
#include <vector>

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
* ����ʱ�临�Ӷ�O(n)
* ʱ�临�Ӷ�O(n/m)
* �ʱ�临�Ӷȣ�O(m*n)
* �ռ临�Ӷ�O(k) ���ַ���ռ��Сk
*/
//�洢�Ӵ����ƥ�䳤��
void GetSuff(const string& str, vector<int>& suff)
{
	int len = str.size();
	int k;
	for (int i = len - 2; i >= 0; i--)
	{
		k = i;
		while (k >= 0 && str[k] == str[len - 1 - i + k])
			k--;
		suff[i] = i - k;
	}
}
//�����ú�׺��
void CreatBmGS(const string& str, vector<int>& BmGS)
{
	int i, j;
	int len = str.size();
	vector<int> suff(len + 1, 0);
	GetSuff(str, suff);//suff�洢�Ӵ����ƥ�䳤��
	//��ʼ�� ��û�кú�׺Ҳû�й���ǰ׺ʱ
	for (i = 0; i < len; i++)
		BmGS[i] = len;
	//û�кú�׺ �й���ǰ׺ ����suff ����Ҫ����һλ ����KMP���next����
	for (i = len - 1; i >= 0; i--)
		if (suff[i] == i + 1)
			for (j = 0; j < len - 1; j++)
				if (BmGS[j] == len)//��֤ÿ��λ�ò����ظ��޸�
					BmGS[j] = len - 1 - i;
	//�кú�׺ �й���ǰ׺
	for (i = 0; i < len - 1; i++)
		BmGS[len - 1 - suff[i]] = len - 1 - i;//�ƶ�����
}
//�������ַ���
void CreatBmBC(const string& str, vector<int>& BmBC)
{
	int len = str.size();
	for (int i = 0; i < 256; i++)//��ƥ���ʱ��ֱ���ƶ��Ӵ�
		BmBC.push_back(len);//��ʼ����
	for (int i = 0; i < len - 1; i++)//Ѱ�����У�����ԭ��
		BmBC[str[i]] = len - i - 1;
}

int BoyerMoore(const string& s1, const string& s2)
{
	int s1_len = s1.size();
	int s2_len = s2.size();
	vector<int> BmBC;
	CreatBmBC(s2, BmBC); //�������ַ���
	vector<int> BmGS(s2_len, 0);
	CreatBmGS(s2, BmGS); //�����ú�׺��
	int i = 0;
	int j = 0;
	while (i <= s1_len - s2_len)
	{
		for (j = s2_len - 1; j > -1 && s1[i + j] == s2[j]; j--);
		if (j == (-1))
			return i;
		i += max(BmGS[j], BmBC[s1[i + j]] - (s2_len - 1 - j));
	}
	//int skipIndex = 0; //������������
	//for (int i = 0; i < s1_len - s2_len; i += skipIndex) {
	//	skipIndex = 0; //���¸�ֵ����
	//	for (int j = s2_len - 1; j >= 0; j--) { //�����������
	//		if (s1[i + j] != s2[j]) {
	//			int _skipIndex = j = BmGS[s1[i + j]]; //���û��ַ�������������ֵ������λ�� = ���ַ����ֵ�λ�� �C ���ַ���ģʽ������һ�γ��ֵ�λ�á�
	//			skipIndex = _skipIndex > 1 ? _skipIndex : 1;//�������Ȳ���С��1
	//			break;
	//		}
	//	}
	//	if (0 == skipIndex)
	//		return i;
	//}
	return 0;
}

#pragma region BM

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
	int* suffix = new int[m];
	bool* prefix = new bool[m];

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

#pragma endregion


bool isMatch(const string& s1, int i, const string& s2, int m)
{
	int is, ip;
	for (is = i, ip = 0; is != m && ip != m; is++, ip++)
		if (s1[is] != s2[ip])
			return false;
	return true;
}

/*
* RKƥ���㷨
* BF�㷨�Ľ��汾
* ԭ����ϣ��ԭ����Ҫ��ƹ�ϣ��ʽ��(S[i]-'a')*d^(S.length-i) i��1��ʼ
* ͨ������ģʽ���Ĺ�ϣֵ��Ȼ��Ƚ�iλ����������ģʽ�����������ĸ�Ĺ�ϣֵ
* ����Ⱦͼ���i+1λ�õ�ֵ����iλ�õ�ֵ��ȥ���λ��ֵ�ٳ��Խ��ƣ��ټ���i+S.lengthλ�õ�ֵ,��ȵ�ʱ���ٽ��ж�����ĸƥ�䣨�����ϣ��ͻ��
* ʱ�临�Ӷȣ�O(m*n)
* ����ʱ�临�Ӷȣ�O(m+n)
*/
bool check(const string& s1, const string& s2)  //�Ƚ�����string�Ƿ���ͬ
{
	if (s1.size() != s2.size())return false;
	int len = (int)s1.size();
	for (int i = 0; i < len; i++) {
		if (s1[i] != s2[i])return false;
	}
	return true;
}
int RobinKarp(const string& s1, const string& s2)
{
	int s1_len = s1.size();
	int s2_len = s2.size();
	int radix = 256;//��ĸ��Ĵ�С
	int prime = 108;//��������ϣֵ������
	int s1_hash = 0; //�ַ���s1(s1_len - 1)λ�Ӵ��Ĺ�ϣֵ
	int s2_hash = 0; //�ַ���s2�Ĺ�ϣֵ
	int lm_hash = 1;//����ߵĹ�ϣֵ
	for (int i = 0; i < s2_len; i++)
		s2_hash = (s2_hash * radix + s2[i]) % prime;//����s2�Ĺ�ϣֵ
	for (int i = 0; i < s2_len - 1; i++)
		s1_hash = (s1_hash * radix + s1[i]) % prime;//�����s1 (s1_len - 1)λ�Ӵ��Ĺ�ϣֵ
	for (int i = 0; i < s2_len - 1; i++)
		lm_hash = (lm_hash * radix) % prime;//����ߵĹ�ϣֵ����radix^(s2_len-1)%prime
	for (int i = s2_len - 1; i < s1_len; i++) {
		s1_hash = (s1_hash * radix + s1[i]) % prime;
		if (s1_hash == s2_hash) {//��ϣֵ��ȿɳ����ж��ַ���ƥ��ɹ�
			string sub = s1.substr(i - s2_len + 1, s2_len);
			if (check(sub, s2)) //�����ַ����Աȱ�֤�����ȷ, ��ҪĿ�ķ�ֹ��ϣ��ͻ
				return i - s2_len + 1;
		}
		s1_hash = (s1_hash + prime - lm_hash * s1[i - s2_len + 1] % prime) % prime;
	}
	return 0;
}

/*
* KMPƥ���㷨
* ԭ���������ַ�����ƥ��ʱ�����Խ�һ����֮ǰ�Ѿ�ƥ����ַ����ݴ洢��next�����У�����next�����д洢����Ϣ�����ͷ��ȥ��ƥ�䡣
* next�����ֳ�Ϊǰ׺��KMP���Ĳ��֣����������ڻ��ˣ�����¼��ģʽ����������ƥ���ʱ��ģʽ��Ӧ�ô����￪ʼ����ƥ�䡣
* ʱ�临�Ӷȣ�O(m+n)
*/

/*
* ǰ׺��(next����)
*/
void getNext(const string &s, int *next)
{
	int k = -1; //��ʼ�����ݣ���-1��ʼ
	next[0] = k;
	int i = 0;
	while (i < s.size() - 1)
	{
		if (k == -1 || s[i] == s[k]) { //��ǰ��׺��ͬ��ʱ��
			k++;  //��������
			i++;
			next[i] = k;//��¼ǰ׺����
		}
		else //��ǰ��׺����ͬ��ʱ��
			k = next[k];//��ʼ����
	}
}

/*
* ǰ׺��next���飩�Ż��汾
*/
void getNextVal(const string& s, int* next)
{
	int k = -1; //��ʼ�����ݣ���-1��ʼ
	next[0] = k;
	int i = 0;
	while (i < s.size() - 1)
	{
		if (k == -1 || s[i] == s[k]) { //��ǰ��׺��ͬ��ʱ��
			k++;  //��������
			i++;
			if (s[i] != s[k])
				next[i] = k;//��¼ǰ׺����
			else //��Ϊ���ܳ���s[i] = s[ next[i]]�����Ե�����ʱ��Ҫ�����ݹ飬k = next[k] = next[next[k]]  
				next[i] = next[k];
		}
		else //��ǰ��׺����ͬ��ʱ��
			k = next[k];//��ʼ����
	}
}

int KnuthMorrisPratt(const string& s1, const string& s2)
{
	int* next = new int[s2.size()];//����next����
	getNext(s2, next);
	int j = -1; //ͬnext��ʼ�±���ͬ
	for (int i = 0; i < s1.size(); i++) { //��ʼ�Ƚ�ģʽ��������
		while (j >= 0 && s1[i] != s2[j + 1]) //ģʽ����������ƥ���ʱ��
			j = next[j]; //��ȡ����λ�ã��Ӵ�λ�ÿ�ʼƥ��
		if (s1[i] == s2[j + 1]) //��ģʽ����������ʼ����ƥ��
			j++; //ģʽ����ʼ�����ƶ�
		if (j == (s2.size() - 1)) //�������г�����ģʽ�� �����ɹ�ƥ��
			return (i - s2.size() + 1); //���ص�ǰƥ��λ��
	}
	//int i = 0;
	//while (i < s1.size() && j < s2.size()) //��ʼ�Ƚ�ģʽ��������
	//{
	//	if (j == -1 || s1[i] == s2[j])  //��ʼ��ʼ��ʱ�����ģʽ����������ʼ����ƥ��
	//	{
	//		i++;//������ʼ�����ƶ�
	//		j++;//ģʽ����ʼ�����ƶ�
	//	}
	//	else //ģʽ����������ƥ���ʱ��
	//		j = next[j];  //��ȡ����λ�ã��Ӵ�λ�ÿ�ʼƥ��
	//}
	//if (j == s2.size())  // ƥ��ɹ�
	//	return i - j;//���ص�ǰƥ��λ��
	delete[]next;
	return 0;
}

/*
* 	int s1_len = s1.size();
	int s2_len = s2.size();
	unsigned int h = 1;
	unsigned int A = 0;
	unsigned int St = 0;

	for (int i = 0; i < s2_len - 1; i++)
		h = (h * 26) % 108;
	//��ȡA��St�Ĺ�ϣֵ
	for (int i = 0; i != s2_len; i++) {
		A = (26*A + (s2[i] - 'a')) % 108;
		St = (26*St + (s1[i] - 'a')) % 108;
	}
	for (int i = 0; i != s1_len- s2_len; i++) {
		if (A == St) {
			if (isMatch(s1, i, s2, s2_len))
				return i;
		}
		else {
			St = ( 28 * (St - h*(s1[i] - 'a'))+(s1[i + s2_len]-'a')) % 108;
		}
	}
*/
