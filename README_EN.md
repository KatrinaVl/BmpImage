PROJECT OBJECTIVE

Implement a console application that allows you to apply various filters to images, similar to filters in popular graphic editors.

GENERAL INFORMATION

Input and output graphic files are presented in 24-bit BMP format without compression and without color table. 
The type of DIB header used is BITMAPINFOHEADER.

Command line arguments format: {path to input file} {path to output file} [-{filter name} [filter option 1] [filter option 2] ...] ...

Each color component is represented by an integer value between 0 and 255. Pixel colors are represented by triplets (R, G, B).

If the filter is specified by a matrix, this means that the value of each color is determined by the weighted sum of the values of that color in adjacent pixels according to the matrix. In this case, the target pixel corresponds to the central element of the matrix.

LIST OF IMPLEMENTED FILTERS

Crop (-crop width height)
Crop the image to the given height and width. The top left of the image is used. If the requested width or height exceeds the dimensions of the original image, the available portion of the image is returned.

grayscale (-gs)
Converts an image to grayscale using the formula:

R' = G' = B' = 0.299R + 0.587G + 0.114*B

Negative (-neg)
Converts an image to a negative using the formulas:

R' = 255 - R

G' = 255 - G

B' = 255 - B

sharpening (-sharp)
Sharpening. Achieved by using a matrix:

[[0, -1, 0],

[-1, 5, -1],

[0, -1, 0]]

Edge Detection (-edge threshold)
Boundary selection. The image is converted to grayscale and a matrix is applied:

[[0, -1, 0],

[-1, 4, -1],

[0, -1, 0]]

Pixels with a value that exceeds the real parameter treshold are painted white, the rest are black.

Shift (-shift)
Offsets all pixel rows, horizontally and vertically, in the current layer or selection, by a random distance and within certain limits (horizontally, the offset limit is 0.045 * width; vertically, the offset limit is 0.01 * height).
