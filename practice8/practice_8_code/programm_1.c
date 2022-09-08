//  Сортировка строк матрицы по сумме элементов в строке с кешированием сумм.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>

#define ERROR 2
#define M 100


//  Получение времени в микросекундах
unsigned long long microseconds_now(void)
{
    struct timeval val;
    if (gettimeofday(&val, NULL))
    {
        return (unsigned long long) - 1;
    }
    return val.tv_sec * 1000000ULL + val.tv_usec;
}


void swap(int a[M], int b[M])
{
    int c[M];
    memcpy(c, a, M);
    memcpy(a, b, M);
    memcpy(b, c, M);
}


void input_elements(int arr[][M], int n)
{
    srand(time(NULL));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < M; j++)
        {
            int element = rand() % 10;
            arr[i][j] = element;
        }
    }
}


int sum_arr(const int arr[], int n)
{
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += arr[i];
    }
    return sum;
}


// Сортировка массивов X и Y по X
void sort_2(int arr1[], int arr2[][M], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - 1; j++)
        {
            if (arr1[j] > arr1[j + 1])
            {
                int s = arr1[j];
                int line[M];
                arr1[j] = arr1[j + 1];
                arr1[j + 1] = s;

                memcpy(line, arr2[j], sizeof(line));
                memcpy(arr2[j], arr2[j + 1], sizeof(line));
                memcpy(arr2[j + 1], line, sizeof(line));
            }

        }
    }
}


void sort_matrix(int matrix[][M], int n)
{
    int array_sum[n];
    //  Заполнение массива сумм
    for (int i = 0; i < n; i++)
    {
        array_sum[i] = sum_arr(matrix[i], M);
    }
    sort_2(array_sum, matrix, n);
}


int main(int argc, char *argv[]) {
    long long unsigned beg, end;
    if (argc != 2) {
        printf("Неверный параметр!\n");
        return ERROR;
    }
    int matrix_len = atoi(argv[1]);
    int matrix[matrix_len][M];
    input_elements(matrix, matrix_len);
    beg = microseconds_now();
    sort_matrix(matrix, matrix_len);
    end = microseconds_now();
    printf("%llu\n", end - beg);
    return 0;
}
