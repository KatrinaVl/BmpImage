#pragma once

#include <string_view>
#include <vector>

namespace constants {

const int NUM_OF_INPUT_FILE = 1;
const int NUM_OF_OUTPUT_FILE = 2;
const int NUM_OTHER_PARAMETERS = 3;
const int FILE_HEADER_SIZE = 14;
const int INFO_HEADER_SIZE = 40;
const int DEFAULT_BITS_F_H = 4;
const int FOR_SIZE_BMP = 4;
const int CNT_BIT_IN_PIX = 24;
const std::vector<char> BMP = {'B', 'M'};
const int HEIGHT_OFFSET = 8;
const int WIDTH_OFFSET = 4;
const std::vector<int> CNT_OF_B_IN_OFFSET = {8, 16, 24};
const int PADDING = 4;
const int CNT_COLOR_PIX = 3;
const double GS_FOR_RED = 0.299;
const double GS_FOR_GREEN = 0.587;
const double GS_FOR_BLUE = 0.114;
const double PIX_OFFSET_RANGE_WID = 0.045;
const double PIX_OFFSET_RANGE_HEI = 0.01;
const int MAX_NUM_PIX = 255;
const uint16_t FORMAT_FOR_WRITE = 0x4D42;
const int FIVE = 5;
const int FOUR = 4;
const int ALIGMENT_31 = 31;
const int ALIGMENT_32 = 32;
const std::vector<std::pair<std::string_view, size_t>> NAME_OF_BASIC_FILTERS{
    {"-crop", 2}, {"-gs", 0}, {"-neg", 0}, {"-sharp", 0}, {"-edge", 1}, {"-blur", 1}, {"-shift", 0}};
const int P_T_NUM_ARGC = 6;
const int P_T_NUM_PAR = 5;
const int P_T_NUM_ARGC_FIVE = 5;

};  // namespace constants
