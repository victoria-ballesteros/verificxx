//
// Created by victoria on 11/4/25.
//

#ifndef VERIFICXX_REGEX_H
#define VERIFICXX_REGEX_H
#include <boost/regex.hpp>

namespace Regexes {
    const boost::regex emailAddressRegex(
        R"((([a-z0-9!#$%&'*+/=?^_`{|}~-]+(\.[a-z0-9!#$%&'*+/=?^_`{|}~-]+)*)|("(\\.|[^"])*"))@([a-z0-9]([a-z0-9-]*[a-z0-9])?(\.[a-z0-9]([a-z0-9-]*[a-z0-9])?)*))",
        boost::regex_constants::icase
    );
}

#endif //VERIFICXX_REGEX_H
