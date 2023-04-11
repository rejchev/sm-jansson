#ifndef SM_JANSSON_JSON_A_NATIVES_H
#define SM_JANSSON_JSON_A_NATIVES_H

#include <PluginContextUtils.h>
#include <extension.h>

extern cell_t JsonArrayGetJson(IPluginContext *pContext, const cell_t *params);
extern cell_t JsonArrayGetInt(IPluginContext *pContext, const cell_t *params);
extern cell_t JsonArrayGetBool(IPluginContext *pContext, const cell_t *params);
extern cell_t JsonArrayGetFloat(IPluginContext *pContext, const cell_t *params);
extern cell_t JsonArrayGetString(IPluginContext *pContext, const cell_t *params);

extern cell_t JsonArraySetJson(IPluginContext *pContext, const cell_t *params);
extern cell_t JsonArraySetInt(IPluginContext *pContext, const cell_t *params);
extern cell_t JsonArraySetBool(IPluginContext *pContext, const cell_t *params);
extern cell_t JsonArraySetFloat(IPluginContext *pContext, const cell_t *params);
extern cell_t JsonArraySetString(IPluginContext *pContext, const cell_t *params);

extern cell_t JsonArrayPushJson(IPluginContext *pContext, const cell_t *params);
extern cell_t JsonArrayPushInt(IPluginContext *pContext, const cell_t *params);
extern cell_t JsonArrayPushBool(IPluginContext *pContext, const cell_t *params);
extern cell_t JsonArrayPushFloat(IPluginContext *pContext, const cell_t *params);
extern cell_t JsonArrayPushString(IPluginContext *pContext, const cell_t *params);

extern cell_t JsonArrayGetType(IPluginContext *pContext, const cell_t *params);
extern cell_t JsonArrayExtend(IPluginContext *pContext, const cell_t *params);
extern cell_t JsonArrayRemove(IPluginContext *pContext, const cell_t *params);

extern const sp_nativeinfo_t JSON_ARRAY_NATIVES[];

#endif //SM_JANSSON_JSON_A_NATIVES_H
