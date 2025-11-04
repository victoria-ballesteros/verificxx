//
// Created by victoria on 11/3/25.
//

#include "../include/IVerify.h"

template<typename T>
class Verify : public IVerify {
private:
    std::vector<std::string> errors;
    T value{};
public:
    explicit Verify(const T& value) {
        this->value = value;
    }

    void execute() override {

    }

    [[nodiscard]] std::vector<std::string> getErrorMessages() const override {
        return errors;
    }
};