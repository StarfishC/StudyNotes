// File:    MaxSubseqSum.cpp
// Author:  csh
// Date:    2021/02/20
// Update:  2024/12/07
// ===================

// 1. 暴力法
int MaxSubseqSum1(int arr[], int n)
{
    int this_sum = 0;
    int max_sum = 0;
    for (int i = 0; i < n; i++) // i是子列左端位置
    {
        for (int j = i; j < n; j++) // j是子列右端位置
        {
            this_sum = 0; // A[i]到A[j]的子列和
            for (int k = i; k <= j; k++)
                this_sum += arr[k];
            if (this_sum > max_sum)
                max_sum = this_sum;
        }
    }
    return max_sum;
}

// 2. 暴力法（优化）
int MaxSubseqSum2(int arr[], int n)
{
    int this_sum = 0;
    int max_sum = 0;
    for (int i = 0; i < n; i++)
    {
        this_sum = 0;
        for (int j = i; j < n; j++)
        {
            this_sum += arr[j]; // 对于相同的i不同的j。只需要在j-1循环的基础上累加1项即可
            if (this_sum > max_sum)
                max_sum = this_sum;
        }
    }
    return max_sum;
}

// 3. 分而治之

inline int Max3(int A, int B, int C)
{
    /* 返回3个整数中的最大值 */

    return A > B ? A > C ? A : C : B > C ? B :
                                           C;
}

int DivideAndConquer(int list[], int left, int right)
{
    /* 分治法求list[left]到list[right]的最大子列和 */

    int max_left_sum, max_right_sum; // 左右两边的最大值
    int max_left_border_sum, max_right_border_sum; // 存放跨分界线的结果

    int left_boreder_sum, right_border_sum;
    int center, i;

    if (left == right)
    {
        // 递归终止条件：子列只有一个数字
        if (list[left] > 0)
            return list[left];
        else
            return 0;
    }

    // 找到中分点
    center = (left + right) / 2;
    // 递归求两边子列的最大和
    max_left_sum = DivideAndConquer(list, left, center);
    max_right_sum = DivideAndConquer(list, center + 1, right);

    // 求跨分界线的最大子列和
    max_left_border_sum = 0;
    left_boreder_sum = 0;
    for (i = center; i >= left; i--)
    {
        // 从中线向左扫描
        left_boreder_sum += list[i];
        if (left_boreder_sum > max_left_border_sum)
            max_left_border_sum = left_boreder_sum;
    } // 左边扫描结束
    // 同理右边扫描
    max_right_border_sum = 0;
    right_border_sum = 0;
    for (i = center + 1; i <= right; i++)
    {
        right_border_sum += list[i];
        if (right_border_sum > max_right_border_sum)
            max_right_border_sum = right_border_sum;
    }

    return Max3(max_left_sum, max_right_sum, max_left_border_sum + max_right_border_sum);
}

int MaxSubseqSum3(int arr[], int n)
{
    return DivideAndConquer(arr, 0, n - 1);
}

// 4. 在线处理
int MaxSubseqSum4(int arr[], int n)
{
    int this_sum = 0;
    int max_sum = 0;
    for (int i = 0; i < n; i++)
    {
        this_sum += arr[i]; // 向右累加
        if (this_sum > max_sum)
            max_sum = this_sum;
        else if (this_sum < 0) // 当前子列和为负，则不可能使后面的部分增大
            this_sum = 0;
    }
    return max_sum;
}

#include <iostream>

int main(int argc, char* argv[])
{
    using namespace std;
    int arr[] = { 4, -3, 5, -2, -1, 2, 6, -2 };
    int n = 8;
    int ret1 = MaxSubseqSum1(arr, n);
    int ret2 = MaxSubseqSum2(arr, n);
    int ret3 = MaxSubseqSum3(arr, n);
    int ret4 = MaxSubseqSum4(arr, n);

    cout << "MaxSubseqSum1: " << ret1 << endl;
    cout << "MaxSubseqSum2: " << ret2 << endl;
    cout << "MaxSubseqSum3: " << ret3 << endl;
    cout << "MaxSubseqSum4: " << ret4 << endl;
    return 0;
}
