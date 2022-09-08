#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>


#define ERROR 2


//  Получение времени в микросекундах
unsigned long long milliseconds_now(void)
{
    struct timeval val;

    if (gettimeofday(&val, NULL))
        return (unsigned long long)-1;

    return val.tv_sec * 1000000ULL + val.tv_usec;
}


int count(const int x_arr[], int k1, const int y_arr[], int k2)
{
    int rez = 0;
    int k;
    if (k1 > k2)
    {
        k = k2;
    }
    else
    {
        k = k1;
    }
    for (int i =0; i < k; i++)
    {
        rez += x_arr[i] * y_arr[i];
    }
    return rez;
}


int main(int argc, char *argv[])
{
    long long unsigned beg, end;
    if (argc != 2)
    {
        printf("Неверный параметр!\n");
        return ERROR;
    }
    int N = atoi(argv[1]);
    int a[N], x[N], y[N];
    int *pabeg = a, *paend = pabeg + N;
    srand(time(NULL));
    while (pabeg < paend)
    {
        int i = rand() % 10;
        if (i > 5)
        {
            i *= -1;
        }
        else if (i < 5)
        {
            i *= 2;
        }
        *pabeg = i;
        pabeg++;
    }
    pabeg = a;
    int *pxbeg = x, p = 0;
    int *pybeg = y, q = 0;
    //  Распределение элементов по массивам
    while (pabeg < paend)
    {
        if (*pabeg < 0)
        {
            *pxbeg = *pabeg;
            p++;
            pxbeg++;
        }
        if (*pabeg > 0)
        {
            *pybeg = *pabeg;
            q++;
            pybeg++;
        }
        pabeg++;
    }
    pxbeg = x;
    pybeg = y;
    // Реверсирование массива
    for (int *ukazatel1 = y, *ukazatel2 = y + q - 1; ukazatel1 < y + q / 2; ukazatel1++, ukazatel2--)
    {
        int temp = *ukazatel2;
        *ukazatel2 = *ukazatel1;
        *ukazatel1 = temp;
    }
    if (p == 0 || q == 0)
    {
//        printf("Нет отрицательных / положительных элементов!\n");
        return ERROR;
    }
//    int *pxend = pxbeg + p;
//    int *pyend = pybeg + q;
    beg = milliseconds_now();
    int rez = count(pxbeg, p, pybeg, q);
    end = milliseconds_now();
    printf("%llu\n", end - beg);
    //  Для обмана оптимизатора
    return rez;
}

