#include <iostream>
#include <cmath>
#include <iomanip>

double f(double x)
{
    return 1 - x * exp(-(x * x));
}

double calcAlphaBar(double a_1, double a_2, double a_3,
                    double f_1, double f_2, double f_3)
{
    return (((a_2 * a_2 - a_3 * a_3) * f_1 + (a_3 * a_3 - a_1 * a_1) * f_2 + (a_1 * a_1 - a_2 * a_2) * f_3) / ((a_2 - a_3) * f_1 + (a_3 - a_1) * f_2 + (a_1 - a_2) * f_3)) / 2;
}

double log(int iter, double a_1, double a_2, double a_3,
           double f_1, double f_2, double f_3)
    {
        std::cout << std::fixed << std::setprecision(3); // 固定小数点格式，保留 3 位小数
        std::cout << "iter: " << iter << ", "
                  << "[a1, a2, a3]: [" << a_1 << ", " << a_2 << ", " << a_3 << "] "
                  << "[f1, f2, f3]: [" << f_1 << ", " << f_2 << ", " << f_3 << "] "
                  << std::endl;
    }

double interpolationSearch(double a_1, double a_3, double precision)
{
    double a_2 = (a_1 + a_3) / 2;
    double f_1 = f(a_1);
    double f_2 = f(a_3);
    double f_3 = f(a_2);
    int iters = 0;

step_1:
    log(iters, a_1, a_2, a_3, f_1, f_2, f_3);
    iters++;
    double a_bar = calcAlphaBar(a_1, a_2, a_3, f_1, f_2, f_3);
    double f_bar = f(a_bar);

step_2:
    if (a_bar > a_2)
        goto step_3;
    else
        goto step_4;
step_3:
    if (f_bar <= f_2)
    {
        a_1 = a_2;
        a_2 = a_bar;
        f_1 = f_2;
        f_2 = f_bar;
        goto step_5;
    }
    else
    {
        a_3 = a_bar;
        f_3 = f_bar;
        goto step_5;
    }
step_4:
    if (f_bar <= f_2)
    {
        a_3 = a_2;
        a_2 = a_bar;
        f_3 = f_2;
        f_2 = f_bar;
        goto step_5;
    }
    else
    {
        a_1 = a_bar;
        f_1 = f_bar;
        goto step_5;
    }
step_5:
    if (a_3 - a_1 < precision)
        return a_bar;
    else
        goto step_1;
}

int main()
{

    double result = interpolationSearch(0, 1, 0.05);

    std::cout << "Minimum value of f(x) is " << result << " at x = " << f(result) << std::endl;

    return 0;
}