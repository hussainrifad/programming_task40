#include "ArgParser.h"
#include <sstream>
#include <stdexcept>
#include <algorithm>

namespace ArgumentParser {

ArgParser::ArgParser(const std::string& program_name) : program_name_(program_name) {}

ArgParser& ArgParser::AddIntArgument(const std::string& name) {
    arguments_[name] = {Argument::Int, "", false, false, 1, nullptr, nullptr};
    last_added_argument_ = name; // Track the last added argument
    return *this;
}

ArgParser& ArgParser::AddFlag(const std::string& name, const std::string& description) {
    arguments_[name] = {Argument::Flag, description, false, false, 1, nullptr, nullptr};
    last_added_argument_ = name; // Track the last added argument
    return *this;
}

ArgParser& ArgParser::AddHelp(char short_flag, const std::string& long_flag, const std::string& description) {
    help_short_flag_ = short_flag;
    help_long_flag_ = long_flag;
    help_description_ = description;
    return *this;
}

ArgParser& ArgParser::MultiValue(int min_count) {
    if (!last_added_argument_) {
        throw std::logic_error("MultiValue must be called after adding an argument.");
    }
    auto& argument = arguments_.at(*last_added_argument_);
    argument.is_multi_value = true;
    argument.min_values = min_count;
    return *this;
}

ArgParser& ArgParser::Positional() {
    if (!last_added_argument_) {
        throw std::logic_error("Positional must be called after adding an argument.");
    }
    auto& argument = arguments_.at(*last_added_argument_);
    argument.is_positional = true;
    return *this;
}

ArgParser& ArgParser::StoreValues(std::vector<int>& values) {
    if (!last_added_argument_) {
        throw std::logic_error("StoreValues must be called after adding an argument.");
    }
    auto& argument = arguments_.at(*last_added_argument_);
    if (argument.type != Argument::Int) {
        throw std::logic_error("StoreValues can only be used with integer arguments.");
    }
    argument.int_values = &values;
    return *this;
}

ArgParser& ArgParser::StoreValue(bool& value) {
    if (!last_added_argument_) {
        throw std::logic_error("StoreValue must be called after adding an argument.");
    }
    auto& argument = arguments_.at(*last_added_argument_);
    if (argument.type != Argument::Flag) {
        throw std::logic_error("StoreValue can only be used with flag arguments.");
    }
    argument.flag_value = &value;
    return *this;
}

bool ArgParser::Parse(int argc, char** argv) {
    std::vector<std::string> args(argv + 1, argv + argc);
    for (const auto& arg : args) {
        if (arg == std::string("-") + help_short_flag_ || arg == "--" + help_long_flag_) {
            help_requested_ = true;
            return true;
        }

        if (arg.starts_with("--")) {
            auto equal_pos = arg.find('=');
            std::string key = arg.substr(2, equal_pos - 2);
            if (arguments_.find(key) == arguments_.end()) {
                return false;
            }
            auto& argument = arguments_[key];
            if (argument.type == Argument::Flag) {
                if (argument.flag_value) {
                    *(argument.flag_value) = true;
                }
            } else if (argument.type == Argument::Int) {
                if (equal_pos == std::string::npos) return false;
                std::string value_str = arg.substr(equal_pos + 1);
                int value = std::stoi(value_str);
                if (argument.int_values) {
                    argument.int_values->push_back(value);
                }
            }
        } else {
            for (auto& [key, argument] : arguments_) {
                if (argument.is_positional && argument.int_values) {
                    argument.int_values->push_back(std::stoi(arg));
                }
            }
        }
    }

    for (const auto& [key, argument] : arguments_) {
        if (argument.is_multi_value && argument.int_values && argument.int_values->size() < argument.min_values) {
            return false;
        }
    }

    return true;
}

bool ArgParser::Help() const {
    return help_requested_;
}

std::string ArgParser::HelpDescription() const {
    std::ostringstream oss;
    oss << program_name_ << " usage:\n";
    for (const auto& [key, argument] : arguments_) {
        oss << "  --" << key;
        if (argument.type == Argument::Int) {
            oss << "=<int>";
        }
        if (!argument.description.empty()) {
            oss << "  - " << argument.description;
        }
        oss << "\n";
    }
    oss << "  -" << help_short_flag_ << ", --" << help_long_flag_ << "  - " << help_description_ << "\n";
    return oss.str();
}

} // namespace ArgumentParser
