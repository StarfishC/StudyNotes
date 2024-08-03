/******************************************************************************
 * File:           1-2-1.cpp
 * Author:         caoshenghui <576365750@qq.com>
 * Github:         https://github.com/caoshenghui
 * Description:
 * LICENSE:        MIT
******************************************************************************/

#include <iostream>

//f(m,n) = f(m-n,n) + f(m,n)
//f(m,0) = 0, f(0,n) = 1
std::size_t f(std::size_t m, std::size_t n)
{
    if (m == 0)
        return 1;
    else if (n == 0)
        return 0;
    else if (m < n)
        return f(m, m);
    else
        return f(m, n - 1) + f(m - n, n);
}

int main(int argc, char** argv)
{
    std::cout << f(5, 3) << std::endl;
    std::cout << f(6, 4) << std::endl;
    return 0;
}
