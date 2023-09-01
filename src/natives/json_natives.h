#ifndef SM_JANSSON_JSON_NATIVES_H
#define SM_JANSSON_JSON_NATIVES_H

#include <ISourceMod.h>

extern cell_t JsonCreate(SourcePawn::IPluginContext *pContext, const cell_t *params);
extern cell_t JsonCreateFromFile(SourcePawn::IPluginContext *pContext, const cell_t *params);
extern cell_t JsonDump(SourcePawn::IPluginContext *pContext, const cell_t *params);
extern cell_t JsonDumpToFile(SourcePawn::IPluginContext *pContext, const cell_t *params);
extern cell_t JsonEqual(SourcePawn::IPluginContext *pContext, const cell_t *params);
extern cell_t JsonGetType(SourcePawn::IPluginContext *pContext, const cell_t *params);
extern cell_t JsonValidState(SourcePawn::IPluginContext *pContext, const cell_t *params);
extern cell_t JsonGetString(SourcePawn::IPluginContext *pContext, const cell_t *params);

extern cell_t JsonGetInt(SourcePawn::IPluginContext *pContext, const cell_t *params);
extern cell_t JsonGetIntEx(SourcePawn::IPluginContext *pContext, const cell_t *params);

extern cell_t JsonGetBool(SourcePawn::IPluginContext *pContext, const cell_t *params);
extern cell_t JsonGetBoolEx(SourcePawn::IPluginContext *pContext, const cell_t *params);

extern cell_t JsonGetFloat(SourcePawn::IPluginContext *pContext, const cell_t *params);
extern cell_t JsonGetFloatEx(SourcePawn::IPluginContext *pContext, const cell_t *params);

extern cell_t JsonGetInt64(SourcePawn::IPluginContext *pContext, const cell_t *params);
extern cell_t JsonClear(SourcePawn::IPluginContext *pContext, const cell_t *params);
extern cell_t JsonSize(SourcePawn::IPluginContext *pContext, const cell_t *params);
extern cell_t JsonSizeOf(SourcePawn::IPluginContext *pContext, const cell_t *params);
extern cell_t JsonFindFirst(SourcePawn::IPluginContext *pContext, const cell_t *params);


extern const sp_nativeinfo_t JSON_NATIVES[];

#endif //SM_JANSSON_JSON_NATIVES_H
