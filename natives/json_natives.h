#ifndef SM_JANSSON_JSON_NATIVES_H
#define SM_JANSSON_JSON_NATIVES_H

#include <extension.h>

#include "../extension.h"

static nJansson::IHandleType* GetVerifiedHandleType(IPluginContext *pContext, const cell_t *params, const char* name);

static nJansson::IJson* JsonCreateGen(IPluginContext *pContext,
                                      const cell_t *params,
                                      nJansson::IJson* (nJansson::IJansson::* funcCreate) (const char* str, const size_t& flags),
                                      nJansson::IHandleType* pType);

static nJansson::IJson* JsonCreateGen(IPluginContext *pContext,
                             const cell_t *params,
                             json_t* (*funcCreate) (const char*, size_t, json_error_t*));

static Handle_t CreateHandle(IPluginContext *pContext,
                             const cell_t *params,
                             nJansson::IHandleType*,
                             nJansson::IJson*);

static cell_t JsonCreate(IPluginContext *pContext, const cell_t *params);
static cell_t JsonCreateFromFile(IPluginContext *pContext, const cell_t *params);
static cell_t JsonDump(IPluginContext *pContext, const cell_t *params);
static cell_t JsonDumpToFile(IPluginContext *pContext, const cell_t *params);
static cell_t JsonEqual(IPluginContext *pContext, const cell_t *params);
static cell_t JsonGetType(IPluginContext *pContext, const cell_t *params);
static cell_t JsonGetError(IPluginContext *pContext, const cell_t *params);
static cell_t JsonGetString(IPluginContext *pContext, const cell_t *params);
static cell_t JsonGetInt(IPluginContext *pContext, const cell_t *params);
static cell_t JsonGetBool(IPluginContext *pContext, const cell_t *params);
static cell_t JsonGetFloat(IPluginContext *pContext, const cell_t *params);


const sp_nativeinfo_t JSON_NATIVES[] =
{
        {"Json.Json",           JsonCreate},
        {"Json.JsonF",          JsonCreateFromFile},
        {"Json.ToString",       JsonDump},
        {"Json.ToFile",         JsonDumpToFile},
        {"Json.Equal",          JsonEqual},
        {"Json.GetInt",         JsonGetInt},
        {"Json.GetString",      JsonGetString},
        {"Json.GetBool",        JsonGetBool},
        {"Json.GetFloat",       JsonGetFloat},
        {"Json.Type.get",       JsonGetType},
        {"Json.Error.get",      JsonGetError},
        {NULL, NULL}
};

#endif //SM_JANSSON_JSON_NATIVES_H
