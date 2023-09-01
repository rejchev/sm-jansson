#include "json_natives.h"

#include <cstdio>
#include <extension.h>
#include <src/utils/types.h>
#include <src/utils/handles.h>

cell_t JsonCreate(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::GetHandleType(pJansson, "Json")) == nullptr)
        return BAD_HANDLE;

    char* str;
    pContext->LocalToString(params[1], &str);

    nJansson::IJson* json;
    nJansson::JsonError_t error = {};
    if((json = pJansson->create(str, params[2], &error)) == nullptr) {

        char* buffer = nullptr;

        if(params[3] && params[4])
            pContext->LocalToString(params[3], &buffer);

        if(buffer != nullptr)
            snprintf(buffer, params[4], "%s [%d:%d]", error.text, error.line, error.column);

        return BAD_HANDLE;
    }

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};
    return (cell_t) nJansson::CreateHandle(json, pType, &sec);
}

cell_t JsonCreateFromFile(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::GetHandleType(pJansson, "Json")) == nullptr)
        return BAD_HANDLE;

    char *path;
    pContext->LocalToString(params[1], &path);

    nJansson::IJson* json;
    nJansson::JsonError_t error = {};
    if((json = pJansson->create(Path_Game, path, params[2], &error)) == nullptr) {

        char* buffer = nullptr;
        if(params[3] && params[4])
            pContext->LocalToString(params[3], &buffer);

        if(buffer != nullptr)
            snprintf(buffer, params[4], "%s [%d:%d]", error.text, error.line, error.column);

        return BAD_HANDLE;
    }

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};
    return (cell_t) nJansson::CreateHandle(json, pType, &sec);
}

cell_t JsonDump(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::GetHandleType(pJansson, "Json")) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJson* json;
    if((json = nJansson::ReadJsonHandle(params[1], pType, &sec)) == nullptr)
        return 0;

    char* buffer;
    pContext->LocalToString(params[2], &buffer);

    if(!json->dump(buffer, params[3],params[4]))
        return 0;

    if(params[5] == 1 && nJansson::FreeHandle(params[1], json, pType, &sec) != nullptr)
        pJansson->close((nJansson::IJson*) json);

    return 1;
}

cell_t JsonEqual(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::GetHandleType(pJansson, "Json")) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJson* json;
    if((json = nJansson::ReadJsonHandle(params[1], pType, &sec)) == nullptr)
        return 0;

    nJansson::IJson* json1;
    if((json1 = nJansson::ReadJsonHandle(params[2], pType, &sec)) == nullptr)
        return 0;

    return json->equal(json1);
}

cell_t JsonGetType(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::GetHandleType(pJansson, "Json")) == nullptr)
        return false;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJson* json;
    if((json = nJansson::ReadJsonHandle(params[1], pType, &sec)) == nullptr)
        return false;

    return json->type();
}

cell_t JsonValidState(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::GetHandleType(pJansson, "Json")) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJson* json;
    if((json = nJansson::ReadJsonHandle(params[1], pType, &sec)) == nullptr)
        return 0;

    return json->isOK();
}

cell_t JsonGetString(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::GetHandleType(pJansson, "Json")) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJson* json;
    if((json = nJansson::ReadJsonHandle(params[1], pType, &sec)) == nullptr)
        return 0;

    const char* value;
    if((value = json->get()) == nullptr
    || pContext->StringToLocalUTF8(params[2], params[3], value, nullptr))
        return 0;

    if(params[4] == 1 && nJansson::FreeHandle(params[1], json, pType, &sec) != nullptr)
        pJansson->close((nJansson::IJson*)json);

    return 1;
}

cell_t JsonGetInt64(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::GetHandleType(pJansson, "Json")) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJson* json;
    if((json = nJansson::ReadJsonHandle(params[1], pType, &sec)) == nullptr)
        return 0;

    long long value = 0;
    if(!json->get(&value)
    || pContext->StringToLocalUTF8(
            params[2],
            params[3],
            std::to_string(value).c_str(),
            nullptr))
        return 0;

    if(params[4] == 1 && nJansson::FreeHandle(params[1], json, pType, &sec) != nullptr)
        pJansson->close((nJansson::IJson*) json);

    return 1;
}

cell_t JsonGetInt(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::GetHandleType(pJansson, "Json")) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJson* json;
    if((json = nJansson::ReadJsonHandle(params[1], pType, &sec)) == nullptr)
        return 0;

    long long int value = 0;
    if(json->get(&value) && params[2] == 1)
        if(nJansson::FreeHandle(params[1], json, pType, &sec) != nullptr)
            pJansson->close((nJansson::IJson*)json);

    return (cell_t) value;
}

cell_t JsonGetIntEx(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::GetHandleType(pJansson, "Json")) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJson* json;
    if((json = nJansson::ReadJsonHandle(params[1], pType, &sec)) == nullptr)
        return 0;

    bool success;
    long long int value = 0;
    if((success = json->get(&value)) && params[3] == 1)
        if(nJansson::FreeHandle(params[1], json, pType, &sec) != nullptr)
            pJansson->close((nJansson::IJson*)json);

    if(success)
        pContext->GetLocalParams()[2] = (cell_t)value;

    return success;
}

cell_t JsonGetBool(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::GetHandleType(pJansson, "Json")) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJson* json;
    if((json = nJansson::ReadJsonHandle(params[1], pType, &sec)) == nullptr)
        return 0;

    bool value = false;
    if(json->get(&value) && params[2] == 1)
        if(nJansson::FreeHandle(params[1], json, pType, &sec) != nullptr)
            pJansson->close((nJansson::IJson*)json);

    return (cell_t)value;
}

cell_t JsonGetBoolEx(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::GetHandleType(pJansson, "Json")) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJson* json;
    if((json = nJansson::ReadJsonHandle(params[1], pType, &sec)) == nullptr)
        return 0;

    bool success;
    bool value = false;
    if((success = json->get(&value)) && params[3] == 1)
        if(nJansson::FreeHandle(params[1], json, pType, &sec) != nullptr)
            pJansson->close((nJansson::IJson*)json);

    if(success)
        pContext->GetLocalParams()[2] = (cell_t)value;

    return success;
}

cell_t JsonGetFloat(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::GetHandleType(pJansson, "Json")) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJson* json;
    if((json = nJansson::ReadJsonHandle(params[1], pType, &sec)) == nullptr)
        return 0;

    double value = 0;
    if(json->get(&value) && params[2] == 1)
        if(nJansson::FreeHandle(params[1], json, pType, &sec) != nullptr)
            pJansson->close((nJansson::IJson*)json);

    return sp_ftoc((float)value);
}

cell_t JsonGetFloatEx(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::GetHandleType(pJansson, "Json")) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJson* json;
    if((json = nJansson::ReadJsonHandle(params[1], pType, &sec)) == nullptr)
        return 0;

    bool success;
    double value = 0;
    if((success = json->get(&value)) && params[3] == 1)
        if(nJansson::FreeHandle(params[1], json, pType, &sec) != nullptr)
            pJansson->close((nJansson::IJson*)json);

    if(success)
        pContext->GetLocalParams()[2] = sp_ftoc((float)value);

    return success;
}

// @param 1 - json object
// @param 2 - path
// @param 3 - flags
// @param 4 - freeHandle
cell_t JsonDumpToFile(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::GetHandleType(pJansson, "Json")) == nullptr)
        return false;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJson* json;
    if((json = nJansson::ReadJsonHandle(params[1], pType, &sec)) == nullptr)
        return false;

    char *buffer;
    pContext->LocalToString(params[2], &buffer);

    char fullPath[PLATFORM_MAX_PATH];
    smutils->BuildPath(Path_Game, fullPath, sizeof(fullPath), "%s", buffer);

    bool success;
    if((success = json->dump(fullPath, params[3]) == 0) && params[4] == 1)
        if(nJansson::FreeHandle(params[1], json, pType, &sec) != nullptr)
            pJansson->close((nJansson::IJson*)json);

    return success;
}

cell_t JsonClear(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::GetHandleType(pJansson, "Json")) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJson* json;
    if((json = nJansson::ReadJsonHandle(params[1], pType, &sec)) == nullptr)
        return 0;

    json->clear();

    return 1;
}

cell_t JsonSize(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::GetHandleType(pJansson, "Json")) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJson* json;
    if((json = nJansson::ReadJsonHandle(params[1], pType, &sec)) == nullptr)
        return 0;

    return (cell_t)json->size();
}

cell_t JsonSizeOf(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::GetHandleType(pJansson, "Json")) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJson* json;
    if((json = nJansson::ReadJsonHandle(params[1], pType, &sec)) == nullptr)
        return 0;

    cell_t size = 0;

    const char* buffer;
    if((buffer = json->dump(params[2])) != nullptr)
        size = (cell_t)strlen(buffer);

    if(buffer != nullptr)
        free((void*) buffer);

    return size;
}

cell_t JsonFindFirst(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::GetHandleType(pJansson, "Json")) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJson* json;
    if((json = nJansson::ReadJsonHandle(params[1], pType, &sec)) == nullptr)
        return 0;

    if(json->type() != nJansson::jtObject && json->type() != nJansson::jtArray)
        return 0;

    IPluginFunction* pFunc;
    if(!(pFunc = pContext->GetFunctionById((funcid_t)params[2])))
        return 0;

    const auto& interestingType = (nJansson::JsonType&)params[3];

    using JsonValidator = std::function<bool(const nJansson::IJson*)>;

    JsonValidator funcCondition = {[&](const nJansson::IJson* ptr) -> bool
    {
        Handle_t handle;

        if((handle = nJansson::CreateHandle((void*)ptr, pType, &sec)) == BAD_HANDLE)
            return false;

        bool result {};

        pFunc->PushCell(interestingType);
        pFunc->PushCell((cell_t)handle);
        pFunc->Execute((cell_t*)&(result));

        // Json object (ptr) is not allocated
        nJansson::FreeHandle(handle, nullptr, pType, &sec);

        return result;
    }};

    nJansson::IJson* pRes;
    if((pRes = json->find(interestingType, funcCondition)) == nullptr)
        return 0;

    return (cell_t) nJansson::CreateHandle((void*)pRes, pType, &sec);
}

const sp_nativeinfo_t JSON_NATIVES[] =
{
        {"Json.Json",           JsonCreate},
        {"Json.JsonF",          JsonCreateFromFile},
        {"Json.SizeOf",          JsonSizeOf},
        {"Json.Dump",           JsonDump},
        {"Json.ToFile",         JsonDumpToFile},
        {"Json.Equal",          JsonEqual},
        {"Json.FindFirst",          JsonFindFirst},

        {"Json.AsInt",         JsonGetInt},
        {"Json.TryAsInt",         JsonGetIntEx},

        {"Json.AsInt64", JsonGetInt64 },
        {"Json.AsString",      JsonGetString},

        {"Json.AsBool",        JsonGetBool},
        {"Json.TryAsBool",         JsonGetBoolEx},

        {"Json.AsFloat",       JsonGetFloat},
        {"Json.TryAsFloat",       JsonGetFloatEx},

        {"Json.Clear",          JsonClear},
        {"Json.Size.get",       JsonSize},
        {"Json.Type.get",       JsonGetType},
        {"Json.Valid.get",      JsonValidState},
        {nullptr, nullptr}
};
