#include "write_file.h"
#include "color.h"
#include <cerrno>
#include <fstream>
#include <string>

writing_file::WriteFile::WriteFile(const std::string_view& path) {
    path_ = path;
}

#pragma pack(push, 1)
struct BmpInfoHeader {
    uint32_t size_of_this_header;
    int32_t width;
    int32_t height;
    uint16_t number_of_color_planes;
    uint16_t color_depth;
    uint32_t compression_method;
    uint32_t raw_bitmap_data_size;
    int32_t horizontal_resolution;
    int32_t vertical_resolution;
    uint32_t color_table_entries;
    uint32_t important_colors;
};

struct BmpHeader {
    uint16_t bitmap_signature_bytes;
    uint32_t size_of_bitmap_file;
    uint16_t reserved_bytes;
    uint16_t reversed_bytes_second;
    uint32_t pixel_data_offset;
};
#pragma pack(pop)

const int writing_file::WriteFile::PaddingSize(int32_t width) const {
    return (constants::PADDING - (width * constants::CNT_COLOR_PIX) % constants::PADDING) % constants::PADDING;
}

void writing_file::WriteFile::GiveImg(image::Image& image) {
    BmpHeader bmp_header;
    bmp_header.bitmap_signature_bytes = constants::FORMAT_FOR_WRITE;
    bmp_header.reserved_bytes = 0;
    bmp_header.reversed_bytes_second = 0;
    bmp_header.pixel_data_offset = constants::INFO_HEADER_SIZE + constants::FILE_HEADER_SIZE;

    BmpInfoHeader bmp_info_header;
    bmp_info_header.size_of_this_header = constants::INFO_HEADER_SIZE;
    bmp_info_header.number_of_color_planes = 1;
    bmp_info_header.color_depth = constants::CNT_BIT_IN_PIX;
    bmp_info_header.compression_method = 0;
    bmp_info_header.horizontal_resolution = 0;
    bmp_info_header.vertical_resolution = 0;
    bmp_info_header.color_table_entries = 0;
    bmp_info_header.important_colors = 0;
    bmp_info_header.width = image.GetWidth();
    bmp_info_header.height = image.GetHeight();
    bmp_info_header.raw_bitmap_data_size =
        ((constants::CNT_BIT_IN_PIX * image.GetWidth() + constants::ALIGMENT_31) / constants::ALIGMENT_32) * 4 *
        image.GetHeight();
    bmp_header.size_of_bitmap_file =
        constants::INFO_HEADER_SIZE + constants::FILE_HEADER_SIZE + bmp_info_header.raw_bitmap_data_size;

    std::ofstream file(path_, std::ios::out | std::ios::binary);
    if (!file.is_open()) {
        throw std::invalid_argument("Can't open file " + path_);
    }
    if (errno == EACCES) {
        throw std::invalid_argument("No permission to open " + path_);
    }
    file.write(reinterpret_cast<char*>(&bmp_header), constants::FILE_HEADER_SIZE);
    try {
        file.write(reinterpret_cast<char*>(&bmp_info_header), constants::INFO_HEADER_SIZE);

        for (int32_t i = 0; i < bmp_info_header.height; ++i) {
            for (int32_t j = 0; j < bmp_info_header.width; ++j) {
                unsigned char pixel[constants::CNT_COLOR_PIX];
                color::Color color = image.GetColor(bmp_info_header.height - i - 1, j);
                pixel[0] = static_cast<unsigned char>(color.blue);
                pixel[1] = static_cast<unsigned char>(color.green);
                pixel[2] = static_cast<unsigned char>(color.red);
                file.write(reinterpret_cast<char*>(pixel), constants::CNT_COLOR_PIX);
            }
            for (int32_t k = 0; k < PaddingSize(image.GetWidth()); ++k) {
                file.write("\0", sizeof(uint8_t));
            }
        }
        file.close();
    } catch (std::exception& e) {
        throw std::invalid_argument("Error during writing file " + path_ + ": " + static_cast<std::string>(e.what()));
    }
}
