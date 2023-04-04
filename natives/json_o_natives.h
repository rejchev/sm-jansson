#ifndef SM_JANSSON_JSON_O_NATIVES_H
#define SM_JANSSON_JSON_O_NATIVES_H

#include <extension.h>

#include "../src/json_object.h"

static cell_t JsonObjectGetJson(IPluginContext *pContext, const cell_t *params);
static cell_t JsonObjectGetInt(IPluginContext *pContext, const cell_t *params);
static cell_t JsonObjectGetBool(IPluginContext *pContext, const cell_t *params);
static cell_t JsonObjectGetFloat(IPluginContext *pContext, const cell_t *params);
static cell_t JsonObjectGetString(IPluginContext *pContext, const cell_t *params);

static cell_t JsonObjectSetJson(IPluginContext *pContext, const cell_t *params);
static cell_t JsonObjectSetInt(IPluginContext *pContext, const cell_t *params);
static cell_t JsonObjectSetBool(IPluginContext *pContext, const cell_t *params);
static cell_t JsonObjectSetFloat(IPluginContext *pContext, const cell_t *params);
static cell_t JsonObjectSetString(IPluginContext *pContext, const cell_t *params);

static cell_t JsonObjectGetType(IPluginContext *pContext, const cell_t *params);
static cell_t JsonObjectHasKey(IPluginContext *pContext, const cell_t *params);
static cell_t JsonObjectUpdate(IPluginContext *pContext, const cell_t *params);
static cell_t JsonObjectClear(IPluginContext *pContext, const cell_t *params);
static cell_t JsonObjectKeys(IPluginContext *pContext, const cell_t *params);
static cell_t JsonObjectGetKeysCount(IPluginContext *pContext, const cell_t *params);


const sp_nativeinfo_t JSON_OBJECT_NATIVES[] =
{
        {"JsonObject.Get",          JsonObjectGetJson    },
        {"JsonObject.GetString",    JsonObjectGetString  },
        {"JsonObject.GetBool",      JsonObjectGetBool    },
        {"JsonObject.GetInt",       JsonObjectGetInt     },
        {"JsonObject.GetFloat",     JsonObjectGetFloat   },
        {"JsonObject.Set",          JsonObjectSetJson    },
        {"JsonObject.SetString",    JsonObjectSetString  },
        {"JsonObject.SetBool",      JsonObjectSetBool    },
        {"JsonObject.SetInt",       JsonObjectSetInt     },
        {"JsonObject.SetFloat",     JsonObjectSetFloat   },
        {"JsonObject.GetType",      JsonObjectGetType    },
        {"JsonObject.HasKey",       JsonObjectHasKey     },
        {"JsonObject.Update",       JsonObjectUpdate     },
        {"JsonObject.Clear",        JsonObjectClear      },
        {"JsonObject.Keys",         JsonObjectKeys       },
        {"JsonObject.KeysCount.get",JsonObjectGetKeysCount      },
        {NULL,                      NULL                  }
};

#endif //SM_JANSSON_JSON_O_NATIVES_H
