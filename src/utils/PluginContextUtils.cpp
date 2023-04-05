#include "PluginContextUtils.h"
#include "../json.h"

namespace nJansson {

    const IHandleType *PluginContextUtils::GetType(IPluginContext *ctx, const IJansson *face, const char *typeName) {
        if(face == nullptr || ctx == nullptr || typeName == nullptr)
            return nullptr;

        IHandleType* type;
        if((type = face->typeManager()->get(typeName)) == nullptr || type->type() == 0)
            type = nullptr;

        if(type == nullptr)
            ctx->ThrowNativeError("Unknown type '%s', aborting...", typeName);

        return const_cast<IHandleType*>(type);
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
        if((json = face->create(str, flags)) == nullptr || IJsonError::null(*json->error()))
        {
            ThrowJsonError(ctx, json);

            delete (Json *) json;

            json = nullptr;
        }

        return json;
    }

    Handle_t
    PluginContextUtils::CreateHandle(IPluginContext *ctx,
                                     const IHandleType *type,
                                     void *object,
                                     SourceMod::IdentityToken_t *owner,
                                     SourceMod::IdentityToken_t *ident) {
        if(ctx == nullptr || type == nullptr || object == nullptr)
            return BAD_HANDLE;

        Handle_t handle;
        HandleError error = {};
        if((handle = type->createHandle(object, owner, ident, &error)) == BAD_HANDLE
        || error != HandleError_None)
        {
            ctx->ThrowNativeError("Create handle failed (code: %d, type: %s)", error, type->name());

            if(g_pHandleSys->FreeHandle(handle, nullptr) != HandleError_None)
                type->dispatch()->OnHandleDestroy(type->type(), object);

            handle = BAD_HANDLE;
        }

        return handle;
    }

    IJson *PluginContextUtils::CreateJsonFromPath(IPluginContext *ctx,
                                                  IJansson *face,
                                                  ISourceMod* utils,
                                                  const cell_t &addr,
                                                  const cell_t &flags) {
        if(ctx == nullptr || face == nullptr)
            return nullptr;

        char *buffer;
        ctx->LocalToString(addr, &buffer);

        char fullPath[PLATFORM_MAX_PATH];
        utils->BuildPath(Path_Game, fullPath, sizeof(fullPath), "%s", buffer);

        json_t* object;
        json_error_t error;
        object = json_load_file(fullPath, flags, &error);

        return new Json(object, error, false);
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
        if((error = hndl->ReadHandle(addr, type->type(), sec, (void**)&obj)) != SourceMod::HandleError_None)
        {
            ctx->ThrowNativeError("Read '%s' handle error (code: %d)", type->name(), error);
            obj = nullptr;
        }

        return obj;
    }

    bool PluginContextUtils::ThrowJsonError(IPluginContext *ctx, IJson *json) {
        if(!IJsonError::null(*json->error()))
            return false;

        ctx->ThrowNativeError("Json is invalid (code: %d, source: %s): %s [line: %d, column: %d]",
                              json->error()->code(),
                              json->error()->source(),
                              json->error()->text(),
                              json->error()->line(),
                              json->error()->column());

        return true;
    }

    void PluginContextUtils::FreeHandle(IHandleSys *sys,
                                        const IHandleType *type,
                                        const Handle_t &handle,
                                        const HandleSecurity* sec,
                                        void *object) {
        if(sys->FreeHandle(handle, sec) == SourceMod::HandleError_None)
            return;

        type->dispatch()->OnHandleDestroy(type->type(), object);
    }

    int PluginContextUtils::DumpJsonToFile(IJson *json, const char *path, const size_t &flags) {
        return json_dump_file(((Json*) json)->json(), path, flags);
    }

    Handle_t
    PluginContextUtils::CreateHandle(IPluginContext *ctx,
                                     const IHandleType *type,
                                     void *object,
                                     const SourceMod::HandleSecurity *sec,
                                     const SourceMod::HandleAccess *access) {
        if(ctx == nullptr || type == nullptr || object == nullptr)
            return BAD_HANDLE;

        Handle_t handle;
        HandleError error = {};
        if((handle = type->createHandle(object, sec, access, &error)) == BAD_HANDLE
        || error != HandleError_None)
        {
            ctx->ThrowNativeError("Create security handle failed (code: %d, type: %s)", error, type->name());

            if(g_pHandleSys->FreeHandle(handle, sec) != HandleError_None)
                type->dispatch()->OnHandleDestroy(type->type(), object);

            handle = BAD_HANDLE;
        }

        return handle;
    }
} // nJansson