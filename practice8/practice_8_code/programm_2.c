//  Сортировка строк матрицы по сумме элементов в строке без кеширования сумм

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


void swap(int *a, int *b)
{
    int c[M];
    memcpy(c, a, sizeof(c));
    memcpy(a, b, sizeof(c));
    memcpy(b, c, sizeof(c));
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


void sort_matrix(int matrix[][M], int n)
{
    for (int i = 0 ; i < n - 1; i++)
    {
        //  Перебор всех строчек матрицы
        for (int j = 0; j < n - i - 1; j++)
        {
            //  Это выражение - сумма элементов массива
            if (sum_arr(matrix[j], M) > sum_arr(matrix[j + 1], M))
            {
                swap(matrix[j], matrix[j + 1]);
            }
        }
    }
}


int main(int argc, char *argv[])
{
    long long unsigned beg, end;
    if (argc != 2)
    {
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
