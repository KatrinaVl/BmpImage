#include "filters.h"
#include "filter_control.h"
#include "parser_com_str.h"
#include "read_file.h"
#include "write_file.h"
#include <iostream>

int main(int argc, char* argv[]) {

    parse_arguments::ParserComStr parser;
    parser.Parse(argc, argv);

    if (parser.is_input_par) {
        reading_file::ReadFile info_image(parser.GetInputPath());
        image::Image my_image = info_image.GetImg();
        try {
            filter_control::FilterControl change_image(parser);
            my_image = change_image.FixedImage(my_image);
        } catch (std::exception& e) {
            std::cout << e.what() << std::endl;
        }

        writing_file::WriteFile give_image(parser.GetOutputPath());
        give_image.GiveImg(my_image);
    } else {
        std::cout << "Image Processor\n"
                     "A simple image manipulation utility\n"
                     "\n"
                     "Usage:\n"
                     "  build/image_processor input_file output_file [FILERS [ARGS]]\n"
                     "\n"
                     "Filters:\n"
                     "  -gs GrayScale filter\n"
                     "  -neg Negative filter\n"
                     "  -sharp Sharpening\n"
                     "  -edge threshold Edge Detection filter\n"
                     "  -crop width height Crop Image filter\n"
                     "  -shift Shift pixels filter\n"
                  << std::endl;
    }
    return 0;
}
