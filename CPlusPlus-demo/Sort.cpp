#include "Sort.h"

/*
* 分治法是一种解决问题的思想：
* 把大的问题分解成小问题的这个过程就叫“分”，
* 解决小问题的过程就叫“治”，
* 解决小问题的方法往往是递归。
* 分治法的三大步骤：
* 「分」：大问题分解成小问题；
* 「治」：用同样的方法解决小问题；
* 「合」：用小问题的解构造大问题的解。
*/


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
* 冒泡排序改进-鸡尾酒排序
* 和冒泡排序不同的是规则能从高到低然后从低到高来回依次遍历，也叫定向冒泡排序
* 平均时间复杂度：O(n^2)
* 理想时间复杂度：O(n)
* 最差时间复杂度：O(n^2)
* 空间复杂度：O(1)
* 稳定性：稳定
* 数据结构：数组
*/
void CocktailSort(int a[], int n)
{
	int left = 0;
	int right = n - 1;
	int s1 = 0;int s2 = 0; //为了方便调试查看数据，可以定义s1和s2
	while (left < right) //相等即排序完成
	{
		for (int i = left; i < right; i++) //先向右遍历
		{
			s1 = a[i];s2 = a[i + 1];
			if (a[i] > a[i + 1])
			{
				swap(a[i], a[i + 1]); //最大值右移
				swap(s1, s2); //交换s1和s2,方便调试查看数据变动过程
			}
		}
		right--;
		for (int i = right; i > left; i--) //回来向左遍历
		{
			s1 = a[i-1];s2 = a[i];
			if (a[i-1] > a[i])
			{
				swap(a[i - 1], a[i]); //最小值往右移
				swap(s1, s2); //交换s1和s2,方便调试查看数据变动过程
			}
		}
		left++;
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

/*
* 希尔排序/（缩小增量排序）/插入排序改进版
* 原理：通过将比较的全部元素分为几个区域去使用插入排序，从而提升插入排序的性能。
* 希尔排序是基于插入排序的以下两点性质而提出改进方法的：
* 插入排序在对几乎已经排好序的数据操作时，效率高，即可以达到线性排序的效率。
* 但插入排序一般来说是低效的，因为插入排序每次只能将数据移动一位。
* 平均时间复杂度：O(nlogn)~O(n^2)
* 理想时间复杂度：O(n^1.3)
* 最差时间复杂度：O(n^2)
* 优化后最差时间复杂度：O(n3/2)
* 空间复杂度：O(1)
* 稳定性：不稳定
*（虽然是插入排序的改进，一次性插入排序是有序的，但是同时插入过程中，相同元素可能在各自插入排序中移动改变顺序，因此不稳定）
* 数据结构：数组
*/
void ShellSort(int a[], int n)
{
	/*int step = 0;
	while (step <= n)
		step = 3 * step + 1;
	while (step >= 1)
	{
		for (int i = 0; i < n; i++)
		{
			int j = i - step;
			int get = a[i];
			while (j >= 0 && a[j] > get)
			{
				a[j + step] = a[j];
				j = j - step;
			}
			int index = j + step;
			a[index] = get;
		}
		step = (step - 1) / 3;
	}*/	
	int step = n / 2;
	if(step % 2 == 0)
		step++;
	int s1 = 0; int s2 = 0; int s3 = 0;//方便调试查看数据
	while(step>0)
	{
		for(int j = step;j < n;j++)
		{
			int temp = a[j];
			int i = j - step;
			s3 = a[i];
			while(i >= 0 && a[i] > temp)
			{
				int index = i + step;
				a[index] = a[i];
				s1 = a[index];
				i = i-step; //比较前一个值
			}
			if (i != j - step) { //交换最大那个值
				a[i + step] = temp;
				s2 = a[i + step];
			}
		}
		if(step == 1)
			break;
		step = step/2; //递减增量
		if(step % 2 ==0)
			step++;
	}
}

/*
* 归并操作，归并算法核心
*/
void Merge(int a[], int temp[], int left, int right)
{
	//申请内存空间N，空间复杂度为O(n)
	int len = right - left + 1;
	int mid = (left + right) / 2;
	int index = 0;
	int i = left;
	int j = mid + 1;
	int s1 = a[i]; int s2 = a[j]; int s3 = 0;//方便调试查看数据
	while (i <= mid && j <= right && index < len) //排序处理
	{   // 带等于是为了不交换相等值位置，即稳定性
		s1 = a[i];s2 = a[j];
		temp[index++] = a[i] <= a[j] ? a[i++] : a[j++];
	}
	//合并左边组数
	while (i <= mid && index < len)
	{
		s1 = a[i];
		temp[index++] = a[i++];
	}
	//合并右边数组
	while (j <= right && index < len)
	{
		s2 = a[j];
		temp[index++] = a[j++];
	}
	//合并临时数组空间数据到指定数组中
	for (int k = 0; k < len; k++)
	{
		a[left++] = temp[k];
		s3 = temp[k]; //此处可以查看 归并时数据的比较过程和合并过程
	}
}

/*
* 归并排序(分治法)
* 原理：该算法主要在于设计归并操作（Merge接口）
* 首先先拆分数组，可以利用递归的思想去进行操作，当拆分的元素只剩一个时，递归也就完成了。
* 接下来就是合并拆分元素（从左到右合并），合并过程中比较待合并数组中的元素大小，按照大（小）排序，然后归并。
* 平均时间复杂度：O(nlogn)
* 理想时间复杂度：O(nlogn)
* 最差时间复杂度：O(nlogn)
* 空间复杂度：O(n)
* 稳定性：稳定
* 数据结构：数组
*/
void MergeSort(int a[], int left, int right)
{
	if (left >= right)
		return;

	int mid = (left + right) / 2;
	//核心思想：使用递归先拆分，直到只剩一个元素，递归就结束了
	//递归处理左边
	MergeSort(a, left, mid);
	//递归处理右边
	MergeSort(a, mid + 1, right);
	//申请内存空间N，空间复杂度为O(n)
	int len = right - left + 1;
	int *temp = new int[len];
	//核心部分，合并数组
	Merge(a, temp, left, right);
}

/*
* 堆排序核心部分
* 根据数组进行堆调整，从右到左，从下到上调整
* 时间复杂度O(logn)
*/
void HeapIfy(int a[], int index, int size)
{
	int iLeftChild = 2 * index + 1; //左子节点索引
	int iRightChild = 2 * index + 2; //右子节点索引
	int iMax = index; //当前节点和左右子节点中最大值
	int s1 = a[iLeftChild]; int s2 = a[iRightChild]; int s3 = a[index]; int s4 = 0;//方便调试查看数据
	if (iLeftChild < size && a[iLeftChild] > a[iMax])
		iMax = iLeftChild;
	if (iRightChild < size && a[iRightChild] > a[iMax])
		iMax = iRightChild;
	s4 = a[iMax];
	if (index != iMax) { //最大值不是父节点
		swap(a[index], a[iMax]); //把当前节点和子节点进行交换
		swap(s3, s4);
		HeapIfy(a, iMax, size); //递归继续进行当前节点向下进行堆调整
	}
}

/*
*  构建初始化堆入口
*  时间复杂度O(n)
*/
int BuildHeap(int a[], int n)
{
	int iHeadSize = n;
	for (int i = iHeadSize / 2 - 1; i >= 0; i--) { //从每一个非叶结点开始向下进行堆调整
		HeapIfy(a, i, n); 
	}
	return iHeadSize;
}

/*
* 堆排序（二叉树）
* 原理：堆是一个近似完全二叉树的结构。
* 算法思想主要分两步，一是初始化堆，二是对堆进行排序(一般升序采用大顶堆，降序采用小顶堆)。
* 每个结点的值都大于或等于其左右孩子结点的值，称为大顶堆。
* 每个结点的值都小于或等于其左右孩子结点的值，称为小顶堆。
* 平均时间复杂度：O(nlogn)
* 理想时间复杂度：O(nlogn)
* 最差时间复杂度：O(nlogn)
* 空间复杂度：O(1)
* 稳定性：不稳定
* 数据结构：数组
*/
void HeapSort(int a[], int n)
{
	/*
	* 此处采用升序 / 大顶堆的方式
	* 思路：首先将待排序的数组构建成大顶堆，大顶堆的构建是算法的核心部分。
	* 从最后一个非叶节点n/2-1的位置开始检查节点与其子节点值是否满足大顶堆的要求，不满足的话下需要调整该节点与其子节点位置，
	* 如果有所调整，那么调整过的子节点也要递归操作之前父节点调整过程，确保子树也是大顶堆。
	* 按照这个步骤依次往前，从右到左，从下到上调整所有非叶节点的值，确保根节点的值是数组最大值。
	* 接下来将根节点的值与数组最后一个值进行交换，保证最大值到数组最后。
	* 以此类推，继续上续操作与数组N-1所在那个值进行交换，最终能得到一个有序的数组。
	*/

	int iHeadSize = BuildHeap(a, n); //首先构造堆(大顶堆)
	while (iHeadSize > 1)
	{   //将堆顶根节点值和数组最后一个值交换
		swap(a[0], a[--iHeadSize]); //此处交换会打乱相同值本身位置，因此不稳定
		//进行堆调整
		HeapIfy(a, 0, iHeadSize);
	}
}
