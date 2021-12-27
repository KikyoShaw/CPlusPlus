#include "Matching.h"


/*
* BF匹配算法
* 暴风(蛮力)匹配算法,又被称为朴素匹配模式算法
* 原理: 假设字符串s1和字符串s2的长度分别为m与n。
* 双循环遍历匹配s1和s2，当s2遍历结束，并且s2的每个字符都和s1的某一部分第一次匹配成功，就完成了此算法
* 最差时间复杂度：O(m*n)
* 理想时间复杂度：O(m+n)
*/
int BruteForce(string s1, string s2)
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
		return index + 1;
	return 0;
}
