#include "json_natives.h"

cell_t JsonCreate(IPluginContext *pContext, const cell_t *params)
{
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PluginContextUtils::GetType(pContext, pJansson, "Json")) == nullptr)
        return BAD_HANDLE;

    nJansson::IJson* json;
    if((json = nJansson::PluginContextUtils::CreateJson(pContext, pJansson, params[1], params[2])) == nullptr)
        return BAD_HANDLE;

    return (cell_t) nJansson::PluginContextUtils::CreateHandle
        (pContext, pType, json, (const HandleSecurity*) nullptr);
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

    return (cell_t) nJansson::PluginContextUtils::CreateHandle
        (pContext, pType, json, (const HandleSecurity*) nullptr);
}

cell_t JsonDump(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PluginContextUtils::GetType(pContext, pJansson, "Json")) == nullptr)
        return false;

    nJansson::IJson* json;
    if((json = static_cast<nJansson::IJson *>
            (nJansson::PluginContextUtils::ReadHandle(pContext, g_pHandleSys, pType, nullptr, params[1]))) == nullptr)
        return false;

    if(nJansson::PluginContextUtils::ThrowJsonError(pContext, json))
        return false;

    const char* buffer;
    if((buffer = json->dump(params[3])) == nullptr)
        return false;

    pContext->StringToLocalUTF8(params[2], params[3], buffer, nullptr);
    free((void *) buffer);

    return 1;
}

cell_t JsonEqual(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PluginContextUtils::GetType(pContext, pJansson, "Json")) == nullptr)
        return false;

    nJansson::IJson* json;
    if((json = static_cast<nJansson::IJson *>
            (nJansson::PluginContextUtils::ReadHandle(pContext, g_pHandleSys, pType, nullptr, params[1]))) == nullptr)
        return false;

    nJansson::IJson* json1;
    if((json1 = static_cast<nJansson::IJson *>
            (nJansson::PluginContextUtils::ReadHandle(pContext, g_pHandleSys, pType, nullptr, params[2]))) == nullptr)
        return false;

    if(nJansson::PluginContextUtils::ThrowJsonError(pContext, json)
    || nJansson::PluginContextUtils::ThrowJsonError(pContext, json1))
        return false;

    return json->equal(*json1);
}

cell_t JsonGetType(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PluginContextUtils::GetType(pContext, pJansson, "Json")) == nullptr)
        return false;

    nJansson::IJson* json;
    if((json = static_cast<nJansson::IJson *>
            (nJansson::PluginContextUtils::ReadHandle(pContext, g_pHandleSys, pType, nullptr, params[1]))) == nullptr)
        return false;

    return json->type();
}

cell_t JsonGetError(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PluginContextUtils::GetType(pContext, pJansson, "Json")) == nullptr)
        return BAD_HANDLE;

    nJansson::IJson* json;
    if((json = static_cast<nJansson::IJson *>
            (nJansson::PluginContextUtils::ReadHandle(pContext, g_pHandleSys, pType, nullptr, params[1]))) == nullptr)
        return BAD_HANDLE;

    const nJansson::IHandleType* pErrorType;
    if((pErrorType = nJansson::PluginContextUtils::GetType(pContext, pJansson, "JsonError")) == nullptr)
        return BAD_HANDLE;

    return (cell_t) nJansson::PluginContextUtils::CreateHandle(
            pContext,
            pErrorType,
            json->error(),
            (const HandleSecurity*) nullptr);
}

cell_t JsonGetString(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PluginContextUtils::GetType(pContext, pJansson, "Json")) == nullptr)
        return 0;

    nJansson::IJson* json;
    if((json = static_cast<nJansson::IJson *>
            (nJansson::PluginContextUtils::ReadHandle(pContext, g_pHandleSys, pType, nullptr, params[1]))) == nullptr)
        return 0;

    if(nJansson::PluginContextUtils::ThrowJsonError(pContext, json))
        return 0;

    if(json->type() != nJansson::String)
        return 0;

    size_t wbt =0;
    pContext->StringToLocalUTF8(params[2], params[3], json->get(), &wbt);

    // auto delete on success
    if(wbt && params[4] == 1)
        nJansson::PluginContextUtils::FreeHandle(g_pHandleSys, pType, params[1], nullptr, json);

    return 1;
}

cell_t JsonGetInt(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PluginContextUtils::GetType(pContext, pJansson, "Json")) == nullptr)
        return 0;

    nJansson::IJson* json;
    if((json = static_cast<nJansson::IJson *>
            (nJansson::PluginContextUtils::ReadHandle(pContext, g_pHandleSys, pType, nullptr, params[1]))) == nullptr)
        return 0;

    if(nJansson::PluginContextUtils::ThrowJsonError(pContext, json))
        return 0;

    if(json->type() != nJansson::Integer)
        return 0;

    long long int value = 0;

    // auto delete on success
    if(json->get(&value) && params[2] == 1)
        nJansson::PluginContextUtils::FreeHandle(g_pHandleSys, pType, params[1], nullptr, json);

    return (cell_t) value;
}

cell_t JsonGetBool(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PluginContextUtils::GetType(pContext, pJansson, "Json")) == nullptr)
        return 0;

    nJansson::IJson* json;
    if((json = static_cast<nJansson::IJson *>
            (nJansson::PluginContextUtils::ReadHandle(pContext, g_pHandleSys, pType, nullptr, params[1]))) == nullptr)
        return 0;

    if(nJansson::PluginContextUtils::ThrowJsonError(pContext, json))
        return 0;

    if(json->type() != nJansson::Boolean)
        return 0;

    bool value = false;

    // auto delete on success
    if(json->get(&value) && params[2] == 1)
        nJansson::PluginContextUtils::FreeHandle(g_pHandleSys, pType, params[1], nullptr, json);

    return (cell_t)value;
}

cell_t JsonGetFloat(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PluginContextUtils::GetType(pContext, pJansson, "Json")) == nullptr)
        return 0;

    nJansson::IJson* json;
    if((json = static_cast<nJansson::IJson *>
            (nJansson::PluginContextUtils::ReadHandle(pContext, g_pHandleSys, pType, nullptr, params[1]))) == nullptr)
        return 0;

    if(nJansson::PluginContextUtils::ThrowJsonError(pContext, json))
        return 0;

    if(json->type() != nJansson::Boolean)
        return 0;

    double value = 0;

    // auto delete on success
    if(json->get(&value) && params[2] == 1)
        nJansson::PluginContextUtils::FreeHandle(g_pHandleSys, pType, params[1], nullptr, json);

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

    nJansson::IJson* json;
    if((json = static_cast<nJansson::IJson *>
            (nJansson::PluginContextUtils::ReadHandle(pContext, g_pHandleSys, pType, nullptr, params[1]))) == nullptr)
        return false;

    if(nJansson::PluginContextUtils::ThrowJsonError(pContext, json))
        return false;

    char *buffer;
    pContext->LocalToString(params[2], &buffer);

    char fullPath[PLATFORM_MAX_PATH];
    smutils->BuildPath(Path_Game, fullPath, sizeof(fullPath), "%s", buffer);

    bool success;
    if((success = nJansson::PluginContextUtils::DumpJsonToFile(json, fullPath, params[3]) == 0) && params[4] == 1)
        nJansson::PluginContextUtils::FreeHandle(g_pHandleSys, pType, params[1], nullptr, json);

    return success;
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
        {"Json.Type.get",       JsonGetType},
        {"Json.Error.get",      JsonGetError}
};
