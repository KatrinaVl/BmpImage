#pragma once

#include "image.h"
#include "parser_com_str.h"

namespace filter_control {

class FilterControl {
public:
    explicit FilterControl(parse_arguments::ParserComStr& parser);
    image::Image& FixedImage(image::Image& image) const;

private:
    parse_arguments::ParserComStr parser_;
    bool IncorrectParametersCrop(std::vector<std::string_view>& parameters) const;
    bool IncorrectParametersEdge(std::vector<std::string_view>& parameters) const;
};

}  // namespace filter_control
