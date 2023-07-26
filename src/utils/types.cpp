#include "types.h"

const nJansson::IHandleType *nJansson::GetHandleType(const nJansson::IJansson *face, const char *typeName) {
    if(face == nullptr || typeName == nullptr)
        return nullptr;

    const IHandleType* type;
    if((type = face->types()->find(typeName)) == nullptr || type->id() == NO_HANDLE_TYPE)
        type = nullptr;

    return type;
}

const nJansson::IHandleType *
nJansson::GetHandleType(const nJansson::IJansson *face, const SourceMod::Handle_t &handle) {
    if(face == nullptr || handle != BAD_HANDLE)
        return nullptr;

    const IHandleType* type;
    if((type = face->types()->find(handle)) == nullptr || type->id() == NO_HANDLE_TYPE)
        type = nullptr;

    return type;
}
