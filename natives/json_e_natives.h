#ifndef SM_JANSSON_JSON_E_NATIVES_H
#define SM_JANSSON_JSON_E_NATIVES_H

#include <PluginContextUtils.h>
#include "../extension.h"

extern cell_t JsonErrorCode(IPluginContext *pContext, const cell_t *params);
extern cell_t JsonErrorText(IPluginContext *pContext, const cell_t *params);
extern cell_t JsonErrorSource(IPluginContext *pContext, const cell_t *params);
extern cell_t JsonErrorLine(IPluginContext *pContext, const cell_t *params);
extern cell_t JsonErrorColumn(IPluginContext *pContext, const cell_t *params);
extern cell_t JsonErrorNull(IPluginContext *pContext, const cell_t *params);

extern const sp_nativeinfo_t JSON_ERROR_NATIVES[];

#endif //SM_JANSSON_JSON_E_NATIVES_H
