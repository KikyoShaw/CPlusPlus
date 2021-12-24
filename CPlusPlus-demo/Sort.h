#pragma once

//冒泡排序
void BubbleSort(int a[], int n);

//鸡尾酒排序
void CocktailSort(int a[], int n);

//选择排序
void SelectionSort(int a[], int n);

//快速排序(重点)
void QuickSort(int a[], int left, int right);

//插入排序
void InsertionSort(int a[], int n);

//二分插入法
void InsertionSortDichotomy(int a[], int n);

//希尔排序
void ShellSort(int a[], int n);

//归并排序
void MergeSort(int a[], int left, int right);

//堆排序
void HeapSort(int a[], int n);


//桶排序
void BucketSort(int a[], int n);

//计数排序
void CountingSort(int a[], int n);

//基数排序
void LsdRadixSort(int a[], int n);