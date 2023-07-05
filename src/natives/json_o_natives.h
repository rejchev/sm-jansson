#ifndef SM_JANSSON_JSON_O_NATIVES_H
#define SM_JANSSON_JSON_O_NATIVES_H

#include <src/utils/PluginContextUtils.h>
#include <extension.h>

extern cell_t JsonObjectGetJson(IPluginContext *pContext, const cell_t *params);
extern cell_t JsonObjectGetInt(IPluginContext *pContext, const cell_t *params);
extern cell_t JsonObjectGetBool(IPluginContext *pContext, const cell_t *params);
extern cell_t JsonObjectGetFloat(IPluginContext *pContext, const cell_t *params);
extern cell_t JsonObjectGetString(IPluginContext *pContext, const cell_t *params);

extern cell_t JsonObjectSetJson(IPluginContext *pContext, const cell_t *params);
extern cell_t JsonObjectSetInt(IPluginContext *pContext, const cell_t *params);
extern cell_t JsonObjectSetBool(IPluginContext *pContext, const cell_t *params);
extern cell_t JsonObjectSetFloat(IPluginContext *pContext, const cell_t *params);
extern cell_t JsonObjectSetString(IPluginContext *pContext, const cell_t *params);

extern cell_t JsonObjectGetType(IPluginContext *pContext, const cell_t *params);
extern cell_t JsonObjectHasKey(IPluginContext *pContext, const cell_t *params);
extern cell_t JsonObjectUpdate(IPluginContext *pContext, const cell_t *params);
extern cell_t JsonObjectKeys(IPluginContext *pContext, const cell_t *params);


extern const sp_nativeinfo_t JSON_OBJECT_NATIVES[];

#endif //SM_JANSSON_JSON_O_NATIVES_H
