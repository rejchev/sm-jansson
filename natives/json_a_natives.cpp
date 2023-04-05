#include "json_a_natives.h"
#include "../src/json.h"

using eIJson =          nJansson::IJson;
using eIJsonArray =     nJansson::IJsonArray;
using eContext =        nJansson::PluginContextUtils;

cell_t JsonArrayGetJson(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = eContext ::GetType(pContext, pJansson, "Json")) == nullptr)
        return BAD_HANDLE;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    eIJsonArray* json;
    if((json = (eIJsonArray *) eContext::ReadJsonHandle(
            pContext,
            g_pHandleSys,
            pType,
            &sec,
            params[1], nJansson::Array)) == nullptr)
        return 0;

    Handle_t handle;
    if((handle = eContext ::CreateHandle(
            pContext,
            pType,
            json->get(params[2]),
            &sec)) != BAD_HANDLE
       && params[3] == 1)
        eContext::FreeHandle(g_pHandleSys, pType, params[1], &sec, json);

    return (cell_t) handle;
}

// param1 - this
// param2 - index
// param3 - free 'param1' handle (bool)
cell_t JsonArrayGetInt(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = eContext ::GetType(pContext, pJansson, "Json")) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    eIJsonArray* json;
    if((json = (eIJsonArray *) eContext::ReadJsonHandle(
            pContext,
            g_pHandleSys,
            pType,
            &sec,
            params[1], nJansson::Array)) == nullptr)
        return 0;

    eIJson* buffer;
    if((buffer = json->get(params[2])) == nullptr)
        return 0;

    long long value;
    if(buffer->type() == nJansson::Integer && buffer->get(&value) && params[3] == 1)
        eContext ::FreeHandle(g_pHandleSys, pType, params[1], &sec, json);

    delete (nJansson::Json*) buffer;
    return (cell_t)value;
}

// param1 - this
// param2 - index
// param3 - free 'param1' handle (bool)
cell_t JsonArrayGetBool(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = eContext ::GetType(pContext, pJansson, "Json")) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    eIJsonArray* json;
    if((json = (eIJsonArray *) eContext::ReadJsonHandle(
            pContext,
            g_pHandleSys,
            pType,
            &sec,
            params[1], nJansson::Array)) == nullptr)
        return 0;

    eIJson* buffer;
    if((buffer = json->get(params[2])) == nullptr)
        return 0;

    bool value;
    if(buffer->type() == nJansson::Boolean && buffer->get(&value) && params[3] == 1)
        eContext::FreeHandle(g_pHandleSys, pType, params[1], &sec, json);

    delete (nJansson::Json*) buffer;
    return (cell_t)value;
}

cell_t JsonArrayGetFloat(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = eContext ::GetType(pContext, pJansson, "Json")) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    eIJsonArray* json;
    if((json = (eIJsonArray *) eContext::ReadJsonHandle(
            pContext,
            g_pHandleSys,
            pType,
            &sec,
            params[1], nJansson::Array)) == nullptr)
        return 0;

    eIJson* buffer;
    if((buffer = json->get(params[2])) == nullptr)
        return 0;

    double value;
    if(buffer->type() == nJansson::Real && buffer->get(&value) && params[3] == 1)
        eContext::FreeHandle(g_pHandleSys, pType, params[1], &sec, json);

    delete (nJansson::Json*) buffer;
    return sp_ftoc((float)value);
}

cell_t JsonArrayGetString(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = eContext ::GetType(pContext, pJansson, "Json")) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    eIJsonArray* json;
    if((json = (eIJsonArray *) eContext::ReadJsonHandle(
            pContext,
            g_pHandleSys,
            pType,
            &sec,
            params[1], nJansson::Array)) == nullptr)
        return 0;

    eIJson* buffer;
    if((buffer = json->get(params[2])) == nullptr)
        return 0;

    const char* value;
    if(buffer->type() == nJansson::String && (value = buffer->get()) != nullptr && params[4] == 1)
        eContext::FreeHandle(g_pHandleSys, pType, params[1], &sec, json);

    if(value != nullptr)
        pContext->StringToLocalUTF8(params[2], params[3], buffer->get(), nullptr);

    delete (nJansson::Json*) buffer;
    return value != nullptr;
}

cell_t JsonArraySetJson(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = eContext::GetType(pContext, pJansson, "Json")) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    eIJsonArray* json;
    if((json = (eIJsonArray *) eContext::ReadJsonHandle(
            pContext,
            g_pHandleSys,
            pType,
            &sec,
            params[1], nJansson::Array)) == nullptr)
        return 0;

    eIJson* buffer;
    if((buffer = static_cast<eIJson *>
            (eContext::ReadHandle(pContext, g_pHandleSys, pType, &sec, params[3]))) == nullptr)
        return 0;

    if(eContext::ThrowJsonError(pContext, buffer))
        return 0;

    return json->set(params[2], buffer);
}

cell_t JsonArraySetInt(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = eContext::GetType(pContext, pJansson, "Json")) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    eIJsonArray* json;
    if((json = (eIJsonArray *) eContext::ReadJsonHandle(
            pContext,
            g_pHandleSys,
            pType,
            &sec,
            params[1], nJansson::Array)) == nullptr)
        return 0;

    return json->set(params[2], (long long)params[3]);
}

cell_t JsonArraySetBool(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = eContext::GetType(pContext, pJansson, "Json")) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    eIJsonArray* json;
    if((json = (eIJsonArray *) eContext::ReadJsonHandle(
            pContext,
            g_pHandleSys,
            pType,
            &sec,
            params[1], nJansson::Array)) == nullptr)
        return 0;

    return json->set(params[2], (bool)params[3]);
}

cell_t JsonArraySetFloat(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = eContext::GetType(pContext, pJansson, "Json")) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    eIJsonArray* json;
    if((json = (eIJsonArray *) eContext::ReadJsonHandle(
            pContext,
            g_pHandleSys,
            pType,
            &sec,
            params[1], nJansson::Array)) == nullptr)
        return 0;

    return json->set(params[2], sp_ctof(params[3]));
}

cell_t JsonArraySetString(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = eContext::GetType(pContext, pJansson, "Json")) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    eIJsonArray* json;
    if((json = (eIJsonArray *) eContext::ReadJsonHandle(
            pContext,
            g_pHandleSys,
            pType,
            &sec,
            params[1], nJansson::Array)) == nullptr)
        return 0;

    char* value;
    pContext->LocalToString(params[3], &value);

    return json->set(params[2], value);
}

cell_t JsonArrayPushJson(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = eContext::GetType(pContext, pJansson, "Json")) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    eIJsonArray* json;
    if((json = (eIJsonArray *) eContext::ReadJsonHandle(
            pContext,
            g_pHandleSys,
            pType,
            &sec,
            params[1], nJansson::Array)) == nullptr)
        return 0;

    eIJson* buffer;
    if((buffer = static_cast<eIJson*>
            (eContext::ReadHandle(pContext, g_pHandleSys, pType, &sec, params[2]))) == nullptr)
        return 0;

    if(eContext::ThrowJsonError(pContext, buffer))
        return 0;

    return json->push(buffer);
}

cell_t JsonArrayPushInt(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = eContext::GetType(pContext, pJansson, "Json")) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    eIJsonArray* json;
    if((json = (eIJsonArray *) eContext::ReadJsonHandle(
            pContext,
            g_pHandleSys,
            pType,
            &sec,
            params[1], nJansson::Array)) == nullptr)
        return 0;

    return json->push((long long)params[2]);
}

cell_t JsonArrayPushBool(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = eContext::GetType(pContext, pJansson, "Json")) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    eIJsonArray* json;
    if((json = (eIJsonArray *) eContext::ReadJsonHandle(
            pContext,
            g_pHandleSys,
            pType,
            &sec,
            params[1], nJansson::Array)) == nullptr)
        return 0;

    return json->push((bool)params[2]);
}

cell_t JsonArrayPushFloat(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = eContext::GetType(pContext, pJansson, "Json")) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    eIJsonArray* json;
    if((json = (eIJsonArray *) eContext::ReadJsonHandle(
            pContext,
            g_pHandleSys,
            pType,
            &sec,
            params[1], nJansson::Array)) == nullptr)
        return 0;

    return json->push(sp_ctof(params[2]));
}

cell_t JsonArrayPushString(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = eContext::GetType(pContext, pJansson, "Json")) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    eIJsonArray* json;
    if((json = (eIJsonArray *) eContext::ReadJsonHandle(
            pContext,
            g_pHandleSys,
            pType,
            &sec,
            params[1], nJansson::Array)) == nullptr)
        return 0;

    char* value;
    pContext->LocalToString(params[2], &value);

    return json->push(value);
}

cell_t JsonArrayGetType(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = eContext::GetType(pContext, pJansson, "Json")) == nullptr)
        return -1;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    eIJsonArray* json;
    if((json = (eIJsonArray *) eContext::ReadJsonHandle(
            pContext,
            g_pHandleSys,
            pType,
            &sec,
            params[1], nJansson::Array)) == nullptr)
        return -1;

    eIJson* buffer;
    if((buffer = json->get(params[2])) == nullptr)
        return -1;

    nJansson::JsonType type = nJansson::Invalid;
    if(nJansson::IJsonError::null(buffer->error()))
        type = buffer->type();

    delete (nJansson::Json *) buffer;
    return type;
}

// 1 - this
// 2 - another array obj
// 3 - freeAnotherObj
cell_t JsonArrayExtend(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = eContext::GetType(pContext, pJansson, "Json")) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJsonArray* json;
    if((json = (eIJsonArray *) eContext::ReadJsonHandle(
            pContext,
            g_pHandleSys,
            pType,
            &sec,
            params[1], nJansson::Array)) == nullptr)
        return 0;

    nJansson::IJsonArray* buffer;
    if((buffer = (eIJsonArray *) eContext::ReadJsonHandle(
            pContext,
            g_pHandleSys,
            pType,
            &sec,
            params[2], nJansson::Array)) == nullptr)
        return 0;

    return json->extend(buffer);
}

cell_t JsonArrayClear(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = eContext::GetType(pContext, pJansson, "Json")) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJsonArray* json;
    if((json = (eIJsonArray *) eContext::ReadJsonHandle(
            pContext,
            g_pHandleSys,
            pType,
            &sec,
            params[1], nJansson::Array)) == nullptr)
        return 0;

    json->clear();
    return 1;
}

cell_t JsonArrayRemove(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = eContext::GetType(pContext, pJansson, "Json")) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJsonArray* json;
    if((json = (eIJsonArray *) eContext::ReadJsonHandle(
            pContext,
            g_pHandleSys,
            pType,
            &sec,
            params[1], nJansson::Array)) == nullptr)
        return 0;

    return json->remove(params[2]);
}

cell_t JsonArrayLength(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = eContext::GetType(pContext, pJansson, "Json")) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJsonArray* json;
    if((json = (eIJsonArray *) eContext::ReadJsonHandle(
            pContext,
            g_pHandleSys,
            pType,
            &sec,
            params[1], nJansson::Array)) == nullptr)
        return 0;

    return (cell_t)json->length();
}

const sp_nativeinfo_t JSON_ARRAY_NATIVES[] =
{
        {"JsonArray.Get",          JsonArrayGetJson    },
        {"JsonArray.GetString",    JsonArrayGetString  },
        {"JsonArray.GetBool",      JsonArrayGetBool    },
        {"JsonArray.GetInt",       JsonArrayGetInt     },
        {"JsonArray.GetFloat",     JsonArrayGetFloat   },

        {"JsonArray.Set",          JsonArraySetJson    },
        {"JsonArray.SetString",    JsonArraySetString  },
        {"JsonArray.SetBool",      JsonArraySetBool    },
        {"JsonArray.SetInt",       JsonArraySetInt     },
        {"JsonArray.SetFloat",     JsonArraySetFloat   },

        {"JsonArray.Push",          JsonArrayPushJson    },
        {"JsonArray.PushString",    JsonArrayPushString  },
        {"JsonArray.PushBool",      JsonArrayPushBool    },
        {"JsonArray.PushInt",       JsonArrayPushInt     },
        {"JsonArray.PushFloat",     JsonArrayPushFloat   },

        {"JsonArray.GetType",      JsonArrayGetType    },
        {"JsonArray.Extend",       JsonArrayExtend     },
        {"JsonArray.Remove",       JsonArrayRemove     },
        {"JsonArray.Clear",        JsonArrayClear      },
        {"JsonArray.Length.get",   JsonArrayLength       },
};