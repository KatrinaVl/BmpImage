#include "parser_com_str.h"
#include "constants.h"
#include <iostream>
#include <string>

bool CorrectNames(parse_arguments::FilterParameters& filter) {
    for (auto i : constants::NAME_OF_BASIC_FILTERS) {
        if (filter.name == i.first) {
            return true;
        }
    }
    return false;
}

bool CorrectNumParameters(parse_arguments::FilterParameters& filter) {
    for (auto i : constants::NAME_OF_BASIC_FILTERS) {
        if (filter.name == i.first && filter.parameters.size() != i.second) {
            return false;
        }
    }
    return true;
}

void parse_arguments::ParserComStr::Parse(int argc, char** argv) {
    if (argc == 0) {
        this->is_input_par = false;
    } else if (argc < constants::NUM_OTHER_PARAMETERS) {
        throw std::invalid_argument("Not enough parameters");  ////Unit Test
    } else {
        this->path_to_input_file_ = argv[constants::NUM_OF_INPUT_FILE];
        this->path_to_output_file_ = argv[constants::NUM_OF_OUTPUT_FILE];
        for (int i = constants::NUM_OTHER_PARAMETERS; i < argc; ++i) {
            if (argv[i][0] == '-') {
                FilterParameters filter;
                filter.name = argv[i];
                filters_.emplace_back(filter);
            } else {
                filters_[filters_.size() - 1].parameters.emplace_back(argv[i]);
            }
        }
        for (auto i : filters_) {
            if (!CorrectNames(i)) {
                throw std::invalid_argument("Wrong filter name " + static_cast<std::string>(i.name));  ////Unit Test
            }
            if (!CorrectNumParameters(i)) {
                throw std::invalid_argument("Incorrectly entered parameters for the filter " +
                                            static_cast<std::string>(i.name));  ////Unit Test
            }
        }
    }
}

std::string_view parse_arguments::ParserComStr::GetInputPath() const {
    return this->path_to_input_file_;
}

std::string_view parse_arguments::ParserComStr::GetOutputPath() const {
    return this->path_to_output_file_;
}

std::vector<parse_arguments::FilterParameters> parse_arguments::ParserComStr::GetFilters() const {
    return this->filters_;
}
