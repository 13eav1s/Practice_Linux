# Отладка 2 программы
##  Сборка программы для дальнейшей отладки
```shell
gcc -std=c99 -Wall -Werror -Wpedantic -g task_02.c -o app.exe
```
##  Запуск сеанса отладки
```shell
gdb ./app.exe
```
##  Пробный запуск программы
```shell
(gdb) run
Starting program: /home/x13eav1sx/Рабочий стол/practice3/app.exe 
Enter 5 numbers:
Enter the next number: 10
Enter the next number: 29
Enter the next number: 12
Enter the next number: 12
Enter the next number: 23
Value [1] is 23
Value [2] is -135943528
Value [3] is 65535
Value [4] is -1431696944
The average is 0
The max is -1431696944
[Inferior 1 (process 2784) exited normally]
```
Очевидно, что в массиве все кроме первого числа мусор, среднеарифметическое и максимум посчитались неправильно
Начнем отладку с записи данных в массив
##  Отладка записи данных
Для отладки записи поставим точку остановы на считывание данных и пошагово пройдем цикл заполнения массива
```shell
(gdb) b 19
Breakpoint 4 at 0xaaaaaaaa0800: file task_02.c, line 19.
(gdb) c
Continuing.

Breakpoint 4, main () at task_02.c:19
19              if (scanf("%d", &arr[1]) != 1)
(gdb) next
Enter the next number: 1
16          for (i = 0; i < N; i++)
(gdb) next
18              printf("Enter the next number: ");
(gdb) next

Breakpoint 4, main () at task_02.c:19
19              if (scanf("%d", &arr[1]) != 1)
(gdb) 
Enter the next number: 2 
16          for (i = 0; i < N; i++)
(gdb) print arr
$1 = {-5088, 2, -135943528, 65535, -1431696944}
(gdb) n
18              printf("Enter the next number: ");
(gdb) 

Breakpoint 4, main () at task_02.c:19
19              if (scanf("%d", &arr[1]) != 1)
(gdb) 
Enter the next number: 3
16          for (i = 0; i < N; i++)
(gdb) print arr
$2 = {-5088, 3, -135943528, 65535, -1431696944}
(gdb)
```
Можно заметить что ввод происходит во второй элемент массива (под индексом 1), что бы это исправить надо поменять параметры scanf:
```c
scanf("%d", &arr[1]) на scanf("%d", &arr[i])
```
скомпилируем программу и запустим под отладчиком заново
```shell
kali% gcc -std=c99 -Wall -Werror -Wpedantic -g task_02.c -o app.exe
kali% gdb ./app.exe                                                
GNU gdb (Debian 10.1-2+b1) 10.1.90.20210103-git
Copyright (C) 2021 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
Type "show copying" and "show warranty" for details.
This GDB was configured as "aarch64-linux-gnu".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
--Type <RET> for more, q to quit, c to continue without paging--с
<https://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
    <http://www.gnu.org/software/gdb/documentation/>.

For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from ./app.exe...
(gdb) run
Starting program: /home/x13eav1sx/Рабочий стол/practice3/app.exe 
Enter 5 numbers:
Enter the next number: 1
Enter the next number: 2
Enter the next number: 3
Enter the next number: 4
Enter the next number: 5
Value [1] is 2
Value [2] is 3
Value [3] is 4
Value [4] is 5
The average is 0
The max is 1
[Inferior 1 (process 3357) exited normally]
```
## Отладка вывода массива
Можно заметить что вместо 5-ти элементов массива выводится только 4
Для исправления этой ошибки поставим точку остановы в цикл вывода массива
```shell
(gdb) b 26
Breakpoint 1 at 0xaaaaaaaa0854: file task_02.c, line 26.
(gdb) run
Starting program: /home/x13eav1sx/Рабочий стол/practice3/app.exe 
Enter 5 numbers:
Enter the next number: 1
Enter the next number: 2
Enter the next number: 3
Enter the next number: 4
Enter the next number: 5

Breakpoint 1, main () at task_02.c:26
26          for (i = 1; i < N; i++)
(gdb) list
21                  printf("Input error");
22                  return 1;
23              }
24          }
25      
26          for (i = 1; i < N; i++)
27              printf("Value [%zu] is %d\n", i, arr[i]);
28      
29          printf("The average is %g\n", get_average(arr, N));
--Type <RET> for more, q to quit, c to continue without paging--c
30      
(gdb) next
27              printf("Value [%zu] is %d\n", i, arr[i]);
(gdb) next
Value [1] is 2
(gdb) print arr
$1 = {1, 2, 3, 4, 5}
```
Здесь видно что вывод массива начинается со 2-го элемента, чтобы это исправить нужно поменять условие цикла for:
```c
for (i = 1; i < N; i++) на for (i = 0; i < N; i++)
```
Скомпилируем и запустим программу
```shell
(gdb) run
Starting program: /home/x13eav1sx/Рабочий стол/practice3/app.exe 
Enter 5 numbers:
Enter the next number: 1
Enter the next number: 2
Enter the next number: 3
Enter the next number: 4
Enter the next number: 5
Value [0] is 1
Value [1] is 2
Value [2] is 3
Value [3] is 4
Value [4] is 5
The average is 0
The max is 1
[Inferior 1 (process 3707) exited normally]
```
## Исправление в нахождении среднеарифметического
Можно заметить что программа выдала 0 вместо среднеарифметического
поставим точку останова в функцию get_average для проверки передаваемого значения и работы функции
```shell
(gdb) break get_average
Breakpoint 1 at 0xaaaaaaaa08e4: file task_02.c, line 38.
(gdb) run
Starting program: /home/x13eav1sx/Рабочий стол/practice3/app.exe 
Enter 5 numbers:
Enter the next number: 1
Enter the next number: 2
Enter the next number: 3
Enter the next number: 4
Enter the next number: 5
Value [0] is 1
Value [1] is 2
Value [2] is 3
Value [3] is 4
Value [4] is 5

Breakpoint 1, get_average (a=0xffffffffec00, n=5) at task_02.c:38
38          double temp = 0.0;
(gdb) print a
$1 = (const int *) 0xffffffffec00
(gdb) print *a
$2 = 1
```
Видно, что параметры передались корректно. Теперь посмотрим что возвращает функция
```shell
(gdb) b 44
Breakpoint 2 at 0xaaaaaaaa0944: file task_02.c, line 44.
(gdb) c
Continuing.

Breakpoint 2, get_average (a=0xffffffffec00, n=5) at task_02.c:44
44          return temp;
(gdb) print temp
$3 = 0
```
Так как функция принимает верные параметры, а возвращает 0 можно сделать вывод, что ошибка в функции, для ее нахождения
пройдем get_average пошагово
```shell
Breakpoint 1, get_average (a=0xffffffffec00, n=5) at task_02.c:38
38          double temp = 0.0;
(gdb) s
40          for (size_t i = 0; i > n; i++)
(gdb) s
42          temp /= n;
(gdb) 
```
Цикл for не срабатывает, значит у него неверное условие. Для корректной работы нужно поменять
```c
for (size_t i = 0; i > n; i++) на for (size_t i = 0; i < n; i++)
```
Скомпилируем и запустим программу
```shell
(gdb) run
Starting program: /home/x13eav1sx/Рабочий стол/practice3/app.exe 
Enter 5 numbers:
Enter the next number: 1
Enter the next number: 2
Enter the next number: 3
Enter the next number: 4
Enter the next number: 5
Value [0] is 1
Value [1] is 2
Value [2] is 3
Value [3] is 4
Value [4] is 5
The average is 3
The max is 1
[Inferior 1 (process 4048) exited normally]
```
##  Устранение ошибки в нахождении максимума
Видно, что программа находит максимум неверно, для устранения этой ошибки поставим точку останова в функцию get_max для
проверки входных и выходных данных и ее работы:
```shell
(gdb) b get_max
Breakpoint 1 at 0xaaaaaaaa095c: file task_02.c, line 49.
(gdb) run
Starting program: /home/x13eav1sx/Рабочий стол/practice3/app.exe 
Enter 5 numbers:
Enter the next number: 1
Enter the next number: 2
Enter the next number: 5
Enter the next number: 4
Enter the next number: 3
Value [0] is 1
Value [1] is 2
Value [2] is 5
Value [3] is 4
Value [4] is 3
The average is 3

Breakpoint 1, get_max (a=0xffffffffec00, n=5) at task_02.c:49
49          int max = a[0];
(gdb) l
44          return temp;
45      }
46      
47      int get_max(const int *a, size_t n)
48      {
49          int max = a[0];
50      
51          for (size_t i = 1; i < n; i++)
52              if (max > a[i])
--Type <RET> for more, q to quit, c to continue without paging--c
53                  max = a[i];
(gdb) l
54      
55          return max;
56      }
(gdb) b 55
Breakpoint 2 at 0xaaaaaaaa09c8: file task_02.c, line 55.
(gdb) c
Continuing.

Breakpoint 2, get_max (a=0xffffffffec00, n=5) at task_02.c:55
55          return max;
(gdb) print max
$1 = 1
```
Входные параметры корректны, а на выходе неверный результат - значит функция работает некорректно для нахождения и устранения
ошибки пройдем функцию пошагово
```shell
Breakpoint 1, get_max (a=0xffffffffec00, n=5) at task_02.c:49
49          int max = a[0];
(gdb) n
51          for (size_t i = 1; i < n; i++)
(gdb) n
52              if (max > a[i])
(gdb) p a[i]
$2 = 2
(gdb) p max
$3 = 1
(gdb) n
51          for (size_t i = 1; i < n; i++)
```
Здесь видно что условие не выполняется из-за его некорректности и вместо максимума находится минимум, что бы это исправить
нужно заменить:
```c
if (max > a[i]) на if (max < a[i])
```
Скомпилируем и запустим
```shell
(gdb) run
Starting program: /home/x13eav1sx/Рабочий стол/practice3/app.exe 
Enter 5 numbers:
Enter the next number: 3
Enter the next number: 2
Enter the next number: 5
Enter the next number: 1
Enter the next number: 4
Value [0] is 3
Value [1] is 2
Value [2] is 5
Value [3] is 1
Value [4] is 4
The average is 3
The max is 5
[Inferior 1 (process 4293) exited normally]
```
Все ошибки исправлены и программа работает корректно
