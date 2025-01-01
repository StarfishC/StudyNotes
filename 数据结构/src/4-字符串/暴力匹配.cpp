// File:    暴力匹配.cpp
// Author:  csh
// Date:    2020/06/14
// Update:  2020/12/16
// ===================


#include <cstring>
#include <cassert>
#include <string>
#include <iostream>

int NaiveStrMatch(const std::string &t, const std::string &p)
{
    int i = 0;                  // 模式的下标变量
    int j = 0;                  // 目标的下标变量
    int pLen = p.length();      // 模式的长度
    int tLen = t.length();      // 目标的长度
    if(tLen < pLen)             // 如果目标长度小于模式长度，匹配失败
        return -1;
    while(i < pLen && j < tLen)
    {
        if(T[j] == P[i])
            i++, j++;
        else
        {
            j = j - i + 1;      // 减掉匹配成功的i，往后挪一位
            i = 0;
        }
    }
    if(i >= pLen)
        return (j-pLen);        // 最后匹配成功时候j已经多加一次1了
    return -1;
}


int main()
{
    std::string target = "abaacababcac";
    std::string pattern = "ababc";
    int pos = NaiveStrMatch(target, pattern);
    std::cout << pos << std::endl;
    return 0;
}
