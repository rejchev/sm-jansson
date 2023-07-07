#include <src/json.h>

#include "PluginContextUtils.h"

namespace nJansson {

    const IHandleType *PluginContextUtils::GetType(IPluginContext *ctx, const IJansson *face, const char *typeName) {
        if(face == nullptr || ctx == nullptr || typeName == nullptr)
            return nullptr;

        const IHandleType* type;
        if((type = face->types()->find(typeName)) == nullptr || type->id() == NO_HANDLE_TYPE)
            type = nullptr;

        if(type == nullptr)
            ctx->ReportError("Type '%s' is unknown type", typeName);

        return type;
    }

    IJson *PluginContextUtils::CreateJson(IPluginContext *ctx,
                                          IJansson *face,
                                          const cell_t &addr,
                                          const cell_t &flags) {
        if(ctx == nullptr || face == nullptr)
            return nullptr;

        char* str;
        ctx->LocalToString(addr, &str);

        IJson* json;
        if((json = face->create(str, flags)) == nullptr)
            ctx->ReportError("Something went wrong on Create Json wrapper...");

        if(!json->isOK())
        {
            ThrowJsonError(ctx, json);
            delete (nJansson::Json*)json;
            json = nullptr;
        }

        return json;
    }

    Handle_t
    PluginContextUtils::CreateHandle(IPluginContext *ctx,
                                     IHandleSys* hndlSys,
                                     const IHandleType *type,
                                     void *object,
                                     SourceMod::IdentityToken_t *owner,
                                     SourceMod::IdentityToken_t *ident) {
        if(ctx == nullptr || type == nullptr || object == nullptr)
            return BAD_HANDLE;

        Handle_t handle = BAD_HANDLE;
        HandleError error = SourceMod::HandleError_None;
        if((handle = type->createHandle(object, owner, ident, &error)) == BAD_HANDLE)
            FreeHandle(hndlSys, type, handle, nullptr, object);

        if(error != HandleError_None)
            ctx->ReportError("Create handle failed (code: %d, type: %s)", error, type->name());

        return handle;
    }

    void* PluginContextUtils::ReadHandle(IPluginContext *ctx,
                                        IHandleSys* hndl,
                                        const IHandleType *type,
                                        const HandleSecurity *sec,
                                        const cell_t &addr) {
        if(ctx == nullptr || type == nullptr)
            return nullptr;

        void* obj;
        HandleError error;
        if((error = hndl->ReadHandle(addr, type->id(), sec, (void**)&obj)) != SourceMod::HandleError_None)
            ctx->ReportError("Read '%s' handle error (code: %d)", type->name(), error);

        if(error != HandleError_None)
            obj = nullptr;

        return obj;
    }

    bool PluginContextUtils::ThrowJsonError(IPluginContext *ctx, IJson *json) {
        if(json->isOK())
            return false;

        ctx->ReportError("Json is invalid (source: %s): %s [line: %d, column: %d]",
                              json->error().source,
                              json->error().text,
                              json->error().line,
                              json->error().column);

        return true;
    }

    void PluginContextUtils::FreeHandle(IHandleSys *sys,
                                        const IHandleType *type,
                                        const Handle_t &handle,
                                        const HandleSecurity* sec,
                                        void *object) {
        if(sys->FreeHandle(handle, sec) == SourceMod::HandleError_None)
            return;

        if(type->dispatch())
            type->dispatch()->OnHandleDestroy(type->id(), object);
    }

    Handle_t
    PluginContextUtils::CreateHandle(IPluginContext *ctx,
                                     IHandleSys* handleSys,
                                     const IHandleType *type,
                                     void *object,
                                     const SourceMod::HandleSecurity *sec,
                                     const SourceMod::HandleAccess *access) {
        if(ctx == nullptr || type == nullptr || object == nullptr)
            return BAD_HANDLE;

        Handle_t handle;
        HandleError error = SourceMod::HandleError_None;
        if((handle = type->createHandle(object, sec, access, &error)) == BAD_HANDLE)
            ctx->ThrowNativeError("Create security handle failed (code: %d, type: %s)", error, type->name());

        if(error != HandleError_None)
            FreeHandle(handleSys, type, handle, sec, object);

        return handle;
    }

    nJansson::IJS* PluginContextUtils::ReadJsonHandle(IPluginContext *ctx,
                                       IHandleSys *hndl,
                                       const IHandleType *pHandleType,
                                       const HandleSecurity *sec,
                                       const cell_t &addr,
                                       bool (*pFunc)(nJansson::IJson*)) {
        nJansson::IJson *obj;
        if((obj = static_cast<IJson *>(ReadHandle(ctx, hndl, pHandleType, sec, addr))) == nullptr)
            return nullptr;

        ThrowJsonError(ctx, obj);

        return ((pFunc != nullptr && !pFunc(obj)) ? nullptr : obj);
    }
} // nJansson