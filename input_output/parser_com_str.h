#pragma once

#include <string>
#include <string_view>
#include <vector>

namespace parse_arguments {

struct FilterParameters {
    std::string_view name;
    std::vector<std::string_view> parameters;
};

class ParserComStr {
public:
    ParserComStr() = default;
    void Parse(int argc, char** argv);
    std::string_view GetInputPath() const;
    std::string_view GetOutputPath() const;
    std::vector<FilterParameters> GetFilters() const;
    bool is_input_par = true;

private:
    std::string_view path_to_input_file_;
    std::string_view path_to_output_file_;
    std::vector<FilterParameters> filters_;
};

}  // namespace parse_arguments
