#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#define lp 1000

double c_od, c_do;

double prostokaty(double(*f)(double))
{
    double krok, p, suma = 0.;
    krok = (c_do - c_od) / lp;

    for (p = c_od + 0.5 * krok; p < c_do; p += krok)
        suma += (*f)(p);

    return suma * krok;
}

double trapezy(double (*f)(double))
{
    double krok, p, suma;
    krok = (c_do - c_od) / lp;
    suma = 0.5 * ((*f)(c_od) + (*f)(c_do));

    for (p = c_od + krok; p < c_do; p += krok)
        suma += (*f)(p);

    return suma * krok;
}

double gen_random(double a, double b) {
    return ((double)rand() / RAND_MAX) * (b - a) + a;
}

double mc(double(*f)(double))
{
    srand(time(NULL));
    double suma, szerokosc, krok, f_min, f_max, y, x, pole, ratio, point;

    suma = f_min = f_max = 0;
    szerokosc = c_do - c_od;
    krok = szerokosc / lp;

    for (x = c_od; x <= c_do; x += krok)
    {
        y = f(x);

        if (y > f_max)
            f_max = y;
        else if (y < f_min)
            f_min = y;
    }

    pole = szerokosc * (f_max - f_min);
    ratio = pole / lp;

    for (int i = 0; i < lp; i++)
    {
        x = gen_random(c_od, c_do);
        y = f(x);
        point = gen_random(f_min, f_max);

        if (point >= 0 && point <= y)
            suma += ratio;
        else if (point <= 0 && point >= y)
            suma -= ratio;
    }
    return suma;
}