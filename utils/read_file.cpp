#include "read_file.h"
#include "color.h"
#include "constants.h"
#include <cerrno>
#include <fstream>
#include <string>

reading_file::ReadFile::ReadFile(const std::string_view& path) {
    path_ = path;
}
const int reading_file::ReadFile::PaddingSize(int32_t width) const {
    return (constants::PADDING - (width * constants::CNT_COLOR_PIX) % constants::PADDING) % constants::PADDING;
}

int32_t reading_file::ReadFile::ToNumb(unsigned char* buf) const {
    int32_t res = *buf;
    for (size_t i = 0; i < constants::CNT_OF_B_IN_OFFSET.size(); ++i) {
        res += *(buf + i + 1) << constants::CNT_OF_B_IN_OFFSET[i];
    }
    return res;
}

image::Image reading_file::ReadFile::GetImg() {
    unsigned char file_header[constants::FILE_HEADER_SIZE];
    unsigned char info_header[constants::INFO_HEADER_SIZE];

    std::ifstream file(path_, std::ios::in | std::ios::binary);
    if (!file.is_open()) {
        throw std::invalid_argument("Can't open file " + path_);  ////Unit Test
    }
    if (errno == EACCES) {
        throw std::invalid_argument("No permission to open " + path_);
    }
    file.read(reinterpret_cast<char*>(file_header), constants::FILE_HEADER_SIZE);
    if (file_header[0] != constants::BMP[0] || file_header[1] != constants::BMP[1]) {
        throw std::invalid_argument(path_ + " is not .bmp\n");  ////Unit Test
    }
    try {
        file.read(reinterpret_cast<char*>(info_header), constants::INFO_HEADER_SIZE);
        int32_t width = ToNumb(info_header + constants::WIDTH_OFFSET);
        int32_t height = ToNumb(info_header + constants::HEIGHT_OFFSET);
        image::Image image(height, width);
        std::vector<std::vector<color::Color>> img_data(height);
        std::vector<color::Color> curr_str(width);
        for (int32_t i = 0; i < height; ++i) {
            for (int32_t j = 0; j < width; ++j) {
                unsigned char pixel[3];
                file.read(reinterpret_cast<char*>(pixel), 3);
                curr_str[j].SetColor(static_cast<uint8_t>(pixel[0]), static_cast<uint8_t>(pixel[1]),
                                     static_cast<uint8_t>(pixel[2]));
            }
            img_data[height - i - 1] = curr_str;
            file.ignore(PaddingSize(width));
        }

        image.GetVecOfColors(img_data);

        file.close();
        return image;
    } catch (std::exception& e) {
        throw std::invalid_argument("Error during reading file " + path_ + ": " + static_cast<std::string>(e.what()));
    }
}
