#include "json_o_natives.h"
#include "../src/json.h"

cell_t JsonObjectGetJson(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PluginContextUtils::GetType(pContext, pJansson, "Json")) == nullptr)
        return BAD_HANDLE;

    nJansson::IJson* json;
    if((json = static_cast<nJansson::IJson *>
            (nJansson::PluginContextUtils::ReadHandle(pContext, g_pHandleSys, pType, nullptr, params[1]))) == nullptr)
        return 0;

    if(nJansson::PluginContextUtils::ThrowJsonError(pContext, json))
        return BAD_HANDLE;

    char* key;
    pContext->LocalToString(params[2], &key);

    if(json->type() != nJansson::Object || !((nJansson::IJsonObject*) json)->exist(key))
        return BAD_HANDLE;

    Handle_t handle;
    if((handle = nJansson::PluginContextUtils::CreateHandle(
            pContext,
            pType,
            ((nJansson::IJsonObject*) json)->get(key),
            (const HandleSecurity*) nullptr)) != BAD_HANDLE
    && params[3] == 1)
        nJansson::PluginContextUtils::FreeHandle(g_pHandleSys, pType, params[1], nullptr, json);

    return (cell_t) handle;
}

cell_t JsonObjectGetInt(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PluginContextUtils::GetType(pContext, pJansson, "Json")) == nullptr)
        return 0;

    nJansson::IJson* json;
    if((json = static_cast<nJansson::IJson *>
            (nJansson::PluginContextUtils::ReadHandle(pContext, g_pHandleSys, pType, nullptr, params[1]))) == nullptr)
        return 0;

    if(nJansson::PluginContextUtils::ThrowJsonError(pContext, json))
        return 0;

    char* key;
    pContext->LocalToString(params[2], &key);

    if(json->type() != nJansson::Object || !((nJansson::IJsonObject*) json)->exist(key))
        return 0;

    nJansson::IJson* buffer;
    if((buffer = ((nJansson::IJsonObject*) json)->get(key)) == nullptr)
        return 0;

    long long value;
    if(buffer->type() == nJansson::Integer && buffer->get(&value) && params[3] == 1)
        nJansson::PluginContextUtils::FreeHandle(g_pHandleSys, pType, params[1], nullptr, json);

    delete (nJansson::Json *) buffer;
    return (cell_t)value;
}

cell_t JsonObjectGetBool(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PluginContextUtils::GetType(pContext, pJansson, "Json")) == nullptr)
        return 0;

    nJansson::IJson* json;
    if((json = static_cast<nJansson::IJson *>
            (nJansson::PluginContextUtils::ReadHandle(pContext, g_pHandleSys, pType, nullptr, params[1]))) == nullptr)
        return 0;

    if(nJansson::PluginContextUtils::ThrowJsonError(pContext, json))
        return 0;

    char* key;
    pContext->LocalToString(params[2], &key);

    if(json->type() != nJansson::Object || !((nJansson::IJsonObject*) json)->exist(key))
        return 0;

    nJansson::IJson* buffer;
    if((buffer = ((nJansson::IJsonObject*) json)->get(key)) == nullptr)
        return 0;

    bool value;
    if(buffer->type() == nJansson::Boolean && buffer->get(&value) && params[3] == 1)
        nJansson::PluginContextUtils::FreeHandle(g_pHandleSys, pType, params[1], nullptr, json);

    delete (nJansson::Json *) buffer;
    return (cell_t)value;
}

cell_t JsonObjectGetFloat(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PluginContextUtils::GetType(pContext, pJansson, "Json")) == nullptr)
        return 0;

    nJansson::IJson* json;
    if((json = static_cast<nJansson::IJson *>
            (nJansson::PluginContextUtils::ReadHandle(pContext, g_pHandleSys, pType, nullptr, params[1]))) == nullptr)
        return 0;

    if(nJansson::PluginContextUtils::ThrowJsonError(pContext, json))
        return 0;

    char* key;
    pContext->LocalToString(params[2], &key);

    if(json->type() != nJansson::Object || !((nJansson::IJsonObject*) json)->exist(key))
        return 0;

    nJansson::IJson* buffer;
    if((buffer = ((nJansson::IJsonObject*) json)->get(key)) == nullptr)
        return 0;

    double value;
    if(buffer->type() == nJansson::Real && buffer->get(&value) && params[3] == 1)
        nJansson::PluginContextUtils::FreeHandle(g_pHandleSys, pType, params[1], nullptr, json);

    delete (nJansson::Json *) buffer;
    return sp_ftoc((float)value);
}

cell_t JsonObjectGetString(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PluginContextUtils::GetType(pContext, pJansson, "Json")) == nullptr)
        return 0;

    nJansson::IJson* json;
    if((json = static_cast<nJansson::IJson *>
            (nJansson::PluginContextUtils::ReadHandle(pContext, g_pHandleSys, pType, nullptr, params[1]))) == nullptr)
        return 0;

    if(nJansson::PluginContextUtils::ThrowJsonError(pContext, json))
        return 0;

    char* key;
    pContext->LocalToString(params[2], &key);

    if(json->type() != nJansson::Object || !((nJansson::IJsonObject*) json)->exist(key))
        return 0;

    nJansson::IJson* buffer;
    if((buffer = ((nJansson::IJsonObject*) json)->get(key)) == nullptr)
        return 0;

    if(buffer->type() == nJansson::String)
        return 0;

    size_t wbt = 0;
    pContext->StringToLocalUTF8(params[2], params[3], json->get(), &wbt);

    // auto delete on success
    if(wbt && params[4] == 1)
        nJansson::PluginContextUtils::FreeHandle(g_pHandleSys, pType, params[1], nullptr, json);

    delete (nJansson::Json *) buffer;
    return 1;
}

cell_t JsonObjectSetJson(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PluginContextUtils::GetType(pContext, pJansson, "Json")) == nullptr)
        return 0;

    nJansson::IJson* json;
    if((json = static_cast<nJansson::IJson *>
            (nJansson::PluginContextUtils::ReadHandle(pContext, g_pHandleSys, pType, nullptr, params[1]))) == nullptr)
        return 0;

    if(nJansson::PluginContextUtils::ThrowJsonError(pContext, json))
        return 0;

    char* key;
    pContext->LocalToString(params[2], &key);

    if(json->type() != nJansson::Object)
        return 0;

    nJansson::IJson* buffer;
    if((buffer = static_cast<nJansson::IJson *>
                (nJansson::PluginContextUtils::ReadHandle(pContext, g_pHandleSys, pType, nullptr, params[3]))) == nullptr)
        return 0;

    if(nJansson::PluginContextUtils::ThrowJsonError(pContext, buffer))
        return 0;

    if(buffer->type() == nJansson::Invalid)
        return 0;

    return ((nJansson::IJsonObject*)json)->set(key, buffer);
}

cell_t JsonObjectSetInt(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PluginContextUtils::GetType(pContext, pJansson, "Json")) == nullptr)
        return 0;

    nJansson::IJson* json;
    if((json = static_cast<nJansson::IJson *>
            (nJansson::PluginContextUtils::ReadHandle(pContext, g_pHandleSys, pType, nullptr, params[1]))) == nullptr)
        return 0;

    if(nJansson::PluginContextUtils::ThrowJsonError(pContext, json))
        return 0;

    if(json->type() != nJansson::Object)
        return 0;

    char* key;
    pContext->LocalToString(params[2], &key);

    return ((nJansson::IJsonObject*)json)->set(key, (long long)params[3]);
}

cell_t JsonObjectSetBool(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PluginContextUtils::GetType(pContext, pJansson, "Json")) == nullptr)
        return 0;

    nJansson::IJson* json;
    if((json = static_cast<nJansson::IJson *>
            (nJansson::PluginContextUtils::ReadHandle(pContext, g_pHandleSys, pType, nullptr, params[1]))) == nullptr)
        return 0;

    if(nJansson::PluginContextUtils::ThrowJsonError(pContext, json))
        return 0;

    if(json->type() != nJansson::Object)
        return 0;

    char* key;
    pContext->LocalToString(params[2], &key);

    return ((nJansson::IJsonObject*)json)->set(key, (bool)params[3]);
}

cell_t JsonObjectSetFloat(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PluginContextUtils::GetType(pContext, pJansson, "Json")) == nullptr)
        return 0;

    nJansson::IJson* json;
    if((json = static_cast<nJansson::IJson *>
            (nJansson::PluginContextUtils::ReadHandle(pContext, g_pHandleSys, pType, nullptr, params[1]))) == nullptr)
        return 0;

    if(nJansson::PluginContextUtils::ThrowJsonError(pContext, json))
        return 0;

    if(json->type() != nJansson::Object)
        return 0;

    char* key;
    pContext->LocalToString(params[2], &key);

    return ((nJansson::IJsonObject*)json)->set(key, sp_ctof(params[3]));
}

cell_t JsonObjectSetString(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PluginContextUtils::GetType(pContext, pJansson, "Json")) == nullptr)
        return 0;

    nJansson::IJson* json;
    if((json = static_cast<nJansson::IJson *>
            (nJansson::PluginContextUtils::ReadHandle(pContext, g_pHandleSys, pType, nullptr, params[1]))) == nullptr)
        return 0;

    if(nJansson::PluginContextUtils::ThrowJsonError(pContext, json))
        return 0;

    if(json->type() != nJansson::Object)
        return 0;

    char* key;
    pContext->LocalToString(params[2], &key);

    char *val;
    pContext->LocalToString(params[3], &val);

    return ((nJansson::IJsonObject*)json)->set(key, val);
}

cell_t JsonObjectGetType(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PluginContextUtils::GetType(pContext, pJansson, "Json")) == nullptr)
        return 0;

    nJansson::IJson* json;
    if((json = static_cast<nJansson::IJson *>
            (nJansson::PluginContextUtils::ReadHandle(pContext, g_pHandleSys, pType, nullptr, params[1]))) == nullptr)
        return 0;

    if(nJansson::PluginContextUtils::ThrowJsonError(pContext, json))
        return 0;

    if(json->type() != nJansson::Object)
        return 0;

    char* key;
    pContext->LocalToString(params[2], &key);

    auto& link = reinterpret_cast<nJansson::IJsonObject *&>(json);

    if(!link->exist(key))
        return 0;

    nJansson::IJson* buffer = link->get(key);
    nJansson::JsonType type = buffer->type();

    delete (nJansson::Json*) buffer;
    return type;
}

cell_t JsonObjectHasKey(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PluginContextUtils::GetType(pContext, pJansson, "Json")) == nullptr)
        return 0;

    nJansson::IJson* json;
    if((json = static_cast<nJansson::IJson *>
            (nJansson::PluginContextUtils::ReadHandle(pContext, g_pHandleSys, pType, nullptr, params[1]))) == nullptr)
        return 0;

    if(nJansson::PluginContextUtils::ThrowJsonError(pContext, json))
        return 0;

    if(json->type() != nJansson::Object)
        return 0;

    char* key;
    pContext->LocalToString(params[2], &key);

    return reinterpret_cast<nJansson::IJsonObject *&>(json)->exist(key);
}

cell_t JsonObjectClear(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PluginContextUtils::GetType(pContext, pJansson, "Json")) == nullptr)
        return 0;

    nJansson::IJson* json;
    if((json = static_cast<nJansson::IJson *>
            (nJansson::PluginContextUtils::ReadHandle(pContext, g_pHandleSys, pType, nullptr, params[1]))) == nullptr)
        return 0;

    if(nJansson::PluginContextUtils::ThrowJsonError(pContext, json))
        return 0;

    if(json->type() != nJansson::Object)
        return 0;

    ((nJansson::IJsonObject*)json)->clear();

    return json->error()->code() == nJansson::Unknown;
}

cell_t JsonObjectUpdate(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PluginContextUtils::GetType(pContext, pJansson, "Json")) == nullptr)
        return 0;

    nJansson::IJson* json;
    if((json = static_cast<nJansson::IJson *>
                (nJansson::PluginContextUtils::ReadHandle(pContext, g_pHandleSys, pType, nullptr, params[1]))) == nullptr)
        return 0;

    if(nJansson::PluginContextUtils::ThrowJsonError(pContext, json))
        return 0;

    if(json->type() != nJansson::Object)
        return 0;

    nJansson::IJson* buffer;
    if((buffer = static_cast<nJansson::IJson *>
            (nJansson::PluginContextUtils::ReadHandle(pContext, g_pHandleSys, pType, nullptr, params[2]))) == nullptr)
        return 0;

    if(nJansson::PluginContextUtils::ThrowJsonError(pContext, buffer))
        return 0;

    if(buffer->type() != nJansson::Object)
        return 0;

    bool success;
    if((success = ((nJansson::IJsonObject*)json)->update(
            ((nJansson::IJsonObject*)buffer),
            (nJansson::JsonObjectUpdateType)params[3]))
    && params[4] == 1)
        nJansson::PluginContextUtils::FreeHandle(g_pHandleSys, pType, params[2], nullptr, buffer);

    return success;
}

cell_t JsonObjectKeys(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PluginContextUtils::GetType(pContext, pJansson, "Json")) == nullptr)
        return 0;

    const nJansson::IHandleType* pIteratorType;
    if((pIteratorType = nJansson::PluginContextUtils::GetType(pContext, pJansson, "JsonObjectKeyIterator")) == nullptr)
        return 0;

    nJansson::IJson* json;
    if((json = static_cast<nJansson::IJson *>
            (nJansson::PluginContextUtils::ReadHandle(pContext, g_pHandleSys, pType, nullptr, params[1]))) == nullptr)
        return 0;

    if(nJansson::PluginContextUtils::ThrowJsonError(pContext, json))
        return 0;

    if(json->type() != nJansson::Object)
        return 0;

    return (cell_t) nJansson::PluginContextUtils::CreateHandle(
            pContext,
            pIteratorType,
            ((nJansson::IJsonObject*)json)->keys(),
            (const HandleSecurity*) nullptr);
}

cell_t JsonObjectGetKeysCount(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PluginContextUtils::GetType(pContext, pJansson, "Json")) == nullptr)
        return 0;

    nJansson::IJson* json;
    if((json = static_cast<nJansson::IJson *>
            (nJansson::PluginContextUtils::ReadHandle(pContext, g_pHandleSys, pType, nullptr, params[1]))) == nullptr)
        return 0;

    if(nJansson::PluginContextUtils::ThrowJsonError(pContext, json))
        return 0;

    if(json->type() != nJansson::Object)
        return 0;

    return (cell_t)((nJansson::IJsonObject*)json)->size();
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
        {"JsonObject.Update",       JsonObjectUpdate     },
        {"JsonObject.Clear",        JsonObjectClear      },
        {"JsonObject.Keys",         JsonObjectKeys       },
        {"JsonObject.KeysCount.get",JsonObjectGetKeysCount      }
};



























