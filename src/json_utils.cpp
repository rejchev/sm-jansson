#include "json_utils.h"

#include <cstring>

namespace nJansson {
    size_t json_string_size(const json_t *obj) {
        const char* value = json_string_value(obj);

        return ((value == nullptr) ? 0 : strlen(value) + 1);
    }

} // nJansson