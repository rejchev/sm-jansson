#ifndef SM_JANSSON_JSON_O_NATIVES_H
#define SM_JANSSON_JSON_O_NATIVES_H

#include <ISourceMod.h>

extern cell_t JsonObjectGetJson(SourcePawn::IPluginContext *pContext, const cell_t *params);
extern cell_t JsonObjectGetInt(SourcePawn::IPluginContext *pContext, const cell_t *params);
extern cell_t JsonObjectGetBool(SourcePawn::IPluginContext *pContext, const cell_t *params);
extern cell_t JsonObjectGetFloat(SourcePawn::IPluginContext *pContext, const cell_t *params);
extern cell_t JsonObjectGetString(SourcePawn::IPluginContext *pContext, const cell_t *params);
extern cell_t JsonObjectGetInt64(SourcePawn::IPluginContext *pContext, const cell_t *params);

extern cell_t JsonObjectSetJson(SourcePawn::IPluginContext *pContext, const cell_t *params);
extern cell_t JsonObjectSetInt(SourcePawn::IPluginContext *pContext, const cell_t *params);
extern cell_t JsonObjectSetBool(SourcePawn::IPluginContext *pContext, const cell_t *params);
extern cell_t JsonObjectSetFloat(SourcePawn::IPluginContext *pContext, const cell_t *params);
extern cell_t JsonObjectSetString(SourcePawn::IPluginContext *pContext, const cell_t *params);
extern cell_t JsonObjectSetInt64(SourcePawn::IPluginContext *pContext, const cell_t *params);

extern cell_t JsonObjectGetType(SourcePawn::IPluginContext *pContext, const cell_t *params);
extern cell_t JsonObjectHasKey(SourcePawn::IPluginContext *pContext, const cell_t *params);
extern cell_t JsonObjectRemoveKey(SourcePawn::IPluginContext *pContext, const cell_t *params);
extern cell_t JsonObjectUpdate(SourcePawn::IPluginContext *pContext, const cell_t *params);
extern cell_t JsonObjectKeys(SourcePawn::IPluginContext *pContext, const cell_t *params);
extern cell_t JsonObjectSize(SourcePawn::IPluginContext *pContext, const cell_t *params);


extern const sp_nativeinfo_t JSON_OBJECT_NATIVES[];

#endif //SM_JANSSON_JSON_O_NATIVES_H
