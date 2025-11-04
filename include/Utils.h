#ifndef VERIFICXX_UTILS_H
#define VERIFICXX_UTILS_H

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
};

#endif // VERIFICXX_UTILS_H
