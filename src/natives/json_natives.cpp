#include "json_natives.h"

cell_t JsonCreate(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PCU::GetType("Json", pJansson)) == nullptr)
        return BAD_HANDLE;

    char* str;
    pContext->LocalToString(params[1], &str);
    
    nJansson::IJson* json;
    if((json = nJansson::PCU::CreateJson(str, params[2], pJansson)) == nullptr)
        return BAD_HANDLE;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};
    return (cell_t) nJansson::PCU::CreateHandle(json, pType, &sec);
}

cell_t JsonCreateFromFile(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PCU::GetType("Json", pJansson)) == nullptr)
        return BAD_HANDLE;

    char *buffer;
    pContext->LocalToString(params[1], &buffer);

    nJansson::IJson* json;
    if((json = pJansson->create(buffer, params[2], smutils)) == nullptr)
        return BAD_HANDLE;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};
    return (cell_t) nJansson::PCU::CreateHandle(json, pType, &sec);
}

cell_t JsonDump(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PCU::GetType("Json", pJansson)) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJson* json;
    if((json = nJansson::PCU::ReadJsonHandle(params[1], pType, &sec)) == nullptr)
        return 0;

    char* buffer;
    pContext->LocalToString(params[2], &buffer);

    if(!json->dump(buffer, params[3],params[4]))
        return 0;

    if(params[5] == 1 && nJansson::PCU::FreeHandle(params[1], json, pType, &sec) == nullptr)
        pJansson->close((nJansson::IJson*) json);

    return 1;
}

cell_t JsonEqual(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PCU::GetType("Json", pJansson)) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJson* json;
    if((json = nJansson::PCU::ReadJsonHandle(params[1], pType, &sec)) == nullptr)
        return 0;

    nJansson::IJson* json1;
    if((json1 = nJansson::PCU::ReadJsonHandle(params[2], pType, &sec)) == nullptr)
        return 0;

    return json->equal(json1);
}

cell_t JsonGetType(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PCU::GetType("Json", pJansson)) == nullptr)
        return false;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJson* json;
    if((json = nJansson::PCU::ReadJsonHandle(params[1], pType, &sec)) == nullptr)
        return false;

    return json->type();
}

cell_t JsonValidState(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PCU::GetType("Json", pJansson)) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJson* json;
    if((json = nJansson::PCU::ReadJsonHandle(params[1], pType, &sec)) == nullptr)
        return 0;

    return json->isOK();
}

cell_t JsonGetString(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PCU::GetType("Json", pJansson)) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJson* json;
    if((json = nJansson::PCU::ReadJsonHandle(params[1], pType, &sec)) == nullptr)
        return 0;

    size_t wbt =0;
    pContext->StringToLocalUTF8(params[2], params[3], json->get(), &wbt);

    // auto delete on success
    if(wbt && params[4] == 1)
        nJansson::PCU::FreeHandle(params[1], json, pType, &sec);

    return 1;
}

cell_t JsonGetInt64(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PCU::GetType("Json", pJansson)) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJson* json;
    if((json = nJansson::PCU::ReadJsonHandle(params[1], pType, &sec)) == nullptr)
        return 0;

    long long value = 0;

    // auto delete on success
    if(json->get(&value) && params[4] == 1)
        nJansson::PCU::FreeHandle(params[1], json, pType, &sec);

    pContext->StringToLocalUTF8(
        params[2], params[3], std::to_string(value).c_str(), nullptr
    );

    return 1;
}

cell_t JsonGetInt(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PCU::GetType("Json", pJansson)) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJson* json;
    if((json = nJansson::PCU::ReadJsonHandle(params[1], pType, &sec)) == nullptr)
        return 0;

    long long int value = 0;

    // auto delete on success
    if(json->get(&value) && params[2] == 1)
        nJansson::PCU::FreeHandle(params[1], json, pType, &sec);

    return (cell_t) value;
}

cell_t JsonGetBool(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PCU::GetType("Json", pJansson)) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJson* json;
    if((json = nJansson::PCU::ReadJsonHandle(params[1], pType, &sec)) == nullptr)
        return 0;

    bool value = false;

    // auto delete on success
    if(json->get(&value) && params[2] == 1)
        nJansson::PCU::FreeHandle(params[1], json, pType, &sec);

    return (cell_t)value;
}

cell_t JsonGetFloat(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PCU::GetType("Json", pJansson)) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJson* json;
    if((json = nJansson::PCU::ReadJsonHandle(params[1], pType, &sec)) == nullptr)
        return 0;

    double value = 0;

    // auto delete on success
    if(json->get(&value) && params[2] == 1)
        nJansson::PCU::FreeHandle(params[1], json, pType, &sec);

    return sp_ftoc((float)value);
}

// @param 1 - json object
// @param 2 - path
// @param 3 - flags
// @param 4 - freeHandle
cell_t JsonDumpToFile(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PCU::GetType("Json", pJansson)) == nullptr)
        return false;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJson* json;
    if((json = nJansson::PCU::ReadJsonHandle(params[1], pType, &sec)) == nullptr)
        return false;

    char *buffer;
    pContext->LocalToString(params[2], &buffer);

    char fullPath[PLATFORM_MAX_PATH];
    smutils->BuildPath(Path_Game, fullPath, sizeof(fullPath), "%s", buffer);

    bool success;
    if((success = json->dump(fullPath, params[3]) == 0) && params[4] == 1)
        nJansson::PCU::FreeHandle(params[1], json, pType, &sec);

    return success;
}

cell_t JsonClear(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PCU::GetType("Json", pJansson)) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJson* json;
    if((json = nJansson::PCU::ReadJsonHandle(params[1], pType, &sec)) == nullptr)
        return 0;

    json->clear();

    return 1;
}

cell_t JsonSize(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PCU::GetType("Json", pJansson)) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJson* json;
    if((json = nJansson::PCU::ReadJsonHandle(params[1], pType, &sec)) == nullptr)
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
        { "Json.AsInt64", JsonGetInt64 },
        {"Json.AsString",      JsonGetString},
        {"Json.AsBool",        JsonGetBool},
        {"Json.AsFloat",       JsonGetFloat},
        {"Json.Clear",          JsonClear},
        {"Json.Size.get",       JsonSize},
        {"Json.Type.get",       JsonGetType},
        {"Json.Valid.get",      JsonValidState},
        {nullptr, nullptr}
};
