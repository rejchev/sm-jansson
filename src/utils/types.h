#ifndef SM_JANSSON_TYPES_H
#define SM_JANSSON_TYPES_H

#include <public/IJansson.h>

namespace nJansson {

    const IHandleType* GetHandleType(const IJansson *face, const char *typeName);
    const IHandleType* GetHandleType(const IJansson *face, const SourceMod::Handle_t& handle);
}

#endif //SM_JANSSON_TYPES_H
