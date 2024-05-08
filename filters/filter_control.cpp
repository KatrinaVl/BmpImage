#include "filter_control.h"
#include "filters.h"
#include <fstream>

filter_control::FilterControl::FilterControl(parse_arguments::ParserComStr& parser) {
    parser_ = parser;
}

image::Image& filter_control::FilterControl::FixedImage(image::Image& image) const {
    if (parser_.GetFilters().empty()) {
        return image;
    }
    for (auto i : parser_.GetFilters()) {
        if (i.name == "-crop") {
            if (!IncorrectParametersCrop(i.parameters)) {
                throw std::invalid_argument("Double numbers in parameters Crop");  ////Unit Test
            }
            filters::Crop crop(i.parameters[0], i.parameters[1]);
            image = crop.App(image);
        } else if (i.name == "-gs") {
            filters::Grayscale gr_image;
            image = gr_image.App(image);
        } else if (i.name == "-neg") {
            filters::Negative ng_image;
            image = ng_image.App(image);
        } else if (i.name == "-sharp") {
            filters::Sharpening sh_image;
            image = sh_image.App(image);
        } else if (i.name == "-edge") {
            if (!IncorrectParametersEdge(i.parameters)) {
                throw std::invalid_argument("Integer number in Edge Detection");  ////Unit Test
            }
            filters::EdgeDetection ed_image(i.parameters[0]);
            image = ed_image.App(image);
        } else if (i.name == "-shift") {
            filters::Shift sh_fil_image;
            image = sh_fil_image.App(image);
        }
    }
    return image;
}

bool filter_control::FilterControl::IncorrectParametersCrop(std::vector<std::string_view>& parameters) const {
    for (auto i : parameters) {
        for (auto j : i) {
            if (j == '.') {
                return false;
            }
        }
    }
    return true;
}

bool filter_control::FilterControl::IncorrectParametersEdge(std::vector<std::string_view>& parameters) const {
    for (auto i : parameters) {
        size_t cnt = 0;
        for (auto j : i) {
            if (j == '.') {
                cnt += 1;
            }
        }
        if (cnt == 0) {
            return false;
        }
    }
    return true;
}
