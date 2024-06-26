# BmpImage

ЗАДАЧА ПРОЕКТА

Реализовать консольное приложение, позволяющее применять к изображениям различные фильтры, аналогичные фильтрам в популярных графических редакторах.

ОБЩАЯ ИНФОРМАЦИЯ

Входные и выходные графические файлы представлены в формате 24-битного BMP без сжатия и без таблицы цветов.
Тип используемого DIB header - BITMAPINFOHEADER.

Формат аргументов командной строки:
{путь к входному файлу} {путь к выходному файлу} [-{название фильтра} [параметр фильтра 1] [параметр фильтра 2] ...] ...

Каждая компонента цвета представлена целочисленным значением от 0 до 255. Цвета пикселей представлены тройками (R, G, B).

Если фильтр задан матрицей, это означает, что значение каждого из цветов определяется взвешенной суммой значений этого цвета в соседних пикселях в соответствии с матрицей. При этом целевому пикселю соответствует центральный элемент матрицы.

СПИСОК РЕАЛИЗОВАННЫХ ФИЛЬТРОВ

1) Crop (-crop width height)

Обрезает изобраажение до заданных высоты и ширины. Используется верхняя левая часть изображения. 
Если запрошенные ширина или высота превышают размеры исходного изображения, выдается доступная часть изображения.


2) Grayscale (-gs)

Преобразует изображение в оттенки серого по формуле:

R' = G' = B' = 0.299*R + 0.587*G + 0.114*B


3) Negative (-neg)

Преобразует изоражение в негатив по формулам:

R' = 255 - R

G' = 255 - G

B' = 255 - B


4) Sharpening (-sharp)

Повышение резкости. Достигается применением матрицы:

[[0, -1, 0], 

 [-1, 5, -1], 
 
 [0, -1, 0]]
 
 
5) Edge Detection (-edge treshold)
 
Выделение границ. Изображение переводится в оттенки серого и применяется матрица:

[[0, -1, 0], 

 [-1, 4, -1], 
 
 [0, -1, 0]]
 
Пиксели со значением, превысившим вещественный параметр treshold, окрашиваются в белый, остальные в черный.

6) Shift (-shift)

Смещает все пиксельные ряды, горизонтально и вертикально, в текущем слое или выделении, на случайное расстояние и в определенных пределах (по горизонтали предел смещения - 0.045 * width; по вертикали предел смещения - 0.01 * height).
 


