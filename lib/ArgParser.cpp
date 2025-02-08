#include "ArgParser.h"
#include <stdexcept>
#include <sstream>
#include <algorithm>
#include <cstring>

namespace ArgumentParser {

// Constructor
ArgParser::ArgParser(const std::string& program_name)
    : program_name_(program_name) {}


ArgParser& ArgParser::AddIntArgument(const std::string& name, const std::string& description) {
    arguments_[name] = {
        Argument::Int,
        description,
        false,          // is_positional
        false,          // is_multi_value
        1,              // min_values
        nullptr,        // int_values
        nullptr,        // string_values
        nullptr,        // store_int_value
        nullptr,        // store_string_value
        nullptr,        // flag_value
        "",             // default_string_value
        0,              // default_int_value
        false           // default_flag_value
    };
    last_added_argument_ = name;
    return *this;
}

// Add integer argument with short flag
ArgParser& ArgParser::AddIntArgument(char short_flag, const std::string& long_flag, const std::string& description) {
    short_to_long_flags_[short_flag] = long_flag;
    arguments_[long_flag] = {
        Argument::Int,
        description,
        false,          // is_positional
        false,          // is_multi_value
        1,              // min_values
        nullptr,        // int_values
        nullptr,        // string_values
        nullptr,        // store_int_value
        nullptr,        // store_string_value
        nullptr,        // flag_value
        "",             // default_string_value
        0,              // default_int_value
        false           // default_flag_value
    };
    last_added_argument_ = long_flag;
    return *this;
}

// Add flag with short flag
ArgParser& ArgParser::AddFlag(char short_flag, const std::string& long_flag, const std::string& description) {
    short_to_long_flags_[short_flag] = long_flag;
    arguments_[long_flag] = {
        Argument::Flag,
        description,
        false,          // is_positional
        false,          // is_multi_value
        1,              // min_values
        nullptr,        // int_values
        nullptr,        // string_values
        nullptr,        // store_int_value
        nullptr,        // store_string_value
        nullptr,        // flag_value
        "",             // default_string_value
        0,              // default_int_value
        false           // default_flag_value
    };
    last_added_argument_ = long_flag;
    return *this;
}



// AddFlag
ArgParser& ArgParser::AddFlag(const std::string& name, const std::string& description) {
    arguments_[name] = {
        Argument::Flag,
        description,
        false,
        false,
        1,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        "",
        0,
        false
    };
    last_added_argument_ = name;
    return *this;
}

// AddHelp
ArgParser& ArgParser::AddHelp(char short_flag, const std::string& long_flag, const std::string& description) {
    help_short_flag_ = short_flag;
    help_long_flag_ = long_flag;
    help_description_ = description;
    short_to_long_flags_[short_flag] = long_flag;
    return *this;
}

// AddStringArgument (long flag)
ArgParser& ArgParser::AddStringArgument(const std::string& name, const std::string& description) {
    arguments_[name] = {
        Argument::String,
        description,
        false,          // is_positional
        false,          // is_multi_value
        1,              // min_values
        nullptr,        // int_values
        new std::vector<std::string>(),  // Initialize string_values
        nullptr,        // store_int_value
        nullptr,        // store_string_value
        nullptr,        // flag_value
        "",            // default_string_value
        0,             // default_int_value
        false          // default_flag_value
    };
    last_added_argument_ = name;
    return *this;
}




// AddStringArgument (short and long flag)
ArgParser& ArgParser::AddStringArgument(char short_flag, const std::string& long_flag, const std::string& description) {
    short_to_long_flags_[short_flag] = long_flag;
    return AddStringArgument(long_flag, description);
}

// MultiValue
ArgParser& ArgParser::MultiValue(int min_count) {
    if (!last_added_argument_) {
        throw std::logic_error("MultiValue must be called after adding an argument.");
    }
    auto& argument = arguments_.at(*last_added_argument_);
    argument.is_multi_value = true;
    argument.min_values = min_count;
    return *this;
}

// Positional
ArgParser& ArgParser::Positional() {
    if (!last_added_argument_) {
        throw std::logic_error("Positional must be called after adding an argument.");
    }
    auto& argument = arguments_.at(*last_added_argument_);
    argument.is_positional = true;
    return *this;
}

// StoreValues (for integers)
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

// StoreValue (for bool flags)
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

// StoreValue (for strings)
ArgParser& ArgParser::StoreValue(std::string& value) {
    if (!last_added_argument_) {
        throw std::logic_error("StoreValue must be called after adding an argument.");
    }
    auto& argument = arguments_.at(*last_added_argument_);
    if (argument.type != Argument::String) {
        throw std::logic_error("StoreValue can only be used with string arguments.");
    }
    argument.store_string_value = &value;
    return *this;
}

// Default value
// ArgParser& ArgParser::Default(const std::string& default_value) {
//     if (!last_added_argument_) {
//         throw std::logic_error("Default must be called after adding an argument.");
//     }
//     auto& argument = arguments_.at(*last_added_argument_);
//     if (argument.type == Argument::String) {
//         argument.default_string_value = default_value;
//     } else if (argument.type == Argument::Int) {
//         argument.default_int_value = std::stoi(default_value);
//     } else if (argument.type == Argument::Flag) {
//         argument.default_flag_value = (default_value == "true");
//     }
//     return *this;
// }

// Existing string version
ArgParser& ArgParser::Default(const std::string& default_value) {
    if (!last_added_argument_) {
        throw std::logic_error("Default must be called after adding an argument.");
    }
    auto& argument = arguments_.at(*last_added_argument_);
    if (argument.type == Argument::String) {
        argument.default_string_value = default_value;
    } else if (argument.type == Argument::Int) {
        argument.default_int_value = std::stoi(default_value);
    } else if (argument.type == Argument::Flag) {
        argument.default_flag_value = (default_value == "true");
    }
    return *this;
}

// New boolean version
ArgParser& ArgParser::Default(bool default_value) {
    if (!last_added_argument_) {
        throw std::logic_error("Default must be called after adding an argument.");
    }
    auto& argument = arguments_.at(*last_added_argument_);
    if (argument.type != Argument::Flag) {
        throw std::logic_error("Boolean default value can only be used with flags.");
    }
    argument.default_flag_value = default_value;
    return *this;
}

// New integer version
ArgParser& ArgParser::Default(int default_value) {
    if (!last_added_argument_) {
        throw std::logic_error("Default must be called after adding an argument.");
    }
    auto& argument = arguments_.at(*last_added_argument_);
    if (argument.type != Argument::Int) {
        throw std::logic_error("Integer default value can only be used with integer arguments.");
    }
    argument.default_int_value = default_value;
    return *this;
}

// ProcessArgumentValue
// bool ArgParser::ProcessArgumentValue(Argument& argument, const std::string& value_str) {
//     try {
//         if (argument.type == Argument::Int) {
//             int value = std::stoi(value_str);
//             if (argument.int_values) {
//                 argument.int_values->push_back(value);
//             }
//             if (argument.store_int_value) {
//                 *(argument.store_int_value) = value;
//             }
//         } else if (argument.type == Argument::String) {
//             if (argument.string_values) {
//                 argument.string_values->push_back(value_str);
//             }
//             if (argument.store_string_value) {
//                 *(argument.store_string_value) = value_str;
//             }
//         } else {
//             // Do nothing for flags here
//         }
//         return true;
//     } catch (const std::exception& e) {
//         return false; // Failed to process argument value
//     }
// }

bool ArgParser::ProcessArgumentValue(Argument& argument, const std::string& value_str) {
    try {
        if (argument.type == Argument::Int) {
            int value = std::stoi(value_str);
            if (argument.int_values) {
                argument.int_values->push_back(value);
            }
            if (argument.store_int_value) {
                *(argument.store_int_value) = value;
            }
            return true;
        } else if (argument.type == Argument::String) {
            if (argument.store_string_value) {
                *(argument.store_string_value) = value_str;
            }
            if (argument.string_values) {
                argument.string_values->push_back(value_str);
            }
            return true;
        }
        return true;
    } catch (const std::exception& e) {
        return false;
    }
}


bool ArgParser::Parse(int argc, char** argv) {
    std::vector<std::string> args(argv + 1, argv + argc);
    
    // Process default values first
    for (auto& [key, argument] : arguments_) {
        if (argument.type == Argument::String && argument.store_string_value) {
            *(argument.store_string_value) = argument.default_string_value;
        } else if (argument.type == Argument::Flag && argument.flag_value) {
            *(argument.flag_value) = argument.default_flag_value;
        }
    }

    // Handle positional arguments separately
    std::vector<std::string> positional_values;

    for (size_t i = 0; i < args.size(); ++i) {
        const auto& arg = args[i];

        // Check for help flag
        if (arg == std::string("-") + help_short_flag_ || arg == "--" + help_long_flag_) {
            help_requested_ = true;
            return true;
        }

        if (arg.rfind("--", 0) == 0) {
            // Long flag or argument
            auto equal_pos = arg.find('=');
            std::string key = arg.substr(2, equal_pos - 2);
            
            auto it = arguments_.find(key);
            if (it == arguments_.end()) {
                return false; // Unknown argument
            }
            
            auto& argument = it->second;
            if (argument.type == Argument::Flag) {
                if (argument.flag_value) {
                    *(argument.flag_value) = true;
                }
            } else {
                std::string value_str;
                if (equal_pos != std::string::npos) {
                    value_str = arg.substr(equal_pos + 1);
                } else if (i + 1 < args.size()) {
                    value_str = args[++i];
                } else {
                    return false;
                }
                if (!ProcessArgumentValue(argument, value_str)) {
                    return false;
                }
            }
        } else if (arg[0] == '-' && arg.length() > 1) {
            // Short flags or arguments
            std::string flag_str = arg.substr(1);
            size_t value_pos = flag_str.find('=');
            
            if (value_pos != std::string::npos) {
                // Format: -p=value
                char short_flag = flag_str[0];
                auto it = short_to_long_flags_.find(short_flag);
                if (it == short_to_long_flags_.end()) return false;
                
                auto& argument = arguments_[it->second];
                std::string value = flag_str.substr(value_pos + 1);
                if (!ProcessArgumentValue(argument, value)) return false;
            } else {
                // Format: -p value or multiple flags -abc
                for (size_t j = 0; j < flag_str.length(); ++j) {
                    char short_flag = flag_str[j];
                    auto it = short_to_long_flags_.find(short_flag);
                    if (it == short_to_long_flags_.end()) return false;
                    
                    auto& argument = arguments_[it->second];
                    if (argument.type == Argument::Flag) {
                        if (argument.flag_value) {
                            *(argument.flag_value) = true;
                        }
                    } else {
                        if (j < flag_str.length() - 1) {
                            // Value is attached to flag
                            std::string value = flag_str.substr(j + 1);
                            if (!ProcessArgumentValue(argument, value)) return false;
                            break;
                        } else if (i + 1 < args.size()) {
                            // Value is next argument
                            if (!ProcessArgumentValue(argument, args[++i])) return false;
                        } else {
                            return false;
                        }
                    }
                }
            }
        } else {
            positional_values.push_back(arg);
        }
    }

    // Process positional arguments
    size_t pos_idx = 0;
    for (auto& [key, argument] : arguments_) {
        if (argument.is_positional) {
            while (pos_idx < positional_values.size()) {
                if (!ProcessArgumentValue(argument, positional_values[pos_idx++])) {
                    return false;
                }
            }
            break;
        }
    }

    // Verify required arguments
    for (const auto& [key, argument] : arguments_) {
        if (!argument.is_multi_value) {
            if (argument.type == Argument::String && 
                argument.default_string_value.empty() && 
                (!argument.store_string_value || argument.store_string_value->empty())) {
                return false;
            }
        } else {
            if (argument.int_values && argument.int_values->size() < static_cast<size_t>(argument.min_values)) {
                return false;
            }
        }
    }

    return true;
}

// Parse (std::vector<std::string>)
bool ArgParser::Parse(const std::vector<std::string>& args) {
    std::vector<const char*> argv;
    argv.reserve(args.size());
    for (const auto& arg : args) {
        argv.push_back(arg.c_str());
    }
    return Parse(static_cast<int>(argv.size()), const_cast<char**>(argv.data()));
}

// Help
bool ArgParser::Help() const {
    return help_requested_;
}

// HelpDescription
std::string ArgParser::HelpDescription() const {
    std::ostringstream oss;
    oss << program_name_ << "\n";
    oss << help_description_ << "\n\n";
    for (const auto& [key, argument] : arguments_) {
        std::string line;
        // Handle short and long flags
        for (const auto& [short_flag, long_flag] : short_to_long_flags_) {
            if (long_flag == key) {
                line += "-";
                line += short_flag;
                line += ", ";
                break;
            }
        }
        line += "--" + key;
        if (argument.type == Argument::Int) {
            line += "=<int>";
        } else if (argument.type == Argument::String) {
            line += "=<string>";
        }
        if (!argument.description.empty()) {
            line += ",  " + argument.description;
        }
        if (argument.is_multi_value) {
            line += " [repeated";
            if (argument.min_values > 1) {
                line += ", min args = " + std::to_string(argument.min_values);
            }
            line += "]";
        }
        if (argument.type == Argument::Flag && argument.default_flag_value) {
            line += " [default = true]";
        }
        oss << line << "\n";
    }
    oss << "\n";
    oss << "-" << help_short_flag_ << ", --" << help_long_flag_ << "  " << help_description_ << "\n";
    return oss.str();
}

// GetStringValue
// std::string ArgParser::GetStringValue(const std::string& name) const {
//     auto it = arguments_.find(name);
//     if (it != arguments_.end()) {
//         const auto& argument = it->second;
//         if (argument.type == Argument::String) {
//             if (argument.store_string_value) {
//                 return *(argument.store_string_value);
//             } else if (argument.string_values && !argument.string_values->empty()) {
//                 return argument.string_values->front();
//             } else {
//                 return argument.default_string_value;
//             }
//         }
//     }
//     throw std::logic_error("String argument not found: " + name);
// }

// std::string ArgParser::GetStringValue(const std::string& name) const {
//     auto it = arguments_.find(name);
//     if (it != arguments_.end()) {
//         const auto& argument = it->second;
//         if (argument.type == Argument::String) {
//             if (argument.store_string_value && !argument.store_string_value->empty()) {
//                 return *argument.store_string_value;
//             } else if (argument.string_values && !argument.string_values->empty()) {
//                 return argument.string_values->front();
//             }
//             return argument.default_string_value;
//         }
//     }
//     throw std::logic_error("String argument not found: " + name);
// }

std::string ArgParser::GetStringValue(const std::string& name) const {
    auto it = arguments_.find(name);
    if (it == arguments_.end() || it->second.type != Argument::String) {
        throw std::runtime_error("String argument not found: " + name);
    }
    
    const auto& argument = it->second;
    if (argument.store_string_value) {
        return *(argument.store_string_value);
    }
    return argument.default_string_value;
}





// GetIntValue
// int ArgParser::GetIntValue(const std::string& name, size_t index) const {
//     auto it = arguments_.find(name);
//     if (it != arguments_.end()) {
//         const auto& argument = it->second;
//         if (argument.type == Argument::Int) {
//             if (argument.int_values && index < argument.int_values->size()) {
//                 return (*argument.int_values)[index];
//             } else if (argument.store_int_value) {
//                 return *(argument.store_int_value);
//             } else {
//                 return argument.default_int_value;
//             }
//         }
//     }
//     throw std::logic_error("Integer argument not found: " + name);
// }


int ArgParser::GetIntValue(const std::string& name, size_t index) const {
    auto it = arguments_.find(name);
    if (it == arguments_.end() || it->second.type != Argument::Int) {
        throw std::runtime_error("Integer argument not found: " + name);
    }
    
    const auto& argument = it->second;
    if (argument.int_values && index < argument.int_values->size()) {
        return (*argument.int_values)[index];
    }
    return argument.default_int_value;
}



// Function to retrieve a flag value from the parsed arguments
bool ArgParser::GetFlag(const std::string& name) const {
    auto it = arguments_.find(name);
    if (it == arguments_.end() || it->second.type != Argument::Flag) {
        throw std::runtime_error("Flag argument not found: " + name);
    }
    return it->second.flag_value ? *(it->second.flag_value) : it->second.default_flag_value;
}




} // namespace ArgumentParser
