#include <cctype>
#include <cstddef>
#include <iostream>
#include <stdexcept>

namespace zakharov {

constexpr std::size_t kInitialCap = 16;

std::size_t str_len(const char* s) {
    std::size_t n = 0;
    while (s[n] != '\0') ++n;
    return n;
}

char* upp_low(const char* src, char* dst) {
    std::size_t i = 0;
    for (; src[i] != '\0'; ++i) {
        unsigned char c = static_cast<unsigned char>(src[i]);
        dst[i] = std::isupper(c) ? static_cast<char>(std::tolower(c)) : src[i];
    }
    dst[i] = '\0';
    return dst;
}

char* uni_two(const char* a, const char* b, char* dst) {
    std::size_t i = 0;
    std::size_t k = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        dst[k++] = a[i];
        dst[k++] = b[i];
        ++i;
    }
    for (std::size_t j = i; a[j] != '\0'; ++j) dst[k++] = a[j];
    for (std::size_t j = i; b[j] != '\0'; ++j) dst[k++] = b[j];
    dst[k] = '\0';
    return dst;
}

char* read_line(std::istream& in) {
    std::size_t cap = kInitialCap;
    std::size_t len = 0;
    char* buf = new char[cap];
    char c = 0;
    while (in.get(c) && c != '\n') {
        if (len + 1 == cap) {  // место под '\0'
            char* bigger = nullptr;
            try {
                bigger = new char[cap * 2];
            } catch (...) {
                delete[] buf;
                throw;
            }
            for (std::size_t i = 0; i < len; ++i) bigger[i] = buf[i];
            delete[] buf;
            buf = bigger;
            cap *= 2;
        }
        buf[len++] = c;
    }
    buf[len] = '\0';
    return buf;
}

int process(std::istream& in, std::ostream& out, std::ostream& err) {
    const char second[] = "def_";
    char* src = nullptr;
    char* res_low = nullptr;
    char* res_uni = nullptr;
    try {
        src = read_line(in);
        res_low = new char[str_len(src) + 1];
        res_uni = new char[str_len(src) + str_len(second) + 1];
    } catch (const std::exception&) {
        err << "memory allocation error\n";
        delete[] src;
        delete[] res_low;
        delete[] res_uni;
        return 1;
    }

    out << upp_low(src, res_low) << '\n';
    out << uni_two(src, second, res_uni) << '\n';

    delete[] src;
    delete[] res_low;
    delete[] res_uni;
    return 0;
}

}

int main() {
    return zakharov::process(std::cin, std::cout, std::cerr);
}
