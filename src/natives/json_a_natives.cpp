#include <src/json.h>

#include "json_a_natives.h"

bool IsObjectAnArrayObject(nJansson::IJS* obj) {
    return obj != nullptr && obj->type() == nJansson::jtArray;
}

cell_t JsonArrayGetJson(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PCU::GetType(pContext, pJansson, "Json")) == nullptr)
        return BAD_HANDLE;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJSA* json;
    if((json = (nJansson::IJSA *) nJansson::PCU::ReadJsonHandle(
            pContext,
            g_pHandleSys,
            pType,
            &sec,
            params[1], IsObjectAnArrayObject)) == nullptr)
        return 0;

    Handle_t handle;
    if((handle = nJansson::PCU::CreateHandle(
            pContext,
            g_pHandleSys,
            pType,
            json->get(params[2]),
            &sec)) != BAD_HANDLE
       && params[3] == 1)
        nJansson::PCU::FreeHandle(g_pHandleSys, pType, params[1], &sec, json);

    return (cell_t) handle;
}

// param1 - this
// param2 - index
// param3 - free 'param1' handle (bool)
cell_t JsonArrayGetInt(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PCU::GetType(pContext, pJansson, "Json")) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJSA* json;
    if((json = (nJansson::IJSA *) nJansson::PCU::ReadJsonHandle(
            pContext,
            g_pHandleSys,
            pType,
            &sec,
            params[1], IsObjectAnArrayObject)) == nullptr)
        return 0;

    nJansson::IJS* buffer;
    if((buffer = json->get(params[2])) == nullptr)
        return 0;

    long long value = 0;
    if(buffer->type() == nJansson::jtInteger && buffer->get(&value) && params[3] == 1)
        nJansson::PCU::FreeHandle(g_pHandleSys, pType, params[1], &sec, json);

    delete (nJansson::Json*) buffer;
    return (cell_t)value;
}

// param1 - this
// param2 - index
// param3 - free 'param1' handle (bool)
cell_t JsonArrayGetBool(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PCU::GetType(pContext, pJansson, "Json")) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJSA* json;
    if((json = (nJansson::IJSA *) nJansson::PCU::ReadJsonHandle(
            pContext,
            g_pHandleSys,
            pType,
            &sec,
            params[1], IsObjectAnArrayObject)) == nullptr)
        return 0;

    nJansson::IJS* buffer;
    if((buffer = json->get(params[2])) == nullptr)
        return 0;

    bool value = false;
    if(buffer->type() == nJansson::jtBoolean && buffer->get(&value) && params[3] == 1)
        nJansson::PCU::FreeHandle(g_pHandleSys, pType, params[1], &sec, json);

    delete (nJansson::Json*) buffer;
    return (cell_t)value;
}

cell_t JsonArrayGetFloat(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PCU::GetType(pContext, pJansson, "Json")) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJSA* json;
    if((json = (nJansson::IJSA *) nJansson::PCU::ReadJsonHandle(
            pContext,
            g_pHandleSys,
            pType,
            &sec,
            params[1], IsObjectAnArrayObject)) == nullptr)
        return 0;

    nJansson::IJS* buffer;
    if((buffer = json->get(params[2])) == nullptr)
        return 0;

    double value = 0;
    if(buffer->type() == nJansson::jtReal && buffer->get(&value) && params[3] == 1)
        nJansson::PCU::FreeHandle(g_pHandleSys, pType, params[1], &sec, json);

    delete (nJansson::Json*) buffer;
    return sp_ftoc((float)value);
}

cell_t JsonArrayGetString(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PCU::GetType(pContext, pJansson, "Json")) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJSA* json;
    if((json = (nJansson::IJSA *) nJansson::PCU::ReadJsonHandle(
            pContext,
            g_pHandleSys,
            pType,
            &sec,
            params[1], IsObjectAnArrayObject)) == nullptr)
        return 0;

    nJansson::IJS* buffer;
    if((buffer = json->get(params[2])) == nullptr)
        return 0;

    const char* value = nullptr;
    if(buffer->type() == nJansson::jtString && (value = buffer->get()) != nullptr && params[5] == 1)
        nJansson::PCU::FreeHandle(g_pHandleSys, pType, params[1], &sec, json);

    if(value != nullptr)
        pContext->StringToLocalUTF8(params[3], params[4], buffer->get(), nullptr);

    delete (nJansson::Json*) buffer;
    return value != nullptr;
}

cell_t JsonArraySetJson(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PCU::GetType(pContext, pJansson, "Json")) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJSA* json;
    if((json = (nJansson::IJSA *) nJansson::PCU::ReadJsonHandle(
            pContext,
            g_pHandleSys,
            pType,
            &sec,
            params[1], IsObjectAnArrayObject)) == nullptr)
        return 0;

    nJansson::IJS* buffer;
    if((buffer = static_cast<nJansson::IJS *>
            (nJansson::PCU::ReadHandle(pContext, g_pHandleSys, pType, &sec, params[3]))) == nullptr)
        return 0;

    if(nJansson::PCU::ThrowJsonError(pContext, buffer))
        return 0;

    return json->set(params[2], buffer);
}

cell_t JsonArraySetInt(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PCU::GetType(pContext, pJansson, "Json")) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJSA* json;
    if((json = (nJansson::IJSA *) nJansson::PCU::ReadJsonHandle(
            pContext,
            g_pHandleSys,
            pType,
            &sec,
            params[1], IsObjectAnArrayObject)) == nullptr)
        return 0;

    return json->set(params[2], (long long)params[3]);
}

cell_t JsonArraySetBool(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PCU::GetType(pContext, pJansson, "Json")) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJSA* json;
    if((json = (nJansson::IJSA *) nJansson::PCU::ReadJsonHandle(
            pContext,
            g_pHandleSys,
            pType,
            &sec,
            params[1], IsObjectAnArrayObject)) == nullptr)
        return 0;

    return json->set(params[2], (bool)params[3]);
}

cell_t JsonArraySetFloat(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PCU::GetType(pContext, pJansson, "Json")) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJSA* json;
    if((json = (nJansson::IJSA *) nJansson::PCU::ReadJsonHandle(
            pContext,
            g_pHandleSys,
            pType,
            &sec,
            params[1], IsObjectAnArrayObject)) == nullptr)
        return 0;

    return json->set(params[2], sp_ctof(params[3]));
}

cell_t JsonArraySetString(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PCU::GetType(pContext, pJansson, "Json")) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJSA* json;
    if((json = (nJansson::IJSA *) nJansson::PCU::ReadJsonHandle(
            pContext,
            g_pHandleSys,
            pType,
            &sec,
            params[1], IsObjectAnArrayObject)) == nullptr)
        return 0;

    char* value;
    pContext->LocalToString(params[3], &value);

    return json->set(params[2], value);
}

cell_t JsonArrayPushJson(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PCU::GetType(pContext, pJansson, "Json")) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJSA* json;
    if((json = (nJansson::IJSA *) nJansson::PCU::ReadJsonHandle(
            pContext,
            g_pHandleSys,
            pType,
            &sec,
            params[1], IsObjectAnArrayObject)) == nullptr)
        return 0;

    nJansson::IJS* buffer;
    if((buffer = static_cast<nJansson::IJS*>
            (nJansson::PCU::ReadHandle(pContext, g_pHandleSys, pType, &sec, params[2]))) == nullptr)
        return 0;

    if(nJansson::PCU::ThrowJsonError(pContext, buffer))
        return 0;

    return json->push(buffer);
}

cell_t JsonArrayPushInt(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PCU::GetType(pContext, pJansson, "Json")) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJSA* json;
    if((json = (nJansson::IJSA *) nJansson::PCU::ReadJsonHandle(
            pContext,
            g_pHandleSys,
            pType,
            &sec,
            params[1], IsObjectAnArrayObject)) == nullptr)
        return 0;

    return json->push((long long)params[2]);
}

cell_t JsonArrayPushBool(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PCU::GetType(pContext, pJansson, "Json")) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJSA* json;
    if((json = (nJansson::IJSA *) nJansson::PCU::ReadJsonHandle(
            pContext,
            g_pHandleSys,
            pType,
            &sec,
            params[1], IsObjectAnArrayObject)) == nullptr)
        return 0;

    return json->push((bool)params[2]);
}

cell_t JsonArrayPushFloat(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PCU::GetType(pContext, pJansson, "Json")) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJSA* json;
    if((json = (nJansson::IJSA *) nJansson::PCU::ReadJsonHandle(
            pContext,
            g_pHandleSys,
            pType,
            &sec,
            params[1], IsObjectAnArrayObject)) == nullptr)
        return 0;

    return json->push(sp_ctof(params[2]));
}

cell_t JsonArrayPushString(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PCU::GetType(pContext, pJansson, "Json")) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJSA* json;
    if((json = (nJansson::IJSA *) nJansson::PCU::ReadJsonHandle(
            pContext,
            g_pHandleSys,
            pType,
            &sec,
            params[1], IsObjectAnArrayObject)) == nullptr)
        return 0;

    char* value;
    pContext->LocalToString(params[2], &value);

    return json->push(value);
}

cell_t JsonArrayGetType(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PCU::GetType(pContext, pJansson, "Json")) == nullptr)
        return -1;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJSA* json;
    if((json = (nJansson::IJSA *) nJansson::PCU::ReadJsonHandle(
            pContext,
            g_pHandleSys,
            pType,
            &sec,
            params[1], IsObjectAnArrayObject)) == nullptr)
        return -1;

    nJansson::IJS* buffer;
    if((buffer = json->get(params[2])) == nullptr)
        return -1;

    nJansson::JsonType type = buffer->type();

    delete (nJansson::Json *) buffer;
    return type;
}

// 1 - this
// 2 - another array obj
// 3 - freeAnotherObj
cell_t JsonArrayExtend(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PCU::GetType(pContext, pJansson, "Json")) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJsonArray* json;
    if((json = (nJansson::IJSA *) nJansson::PCU::ReadJsonHandle(
            pContext,
            g_pHandleSys,
            pType,
            &sec,
            params[1], IsObjectAnArrayObject)) == nullptr)
        return 0;

    nJansson::IJsonArray* buffer;
    if((buffer = (nJansson::IJSA *) nJansson::PCU::ReadJsonHandle(
            pContext,
            g_pHandleSys,
            pType,
            &sec,
            params[2], IsObjectAnArrayObject)) == nullptr)
        return 0;

    if(!json->extend(buffer))
        return 0;

    if(params[3] == 1)
        nJansson::PCU::FreeHandle(g_pHandleSys, pType, params[2], &sec, buffer);

    return 1;
}

cell_t JsonArrayRemove(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PCU::GetType(pContext, pJansson, "Json")) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJsonArray* json;
    if((json = (nJansson::IJSA *) nJansson::PCU::ReadJsonHandle(
            pContext,
            g_pHandleSys,
            pType,
            &sec,
            params[1], IsObjectAnArrayObject)) == nullptr)
        return 0;

    return json->remove(params[2]);
}

cell_t JsonArrayGetSize(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PCU::GetType(pContext, pJansson, "Json")) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJS* json;
    if((json = (nJansson::IJS *) nJansson::PCU::ReadJsonHandle(
            pContext,
            g_pHandleSys,
            pType,
            &sec,
            params[1], IsObjectAnArrayObject)) == nullptr)
        return 0;

    return (cell_t)json->size();
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
        {"JsonArray.Size.get",       JsonArrayGetSize     },
        {nullptr, nullptr}
};