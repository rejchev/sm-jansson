#include <src/json.h>

#include "json_o_natives.h"

bool IsObjectAnJsonObject(nJansson::IJson* obj) {
    return obj != nullptr && obj->type() == nJansson::jtObject;
}

cell_t JsonObjectGetJson(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PCU::GetType(pContext, pJansson, "Json")) == nullptr)
        return BAD_HANDLE;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJsonObject* json;
    if((json = (nJansson::IJsonObject*) nJansson::PCU::ReadJsonHandle(
            pContext,
            g_pHandleSys,
            pType,
            &sec,
            params[1], IsObjectAnJsonObject)) == nullptr)
        return 0;

    char* key;
    pContext->LocalToString(params[2], &key);

    Handle_t handle;
    if((handle = nJansson::PCU::CreateHandle(
            pContext,
            g_pHandleSys,
            pType,
            json->get(key),
            &sec)) != BAD_HANDLE
    && params[3] == 1)
        nJansson::PCU::FreeHandle(g_pHandleSys, pType, params[1], &sec, json);

    return (cell_t) handle;
}

cell_t JsonObjectGetInt(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PCU::GetType(pContext, pJansson, "Json")) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJsonObject* json;
    if((json = (nJansson::IJsonObject*) nJansson::PCU::ReadJsonHandle(
            pContext,
            g_pHandleSys,
            pType,
            &sec,
            params[1], IsObjectAnJsonObject)) == nullptr)
        return 0;

    char* key;
    pContext->LocalToString(params[2], &key);

    nJansson::IJson* buffer;
    if((buffer = json->get(key)) == nullptr)
        return 0;

    long long value = 0;
    if(buffer->type() == nJansson::jtInteger && buffer->get(&value) && params[3] == 1)
        nJansson::PCU::FreeHandle(g_pHandleSys, pType, params[1], &sec, json);

    delete (nJansson::Json *) buffer;
    return (cell_t)value;
}

cell_t JsonObjectGetBool(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PCU::GetType(pContext, pJansson, "Json")) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJsonObject* json;
    if((json = (nJansson::IJsonObject*) nJansson::PCU::ReadJsonHandle(
            pContext,
            g_pHandleSys,
            pType,
            &sec,
            params[1], IsObjectAnJsonObject)) == nullptr)
        return 0;

    char* key;
    pContext->LocalToString(params[2], &key);

    nJansson::IJson* buffer;
    if((buffer = json->get(key)) == nullptr)
        return 0;

    bool value = false;
    if(buffer->type() == nJansson::jtBoolean && buffer->get(&value) && params[3] == 1)
        nJansson::PCU::FreeHandle(g_pHandleSys, pType, params[1], &sec, json);

    delete (nJansson::Json *) buffer;
    return (cell_t)value;
}

cell_t JsonObjectGetFloat(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PCU::GetType(pContext, pJansson, "Json")) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJsonObject* json;
    if((json = (nJansson::IJsonObject*) nJansson::PCU::ReadJsonHandle(
            pContext,
            g_pHandleSys,
            pType,
            &sec,
            params[1], IsObjectAnJsonObject)) == nullptr)
        return 0;

    char* key;
    pContext->LocalToString(params[2], &key);

    nJansson::IJson* buffer;
    if((buffer = json->get(key)) == nullptr)
        return 0;

    double value = 0;
    if(buffer->type() == nJansson::jtReal && buffer->get(&value) && params[3] == 1)
        nJansson::PCU::FreeHandle(g_pHandleSys, pType, params[1], &sec, json);

    delete (nJansson::Json *) buffer;
    return sp_ftoc((float)value);
}

cell_t JsonObjectGetString(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PCU::GetType(pContext, pJansson, "Json")) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJsonObject* json;
    if((json = (nJansson::IJsonObject*) nJansson::PCU::ReadJsonHandle(
            pContext,
            g_pHandleSys,
            pType,
            &sec,
            params[1], IsObjectAnJsonObject)) == nullptr)
        return 0;

    char* key;
    pContext->LocalToString(params[2], &key);

    nJansson::IJson* buffer;
    if((buffer = json->get(key)) == nullptr)
        return 0;

    if(buffer->type() == nJansson::jtString)
        return 0;

    size_t wbt = 0;
    pContext->StringToLocalUTF8(params[2], params[3], buffer->get(), &wbt);

    // auto delete on success
    if(wbt && params[4] == 1)
        nJansson::PCU::FreeHandle(g_pHandleSys, pType, params[1], &sec, json);

    delete (nJansson::Json *) buffer;
    return 1;
}

cell_t JsonObjectSetJson(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PCU::GetType(pContext, pJansson, "Json")) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJsonObject* json;
    if((json = (nJansson::IJsonObject*) nJansson::PCU::ReadJsonHandle(
            pContext,
            g_pHandleSys,
            pType,
            &sec,
            params[1], IsObjectAnJsonObject)) == nullptr)
        return 0;

    char* key;
    pContext->LocalToString(params[2], &key);

    nJansson::IJson* buffer;
    if((buffer = nJansson::PCU::ReadJsonHandle(pContext, g_pHandleSys, pType, &sec, params[3])) == nullptr)
        return 0;

    if(buffer->type() == nJansson::jtInvalid) // :/
        return 0;

    return json->set(key, buffer);
}

cell_t JsonObjectSetInt(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PCU::GetType(pContext, pJansson, "Json")) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJsonObject* json;
    if((json = (nJansson::IJsonObject*) nJansson::PCU::ReadJsonHandle(
            pContext,
            g_pHandleSys,
            pType,
            &sec,
            params[1], IsObjectAnJsonObject)) == nullptr)
        return 0;

    char* key;
    pContext->LocalToString(params[2], &key);

    return json->set(key, (long long)params[3]);
}

cell_t JsonObjectSetBool(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PCU::GetType(pContext, pJansson, "Json")) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJsonObject* json;
    if((json = (nJansson::IJsonObject*) nJansson::PCU::ReadJsonHandle(
            pContext,
            g_pHandleSys,
            pType,
            &sec,
            params[1], IsObjectAnJsonObject)) == nullptr)
        return 0;

    char* key;
    pContext->LocalToString(params[2], &key);

    return json->set(key, (bool)params[3]);
}

cell_t JsonObjectSetFloat(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PCU::GetType(pContext, pJansson, "Json")) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJsonObject* json;
    if((json = (nJansson::IJsonObject*) nJansson::PCU::ReadJsonHandle(
            pContext,
            g_pHandleSys,
            pType,
            &sec,
            params[1], IsObjectAnJsonObject)) == nullptr)
        return 0;

    char* key;
    pContext->LocalToString(params[2], &key);

    return json->set(key, sp_ctof(params[3]));
}

cell_t JsonObjectSetString(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PCU::GetType(pContext, pJansson, "Json")) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJsonObject* json;
    if((json = (nJansson::IJsonObject*) nJansson::PCU::ReadJsonHandle(
            pContext,
            g_pHandleSys,
            pType,
            &sec,
            params[1], IsObjectAnJsonObject)) == nullptr)
        return 0;

    char* key;
    pContext->LocalToString(params[2], &key);

    char *val;
    pContext->LocalToString(params[3], &val);

    return json->set(key, val);
}

cell_t JsonObjectGetType(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PCU::GetType(pContext, pJansson, "Json")) == nullptr)
        return -1;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJsonObject* json;
    if((json = (nJansson::IJsonObject*) nJansson::PCU::ReadJsonHandle(
            pContext,
            g_pHandleSys,
            pType,
            &sec,
            params[1], IsObjectAnJsonObject)) == nullptr)
        return -1;

    char* key;
    pContext->LocalToString(params[2], &key);

    nJansson::IJson* buffer;
    if((buffer = json->get(key)) == nullptr)
        return -1;

    nJansson::JsonType type = buffer->type();

    delete (nJansson::Json*) buffer;
    return type;
}

cell_t JsonObjectHasKey(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PCU::GetType(pContext, pJansson, "Json")) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJsonObject* json;
    if((json = (nJansson::IJsonObject*) nJansson::PCU::ReadJsonHandle(
            pContext,
            g_pHandleSys,
            pType,
            &sec,
            params[1], IsObjectAnJsonObject)) == nullptr)
        return 0;

    char* key;
    pContext->LocalToString(params[2], &key);

    return json->exist(key);
}

cell_t JsonObjectRemoveKey(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PCU::GetType(pContext, pJansson, "Json")) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJsonObject* json;
    if((json = (nJansson::IJsonObject*) nJansson::PCU::ReadJsonHandle(
            pContext,
            g_pHandleSys,
            pType,
            &sec,
            params[1], IsObjectAnJsonObject)) == nullptr)
        return 0;

    char* key;
    pContext->LocalToString(params[2], &key);

    return json->remove(key);
}

cell_t JsonObjectUpdate(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PCU::GetType(pContext, pJansson, "Json")) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJsonObject* json;
    if((json = (nJansson::IJsonObject*) nJansson::PCU::ReadJsonHandle(
            pContext,
            g_pHandleSys,
            pType,
            &sec,
            params[1], IsObjectAnJsonObject)) == nullptr)
        return 0;

    nJansson::IJsonObject* buffer;
    if((buffer = (nJansson::IJsonObject*) nJansson::PCU::ReadJsonHandle(
            pContext,
            g_pHandleSys,
            pType,
            &sec,
            params[2], IsObjectAnJsonObject)) == nullptr)
        return 0;

    bool success;
    if((success = json->update(buffer,(nJansson::JsonObjectUpdateType)params[3]))
    && params[4] == 1)
        nJansson::PCU::FreeHandle(g_pHandleSys, pType, params[2], &sec, buffer);

    return success;
}

cell_t JsonObjectKeys(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PCU::GetType(pContext, pJansson, "Json")) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJsonObject* json;
    if((json = (nJansson::IJsonObject*) nJansson::PCU::ReadJsonHandle(
            pContext,
            g_pHandleSys,
            pType,
            &sec,
            params[1], IsObjectAnJsonObject)) == nullptr)
        return 0;

    return (cell_t) nJansson::PCU::CreateHandle(
            pContext, g_pHandleSys, pType, json->keys((nJansson::JsonType)params[2], params[3]), &sec
    );
}

cell_t JsonObjectSize(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PCU::GetType(pContext, pJansson, "Json")) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJson* json;
    if((json = (nJansson::IJson*) nJansson::PCU::ReadJsonHandle(
            pContext,
            g_pHandleSys,
            pType,
            &sec,
            params[1], IsObjectAnJsonObject)) == nullptr)
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
        {"JsonObject.Set",          JsonObjectSetJson    },
        {"JsonObject.SetString",    JsonObjectSetString  },
        {"JsonObject.SetBool",      JsonObjectSetBool    },
        {"JsonObject.SetInt",       JsonObjectSetInt     },
        {"JsonObject.SetFloat",     JsonObjectSetFloat   },
        {"JsonObject.GetType",      JsonObjectGetType    },
        {"JsonObject.HasKey",       JsonObjectHasKey     },
        { "JsonObject.Remove", JsonObjectRemoveKey },
        {"JsonObject.Update",       JsonObjectUpdate     },
        {"JsonObject.Keys",         JsonObjectKeys       },
        {"JsonObject.Size.get",         JsonObjectSize   },
        {nullptr, nullptr}
};