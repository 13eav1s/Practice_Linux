import os
import shutil

import matplotlib.pyplot as plt


# Обычный кусочно-линейный график зависимости времени выполнения в любых единицах измерения времени от числа
# элементов массива для всех 10 вариантов программы.

#  Получение информации из переданной строки о том, что содержится в файле
def whats_in_file(file):
    sp_file = file.split("_")
    prog_num = sp_file[1]
    opt_lvl = sp_file[2]
    col_elems = sp_file[3]
    col_elems = col_elems.partition('.')[0]
    file = 'post_prep_data_' + prog_num + '_' + opt_lvl + '.txt'

    return prog_num, opt_lvl, col_elems, file


#  Плучение информации из файла
def params_from_file(folder_input, file):
    val = []
    with open(folder_input + file) as f:
        for line in f:
            val.append(float(line))
    return val


#  Функция подготавливает данные для дальнейшего построения графика
def linal_graph_data(files_input, folder_input, folder_out):
    print("____Таблица данных для кусочного графика____")
    print("col_elems\t time")
    files_input.sort()
    for file in files_input:
        avg = params_from_file(folder_input, file)[0]
        prog_num, opt_lvl, col_elems, file = whats_in_file(file)
        with open(folder_out + file, 'a') as f:
            f.write(str(col_elems) + ' ' + str(avg) + '\n')

    files_table = os.listdir(folder_out)
    files_table.sort()
    for file_tab in files_table:
        print("__tab data", file_tab, "__")
        with open(folder_out + file_tab) as f:
            for line in f:
                print(line, end="")


#  Сортировка массивов X и Y по X
def sort_2(arr1, arr2):
    for i in range(len(arr1)):
        for j in range(len(arr1) - 1):
            if arr1[j] > arr1[j + 1]:
                s = arr1[j]
                arr1[j] = arr1[j + 1]
                arr1[j + 1] = s
                s = arr2[j]
                arr2[j] = arr2[j + 1]
                arr2[j + 1] = s


#  Запись подготовленных данных в массивы по X и по Y для линейного графика
def linal_graph_to_mass(folder):
    x_array = []
    y_array = []
    files_input = os.listdir(folder)
    files_input.sort()
    for file in files_input:
        file = folder + file
        x_arg = []
        y_arg = []
        with open(file, "r") as f:
            for line in f:
                args = line.split(' ')
                x_arg.append(int(args[0]))
                y_arg.append(float(args[1]))
        sort_2(x_arg, y_arg)
        x_array.append(x_arg)
        y_array.append(y_arg)
    return x_array, y_array, files_input


#  Строит линейный график
def plot_linal_graph(x_array, y_array, labels_array):
    #  Удаление лишнего из лэйблов
    for i in range(len(labels_array)):
        labels_array[i] = labels_array[i].replace(".txt", "")
        labels_array[i] = labels_array[i].replace("post_prep_", "", 1)
        labels_array[i] = labels_array[i].replace("data", "prog")
    fig, ax = plt.subplots()
    #  Набор параметров для отображения графиков
    linestyle_array = ['-', '--', '-.', ':', (0, (3, 1, 1, 1, 1, 1))]
    markers = ['^', 's', 'X']
    #  Генерация 15 видов линий
    difference = []
    for j in range(len(markers)):
        for i in range(len(linestyle_array)):
            typ = [linestyle_array[i], markers[j]]
            difference.append(typ)
    #  Построение графиков
    for i in range(len(x_array)):
        ax.plot(x_array[i], y_array[i], label=labels_array[i], linestyle=difference[i][0], marker=difference[i][1])

    #  Добавляем подписи к осям:
    ax.set_xlabel('Кол-во элементов')
    ax.set_ylabel('Время (микросекунды)')

    #  Добавление легенды, масштабной сетки и вывод графиков на поле
    ax.legend()
    ax.grid()

    #  Сохранение графика
    fig.savefig('line_plot.svg')


#  Функция удаляет подготовленные данные с прошлых эксперементов
def del_old(folder):
    shutil.rmtree(folder)
    os.mkdir(folder)


#  Заданные папки
folder_in = "prep_data/"
folder_lingraph = "post_prep_lingraph_data/"
folder_data = 'data/'

#  Массив в котором хранятся имена файлов из папки folder_in
files = os.listdir(folder_in)

#  Линейный график

#  Удаление старых данных
del_old(folder_lingraph)

#  Подготовка данных для построения графика
linal_graph_data(files, folder_in, folder_lingraph)

#  Построение графика по подготовленным данным
x, y, labels = linal_graph_to_mass(folder_lingraph)
plot_linal_graph(x, y, labels)
plt.show()
