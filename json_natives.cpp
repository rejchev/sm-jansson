/**
 * vim: set ts=4 :
 * =============================================================================
 * SourceMod REST in Pawn Extension
 * Copyright 2017-2020 Erik Minekus
 * =============================================================================
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "extension.h"

static json_t *GetJSONFromHandle(IPluginContext *pContext, Handle_t hndl)
{
    HandleError err;
    json_t *object = NULL;
    HandleSecurity sec(pContext->GetIdentity(), myself->GetIdentity());
    if((err = handlesys->ReadHandle(hndl, htJSON, &sec, (void **)&object)) == HandleError_None)
        pContext->ThrowNativeError(
            "JSON(ReadHandle: %d): Invalid (%x) handle", err, hndl);

    return err != HandleError_None ? NULL : object;
}

static Handle_t CreateJSONHandle(IPluginContext *pContext, json_t *object) 
{
    Handle_t hndl;
    HandleError *err = NULL;
    if((hndl = handlesys->CreateHandle(htJSON, object, pContext->GetIdentity(), myself->GetIdentity(), err)) == BAD_HANDLE 
        || err != NULL) 
    {
        json_decref(object);
        pContext->ThrowNativeError(
            "JSON(CreateHandle: %d): Could not create handle.", *err);
    }

    if(err && hndl != BAD_HANDLE)
        hndl = BAD_HANDLE;
        
    return hndl;
}

static Handle_t CreateJSONHandleEx(IPluginContext *pContext, json_t *object) 
{
    Handle_t hndl;
    HandleError *err = NULL;	
    HandleSecurity sec(pContext->GetIdentity(), myself->GetIdentity());
    if((hndl = handlesys->CreateHandleEx(htJSON, object, &sec, NULL, err)) == BAD_HANDLE 
        || err != NULL) 
    {
        pContext->ThrowNativeError(
            "JSON(CreateHandleEx: %d): Could not create handle.", *err);
    }

    // ?
    if(err && hndl != BAD_HANDLE)
        hndl = BAD_HANDLE;

    if(hndl != BAD_HANDLE)
        json_incref(object);
    
    return hndl;
}

static inline json_t *ObjectGetValue(IPluginContext *pContext, json_t *o, const char *k) 
{
    json_t *v;
    if ((v = json_object_get(o, k)) == NULL)
        pContext->ThrowNativeError("JSON(GetValue): Key '%s' is not exists", k);

    return v;
}

static inline json_t *ArrayGetValue(IPluginContext *pContext, json_t *o, const int i)
{
    json_t *v;
    if ((v = json_array_get(o, i)) == NULL)
        pContext->ThrowNativeError("JSON(GetValue): Could not retrieve value at index %d", i);

    return v;
}

// JSON.JSON(const char[], int = 0)
static cell_t JSONCreate(IPluginContext *pContext, const cell_t *params)
{
    char *buffer;
    pContext->LocalToString(params[1], &buffer);

    size_t flags = (size_t) params[2];

    json_t *object;
    json_error_t error;
    if((object = json_loads(buffer, flags, &error)) == NULL) {
        pContext->ThrowNativeError("JSON(constructor: %d): %s [l: %d , c: %d]", 
                                        json_error_code(&error), error.text, error.line, error.column);
        return BAD_HANDLE;
    }

    return CreateJSONHandle(pContext, object);
}

// JSON.JSONF(const char[], int = 0)
static cell_t JSONCreateF(IPluginContext *pContext, const cell_t *params)
{
    char *path;
    pContext->LocalToString(params[1], &path);

    char realpath[PLATFORM_MAX_PATH];
    smutils->BuildPath(Path_Game, realpath, sizeof(realpath), "%s", path);

    size_t flags = (size_t)params[2];

    json_t *object;
    json_error_t error;
    if((object = json_load_file(realpath, flags, &error)) == NULL) {
        pContext->ThrowNativeError("JSONF(constructor: %d): %s [l: %d , c: %d]", 
                                        json_error_code(&error), error.text, error.line, error.column);
        return BAD_HANDLE;
    }

    return CreateJSONHandle(pContext, object);
}

// JSON.ToString(char[], int, int = 0)
static cell_t JSONToString(IPluginContext *pContext, const cell_t *params)
{
    json_t *object;
    if((object = GetJSONFromHandle(pContext, params[1])) == NULL)
        return 0;

    char *result;
    if ((result = json_dumps(object, (size_t) params[4])) == NULL)
        return 0;
    
    pContext->StringToLocalUTF8(params[2], params[3], result, NULL);
    free(result);

    return 1;
}

// JSON.ToFile(const char[], int = 0)
static cell_t JSONToFile(IPluginContext *pContext, const cell_t *params)
{
    json_t *object;
    if((object = GetJSONFromHandle(pContext, params[1])) == NULL)
        return 0;

    char *path;
    pContext->LocalToString(params[2], &path);

    char realpath[PLATFORM_MAX_PATH];
    smutils->BuildPath(Path_Game, realpath, sizeof(realpath), "%s", path);

    size_t flags = (size_t)params[3];

    return (json_dump_file(object, realpath, flags) == 0);
}

// JSON.Type.get()
static cell_t JSONGetType(IPluginContext *pContext, const cell_t *params)
{
    json_t *object;
    if((object = GetJSONFromHandle(pContext, params[1])) == NULL)
        return 0;

    return json_typeof(object);
}

// JSONObject.Get(const char[])
static cell_t ObjectGet(IPluginContext *pContext, const cell_t *params)
{
    json_t *object;
    if((object = GetJSONFromHandle(pContext, params[1])) == NULL)
        return BAD_HANDLE;
    
    char *key;	
    pContext->LocalToString(params[2], &key);

    json_t *value;
    if((value = ObjectGetValue(pContext, object, key)) == NULL)
        return BAD_HANDLE;

    return CreateJSONHandleEx(pContext, value);
}

// JSONObject.GetBool(const char[])
static cell_t ObjectGetBool(IPluginContext *pContext, const cell_t *params)
{
    json_t *object;
    if((object = GetJSONFromHandle(pContext, params[1])) == NULL)
        return 0;
    
    char *key;
    pContext->LocalToString(params[2], &key);

    json_t *value = ObjectGetValue(pContext, object, key);
    return (value != NULL) 
                ? json_boolean_value(value) 
                : 0;
}

// JSONObject.GetFloat(const char[])
static cell_t ObjectGetFloat(IPluginContext *pContext, const cell_t *params)
{
    json_t *object;
    if((object = GetJSONFromHandle(pContext, params[1])) == NULL)
        return 0;
    
    char *key;
    pContext->LocalToString(params[2], &key);

    json_t *value = ObjectGetValue(pContext, object, key);
    return (value != NULL) 
                ? sp_ftoc(static_cast<float>(json_real_value(value))) 
                : 0;
}

// JSONObject.GetInt(const char[])
static cell_t ObjectGetInt(IPluginContext *pContext, const cell_t *params)
{
    json_t *object;
    if((object = GetJSONFromHandle(pContext, params[1])) == NULL)
        return 0;
    
    char *key;
    pContext->LocalToString(params[2], &key);

    json_t *value = ObjectGetValue(pContext, object, key);
    return (value != NULL) 
                ? static_cast<cell_t>(json_integer_value(value)) 
                : 0;
}

// JSONObject.GetInt64(const char[], char[], int)
static cell_t ObjectGetInt64(IPluginContext *pContext, const cell_t *params)
{
    json_t *object;
    if((object = GetJSONFromHandle(pContext, params[1])) == NULL)
        return 0;
    
    char *key;
    pContext->LocalToString(params[2], &key);

    json_t *value;
    if((value = ObjectGetValue(pContext, object, key)) == NULL)
        return 0;

    char result[20];
    snprintf(result, sizeof(result), "%" JSON_INTEGER_FORMAT, json_integer_value(value));
    pContext->StringToLocalUTF8(params[3], params[4], result, NULL);

    return 1;
}

// JSONObject.GetString(const char[], char[], int)
static cell_t ObjectGetString(IPluginContext *pContext, const cell_t *params)
{
    json_t *object;
    if((object = GetJSONFromHandle(pContext, params[1])) == NULL)
        return 0;
    
    char *key;
    pContext->LocalToString(params[2], &key);

    json_t *value;
    if((value = ObjectGetValue(pContext, object, key)) == NULL)
        return 0;

    const char *result;
    if((result = json_string_value(value)) != NULL)
        pContext->StringToLocalUTF8(params[3], params[4], result, NULL);

    return (result != NULL);
}

// JSONObject.GetType(const char[])
static cell_t ObjectGetType(IPluginContext *pContext, const cell_t *params)
{
    json_t *object;
    if((object = GetJSONFromHandle(pContext, params[1])) == NULL)
        return 0;

    char *key;	
    pContext->LocalToString(params[2], &key);

    json_t *value;
    if((value = ObjectGetValue(pContext, object, key)) == NULL)
        return 0;

    return json_typeof(value);
}

// JSONObject.IsKeyValid(const char[])
static cell_t IsObjectKeyValid(IPluginContext *pContext, const cell_t *params)
{
    json_t *object;
    if((object = GetJSONFromHandle(pContext, params[1])) == NULL)
        return 0;
    
    char *key;
    pContext->LocalToString(params[2], &key);

    return json_object_get(object, key) != NULL;
}

// JSONObject.Set(const char[], JSON)
static cell_t ObjectSet(IPluginContext *pContext, const cell_t *params)
{
    json_t *object;
    if((object = GetJSONFromHandle(pContext, params[1])) == NULL)
        return 0;

    char *key;
    pContext->LocalToString(params[2], &key);

    json_t *value;
    value = (((Handle_t) params[3]) == BAD_HANDLE)
                    ? json_null()
                    : GetJSONFromHandle(pContext, params[3]);

    return (value != NULL) 
                ?  (json_typeof(value) != JSON_NULL)
                        ? (json_object_set(object, key, value) == 0)
                        : (json_object_set_new(object, key, value) == 0)
                : 0;
}

// JSONObject.SetBool(const char[], bool)
static cell_t ObjectSetBool(IPluginContext *pContext, const cell_t *params)
{
    json_t *object;
    if((object = GetJSONFromHandle(pContext, params[1])) == NULL)
        return 0;

    char *key;
    pContext->LocalToString(params[2], &key);

    return (json_object_set_new(object, key, (json_boolean(params[3]))) == 0);
}

// JSONObject.SetFloat(const char[], float)
static cell_t ObjectSetFloat(IPluginContext *pContext, const cell_t *params)
{
    json_t *object;
    if((object = GetJSONFromHandle(pContext, params[1])) == NULL)
        return 0;

    char *key;
    pContext->LocalToString(params[2], &key);

    return (json_object_set_new(object, key, (json_real(sp_ctof(params[3])))) == 0);
}

// JSONObject.SetInt(const char[], int)
static cell_t ObjectSetInt(IPluginContext *pContext, const cell_t *params)
{
    json_t *object;
    if((object = GetJSONFromHandle(pContext, params[1])) == NULL)
        return 0;

    char *key;
    pContext->LocalToString(params[2], &key);

    return (json_object_set_new(object, key, (json_integer(params[3]))) == 0);
}

// JSONObject.SetInt64(cosnt char[], const char[])
static cell_t ObjectSetInt64(IPluginContext *pContext, const cell_t *params)
{
    json_t *object;
    if((object = GetJSONFromHandle(pContext, params[1])) == NULL)
        return 0;

    char *key;
    pContext->LocalToString(params[2], &key);

    char *val;
    pContext->LocalToString(params[3], &val);

    return (json_object_set_new(object, key, (json_integer(strtoll(val, NULL, 10)))) == 0);
}

// JSONObject.SetString(const char[], const char[])
static cell_t ObjectSetString(IPluginContext *pContext, const cell_t *params)
{
    json_t *object;
    if((object = GetJSONFromHandle(pContext, params[1])) == NULL)
        return 0;

    char *key;
    pContext->LocalToString(params[2], &key);

    char *val;
    pContext->LocalToString(params[3], &val);

    return (json_object_set_new(object, key, (json_string(val))) == 0);
}

// JSONObject.Remove(const char[])
static cell_t ObjectRemoveKey(IPluginContext *pContext, const cell_t *params)
{
    json_t *object;
    if((object = GetJSONFromHandle(pContext, params[1])) == NULL)
        return 0;

    char *key;
    pContext->LocalToString(params[2], &key);

    return (json_object_del(object, key) == 0);
}

// JSONObject.Clear()
static cell_t ObjectClear(IPluginContext *pContext, const cell_t *params)
{
    json_t *object;
    if((object = GetJSONFromHandle(pContext, params[1])) == NULL)
        return 0;

    return (json_object_clear(object) == 0);
}

// JSONObject.Size.get()
static cell_t ObjectSize(IPluginContext *pContext, const cell_t *params)
{
    json_t *o;
    return ((o = GetJSONFromHandle(pContext, params[1])) != NULL) 
                ? json_object_size(o) : 0;
}

// JSONObject.Keys()
static cell_t ObjectKeys(IPluginContext *pContext, const cell_t *params)
{
    HandleSecurity sec(pContext->GetIdentity(), myself->GetIdentity());

    json_t *object;
    if((object = GetJSONFromHandle(pContext, params[1])) == NULL)
        return BAD_HANDLE;

    struct JSONObjectKeys *keys = new struct JSONObjectKeys(object);

    Handle_t hndlKeys;
    HandleError *err = NULL;
    if ((hndlKeys = handlesys->CreateHandleEx(htJSONObjectKeys, keys, &sec, NULL, err)) == BAD_HANDLE
            || err != NULL)
    {
        pContext->ThrowNativeError("JSON(Keys: %d): Could not create iterator handle.", *err);
        delete keys;
        return BAD_HANDLE;
    }

    return hndlKeys;
}

// JSONKeys.Next(char[], int)
static cell_t ReadObjectKey(IPluginContext *pContext, const cell_t *params)
{
    HandleError err;
    HandleSecurity sec(pContext->GetIdentity(), myself->GetIdentity());

    struct JSONObjectKeys *keys;
    Handle_t hndlKeys = static_cast<Handle_t>(params[1]);
    if ((err=handlesys->ReadHandle(hndlKeys, htJSONObjectKeys, &sec, (void **)&keys)) != HandleError_None)
        return pContext->ThrowNativeError("JSON(Keys): Invalid object keys handle %x (error %d)", hndlKeys, err);

    const char *key;
    if ((key = keys->GetKey()) != NULL)
        return 0;

    pContext->StringToLocalUTF8(params[2], params[3], key, NULL);
    keys->Next();

    return 1;
}

// JSONArray.Get(const int)
static cell_t ArrayGet(IPluginContext *pContext, const cell_t *params)
{
    json_t *object;
    if((object = GetJSONFromHandle(pContext, params[1])) == NULL)
        return BAD_HANDLE;

    json_t *value;
    if((value = ArrayGetValue(pContext,object, params[2])) == NULL)
        return BAD_HANDLE;

    return CreateJSONHandleEx(pContext, value);
}

// JSONArray.GetBool(const int)
static cell_t ArrayGetBool(IPluginContext *pContext, const cell_t *params)
{
    json_t *object;
    if((object = GetJSONFromHandle(pContext, params[1])) == NULL)
        return 0;

    json_t *value;
    if((value = ArrayGetValue(pContext,object, params[2])) == NULL)
        return 0;

    return json_boolean_value(value);
}

// JSONArray.GetFloat(const int)
static cell_t ArrayGetFloat(IPluginContext *pContext, const cell_t *params)
{
    json_t *object;
    if((object = GetJSONFromHandle(pContext, params[1])) == NULL)
        return 0;

    json_t *value;
    if((value = ArrayGetValue(pContext,object, params[2])) == NULL)
        return 0;

    return sp_ftoc(static_cast<float>(json_real_value(value)));
}

// JSONArray.GetInt(const int)
static cell_t ArrayGetInt(IPluginContext *pContext, const cell_t *params)
{
    json_t *object;
    if((object = GetJSONFromHandle(pContext, params[1])) == NULL)
        return 0;

    json_t *value;
    if((value = ArrayGetValue(pContext,object, params[2])) == NULL)
        return 0;

    return static_cast<cell_t>(json_integer_value(value));
}

// JSONArray.GetInt64(const int)
static cell_t ArrayGetInt64(IPluginContext *pContext, const cell_t *params)
{
    json_t *object;
    if((object = GetJSONFromHandle(pContext, params[1])) == NULL)
        return 0;

    json_t *value;
    if((value = ArrayGetValue(pContext,object, params[2])) == NULL)
        return 0;

    char result[20];
    snprintf(result, sizeof(result), "%" JSON_INTEGER_FORMAT, json_integer_value(value));
    pContext->StringToLocalUTF8(params[3], params[4], result, NULL);

    return 1;
}

// JSONArray.GetString(const int)
static cell_t ArrayGetString(IPluginContext *pContext, const cell_t *params)
{
    json_t *object;
    if((object = GetJSONFromHandle(pContext, params[1])) == NULL)
        return 0;

    json_t *value;
    if((value = ArrayGetValue(pContext,object, params[2])) == NULL)
        return 0;

    const char *result;
    if ((result = json_string_value(value)) == NULL)
        return 0;

    pContext->StringToLocalUTF8(params[3], params[4], result, NULL);

    return 1;
}

// JSONArray.GetType(const int)
static cell_t ArrayGetType(IPluginContext *pContext, const cell_t *params)
{
    json_t *object;
    if((object = GetJSONFromHandle(pContext, params[1])) == NULL)
        return 0;

    json_t *value;
    if((value = ArrayGetValue(pContext,object, params[2])) == NULL)
        return BAD_HANDLE;

    return json_typeof(value);
}

// JSONArray.Set(const int, JSON)
static cell_t ArraySet(IPluginContext *pContext, const cell_t *params)
{
    json_t *object;
    if((object = GetJSONFromHandle(pContext, params[1])) == NULL)
        return 0;

    json_t *value;
    value = (((Handle_t) params[3]) == BAD_HANDLE)
                    ? json_null()
                    : GetJSONFromHandle(pContext, params[3]);

    return (value != NULL) 
                ?  (json_typeof(value) != JSON_NULL)
                        ? (json_array_set(object, params[2], value) == 0)
                        : (json_array_set_new(object, params[2], value) == 0)
                : 0;
}

// JSONArray.SetBool(const int, bool)
static cell_t ArraySetBool(IPluginContext *pContext, const cell_t *params)
{
    json_t *object;
    if((object = GetJSONFromHandle(pContext, params[1])) == NULL)
        return 0;

    return (json_array_set_new(object, params[2], (json_boolean(params[3]))) == 0);
}

// JSONArray.SetFloat(const int, float)
static cell_t ArraySetFloat(IPluginContext *pContext, const cell_t *params)
{
    json_t *object;
    if((object = GetJSONFromHandle(pContext, params[1])) == NULL)
        return 0;

    return (json_array_set_new(object, params[2], (json_real(sp_ctof(params[3])))) == 0);
}

// JSONArray.SetInt(const int, int)
static cell_t ArraySetInt(IPluginContext *pContext, const cell_t *params)
{
    json_t *object;
    if((object = GetJSONFromHandle(pContext, params[1])) == NULL)
        return 0;

    return (json_array_set_new(object, params[2], (json_integer(params[3]))) == 0);
}

// JSONArray.SetInt64(const int, const char[])
static cell_t ArraySetInt64(IPluginContext *pContext, const cell_t *params)
{
    json_t *object;
    if((object = GetJSONFromHandle(pContext, params[1])) == NULL)
        return 0;

    char *val;
    pContext->LocalToString(params[3], &val);

    return (json_array_set_new(
                object, params[2], (json_integer(json_strtoint(val, NULL, 10)))) == 0);
}

// JSONArray.SetString(const int, const char[])
static cell_t ArraySetString(IPluginContext *pContext, const cell_t *params)
{
    json_t *object;
    if((object = GetJSONFromHandle(pContext, params[1])) == NULL)
        return 0;

    char *val;
    pContext->LocalToString(params[3], &val);

    return (json_array_set_new(object, params[2], (json_string(val))) == 0);
}

// JSONArray.Push(JSON)
static cell_t ArrayPush(IPluginContext *pContext, const cell_t *params)
{
    json_t *object;
    if((object = GetJSONFromHandle(pContext, params[1])) == NULL)
        return 0;

    json_t *value;
    value = (((Handle_t) params[2]) == BAD_HANDLE)
                    ? json_null()
                    : GetJSONFromHandle(pContext, params[2]);

    return (value != NULL) 
                ?  (json_typeof(value) != JSON_NULL)
                        ? (json_array_append(object, value) == 0)
                        : (json_array_append_new(object, value) == 0)
                : 0;
}

// JSONArray.PushBool(bool)
static cell_t ArrayPushBool(IPluginContext *pContext, const cell_t *params)
{
    json_t *object;
    if((object = GetJSONFromHandle(pContext, params[1])) == NULL)
        return 0;

    return (json_array_append_new(object, (json_boolean(params[2]))) == 0);
}

// JSONArray.PushFloat(float)
static cell_t ArrayPushFloat(IPluginContext *pContext, const cell_t *params)
{
    json_t *object;
    if((object = GetJSONFromHandle(pContext, params[1])) == NULL)
        return 0;

    return (json_array_append_new(object, (json_real(sp_ctof(params[2])))) == 0);
}

// JSONArray.PushInt(int)
static cell_t ArrayPushInt(IPluginContext *pContext, const cell_t *params)
{
    json_t *object;
    if((object = GetJSONFromHandle(pContext, params[1])) == NULL)
        return 0;

    return (json_array_append_new(object, (json_integer(params[2]))) == 0);
}

// JSONArray.PushInt64(const char[])
static cell_t ArrayPushInt64(IPluginContext *pContext, const cell_t *params)
{
    json_t *object;
    if((object = GetJSONFromHandle(pContext, params[1])) == NULL)
        return 0;

    char *val;
    pContext->LocalToString(params[2], &val);

    return (json_array_append_new(object, (json_integer(json_strtoint(val, NULL, 10)))) == 0);
}

// JSONArray.PushString(const char[])
static cell_t ArrayPushString(IPluginContext *pContext, const cell_t *params)
{
    json_t *object;
    if((object = GetJSONFromHandle(pContext, params[1])) == NULL)
        return 0;

    char *val;
    pContext->LocalToString(params[2], &val);

    return (json_array_append_new(object, (json_string(val))) == 0);
}

// JSONArray.Remove(const int)
static cell_t ArrayRemove(IPluginContext *pContext, const cell_t *params)
{
    json_t *object;
    if((object = GetJSONFromHandle(pContext, params[1])) == NULL)
        return 0;
        
    return (json_array_remove(object, params[2]) == 0);
}

// JSONArray.Clear()
static cell_t ArrayClear(IPluginContext *pContext, const cell_t *params)
{
    json_t *object;
    if((object = GetJSONFromHandle(pContext, params[1])) == NULL)
        return 0;

    return (json_array_clear(object) == 0);
}

// JSONArray.Size.get()
static cell_t ArraySize(IPluginContext *pContext, const cell_t *params)
{
    json_t *object;
    if((object = GetJSONFromHandle(pContext, params[1])) == NULL)
        return 0;

    return json_array_size(object);
}


const sp_nativeinfo_t json_natives[] =
{
    {"JSON.JSON", 						JSONCreate},
    {"JSON.JSONF", 						JSONCreateF},
    {"JSON.ToString",					JSONToString},
    {"JSON.ToFile",						JSONToFile},
    {"JSON.Type.get",					JSONGetType},

    {"JSONObject.Get",					ObjectGet},
    {"JSONObject.GetBool",				ObjectGetBool},
    {"JSONObject.GetFloat",				ObjectGetFloat},
    {"JSONObject.GetInt",				ObjectGetInt},
    {"JSONObject.GetInt64",				ObjectGetInt64},
    {"JSONObject.GetString",			ObjectGetString},
    {"JSONObject.GetType",				ObjectGetType},
    {"JSONObject.Set",					ObjectSet},
    {"JSONObject.SetBool",				ObjectSetBool},
    {"JSONObject.SetFloat",				ObjectSetFloat},
    {"JSONObject.SetInt",				ObjectSetInt},
    {"JSONObject.SetInt64",				ObjectSetInt64},
    {"JSONObject.SetString",			ObjectSetString},
    {"JSONObject.HasKey",				IsObjectKeyValid},
    {"JSONObject.Remove",				ObjectRemoveKey},
    {"JSONObject.Clear",				ObjectClear},
    {"JSONObject.Size.get",				ObjectSize},
    
    {"JSONObject.Keys",					ObjectKeys},
    {"JSONKeys.Next",			        ReadObjectKey},

    {"JSONArray.Get",					ArrayGet},
    {"JSONArray.GetBool",				ArrayGetBool},
    {"JSONArray.GetFloat",				ArrayGetFloat},
    {"JSONArray.GetInt",				ArrayGetInt},
    {"JSONArray.GetInt64",				ArrayGetInt64},
    {"JSONArray.GetString",				ArrayGetString},
    {"JSONArray.GetType",				ArrayGetType},
    {"JSONArray.Set",					ArraySet},
    {"JSONArray.SetBool",				ArraySetBool},
    {"JSONArray.SetFloat",				ArraySetFloat},
    {"JSONArray.SetInt",				ArraySetInt},
    {"JSONArray.SetInt64",				ArraySetInt64},
    {"JSONArray.SetString",				ArraySetString},
    {"JSONArray.Push",					ArrayPush},
    {"JSONArray.PushBool",				ArrayPushBool},
    {"JSONArray.PushFloat",				ArrayPushFloat},
    {"JSONArray.PushInt",				ArrayPushInt},
    {"JSONArray.PushInt64",				ArrayPushInt64},
    {"JSONArray.PushString",			ArrayPushString},
    {"JSONArray.Remove",				ArrayRemove},
    {"JSONArray.Clear",					ArrayClear},
    {"JSONArray.Length.get",			ArraySize},

    {NULL,								NULL}
};
