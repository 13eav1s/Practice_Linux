import os
import shutil


#  Функция принимает имя файла и возвращает массив целых чисел из этого файла
def read(str):
    with open(str, "r") as f:
        mass = []
        for line in f:
            a = int(line)
            mass.append(a)
    return mass


def find_sizes(folder):
    sizes = []
    files = os.listdir(folder)
    for i in range(len(files)):
        file = files[i]
        file = file[14:]
        file = file.replace(".txt", "", 1)
        sizes.append(int(file))
    sizes = list(set(sizes))
    sizes.sort()
    for i in range(len(sizes)):
        sizes[i] = str(sizes[i])
    # print(sizes)
    return sizes


#  Функция принимает массив и возвращает среднеарифметическое
def average(arr):
    sum = 0
    for i in range(len(arr)):
        sum += arr[i]
    return sum/len(arr)


#  Функция принимает массив и возвращает его медианное значение
def find_median(arr):
    arr.sort()
    # print(arr)
    if len(arr) == 1:
        return arr[0]
    if len(arr) % 2 == 0:
        return arr[len(arr)//2]
    return (int(arr[int(len(arr)/2) - 1]) + int(arr[int(len(arr)/2)])) / 2


#  Находит нижний квартиль
def finde_lower_quartile(arr):
    a = len(arr)
    #  граница 25%
    a //= 4
    return arr[a]


#  Находит верхний квартиль
def find_upper_quartile(arr):
    a = len(arr)
    #  Граница 75%
    a //= 4
    a *= 3
    return arr[a]


#  Функция удаляет подготовленные данные с прошлых эксперементов
def del_old(folder):
    shutil.rmtree(folder)
    os.mkdir(folder)


#  Записывает полученные данные в файл
def save_prep_data(stri, avg, med, mini, maxi, up_quart, low_quart):
    folder = './prep_data/'
    file = folder + stri
    with open(file, "w") as f:
        f.write(str(avg) + '\n')
        f.write(str(med) + '\n')
        f.write(str(mini) + '\n')
        f.write(str(maxi) + '\n')
        f.write(str(low_quart) + '\n')
        f.write(str(up_quart))
        file = "\r" + file



folder = './data/'
folder_out = './prep_data'

#  Удаляет предыдущие данные
del_old(folder_out)

programm = ['programm_1', 'programm_2']
option = ['O0', 'O1', 'O2', 'O3', 'Os']
for i in range(len(option)):
    option[i] = "_" + option[i]

size = find_sizes(folder)
for i in range(len(size)):
    size[i] = "_" + size[i]

ex = '.txt'
n = 0
print("Подготовка данных")
for prog in range(len(programm)):
    for opt in range(len(option)):
        for siz in range(len(size)):
            stri = programm[prog] + option[opt] + size[siz] + ex
            arr = read(folder + stri)
            avg = average(arr)
            med = find_median(arr)
            low_quart = finde_lower_quartile(arr)
            up_quart = find_upper_quartile(arr)
            mini = arr[0]
            maxi = arr[len(arr) - 1]
            save_prep_data(stri, avg, med, mini, maxi, up_quart, low_quart)
            n += 1
            progress = str(n) + ' / ' + str(len(programm) * len(option) * len(size)) + '\r'
            print(progress, end="")
print()