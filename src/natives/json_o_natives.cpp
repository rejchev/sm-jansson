#include "json_o_natives.h"

bool IsObject(nJansson::IJson* obj) {
    return obj != nullptr && obj->type() == nJansson::jtObject;
}

cell_t JsonObjectGetJson(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PCU::GetType("Json", pJansson)) == nullptr)
        return BAD_HANDLE;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJsonObject* json;
    if((json = nJansson::PCU::ReadJsonHandle(params[1], pType, &sec, IsObject)) == nullptr)
        return 0;

    char* key;
    pContext->LocalToString(params[2], &key);

    Handle_t handle;
    if((handle = nJansson::PCU::CreateHandle(json->get(key), pType, &sec)) != BAD_HANDLE && params[3] == 1)
        if(nJansson::PCU::FreeHandle(params[1], json, pType, &sec) != nullptr)
            pJansson->close((nJansson::IJson*)json);

    return (cell_t) handle;
}

cell_t JsonObjectGetInt(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PCU::GetType("Json", pJansson)) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJsonObject* json;
    if((json = nJansson::PCU::ReadJsonHandle(params[1], pType, &sec, IsObject)) == nullptr)
        return 0;

    char* key;
    pContext->LocalToString(params[2], &key);

    nJansson::IJson* buffer;
    if((buffer = json->get(key)) == nullptr)
        return 0;

    long long value = 0;
    if(buffer->get(&value) && params[3] == 1)
        if(nJansson::PCU::FreeHandle(params[1], json, pType, &sec) != nullptr)
            pJansson->close((nJansson::IJson*)json);

    pJansson->close(buffer);

    return (cell_t)value;
}

cell_t JsonObjectGetInt64(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PCU::GetType("Json", pJansson)) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJsonObject* json;
    if((json = nJansson::PCU::ReadJsonHandle(params[1], pType, &sec, IsObject)) == nullptr)
        return 0;

    char* key;
    pContext->LocalToString(params[2], &key);

    nJansson::IJson* buffer;
    if((buffer = json->get(key)) == nullptr)
        return 0;

    long long value = 0;
    if(!buffer->get(&value)
    || pContext->StringToLocalUTF8(
            params[3],
            params[4],
            std::to_string(value).c_str(),
            nullptr)) {

        pJansson->close(buffer);
        return 0;
    }

    pJansson->close(buffer);

    if(params[5] == 1 && nJansson::PCU::FreeHandle(params[1], json, pType, &sec) != nullptr)
        pJansson->close((nJansson::IJson*) json);

    return 1;
}


cell_t JsonObjectGetBool(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PCU::GetType("Json", pJansson)) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJsonObject* json;
    if((json = nJansson::PCU::ReadJsonHandle(params[1], pType, &sec, IsObject)) == nullptr)
        return 0;

    char* key;
    pContext->LocalToString(params[2], &key);

    nJansson::IJson* buffer;
    if((buffer = json->get(key)) == nullptr)
        return 0;

    bool value = false;
    if(buffer->get(&value) && params[3] == 1)
        if(nJansson::PCU::FreeHandle(params[1], json, pType, &sec) != nullptr)
            pJansson->close((nJansson::IJson*)json);

    pJansson->close(buffer);

    return (cell_t)value;
}

cell_t JsonObjectGetFloat(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PCU::GetType("Json", pJansson)) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJsonObject* json;
    if((json = nJansson::PCU::ReadJsonHandle(params[1], pType, &sec, IsObject)) == nullptr)
        return 0;

    char* key;
    pContext->LocalToString(params[2], &key);

    nJansson::IJson* buffer;
    if((buffer = json->get(key)) == nullptr)
        return 0;

    double value = 0;
    if(buffer->get(&value) && params[3] == 1)
        if(nJansson::PCU::FreeHandle(params[1], json, pType, &sec) != nullptr)
            pJansson->close((nJansson::IJson*)json);

    pJansson->close(buffer);

    return sp_ftoc((float)value);
}

cell_t JsonObjectGetString(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PCU::GetType("Json", pJansson)) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJsonObject* json;
    if((json = nJansson::PCU::ReadJsonHandle(params[1], pType, &sec, IsObject)) == nullptr)
        return 0;

    char* key;
    pContext->LocalToString(params[2], &key);

    nJansson::IJson* buffer;
    if((buffer = json->get(key)) == nullptr)
        return 0;

    const char *value;
    if((value = buffer->get()) == nullptr
    || pContext->StringToLocalUTF8(params[3], params[4], value, nullptr)) {

        pJansson->close(buffer);
        return 0;
    }

    pJansson->close(buffer);

    if(params[5] == 1 && nJansson::PCU::FreeHandle(params[1], json, pType, &sec) != nullptr)
        pJansson->close((nJansson::IJson*)json);

    return 1;
}

cell_t JsonObjectSetJson(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PCU::GetType("Json", pJansson)) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJsonObject* json;
    if((json = nJansson::PCU::ReadJsonHandle(params[1], pType, &sec, IsObject)) == nullptr)
        return 0;

    char* key;
    pContext->LocalToString(params[2], &key);

    return json->set(key, nJansson::PCU::ReadJsonHandle(params[3], pType, &sec));
}

cell_t JsonObjectSetInt(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PCU::GetType("Json", pJansson)) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJsonObject* json;
    if((json = nJansson::PCU::ReadJsonHandle(params[1], pType, &sec, IsObject)) == nullptr)
        return 0;

    char* key;
    pContext->LocalToString(params[2], &key);

    return json->set(key, (long long)params[3]);
}

cell_t JsonObjectSetBool(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PCU::GetType("Json", pJansson)) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJsonObject* json;
    if((json = nJansson::PCU::ReadJsonHandle(params[1], pType, &sec, IsObject)) == nullptr)
        return 0;

    char* key;
    pContext->LocalToString(params[2], &key);

    return json->set(key, (bool)params[3]);
}

cell_t JsonObjectSetFloat(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PCU::GetType("Json", pJansson)) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJsonObject* json;
    if((json = nJansson::PCU::ReadJsonHandle(params[1], pType, &sec, IsObject)) == nullptr)
        return 0;

    char* key;
    pContext->LocalToString(params[2], &key);

    return json->set(key, sp_ctof(params[3]));
}

cell_t JsonObjectSetString(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PCU::GetType("Json", pJansson)) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJsonObject* json;
    if((json = nJansson::PCU::ReadJsonHandle(params[1], pType, &sec, IsObject)) == nullptr)
        return 0;

    char* key;
    pContext->LocalToString(params[2], &key);

    char *val;
    pContext->LocalToString(params[3], &val);

    return json->set(key, val);
}

cell_t JsonObjectSetInt64(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PCU::GetType("Json", pJansson)) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJSO* json;
    if((json = nJansson::PCU::ReadJsonHandle(params[1], pType, &sec, IsObject)) == nullptr)
        return 0;

    char* key;
    pContext->LocalToString(params[2], &key);

    char* value;
    pContext->LocalToString(params[3], &value);

    char* end;
    long long num = std::strtoll(value, &end, 10);

    return ((*end) ? 0 : json->set(key, num));
}

cell_t JsonObjectGetType(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PCU::GetType("Json", pJansson)) == nullptr)
        return -1;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJsonObject* json;
    if((json = nJansson::PCU::ReadJsonHandle(params[1], pType, &sec, IsObject)) == nullptr)
        return -1;

    char* key;
    pContext->LocalToString(params[2], &key);

    return json->type(key);
}

cell_t JsonObjectHasKey(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PCU::GetType("Json", pJansson)) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJsonObject* json;
    if((json = nJansson::PCU::ReadJsonHandle(params[1], pType, &sec, IsObject)) == nullptr)
        return 0;

    char* key;
    pContext->LocalToString(params[2], &key);

    return json->exist(key);
}

cell_t JsonObjectRemoveKey(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PCU::GetType("Json", pJansson)) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJsonObject* json;
    if((json = nJansson::PCU::ReadJsonHandle(params[1], pType, &sec, IsObject)) == nullptr)
        return 0;

    char* key;
    pContext->LocalToString(params[2], &key);

    return json->remove(key);
}

cell_t JsonObjectUpdate(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PCU::GetType("Json", pJansson)) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJsonObject* json;
    if((json = nJansson::PCU::ReadJsonHandle(params[1], pType, &sec, IsObject)) == nullptr)
        return 0;

    nJansson::IJsonObject* buffer;
    if((buffer = nJansson::PCU::ReadJsonHandle(params[2], pType, &sec, IsObject)) == nullptr)
        return 0;

    bool success;
    if((success = json->update(buffer,(nJansson::JsonObjectUpdateType)params[3]))
    && params[4] == 1)
        if(nJansson::PCU::FreeHandle(params[2], buffer, pType, &sec) != nullptr)
            pJansson->close((nJansson::IJson*)buffer);

    return success;
}

cell_t JsonObjectKeys(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PCU::GetType("Json", pJansson)) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJsonObject* json;
    if((json = nJansson::PCU::ReadJsonHandle(params[1], pType, &sec, IsObject)) == nullptr)
        return 0;

    return (cell_t) nJansson::PCU::CreateHandle(
            json->keys((nJansson::JsonType)params[2], params[3]),
            pType,
            &sec);
}

cell_t JsonObjectSize(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PCU::GetType("Json", pJansson)) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJson* json;
    if((json = nJansson::PCU::ReadJsonHandle(params[1], pType, &sec)) == nullptr)
        return 0;
    
    return (cell_t)json->size();
}

const sp_nativeinfo_t JSON_OBJECT_NATIVES[] =
{
        {"JsonObject.Get",          JsonObjectGetJson    },
        {"JsonObject.GetString",    JsonObjectGetString  },
        {"JsonObject.GetBool",      JsonObjectGetBool    },
        {"JsonObject.GetInt",       JsonObjectGetInt     },
        {"JsonObject.GetFloat",     JsonObjectGetFloat   },
        { "JsonObject.GetInt64", JsonObjectGetInt64 },

        {"JsonObject.Set",          JsonObjectSetJson    },
        {"JsonObject.SetString",    JsonObjectSetString  },
        {"JsonObject.SetBool",      JsonObjectSetBool    },
        {"JsonObject.SetInt",       JsonObjectSetInt     },
        {"JsonObject.SetFloat",     JsonObjectSetFloat   },
        { "JsonObject.SetInt64", JsonObjectSetInt64 },

        {"JsonObject.GetType",      JsonObjectGetType    },
        {"JsonObject.HasKey",       JsonObjectHasKey     },
        { "JsonObject.Remove", JsonObjectRemoveKey },
        {"JsonObject.Update",       JsonObjectUpdate     },
        {"JsonObject.Keys",         JsonObjectKeys       },
        {"JsonObject.Size.get",         JsonObjectSize   },
        {nullptr, nullptr}
};