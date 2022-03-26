#include <exception>
#include <string>
class WrongArgumentsException : public std::exception {
public:
    WrongArgumentsException(std::string message) : message_(message) {
    }

    const char* what() const noexcept override {
        return message_.c_str();
    }

private:
    std::string message_;
};

class FileProblemException : public std::exception {
public:
    FileProblemException(std::string message) : message_(message) {
    }

    const char* what() const noexcept override {
        return message_.c_str();
    }

private:
    std::string message_;
};

class WrongFilterException : public std::exception {
public:
    WrongFilterException(std::string message) : message_(message) {
    }

    const char* what() const noexcept override {
        return message_.c_str();
    }

private:
    std::string message_;
};
