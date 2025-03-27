#include <iostream>
#include <cmath>
#include <iomanip>

double f(double x)
{
    // x^2 + 2x
    return x * x + 2 * x;
}

double f_prime(double x)
{
    // 2x + 2
    return 2 * x + 2;
}

void log(int iter, double a, double b, double mid, double f_mid)
{
    std::cout << std::fixed << std::setprecision(3); // 固定小数点格式，保留 3 位小数
    std::cout << "iter: " << iter << ", "
              << "[" << a << ", " << b << "] "
              << "mid: " << mid << ", "
              << "f_mid: " << f_mid << ", "
              << "diff: " << b - a
              << std::endl;
    // std::cout.unsetf(std::ios::fixed);
    // std::cout.precision(6); // 恢复默认精度
}

double binarySearch(double a, double b, double precision)
{
    double mid = (a + b) / 2;
    int iter = 0;
    while (b - a > precision)
    {
        iter++;
        if (f_prime(mid) == 0)
        {
            return mid;
        }
        else if (f_prime(mid) > 0)
        {
            b = mid;
        }
        else
        {
            a = mid;
        }
        mid = (a + b) / 2;
        log(iter, a, b, mid, f(mid));
    }
    return mid;
}

int main() {
    double result = binarySearch(-3, 6, 0.2);

    std::cout << "Minimum value of f(x) is " << result << " at x = " << f(result) << std::endl;

    return 0;
}