#include "json_natives.h"

cell_t JsonCreate(IPluginContext *pContext, const cell_t *params)
{
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PluginContextUtils::GetType(pContext, pJansson, "Json")) == nullptr)
        return BAD_HANDLE;

    nJansson::IJson* json;
    if((json = nJansson::PluginContextUtils::CreateJson(pContext, pJansson, params[1], params[2])) == nullptr)
        return BAD_HANDLE;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};
    return (cell_t) nJansson::PluginContextUtils::CreateHandle(pContext, g_pHandleSys, pType, json, &sec);
}

cell_t JsonCreateFromFile(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PluginContextUtils::GetType(pContext, pJansson, "Json")) == nullptr)
        return BAD_HANDLE;

    nJansson::IJson* json;
    if((json = nJansson::PluginContextUtils::CreateJsonFromPath(
            pContext,
            pJansson,
            smutils,
            params[1],
            params[2])) == nullptr)
        return BAD_HANDLE;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};
    return (cell_t) nJansson::PluginContextUtils::CreateHandle(pContext, g_pHandleSys, pType, json, &sec);
}

cell_t JsonDump(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHT* pType;
    if((pType = nJansson::PCU::GetType(pContext, pJansson, "Json")) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJson* json;
    if((json = nJansson::PCU::ReadJsonHandle(pContext, g_pHandleSys, pType, &sec, params[1])) == nullptr)
        return 0;

    const char* buffer;
    if((buffer = json->dump(params[4])) == nullptr)
        return 0;

    pContext->StringToLocalUTF8(params[2], params[3], buffer, nullptr);

    free((void *) buffer);

    if(params[5] == 1)
        nJansson::PCU::FreeHandle(g_pHandleSys, pType, params[1], &sec, json);

    return 1;
}

cell_t JsonEqual(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PluginContextUtils::GetType(pContext, pJansson, "Json")) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJson* json;
    if((json = nJansson::PCU::ReadJsonHandle(pContext, g_pHandleSys, pType, &sec, params[1])) == nullptr)
        return 0;

    nJansson::IJson* json1;
    if((json1 = nJansson::PCU::ReadJsonHandle(pContext, g_pHandleSys, pType, &sec, params[2])) == nullptr)
        return 0;

    return json->equal(*json1);
}

cell_t JsonGetType(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PluginContextUtils::GetType(pContext, pJansson, "Json")) == nullptr)
        return false;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJson* json;
    if((json = nJansson::PCU::ReadJsonHandle(pContext, g_pHandleSys, pType, &sec, params[1])) == nullptr)
        return false;

    return json->type();
}

cell_t JsonGetError(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PluginContextUtils::GetType(pContext, pJansson, "Json")) == nullptr)
        return BAD_HANDLE;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJson* json;
    if((json = static_cast<nJansson::IJson *>
            (nJansson::PluginContextUtils::ReadHandle(pContext, g_pHandleSys, pType, &sec, params[1]))) == nullptr)
        return BAD_HANDLE;

    const nJansson::IHandleType* pErrorType;
    if((pErrorType = nJansson::PluginContextUtils::GetType(pContext, pJansson, "JsonError")) == nullptr)
        return BAD_HANDLE;

    return (cell_t) nJansson::PluginContextUtils::CreateHandle(
            pContext,
            g_pHandleSys,
            pErrorType,
            json->error(),
            &sec);
}

cell_t JsonGetString(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PluginContextUtils::GetType(pContext, pJansson, "Json")) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJson* json;
    if((json = static_cast<nJansson::IJson *>
            (nJansson::PluginContextUtils::ReadHandle(pContext, g_pHandleSys, pType, &sec, params[1]))) == nullptr)
        return 0;

    if(nJansson::PluginContextUtils::ThrowJsonError(pContext, json))
        return 0;

    size_t wbt =0;
    pContext->StringToLocalUTF8(params[2], params[3], json->get(), &wbt);

    // auto delete on success
    if(wbt && params[4] == 1)
        nJansson::PluginContextUtils::FreeHandle(g_pHandleSys, pType, params[1], &sec, json);

    return 1;
}

cell_t JsonGetInt(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PluginContextUtils::GetType(pContext, pJansson, "Json")) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJson* json;
    if((json = static_cast<nJansson::IJson *>
            (nJansson::PluginContextUtils::ReadHandle(pContext, g_pHandleSys, pType, &sec, params[1]))) == nullptr)
        return 0;

    if(nJansson::PluginContextUtils::ThrowJsonError(pContext, json))
        return 0;

    long long int value = 0;

    // auto delete on success
    if(json->get(&value) && params[2] == 1)
        nJansson::PluginContextUtils::FreeHandle(g_pHandleSys, pType, params[1], &sec, json);

    return (cell_t) value;
}

cell_t JsonGetBool(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PluginContextUtils::GetType(pContext, pJansson, "Json")) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJson* json;
    if((json = static_cast<nJansson::IJson *>
            (nJansson::PluginContextUtils::ReadHandle(pContext, g_pHandleSys, pType, &sec, params[1]))) == nullptr)
        return 0;

    if(nJansson::PluginContextUtils::ThrowJsonError(pContext, json))
        return 0;

    bool value = false;

    // auto delete on success
    if(json->get(&value) && params[2] == 1)
        nJansson::PluginContextUtils::FreeHandle(g_pHandleSys, pType, params[1], &sec, json);

    return (cell_t)value;
}

cell_t JsonGetFloat(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PluginContextUtils::GetType(pContext, pJansson, "Json")) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJson* json;
    if((json = static_cast<nJansson::IJson *>
            (nJansson::PluginContextUtils::ReadHandle(pContext, g_pHandleSys, pType, &sec, params[1]))) == nullptr)
        return 0;

    if(nJansson::PluginContextUtils::ThrowJsonError(pContext, json))
        return 0;

    double value = 0;

    // auto delete on success
    if(json->get(&value) && params[2] == 1)
        nJansson::PluginContextUtils::FreeHandle(g_pHandleSys, pType, params[1], &sec, json);

    return sp_ftoc((float)value);
}

// @param 1 - json object
// @param 2 - path
// @param 3 - flags
// @param 4 - freeHandle
cell_t JsonDumpToFile(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PluginContextUtils::GetType(pContext, pJansson, "Json")) == nullptr)
        return false;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJson* json;
    if((json = static_cast<nJansson::IJson *>
            (nJansson::PluginContextUtils::ReadHandle(pContext, g_pHandleSys, pType, &sec, params[1]))) == nullptr)
        return false;

    if(nJansson::PluginContextUtils::ThrowJsonError(pContext, json))
        return false;

    char *buffer;
    pContext->LocalToString(params[2], &buffer);

    char fullPath[PLATFORM_MAX_PATH];
    smutils->BuildPath(Path_Game, fullPath, sizeof(fullPath), "%s", buffer);

    bool success;
    if((success = nJansson::PluginContextUtils::DumpJsonToFile(json, fullPath, params[3]) == 0) && params[4] == 1)
        nJansson::PluginContextUtils::FreeHandle(g_pHandleSys, pType, params[1], &sec, json);

    return success;
}

cell_t JsonClear(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHT* pType;
    if((pType = nJansson::PCU::GetType(pContext, pJansson, "Json")) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJS* json;
    if((json = nJansson::PCU::ReadJsonHandle(
            pContext,
            g_pHandleSys,
            pType,
            &sec,
            params[1])) == nullptr)
        return 0;

    json->clear();

    return 1;
}

cell_t JsonSize(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHT* pType;
    if((pType = nJansson::PCU::GetType(pContext, pJansson, "Json")) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJS* json;
    if((json = nJansson::PCU::ReadJsonHandle(
            pContext,
            g_pHandleSys,
            pType,
            &sec,
            params[1])) == nullptr)
        return 0;

    return (cell_t)json->size();
}

const sp_nativeinfo_t JSON_NATIVES[] =
{
        {"Json.Json",           JsonCreate},
        {"Json.JsonF",          JsonCreateFromFile},
        {"Json.Dump",           JsonDump},
        {"Json.ToFile",         JsonDumpToFile},
        {"Json.Equal",          JsonEqual},
        {"Json.AsInt",         JsonGetInt},
        {"Json.AsString",      JsonGetString},
        {"Json.AsBool",        JsonGetBool},
        {"Json.AsFloat",       JsonGetFloat},
        {"Json.Clear",          JsonClear},
        {"Json.Size.get",       JsonSize},
        {"Json.Type.get",       JsonGetType},
        {"Json.Error.get",      JsonGetError}
};
