#include <iostream>

int MaxDivPow(int n)
{
    return n & - n;
}

int main()
{
    int n = 192;
    int col = MaxDivPow(n);
    int row = n / col;
    std::cout << row << " " << col << std::endl;
}