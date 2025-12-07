#ifndef VERIFICXX_UTILS_H
#define VERIFICXX_UTILS_H

#include <regex>
#include <string>
#include <vector>

class Utils {
public:
    static std::string formatMessage(const std::string& templateMsg, const std::vector<std::string>& args) {
        std::string result = templateMsg;
        size_t pos = 0;
        for (const auto& arg : args) {
            pos = result.find("{}", pos);
            if (pos == std::string::npos)
                break;
            result.replace(pos, 2, arg);
            pos += arg.size();
        }
        return result;
    }

    static std::string errorCharactersFormatter(const std::vector<char>& invalid_characters) {
        std::string invalid_characters_string;
        invalid_characters_string.reserve(invalid_characters.size() * 4);

        for (const char c : invalid_characters) {
            invalid_characters_string += "'";
            invalid_characters_string += c;
            invalid_characters_string += "' ";
        }

        return invalid_characters_string;
    }
};

#endif // VERIFICXX_UTILS_H
