#include <src/json.h>

#include "PluginContextUtils.h"

namespace nJansson {

    const IHandleType *PluginContextUtils::GetType(const char *typeName, const IJansson *face) {
        if(face == nullptr || typeName == nullptr)
            return nullptr;

        const IHandleType* type;
        if((type = face->types()->find(typeName)) == nullptr || type->id() == NO_HANDLE_TYPE)
            type = nullptr;

        return type;
    }

    IJson *PluginContextUtils::CreateJson(const char* str, const cell_t &flags, IJansson *face) {
        if(face == nullptr)
            return nullptr;

        IJson* json;
        if((json = face->create(str, flags)) == nullptr) {

            smutils->LogError(myself, "Something went wrong on create Json wrapper...");
            return nullptr;
        }

        if(LogJsonError("CreateJson", json->error())) {
            face->close(json);
            return nullptr;
        }

        return json;
    }

    Handle_t PluginContextUtils::CreateHandle(
            void *object,
            const IHandleType *type,
            SourceMod::IdentityToken_t *owner,
            SourceMod::IdentityToken_t *ident) {
        if(type == nullptr || object == nullptr)
            return BAD_HANDLE;

        Handle_t handle = BAD_HANDLE;
        HandleError error = SourceMod::HandleError_None;
        if((handle = type->createHandle(object, owner, ident, &error)) == BAD_HANDLE)
            FreeHandle(handle, object, type, nullptr);

        if(error != HandleError_None)
            smutils->LogError(myself, "Create handle failed (code: %d, type: %s)", error, type->name());

        return handle;
    }

    void* PluginContextUtils::ReadHandle(const cell_t &addr, const IHandleType *type, const HandleSecurity* sec) {
        if(type == nullptr)
            return nullptr;

        void* obj;
        HandleError error;
        if((error = handlesys->ReadHandle(addr, type->id(), sec, (void**)&obj))
        != SourceMod::HandleError_None)
            smutils->LogError(myself,"Read '%s' handle error (code: %d)", type->name(), error);

        if(error != HandleError_None)
            obj = nullptr;

        return obj;
    }

    bool PluginContextUtils::LogJsonError(const char* on, const JsonError_t& error) {

        if(error.equal(JSON_ERROR_NULL))
            return false;

        smutils->LogError(
                myself,"Json error detected: \nOn: %s\nSource: %s\nText: %s\nLine: %d\nColumn: %d",
                on,
                error.source,
                error.text,
                error.line,
                error.column
        );

        return true;
    }

    void* PluginContextUtils::FreeHandle(
            const Handle_t &handle,
            void *object,
            const IHandleType *type,
            const HandleSecurity* sec) {
        if(handlesys->FreeHandle(handle, sec) == SourceMod::HandleError_None)
            return nullptr;

        if(!type->dispatch())
            return object;

        type->dispatch()->OnHandleDestroy(type->id(), object);

        return nullptr;
    }

    Handle_t PluginContextUtils::CreateHandle(
            void *object,
            const IHandleType *type,
            const SourceMod::HandleSecurity* sec,
            const SourceMod::HandleAccess* access) {
        if(type == nullptr || object == nullptr)
            return BAD_HANDLE;

        Handle_t handle;
        HandleError error = SourceMod::HandleError_None;
        if((handle = type->createHandle(object, sec, access, &error)) == BAD_HANDLE)
            smutils->LogError(myself, "Create security handle failed (code: %d, type: %s)", error, type->name());

        if(error != HandleError_None)
            FreeHandle(handle, object, type, sec);

        return handle;
    }

    nJansson::IJS* PluginContextUtils::ReadJsonHandle(
            const cell_t &addr,
            const IHandleType *pHandleType,
            const HandleSecurity* sec,
            bool (*pFunc)(nJansson::IJson*)) {

        nJansson::IJson *obj;
        if((obj = static_cast<IJson *>(ReadHandle(addr, pHandleType, sec))) == nullptr)
            return nullptr;

        if(LogJsonError("ReadJsonHandle", obj->error())) {

            delete (nJansson::Json*) obj;
            return nullptr;
        }

        return ((pFunc != nullptr && !pFunc(obj)) ? nullptr : obj);
    }
} // nJansson