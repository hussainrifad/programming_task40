#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <functional>
#include <iostream>

namespace ArgumentParser {

class ArgParser {
public:
    explicit ArgParser(const std::string& program_name);

    ArgParser& AddIntArgument(const std::string& name);
    ArgParser& AddFlag(const std::string& name, const std::string& description);
    ArgParser& AddHelp(char short_flag, const std::string& long_flag, const std::string& description);

    ArgParser& MultiValue(int min_count);
    ArgParser& Positional();
    ArgParser& StoreValues(std::vector<int>& values);
    ArgParser& StoreValue(bool& value);

    bool Parse(int argc, char** argv);
    bool Help() const;
    std::string HelpDescription() const;

private:
    struct Argument {
        enum Type { Int, Flag } type;
        std::string description;
        bool is_positional = false;
        bool is_multi_value = false;
        int min_values = 1;
        std::vector<int>* int_values = nullptr;
        bool* flag_value = nullptr;
    };

    std::string program_name_;
    std::unordered_map<std::string, Argument> arguments_;
    std::optional<std::string> last_added_argument_; // Track the last added argument name
    char help_short_flag_;
    std::string help_long_flag_;
    std::string help_description_;
    bool help_requested_ = false;

    void PrintHelp() const;
};

} // namespace ArgumentParser
