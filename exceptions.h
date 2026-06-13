
#ifndef PROJ2_EXCEPTIONS_H
#define PROJ2_EXCEPTIONS_H
#include <string>

class InvalidFileContentException {
private:
    std::string m_error;
public:
    InvalidFileContentException(std::string error) {
        m_error = error;
    }

    std::string_view GetError() const {
        return m_error;
    }
};

#endif //PROJ2_EXCEPTIONS_H