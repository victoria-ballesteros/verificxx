//
// Created by victoria on 11/3/25.
//

#ifndef VERIFICXX_IVERIFY_H
#define VERIFICXX_IVERIFY_H
#include <string>
#include <vector>

class IVerify {
public:
    [[nodiscard]] virtual std::vector<std::string> getErrorMessages() const = 0;
    virtual void execute() = 0;
    virtual ~IVerify() = default;
};

#endif //VERIFICXX_IVERIFY_H