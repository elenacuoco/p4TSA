#include <tsaSerialize.hpp>

namespace tsa {

    char* Tag(char *buffer, int n, const char* base, const char* rec) {
        snprintf(buffer, n, "%s.%s", base, rec);
        return buffer;
    }

    char* Tag(char *buffer, int n, const char* base, const char* rec, unsigned int i) {
        snprintf(buffer, n, "%s.%s.%d", base, rec, i);
        return buffer;
    }

    char* Tag(char *buffer, int n, const char* base, const char* rec, unsigned int i, unsigned int j) {
        snprintf(buffer, n, "%s.%s.%d.%d", base, rec, i, j);
        return buffer;
    }



};
