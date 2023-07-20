#include "json_a_natives.h"

bool IsArray(nJansson::IJS* obj) {
    return obj != nullptr && obj->type() == nJansson::jtArray;
}

cell_t JsonArrayGetJson(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PCU::GetType("Json", pJansson)) == nullptr)
        return BAD_HANDLE;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJsonArray* json;
    if((json = nJansson::PCU::ReadJsonHandle(params[1], pType, &sec, IsArray)) == nullptr)
        return 0;

    Handle_t handle;
    if((handle = nJansson::PCU::CreateHandle(json->get(params[2]), pType, &sec)) != BAD_HANDLE && params[3] == 1)
        if(nJansson::PCU::FreeHandle(params[1], json, pType, &sec) != nullptr)
            pJansson->close((nJansson::IJson*)json);

    return (cell_t) handle;
}

// param1 - this
// param2 - index
// param3 - free 'param1' handle (bool)
cell_t JsonArrayGetInt(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PCU::GetType("Json", pJansson)) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJSA* json;
    if((json = nJansson::PCU::ReadJsonHandle(params[1], pType, &sec, IsArray)) == nullptr)
        return 0;

    nJansson::IJS* buffer;
    if((buffer = json->get(params[2])) == nullptr)
        return 0;

    long long value = 0;
    if(buffer->get(&value) && params[3] == 1)
        if(nJansson::PCU::FreeHandle(params[1], json, pType, &sec) != nullptr)
            pJansson->close((nJansson::IJson*)json);

    pJansson->close(buffer);

    return (cell_t)value;
}

// param1 - this
// param2 - index
// param3 - free 'param1' handle (bool)
cell_t JsonArrayGetBool(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PCU::GetType("Json", pJansson)) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJSA* json;
    if((json = nJansson::PCU::ReadJsonHandle(params[1], pType, &sec, IsArray)) == nullptr)
        return 0;

    nJansson::IJS* buffer;
    if((buffer = json->get(params[2])) == nullptr)
        return 0;

    bool value = false;
    if(buffer->get(&value) && params[3] == 1)
        if(nJansson::PCU::FreeHandle(params[1], json, pType, &sec) != nullptr)
            pJansson->close((nJansson::IJson*)json);

    pJansson->close(buffer);

    return (cell_t)value;
}

cell_t JsonArrayGetFloat(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PCU::GetType("Json", pJansson)) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJSA* json;
    if((json = nJansson::PCU::ReadJsonHandle(params[1], pType, &sec, IsArray)) == nullptr)
        return 0;

    nJansson::IJS* buffer;
    if((buffer = json->get(params[2])) == nullptr)
        return 0;

    double value = 0;
    if(buffer->get(&value) && params[3] == 1)
        if(nJansson::PCU::FreeHandle(params[1], json, pType, &sec) != nullptr)
            pJansson->close((nJansson::IJson*)json);

    pJansson->close(buffer);

    return sp_ftoc((float)value);
}

cell_t JsonArrayGetString(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PCU::GetType("Json", pJansson)) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJSA* json;
    if((json = nJansson::PCU::ReadJsonHandle(params[1], pType, &sec, IsArray)) == nullptr)
        return 0;

    nJansson::IJS* buffer;
    if((buffer = json->get(params[2])) == nullptr)
        return 0;

    const char* value;
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

cell_t JsonArrayGetInt64(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PCU::GetType("Json", pJansson)) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJSA* json;
    if((json = nJansson::PCU::ReadJsonHandle(params[1], pType, &sec, IsArray)) == nullptr)
        return 0;

    nJansson::IJS* buffer;
    if((buffer = json->get(params[2])) == nullptr)
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
        pJansson->close((nJansson::IJson*)json);

    return 1;
}

cell_t JsonArraySetJson(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PCU::GetType("Json", pJansson)) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJSA* json;
    if((json = nJansson::PCU::ReadJsonHandle(params[1], pType, &sec, IsArray)) == nullptr)
        return 0;

    return json->set(params[2], nJansson::PCU::ReadJsonHandle(params[3], pType, &sec));
}

cell_t JsonArraySetInt(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PCU::GetType("Json", pJansson)) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJSA* json;
    if((json = nJansson::PCU::ReadJsonHandle(params[1], pType, &sec, IsArray)) == nullptr)
        return 0;

    return json->set(params[2], (long long)params[3]);
}

cell_t JsonArraySetBool(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PCU::GetType("Json", pJansson)) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJSA* json;
    if((json = nJansson::PCU::ReadJsonHandle(params[1], pType, &sec, IsArray)) == nullptr)
        return 0;

    return json->set(params[2], (bool)params[3]);
}

cell_t JsonArraySetFloat(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PCU::GetType("Json", pJansson)) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJSA* json;
    if((json = nJansson::PCU::ReadJsonHandle(params[1], pType, &sec, IsArray)) == nullptr)
        return 0;

    return json->set(params[2], sp_ctof(params[3]));
}

cell_t JsonArraySetInt64(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PCU::GetType("Json", pJansson)) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJSA* json;
    if((json = nJansson::PCU::ReadJsonHandle(params[1], pType, &sec, IsArray)) == nullptr)
        return 0;

    char* value;
    pContext->LocalToString(params[3], &value);

    char* end;
    long long num = std::strtoll(value, &end, 10);

    return ((*end) ? 0 : json->set(params[2], num));
}

cell_t JsonArraySetString(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PCU::GetType("Json", pJansson)) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJSA* json;
    if((json = nJansson::PCU::ReadJsonHandle(params[1], pType, &sec, IsArray)) == nullptr)
        return 0;

    char* value;
    pContext->LocalToString(params[3], &value);

    return json->set(params[2], value);
}

cell_t JsonArrayPushJson(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PCU::GetType("Json", pJansson)) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJSA* json;
    if((json = nJansson::PCU::ReadJsonHandle(params[1], pType, &sec, IsArray)) == nullptr)
        return 0;

    return json->push(nJansson::PCU::ReadJsonHandle(params[2], pType, &sec));
}

cell_t JsonArrayPushInt(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PCU::GetType("Json", pJansson)) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJSA* json;
    if((json = nJansson::PCU::ReadJsonHandle(params[1], pType, &sec, IsArray)) == nullptr)
        return 0;

    return json->push((long long)params[2]);
}

cell_t JsonArrayPushBool(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PCU::GetType("Json", pJansson)) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJSA* json;
    if((json = nJansson::PCU::ReadJsonHandle(params[1], pType, &sec, IsArray)) == nullptr)
        return 0;

    return json->push((bool)params[2]);
}

cell_t JsonArrayPushFloat(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PCU::GetType("Json", pJansson)) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJSA* json;
    if((json = nJansson::PCU::ReadJsonHandle(params[1], pType, &sec, IsArray)) == nullptr)
        return 0;

    return json->push(sp_ctof(params[2]));
}

cell_t JsonArrayPushString(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PCU::GetType("Json", pJansson)) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJSA* json;
    if((json = nJansson::PCU::ReadJsonHandle(params[1], pType, &sec, IsArray)) == nullptr)
        return 0;

    char* value;
    pContext->LocalToString(params[2], &value);

    return json->push(value);
}

cell_t JsonArrayPushInt64(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PCU::GetType("Json", pJansson)) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJSA* json;
    if((json = nJansson::PCU::ReadJsonHandle(params[1], pType, &sec, IsArray)) == nullptr)
        return 0;

    char* value;
    pContext->LocalToString(params[2], &value);

    char* end;
    long long num = std::strtoll(value, &end, 10);

    return ((*end) ? 0 : json->push(num));
}

cell_t JsonArrayGetType(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PCU::GetType("Json", pJansson)) == nullptr)
        return nJansson::jtInvalid;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJSA* json;
    if((json = nJansson::PCU::ReadJsonHandle(params[1], pType, &sec, IsArray)) == nullptr)
        return nJansson::jtInvalid;

    return json->type(params[2]);
}

// 1 - this
// 2 - another array obj
// 3 - freeAnotherObj
cell_t JsonArrayExtend(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PCU::GetType("Json", pJansson)) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJS* json;
    if((json = nJansson::PCU::ReadJsonHandle(params[1], pType, &sec, IsArray)) == nullptr)
        return 0;

    nJansson::IJS* buffer;
    if((buffer = nJansson::PCU::ReadJsonHandle(params[2], pType, &sec, IsArray)) == nullptr)
        return 0;

    if(!json->extend(buffer))
        return 0;

    if(params[3] == 1 && nJansson::PCU::FreeHandle(params[2], buffer, pType, &sec) != nullptr)
        pJansson->close((nJansson::IJson*) buffer);

    return 1;
}

cell_t JsonArrayRemove(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PCU::GetType("Json", pJansson)) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJSA* json;
    if((json = nJansson::PCU::ReadJsonHandle(params[1], pType, &sec, IsArray)) == nullptr)
        return 0;

    return json->remove(params[2]);
}

cell_t JsonArrayGetSize(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PCU::GetType("Json", pJansson)) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJS* json;
    if((json = nJansson::PCU::ReadJsonHandle(params[1], pType, &sec)) == nullptr)
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
        { "JsonArray.GetInt64", JsonArrayGetInt64 },

        {"JsonArray.Set",          JsonArraySetJson    },
        {"JsonArray.SetString",    JsonArraySetString  },
        {"JsonArray.SetBool",      JsonArraySetBool    },
        {"JsonArray.SetInt",       JsonArraySetInt     },
        {"JsonArray.SetFloat",     JsonArraySetFloat   },
        { "JsonArray.SetInt64", JsonArraySetInt64 },

        {"JsonArray.Push",          JsonArrayPushJson    },
        {"JsonArray.PushString",    JsonArrayPushString  },
        {"JsonArray.PushBool",      JsonArrayPushBool    },
        {"JsonArray.PushInt",       JsonArrayPushInt     },
        {"JsonArray.PushFloat",     JsonArrayPushFloat   },
        { "JsonArray.PushInt64", JsonArrayPushInt64 },

        {"JsonArray.GetType",      JsonArrayGetType    },
        {"JsonArray.Extend",       JsonArrayExtend     },
        {"JsonArray.Remove",       JsonArrayRemove     },
        {"JsonArray.Size.get",       JsonArrayGetSize     },
        {nullptr, nullptr}
};