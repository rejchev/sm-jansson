#ifndef SM_JANSSON_JSON_A_NATIVES_H
#define SM_JANSSON_JSON_A_NATIVES_H

#include <ISourceMod.h>

extern cell_t JsonArrayGetJson(SourcePawn::IPluginContext *pContext, const cell_t *params);
extern cell_t JsonArrayGetInt(SourcePawn::IPluginContext *pContext, const cell_t *params);
extern cell_t JsonArrayGetBool(SourcePawn::IPluginContext *pContext, const cell_t *params);
extern cell_t JsonArrayGetFloat(SourcePawn::IPluginContext *pContext, const cell_t *params);
extern cell_t JsonArrayGetString(SourcePawn::IPluginContext *pContext, const cell_t *params);
extern cell_t JsonArrayGetInt64(SourcePawn::IPluginContext *pContext, const cell_t *params);

extern cell_t JsonArraySetJson(SourcePawn::IPluginContext *pContext, const cell_t *params);
extern cell_t JsonArraySetInt(SourcePawn::IPluginContext *pContext, const cell_t *params);
extern cell_t JsonArraySetBool(SourcePawn::IPluginContext *pContext, const cell_t *params);
extern cell_t JsonArraySetFloat(SourcePawn::IPluginContext *pContext, const cell_t *params);
extern cell_t JsonArraySetString(SourcePawn::IPluginContext *pContext, const cell_t *params);
extern cell_t JsonArraySetInt64(SourcePawn::IPluginContext *pContext, const cell_t *params);

extern cell_t JsonArrayPushJson(SourcePawn::IPluginContext *pContext, const cell_t *params);
extern cell_t JsonArrayPushInt(SourcePawn::IPluginContext *pContext, const cell_t *params);
extern cell_t JsonArrayPushBool(SourcePawn::IPluginContext *pContext, const cell_t *params);
extern cell_t JsonArrayPushFloat(SourcePawn::IPluginContext *pContext, const cell_t *params);
extern cell_t JsonArrayPushString(SourcePawn::IPluginContext *pContext, const cell_t *params);
extern cell_t JsonArrayPushInt64(SourcePawn::IPluginContext *pContext, const cell_t *params);

extern cell_t JsonArrayGetType(SourcePawn::IPluginContext *pContext, const cell_t *params);
extern cell_t JsonArrayExtend(SourcePawn::IPluginContext *pContext, const cell_t *params);
extern cell_t JsonArrayRemove(SourcePawn::IPluginContext *pContext, const cell_t *params);
extern cell_t JsonArrayGetSize(SourcePawn::IPluginContext *pContext, const cell_t *params);

extern const sp_nativeinfo_t JSON_ARRAY_NATIVES[];

#endif //SM_JANSSON_JSON_A_NATIVES_H
