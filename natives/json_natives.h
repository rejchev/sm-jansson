#ifndef SM_JANSSON_JSON_NATIVES_H
#define SM_JANSSON_JSON_NATIVES_H

#include <src/utils/PluginContextUtils.h>
#include <extension.h>

extern cell_t JsonCreate(IPluginContext *pContext, const cell_t *params);
extern cell_t JsonCreateFromFile(IPluginContext *pContext, const cell_t *params);
extern cell_t JsonDump(IPluginContext *pContext, const cell_t *params);
extern cell_t JsonDumpToFile(IPluginContext *pContext, const cell_t *params);
extern cell_t JsonEqual(IPluginContext *pContext, const cell_t *params);
extern cell_t JsonGetType(IPluginContext *pContext, const cell_t *params);
extern cell_t JsonGetError(IPluginContext *pContext, const cell_t *params);
extern cell_t JsonGetString(IPluginContext *pContext, const cell_t *params);
extern cell_t JsonGetInt(IPluginContext *pContext, const cell_t *params);
extern cell_t JsonGetBool(IPluginContext *pContext, const cell_t *params);
extern cell_t JsonGetFloat(IPluginContext *pContext, const cell_t *params);
extern cell_t JsonClear(IPluginContext *pContext, const cell_t *params);
extern cell_t JsonSize(IPluginContext *pContext, const cell_t *params);


extern const sp_nativeinfo_t JSON_NATIVES[];

#endif //SM_JANSSON_JSON_NATIVES_H
