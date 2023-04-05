#ifndef SM_JANSSON_JSON_I_NATIVES_H
#define SM_JANSSON_JSON_I_NATIVES_H

#include <PluginContextUtils.h>
#include <extension.h>

extern cell_t JsonObjectKeyIteratorNext(IPluginContext *pContext, const cell_t *params);

extern const sp_nativeinfo_t JSON_OBJECT_KEY_ITERATOR_NATIVES[];

#endif //SM_JANSSON_JSON_I_NATIVES_H
