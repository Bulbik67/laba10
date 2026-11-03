#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <locale.h>


double fa(double x);
double fb(double x);
double product(double a, double b);
double diff_squares(double a, double b);
double double_sum(double a, double b);


double cos_n(double x, int N);
double cos_eps(double x, double eps);

int main(void)
{
    double x, f1, f2;
    double res;
    int choice;
    int N, i;
    double eps;

    
    double c_std, c_n, c_eps;

    setlocale(LC_ALL, "Russian");

    
    printf("Задание 1\n");
    printf("F1(x) = x^2 - 3x + 9, если x <= 3;  1 / (x^3 + 3), если x > 3\n");
    printf("F2(x) = x * e^(sin(x^2))\n");
    printf("Введите x: ");
    scanf("%lf", &x);

    f1 = fa(x);
    f2 = fb(x);

    
    printf("fa(x) = %lf, fb(x) = %lf\n", f1, f2);

    
    printf("произведение = %lf, разность квадратов = %lf, удвоенная сумма = %lf\n\n",
        product(f1, f2), diff_squares(f1, f2), double_sum(f1, f2));

    
    do
    {
        printf("Меню:\n");
        printf("1 - значение F1(x)\n");
        printf("2 - значение F2(x)\n");
        printf("3 - произведение F1(x) * F2(x)\n");
        printf("4 - разность квадратов F1(x)^2 - F2(x)^2\n");
        printf("5 - удвоенная сумма 2 * (F1(x) + F2(x))\n");
        printf("0 - выход из меню\n");
        printf("Ваш выбор: ");
        scanf("%d", &choice);

        if (choice >= 1 && choice <= 5)
        {
            printf("Введите x: ");
            scanf("%lf", &x);
            f1 = fa(x);
            f2 = fb(x);
        }

        switch (choice)
        {
        case 1:
            res = f1;
            printf("F1(%.4lf) = %lf\n\n", x, res);
            break;
        case 2:
            res = f2;
            printf("F2(%.4lf) = %lf\n\n", x, res);
            break;
        case 3:
            res = product(f1, f2);
            printf("Произведение = %lf\n\n", res);
            break;
        case 4:
            res = diff_squares(f1, f2);
            printf("Разность квадратов = %lf\n\n", res);
            break;
        case 5:
            res = double_sum(f1, f2);
            printf("Удвоенная сумма = %lf\n\n", res);
            break;
        case 0:
            printf("Выход из меню\n\n");
            break;
        default:
            printf("Неизвестный пункт меню\n\n");
            break;
        }
    } while (choice != 0);

    
    printf("Задание 2. cos(x)\n");
    printf("cos(x) = 1 - x^2/2! + x^4/4! - x^6/6! + ...\n");
    printf("Введите x (в радианах): ");
    scanf("%lf", &x);
    printf("Введите число членов ряда N: ");
    scanf("%d", &N);
    printf("Введите точность eps: ");
    scanf("%lf", &eps);

    if (N < 1 || eps <= 0)
    {
        printf("Ошибка: N должно быть >= 1, eps > 0\n\n");
    }
    else
    {
        c_std = cos(x);

        printf("\n  N |    cos_N     |  отклонение\n");
        printf("----+--------------+--------------\n");
        for (i = 1; i <= N; i++)
        {
            c_n = cos_n(x, i);
            printf("%3d | %12.8lf | %+.4e\n", i, c_n, c_n - c_std);
        }

        c_eps = cos_eps(x, eps);
        printf("\nСтандартная cos(x)  = %.10lf\n", c_std);
        printf("Ряд по N = %d       = %.10lf, отклонение %+.4e\n",
            N, cos_n(x, N), cos_n(x, N) - c_std);
        printf("Ряд по eps = %g = %.10lf, отклонение %+.4e\n\n",
            eps, c_eps, c_eps - c_std);
    }

    return 0;
}


double fa(double x)
{
    double y;
    if (x <= 3)
        y = x * x - 3 * x + 9;
    else
        y = 1.0 / (x * x * x + 3);
    return y;
}


double fb(double x)
{
    double y;
    y = x * exp(sin(x * x));
    return y;
}


double product(double a, double b)
{
    return a * b;
}

double diff_squares(double a, double b)
{
    return a * a - b * b;
}


double double_sum(double a, double b)
{
    return 2 * (a + b);
}


double cos_n(double x, int N)
{
    double sum = 0.0;
    double term = 1.0; 
    int n;

    for (n = 0; n < N; n++)
    {
        sum += term;
        term *= -1.0 * x * x / ((2.0 * n + 1.0) * (2.0 * n + 2.0));
    }
    return sum;
}


double cos_eps(double x, double eps)
{
    double sum = 0.0;
    double term = 1.0;
    int n = 0;

    while (fabs(term) >= eps)
    {
        sum += term;
        term *= -1.0 * x * x / ((2.0 * n + 1.0) * (2.0 * n + 2.0));
        n++;
    }
    return sum;
}