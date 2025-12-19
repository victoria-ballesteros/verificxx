//
// Created by victoria on 12/7/25.
//

#ifndef VERIFICXX_EXECUTIONERRORMESSAGES_H
#define VERIFICXX_EXECUTIONERRORMESSAGES_H
#include <string>

namespace ExecutionErrorMessages {
    inline std::string FILE_NOT_OPEN = "Could not open the specified file";
    inline std::string JSON_PARSING_ERROR = "Error parsing file '{}'";
    inline std::string JSON_INVALID_FORMAT = "File schema error: {}";
};

#endif //VERIFICXX_EXECUTIONERRORMESSAGES_H