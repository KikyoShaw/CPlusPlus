#include "Sort.h"

static void swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}

/*
* 冒泡排序
* 原理：通过双重for循环，依次比较相邻两个值，将最大（小）值移到数组最后位置
* 平均时间复杂度：O(n^2)
* 理想时间复杂度：O(n)
* 最差时间复杂度：O(n^2)
* 空间复杂度：O(1)
* 稳定性：稳定
* 数据结构：数组
*/
void BubbleSort(int a[], int n)
{
	int s1 = 0; //为了方便调试查看数据，可以定义s1和s2
	int s2 = 0;
	for (int i = 0; i < n - 1; i++) { 
		for (int j = 0; j < n - 1 - i; j++) { //两两比较，将最大（小）值进行交换
			 s1 = a[j];
			 s2 = a[j + 1];
			if (a[j] > a[j + 1]) {  //此处比较是稳定的，但注意如果换成a[j] >= a[j+1]就不稳定
				swap(a[j], a[j + 1]);
				swap(s1, s2); //交换s1和s2,方便调试查看数据变动过程
			}
		}
	}
}

/*
* 选择排序
* 原理：初始时在序列中找到最大（小）值，放到序列的起始位置作为已排序序列，
* 然后，再从剩余未排序元素中继续寻找最大（小）值，放到已排序序列的末尾。
* 以此类推，直到所有元素均排序完毕。
* 平均时间复杂度：O(n^2)
* 理想时间复杂度：O(n)
* 最差时间复杂度：O(n^2)
* 空间复杂度：O(1)
* 稳定性：不稳定
* 数据结构：数组
*/
void SelectionSort(int a[], int n)
{
	int s1 = 0; //为了方便调试查看数据，可以定义s1和s2
	int s2 = 0;
	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			s1 = a[i];
			s2 = a[j];
			if (a[i] > a[j]) {
				swap(a[i], a[j]);
				swap(s1, s2); //交换s1和s2,方便调试查看数据变动过程
			}
		}
	}
}

void Swap(int a[], int i, int j)
{
	int temp = a[i];
	a[i] = a[j];
	a[j] = temp;
}

int Partition(int a[], int left, int right)  // 划分函数
{
	int pivot = a[right];               // 这里每次都选择最后一个元素作为基准
	int tail = left - 1;                // tail为小于基准的子数组最后一个元素的索引
	for (int i = left; i < right; i++)  // 遍历基准以外的其他元素
	{
		if (a[i] <= pivot)              // 把小于等于基准的元素放到前一个子数组末尾
		{
			Swap(a, ++tail, i);
		}
	}
	Swap(a, tail + 1, right);           // 最后把基准放到前一个子数组的后边，剩下的子数组既是大于基准的子数组
										// 该操作很有可能把后面元素的稳定性打乱，所以快速排序是不稳定的排序算法
	return tail + 1;                    // 返回基准的索引
}

/*
* 快速排序（分治法）
* 原理：首先挑选一个数组里一个值当基准，首先通过一次循环将比基准小（大）的值放在基准左边，比基准大（小）的值放在基准右边。
* 然后对基准左边和右边做同样的操作，此处可以使用递归的方式完成，递归的结束条件是数组大小为0或者1，此时数组已经排序完成了。
* 平均时间复杂度：O(nlogn)
* 理想时间复杂度：O(nlogn)
* 最差时间复杂度：O(n^2)
* 空间复杂度：O(logn)~O(n)
* 稳定性：不稳定
* 数据结构：数组
*/
void QuickSort(int a[], int left, int right)
{
	if (left >= right) //递归结束的条件
		return;
	//int pivot_index = Partition(a, left, right); // 基准的索引
	//QuickSort(a, left, pivot_index - 1);
	//QuickSort(a, pivot_index + 1, right);
	//return;
	int i = left;
	int j = right;
	int s1 = a[i]; //为了方便调试查看数据，可以定义s1和s2
	int s2 = a[j];
	int pivot = a[right]; //选定基准，最左最右都可以,之间有在书上看到把基准设到中间数上，然后交换首位/末尾的方法（更可取）

	while (i != j) //左右下标开始向中移位,且两者下标值不能相等
	{ //注意左右下标先移动顺序，如果基准选择右边，先判断左边下标右移，反之则先判断右边下标左移
		if (a[i] <= pivot && i < j) //左下标所在的值不大于基准，向右移位
			i++;
		s1 = a[i];
		if (a[j] >= pivot && i < j) //右下标所在的值不小于基准，向左移位
			j--;
		s2 = a[j];
		if (i < j) { //左右下标值不能相等
			swap(a[i], a[j]);
			swap(s1, s2);
		}
	}
	//当左下标遇到右下标的时候，交换基准和相遇时所在数组里的那个值
	a[right] = a[i];
	a[i] = pivot;
	QuickSort(a, left, i -1); //左边递归
	QuickSort(a, i +1, right); //右边递归
}
/*
* 插入排序
* 原理：类似于抓扑克牌，把第一个元素当做已经被排序，放在已排序区域（左手抓第一张牌），然后剩余值都当做在未排序区域（牌堆）
* 然后从牌堆依次摸牌（取值），从右往左遍历左手抓的牌（已排序的区域），按照大（小）排序规则把牌（值）插入合适的位置。
* 平均时间复杂度：O(n^2)
* 理想时间复杂度：O(n)
* 最差时间复杂度：O(n^2)
* 空间复杂度：O(1)
* 稳定性：稳定
* 数据结构：数组
*/
void InsertionSort(int a[], int n)
{
	for (int i = 1; i < n; i++) //默认第一个元素已经排序好，因此从第一个元素开始操作，下标从1开始
	{
		int target = a[i]; //相从牌堆摸到的牌
		int j = i - 1; //遍历左手抓的牌
		while (j >=0 && a[j] > target) //从右往左进行比较,选择合适位置插入
		{
			a[j + 1] = a[j]; //当前遍历到的牌比待插入的牌大，就当前遍历到的牌右移
			j--;
		}

		a[j + 1] = target; //通过循环找到合适的空位，将牌插入
	}
}
