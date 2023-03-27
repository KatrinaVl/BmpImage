#pragma once

#include "constants.h"
#include "image.h"
#include "parser_com_str.h"
#include <string>

namespace reading_file {

class ReadFile {
public:
    explicit ReadFile(const std::string_view& path);
    image::Image GetImg();

private:
    std::string path_;
    int32_t ToNumb(unsigned char* buf) const;
    const int PaddingSize(int32_t width) const;
};

}  // namespace reading_file
