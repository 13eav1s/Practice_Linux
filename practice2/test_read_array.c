#include "test.h"
#include "libs.h"
#include "read_array.h"

bool is_equal(int* arr, int *expected, int n)
{
	for (int i = 0; i < n; i++)
	{
		if (arr[i] != expected[i])
		{
			return false;
		}
	}
	return true;
}

short int test_read_array()
{
	FILE* f;
	int n = 0, error_count = 0, n_expected = 8,
		arr[MAX_NUM_COUNT + 1] = { 0 },
		expected[MAX_NUM_COUNT] = { 4, 56, -258, 741, 0, -32, 8, -8 };
	char fileName_in[] = "testing_in_file.txt";
	char str[MAX_STR_LEN + 2] = { "2 11 abs - 5 9\n 2.5 62 - 8.7 \n 15 (, -39 \n" };
	f = fopen(fileName_in, "w");
	fprintf(f, "%s", str);
	for (int i = 0; i < 101; i++)
	{
		fprintf(f, "%d ", i);
	}
	fprintf(f, "\n");
	for (int i = 0; i < 4095; i++)
	{
		fprintf(f, "%d", i % 10);
	}
	strcpy(str, "\n 4 56 -258 741 0 -32 8 -8 \n 0   0   0 0 0 \n");
	strcat(str, "2147483646 -2147483647   2147483645  2147483647\n 87 -91   4210 000561  015 48");
	fprintf(f, "%s", str);
	fclose(f);
	f = fopen(fileName_in, "r");
	//Тесты с неверным форматом
	for (int i = 0; i < 3; i++)
	{
		if (read_array(f, arr, &n) != INCORRECT_FILE)
		{
			printf("Ошибка при обработке файла! Неверный формат данных \n");
			error_count++;
		}
	}
	//4-й тест Слишком много чисел в строке
	if (read_array(f, arr, &n) != TOO_MANY_NUMBERS)
	{
		printf("Ошибка при обработке файла! Слишком много чисел в строке \n");
		error_count++;
	}
	//5-й тест Слишком длинная строка
	if (read_array(f, arr, &n) != TOO_LONG_STRING)
	{
		printf("Ошибка при обработке файла! Слишком длинная строка \n");
		error_count++;
	}
	//6-й тест к read_arr  Содержится пустая строка
	if (read_array(f, arr, &n) != CONTAIN_EMPTY_STRING)
	{
		printf("Ошибка при обработке файла! Содержится пустая строка \n");
		error_count++;
	}
	//7-й тест к read_arr
	if (read_array(f, arr, &n) != 0 || n != n_expected || !is_equal(arr, expected, n))
	{
		printf("Ошибка при обработке файла! Неверный результат работы программы при считывании строки:  \n\"4 56 -258 741 0 -32 8 -8\"\n");
		error_count++;
	}
	//8-й тест к read_arr 
	for (int i = 0; i < n_expected; i++)
	{
		expected[i] = 0;
	}
	n_expected = 5;
	if (read_array(f, arr, &n) != 0 || n != n_expected || !is_equal(arr, expected, n))
	{
		printf("Ошибка при обработке файла! Неверный результат работы программы при считывании строки: \n\" 0   0   0 0 0 \"\n");
		error_count++;
	}
	//9-й тест к read_arr 
	n_expected = 4;
	expected[0] = 2147483646;
	expected[1] = -2147483647;
	expected[2] = 2147483645;
	expected[3] = 2147483647;
	if (read_array(f, arr, &n) != 0 || n != n_expected || !is_equal(arr, expected, n))
	{
		printf("Ошибка при обработке файла! Неверный результат работы программы при считывании строки: \n\" 2147483646 -2147483647   2147483645  2147483647 \"\n");
		error_count++;
	}
	//10-й тест к read_arr
	n_expected = 6;
	expected[0] = 87;
	expected[1] = -91;
	expected[2] = 4210;
	expected[3] = 561;
	expected[4] = 15;
	expected[5] = 48;
	if (read_array(f, arr, &n) != 0 || n != n_expected || !is_equal(arr, expected, n))
	{
		printf("Ошибка при обработке файла! Неверный результат работы программы при считывании строки: \n\"87 -91   4210 000561  015 48\"\n");
		error_count++;
	}
	fclose(f);

	return error_count;
}


