#include "Matching.h"
#include <iostream>

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
* 时间复杂度O(n/m)
* 最坏时间复杂度：O(m*n)
* 空间复杂度O(k) 坏字符表空间大小k
*/

int *CreatPreBmGS(const string& str)
{
	int* BmGS = new int[256]; //为坏字符表申请内存空间
	for (int i = 0; i < 256; i++) //初始化表
		BmGS[i] = 0;
	for (int i = 0; i < str.size(); i++) //寻访序列
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
	int *BmGS = CreatPreBmGS(s2); //创建坏字符表
	int skipIndex = 0; //跳进长度区域
	for (int i = 0; i < s1_len - s2_len; i += skipIndex) {
		skipIndex = 0; //重新赋值计算
		for (int j = s2_len - 1; j >= 0; j--) { //从右往左遍历
			if (s1[i + j] != s2[j]) {
				int _skipIndex = j = BmGS[s1[i + j]]; //利用坏字符表计算最大右移值：右移位数 = 坏字符出现的位置 – 坏字符在模式串中上一次出现的位置。
				skipIndex = _skipIndex > 1 ? _skipIndex : 1;//跳进长度不能小于1
				break;
			}
		}
		if (0 == skipIndex)
			return i;
	}
	return 0;
}

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
	int *suffix = new int[m];
	bool *prefix = new bool[m];

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