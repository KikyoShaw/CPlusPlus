#include "Matching.h"
#include <iostream>
#include <vector>

/*
* BF匹配算法
* 暴风(蛮力)匹配算法,又被称为朴素匹配模式算法
* 原理: 假设字符串s1和字符串s2的长度分别为m与n。
* 双循环遍历匹配s1和s2，当s2遍历结束，并且s2的每个字符都和s1的某一部分第一次匹配成功，就完成了此算法
* 最差时间复杂度：O(m*n)
* 理想时间复杂度：O(m+n)
*/
int BruteForce(const string& s1, const string& s2)
{
	int index = 0;
	int i = 0; 
	int j = 0;
	while (s1[i] != '\0' && s2[j] != '\0'){
		if (s1[i] == s2[j]) { //找到相等位置后比较双方后一个字符
			i++;
			j++;
		}
		else { //不相等的时候
			index++; //记录下一个位置
			i = index; //s1字符串移到下一个位置
			j = 0; //s2字符串从首个开始匹配
		}
	}
	if (s2[j] == '\0')
		return index;
	return 0;
}

/*
* BM匹配算法
* 单模式匹配的字符串搜索算法,效率快于KMP算法。
* 三大特点：从模式串最右开始进行匹配，坏字符表，好后缀表。
* 原理：从右往左遍历进行字符匹配，当字符不匹配的时候，就从坏字符表和好字符表找一个最大右移值，而后将模式串右移继续匹配。
* 坏字符针对的是主串，好后缀针对的是模式串。
* 坏字符表右移位数 = 坏字符出现的位置 – 坏字符在模式串中上一次出现的位置。
* 好后缀表右移位数 = 好后缀出现的位置 – 好后缀在模式串中上一次出现的位置。
* 实际运用过程中，遇到坏字符的概率要远远大于好后缀的情况，因此大部分情况只需要用到坏字符表即可，这也是BM算法后面改进版本BMH的思想
* https://www.ruanyifeng.com/blog/2013/05/boyer-moore_string_search_algorithm.html
* 理想时间复杂度O(n)
* 时间复杂度O(n/m)
* 最坏时间复杂度：O(m*n)
* 空间复杂度O(k) 坏字符表空间大小k
*/
//存储子串的最长匹配长度
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
//创建好后缀表
void CreatBmGS(const string& str, vector<int>& BmGS)
{
	int i, j;
	int len = str.size();
	vector<int> suff(len + 1, 0);
	GetSuff(str, suff);//suff存储子串的最长匹配长度
	//初始化 当没有好后缀也没有公共前缀时
	for (i = 0; i < len; i++)
		BmGS[i] = len;
	//没有好后缀 有公共前缀 调用suff 但是要右移一位 类似KMP里的next数组
	for (i = len - 1; i >= 0; i--)
		if (suff[i] == i + 1)
			for (j = 0; j < len - 1; j++)
				if (BmGS[j] == len)//保证每个位置不会重复修改
					BmGS[j] = len - 1 - i;
	//有好后缀 有公共前缀
	for (i = 0; i < len - 1; i++)
		BmGS[len - 1 - suff[i]] = len - 1 - i;//移动距离
}
//创建坏字符表
void CreatBmBC(const string& str, vector<int>& BmBC)
{
	int len = str.size();
	for (int i = 0; i < 256; i++)//不匹配的时候直接移动子串
		BmBC.push_back(len);//初始化表
	for (int i = 0; i < len - 1; i++)//寻访序列，靠右原则
		BmBC[str[i]] = len - i - 1;
}

int BoyerMoore(const string& s1, const string& s2)
{
	int s1_len = s1.size();
	int s2_len = s2.size();
	vector<int> BmBC;
	CreatBmBC(s2, BmBC); //创建坏字符表
	vector<int> BmGS(s2_len, 0);
	CreatBmGS(s2, BmGS); //创建好后缀表
	int i = 0;
	int j = 0;
	while (i <= s1_len - s2_len)
	{
		for (j = s2_len - 1; j > -1 && s1[i + j] == s2[j]; j--);
		if (j == (-1))
			return i;
		i += max(BmGS[j], BmBC[s1[i + j]] - (s2_len - 1 - j));
	}
	//int skipIndex = 0; //跳进长度区域
	//for (int i = 0; i < s1_len - s2_len; i += skipIndex) {
	//	skipIndex = 0; //重新赋值计算
	//	for (int j = s2_len - 1; j >= 0; j--) { //从右往左遍历
	//		if (s1[i + j] != s2[j]) {
	//			int _skipIndex = j = BmGS[s1[i + j]]; //利用坏字符表计算最大右移值：右移位数 = 坏字符出现的位置 – 坏字符在模式串中上一次出现的位置。
	//			skipIndex = _skipIndex > 1 ? _skipIndex : 1;//跳进长度不能小于1
	//			break;
	//		}
	//	}
	//	if (0 == skipIndex)
	//		return i;
	//}
	return 0;
}

#pragma region BM

//将模式串字符使用hash表示
void generateBC(const string& b, int m, int bc[]) {
	//b是模式串， m是模式串的长度， bc是散列表
	//bc的下标是字符集的ASCII码，数组值是每个字符在模式串中出现的位置。
	for (int i = 0; i < 256; i++) {
		bc[i] = -1;
	}
	for (int i = 0; i < m; i++) {
		int ascii = (int)b[i];
		bc[ascii] = i;
	}
}
/*
求suffix数组和prefix数组
suffix数组的下标K表示后缀字串的长度，数组值对应存储的是，在模式串中跟好后缀{u}相匹配的子串{u*}
的起始下标值。
prefix数组是布尔型。来记录模式串的后缀字串是否能匹配模式串的前缀子串。

*/
void generateGS(const string& b, int m, int suffix[], bool prefix[]) {
	for (int i = 0; i < m; i++) {
		suffix[i] = -1;
		prefix[i] = false;
	}
	for (int i = 0; i < m - 1; ++i) {
		int j = i;
		int k = 0; //公共后缀字串长度
		while (j >= 0 && b[j] == b[m - 1 - k]) {
			//与b[0, m-1]求公共后缀字串
			--j;
			++k;
			suffix[k] = j + 1; //j+1表示公共后缀字串在b[0,i]中的起始下标
		}
		if (j == -1) prefix[k] = true;//如果公共后缀字串也是模式串的前缀字串

	}
}

//j表示坏字符对应的模式串中的字符下标，m是模式串的长度
//计算在好后缀规则下模式串向后移动的个数 
int moveByGS(int j, int m, int suffix[], bool prefix[]) {
	int k = m - 1 - j; //好后缀的长度
	if (suffix[k] != -1) return j - suffix[k] + 1;
	for (int r = j + 2; r <= m - 1; ++r) {
		if (prefix[m - r] == true) {
			return r;
		}
	}
	return m;
}

//BM算法
int BM(const string& a, const string& b)
{
	const int n = a.size();
	const int m = b.size();
	int* suffix = new int[m];
	bool* prefix = new bool[m];

	int bc[256];//bc记录模式串中每个字符最后出现的位置

	generateBC(b, m, bc); //构建字符串hash表
	//generateGS(b, m, suffix, prefix); //计算好后缀和好前缀数组

	int i = 0; //表示主串与模式串对齐的第一个字符
	while (i <= n - m) {
		int j;
		for (j = m - 1; j >= 0; j--) { //模式串从后往前匹配
			if (a[i + j] != b[j]) break; //坏字符对应的模式串下标是j,即i+j 位置是坏字符的位置si        
		}
		if (j < 0) {
			return i; //匹配成功，返回主串与模式串第一个匹配的字符的位置
		}
		//这里x等同于将模式串往后滑动j-bc[(int)a[i+j]]位
		//bc[(int)a[i+j]]表示主串中坏字符在模式串中出现的位置xi
		int x = i + (j - bc[(int)a[i + j]]);

		int y = 0;
		if (j < m - 1) {//如果有好后缀的话,计算在此情况下向后移动的位数y
			y = moveByGS(j, m, suffix, prefix);
		}
		i = i + max(x, y); //i更新位可以后移较多的位置

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
* RK匹配算法
* BF算法改进版本
* 原理：哈希表原理，需要设计哈希公式：(S[i]-'a')*d^(S.length-i) i从1开始
* 通过计算模式串的哈希值，然后比较i位置上主串与模式串长度相等字母的哈希值
* 不相等就计算i+1位置的值等于i位置的值减去最高位的值再乘以进制，再加上i+S.length位置的值,相等的时候再进行二次字母匹配（避免哈希冲突）
* 时间复杂度：O(m*n)
* 理想时间复杂度：O(m+n)
*/
bool check(const string& s1, const string& s2)  //比较两个string是否相同
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
	int radix = 256;//字母表的大小
	int prime = 108;//参与计算哈希值的素数
	int s1_hash = 0; //字符串s1(s1_len - 1)位子串的哈希值
	int s2_hash = 0; //字符串s2的哈希值
	int lm_hash = 1;//最左边的哈希值
	for (int i = 0; i < s2_len; i++)
		s2_hash = (s2_hash * radix + s2[i]) % prime;//计算s2的哈希值
	for (int i = 0; i < s2_len - 1; i++)
		s1_hash = (s1_hash * radix + s1[i]) % prime;//计算出s1 (s1_len - 1)位子串的哈希值
	for (int i = 0; i < s2_len - 1; i++)
		lm_hash = (lm_hash * radix) % prime;//最左边的哈希值，即radix^(s2_len-1)%prime
	for (int i = s2_len - 1; i < s1_len; i++) {
		s1_hash = (s1_hash * radix + s1[i]) % prime;
		if (s1_hash == s2_hash) {//哈希值相等可初步判定字符串匹配成功
			string sub = s1.substr(i - s2_len + 1, s2_len);
			if (check(sub, s2)) //加上字符串对比保证结果正确, 主要目的防止哈希冲突
				return i - s2_len + 1;
		}
		s1_hash = (s1_hash + prime - lm_hash * s1[i - s2_len + 1] % prime) % prime;
	}
	return 0;
}

/*
* KMP匹配算法
* 原理：当出现字符串不匹配时，可以将一部分之前已经匹配的字符内容存储到next数组中，利用next数组中存储的信息避免从头再去做匹配。
* next数组又称为前缀表，KMP核心部分，作用是用于回退，它记录了模式串和主串不匹配的时候，模式串应该从哪里开始重新匹配。
* 时间复杂度：O(m+n)
*/

/*
* 前缀表(next数组)
*/
void getNext(const string &s, int *next)
{
	int k = -1; //初始化数据，从-1开始
	next[0] = k;
	int i = 0;
	while (i < s.size() - 1)
	{
		if (k == -1 || s[i] == s[k]) { //当前后缀相同的时候
			k++;  //长度增加
			i++;
			next[i] = k;//记录前缀长度
		}
		else //当前后缀不相同的时候
			k = next[k];//开始回退
	}
}

/*
* 前缀表（next数组）优化版本
*/
void getNextVal(const string& s, int* next)
{
	int k = -1; //初始化数据，从-1开始
	next[0] = k;
	int i = 0;
	while (i < s.size() - 1)
	{
		if (k == -1 || s[i] == s[k]) { //当前后缀相同的时候
			k++;  //长度增加
			i++;
			if (s[i] != s[k])
				next[i] = k;//记录前缀长度
			else //因为不能出现s[i] = s[ next[i]]，所以当出现时需要继续递归，k = next[k] = next[next[k]]  
				next[i] = next[k];
		}
		else //当前后缀不相同的时候
			k = next[k];//开始回退
	}
}

int KnuthMorrisPratt(const string& s1, const string& s2)
{
	int* next = new int[s2.size()];//创建next数组
	getNext(s2, next);
	int j = -1; //同next起始下标相同
	for (int i = 0; i < s1.size(); i++) { //开始比较模式串和主串
		while (j >= 0 && s1[i] != s2[j + 1]) //模式串和主串不匹配的时候
			j = next[j]; //获取回退位置，从此位置开始匹配
		if (s1[i] == s2[j + 1]) //当模式串和主串开始出现匹配
			j++; //模式串开始往后移动
		if (j == (s2.size() - 1)) //当主串中出现了模式串 则代表成功匹配
			return (i - s2.size() + 1); //返回当前匹配位置
	}
	//int i = 0;
	//while (i < s1.size() && j < s2.size()) //开始比较模式串和主串
	//{
	//	if (j == -1 || s1[i] == s2[j])  //初始开始的时候或者模式串和主串开始出现匹配
	//	{
	//		i++;//主串开始往后移动
	//		j++;//模式串开始往后移动
	//	}
	//	else //模式串和主串不匹配的时候
	//		j = next[j];  //获取回退位置，从此位置开始匹配
	//}
	//if (j == s2.size())  // 匹配成功
	//	return i - j;//返回当前匹配位置
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
	//获取A和St的哈希值
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
