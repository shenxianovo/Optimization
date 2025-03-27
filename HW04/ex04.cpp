#include <iostream>
#include <cmath>
#include <iomanip>

double f(double x)
{
    // e^(-x) + e^(x)
    return exp(-x) + exp(x);
}

// Golden Section Search
double calcLambda_GSS(double a, double b)
{
    return a + 0.382 * (b - a);
}

double calcMu_GSS(double a, double b)
{
    return a + 0.618 * (b - a);
}

void log(int iter, double a, double b, double lambda, double mu, double f_lambda, double f_mu)
{
    std::cout << std::fixed << std::setprecision(3); // 固定小数点格式，保留 3 位小数
    std::cout << "iter: " << iter << ", "
              << "[" << a << ", " << b << "] "
              << "lambda: " << lambda << ", "
              << "mu: " << mu << ", "
              << "f_lambda: " << f_lambda << ", "
              << "f_mu: " << f_mu << ", "
              << "diff: " << b - a
              << std::endl;
    // std::cout.unsetf(std::ios::fixed);
    // std::cout.precision(6); // 恢复默认精度
}

double goldenSectionSearch(double a, double b, double precision)
{
    double lambda = calcLambda_GSS(a, b);
    double mu = calcMu_GSS(a, b);
    double f_lambda = f(lambda);
    double f_mu = f(mu);
    int iter = 0;

label:
    iter++;
    if (f_lambda > f_mu)
    {
        log(iter, a, b, lambda, mu, f_lambda, f_mu);
        if (b - lambda <= precision)
            return mu;
        else
        {
            a = lambda;
            lambda = mu;
            f_lambda = f_mu;
            mu = calcMu_GSS(a, b);
            f_mu = f(mu);
            goto label;
        };
    }
    else
    {
        log(iter, a, b, lambda, mu, f_lambda, f_mu);
        if (mu - a <= precision)
            return lambda;
        else
        {
            b = mu;
            mu = lambda;
            f_mu = f_lambda;
            lambda = calcLambda_GSS(a, b);
            f_lambda = f(lambda);
            goto label;
        }
    }
}

// Fibonacci Search
double fibonacci(int n)
{
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

double calcLambda_FS(double a, double b, int n)
{
    return a + (fibonacci(n - 1) / fibonacci(n + 1)) * (b - a);
}

double calcMu_FS(double a, double b, int n)
{
    return a + (fibonacci(n) / fibonacci(n + 1)) * (b - a);
}

int calcN(double a, double b, double precision)
{
    int n = 0;
    while ((b - a) / precision > fibonacci(n + 1))
    {
        n++;
    }
    std::cout << "n: " << n << std::endl;
    return n;
}

double FibonacciSearch(double a, double b, double precision)
{
    int n = calcN(a, b, precision);
    double lambda = calcLambda_FS(a, b, n);
    double mu = calcMu_FS(a, b, n);
    double f_lambda = f(lambda);
    double f_mu = f(mu);
    int iter = 0;

    while (iter < n)
    {
        iter++;
        if (f_lambda > f_mu)
        {
            log(iter, a, b, lambda, mu, f_lambda, f_mu);
            if (b - lambda <= precision)
                return mu;
            else
            {
                a = lambda;
                lambda = mu;
                f_lambda = f_mu;
                mu = calcMu_FS(a, b, n - iter);
                f_mu = f(mu);
            }
        }
        else
        {
            log(iter, a, b, lambda, mu, f_lambda, f_mu);
            if (mu - a <= precision)
                return lambda;
            else
            {
                b = mu;
                mu = lambda;
                f_mu = f_lambda;
                lambda = calcLambda_FS(a, b, n - iter);
                f_lambda = f(lambda);
            }
        }
    }
}

int main()
{
    // double result = goldenSectionSearch(-1, 1, 0.2);
    double result = FibonacciSearch(-1, 1, 0.2);
    std::cout << "Minimum value of f(x) is " << f(result) << " at x = " << result << std::endl;
    return 0;
}