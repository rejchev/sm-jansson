#include "handles.h"

#include <smsdk_ext.h>

SourceMod::Handle_t
nJansson::CreateHandle(void *obj, const IHandleType *type, const SourceMod::HandleSecurity *sec,
                       const SourceMod::HandleAccess *access) {
    if(type == nullptr || obj == nullptr)
        return BAD_HANDLE;

    SourceMod::Handle_t handle;
    SourceMod::HandleError error = SourceMod::HandleError_None;
    if((handle = type->createHandle(obj, sec, access, &error)) == BAD_HANDLE)
        smutils->LogError(myself, "Create security handle failed (code: %d, type: %s)", error, type->name());

    if(error != HandleError_None)
        FreeHandle(handle, obj, type, sec);

    return handle;
}

void *nJansson::ReadHandle(const cell_t &address, const IHandleType *type, const SourceMod::HandleSecurity *sec) {
    if(type == nullptr)
        return nullptr;

    void* obj;
    HandleError error;
    if((error = handlesys->ReadHandle(address, type->id(), sec, (void**)&obj))
       != SourceMod::HandleError_None)
        smutils->LogError(myself,"Read '%s' handle error (code: %d)", type->name(), error);

    if(error != HandleError_None)
        obj = nullptr;

    return obj;
}

void *nJansson::FreeHandle(const Handle_t &handle, void *obj, const IHandleType *type,
                           const SourceMod::HandleSecurity *sec) {
    if(handlesys->FreeHandle(handle, sec) == SourceMod::HandleError_None)
        return nullptr;

    if(!type->dispatch())
        return obj;

    type->dispatch()->OnHandleDestroy(type->id(), obj);

    return nullptr;
}

nJansson::IJson *
nJansson::ReadJsonHandle(const cell_t &address, const IHandleType *type, const SourceMod::HandleSecurity *sec,
                         bool (*pFunc)(nJansson::IJS *)) {
    nJansson::IJson *obj;
    if((obj = static_cast<IJson *>(ReadHandle(address, type, sec))) == nullptr)
        return nullptr;

    return ((pFunc != nullptr && !pFunc(obj)) ? nullptr : obj);
}
