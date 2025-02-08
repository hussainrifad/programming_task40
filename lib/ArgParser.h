#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <functional>
#include <iostream>
#include <optional>
#include <map>

namespace ArgumentParser {
class ArgParser {
public:
    explicit ArgParser(const std::string& program_name);

    // Integer arguments
    ArgParser& AddIntArgument(const std::string& name, const std::string& description = "");
    ArgParser& AddIntArgument(char short_flag, const std::string& long_flag, const std::string& description = "");

    // Flag arguments
    ArgParser& AddFlag(const std::string& name, const std::string& description = "");
    ArgParser& AddFlag(char short_flag, const std::string& long_flag, const std::string& description = "");

    // Help
    ArgParser& AddHelp(char short_flag, const std::string& long_flag, const std::string& description);

    // String arguments
    ArgParser& AddStringArgument(const std::string& name, const std::string& description = "");
    ArgParser& AddStringArgument(char short_flag, const std::string& long_flag, const std::string& description = "");
    std::string GetStringValue(const std::string& name) const;

    // Modifiers
    ArgParser& MultiValue(int min_count = 1);
    ArgParser& Positional();
    ArgParser& StoreValues(std::vector<int>& values);
    ArgParser& StoreValue(bool& value);
    ArgParser& StoreValue(std::string& value);
    ArgParser& Default(const std::string& default_value);
    ArgParser& Default(bool default_value);
    ArgParser& Default(int default_value);
    
    // Parsing
    bool Parse(int argc, char** argv);
    bool Parse(const std::vector<std::string>& args);

    // Help and info
    bool Help() const;
    std::string HelpDescription() const;

    // Value getters
    int GetIntValue(const std::string& name, size_t index = 0) const;
    bool GetFlag(const std::string& name) const;

private:
    struct Argument {
        enum Type { Int, String, Flag } type;
        std::string description;
        bool is_positional = false;
        bool is_multi_value = false;
        int min_values = 1;
        std::vector<int>* int_values = nullptr;
        std::vector<std::string>* string_values = nullptr;
        int* store_int_value = nullptr;
        std::string* store_string_value = nullptr;
        bool* flag_value = nullptr;
        std::string default_string_value;
        int default_int_value = 0;
        bool default_flag_value = false;
    };

    std::string program_name_;
    std::unordered_map<std::string, Argument> arguments_;
    std::optional<std::string> last_added_argument_;
    char help_short_flag_;
    std::string help_long_flag_;
    std::string help_description_;
    bool help_requested_ = false;
    std::unordered_map<char, std::string> short_to_long_flags_;

    bool ProcessArgumentValue(Argument& argument, const std::string& value_str);
};
} // namespace ArgumentParser