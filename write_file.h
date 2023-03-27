#pragma once

#include "constants.h"
#include "image.h"
#include "parser_com_str.h"

namespace writing_file {

class WriteFile {
public:
    explicit WriteFile(const std::string_view& path);
    void GiveImg(image::Image& image);

private:
    std::string path_;
    const int PaddingSize(int32_t width) const;
};

}  // namespace writing_file
