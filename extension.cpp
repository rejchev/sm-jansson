#include <src/jansson.h>
#include <src/natives.h>

#include "extension.h"

CJanssonExtension g_JanssonExtension;

nJansson::IJansson* pJansson;

SMEXT_LINK(&g_JanssonExtension)

#define REGISTER_TYPE(manager, type, dispatch, ident) manager \
    ->typeManager()->registerType(type, dispatch, 0, nullptr, nullptr, ident)

bool CJanssonExtension::SDK_OnLoad(char *error, size_t maxlength, bool late)
{
	sharesys->AddNatives(myself, JSON_NATIVES);
    sharesys->AddNatives(myself, JSON_OBJECT_NATIVES);
    sharesys->AddNatives(myself, JSON_ARRAY_NATIVES);
    sharesys->AddNatives(myself, JSON_ERROR_NATIVES);
	sharesys->RegisterLibrary(myself, "jansson");

    if(pJansson != nullptr)
        delete (nJansson::Jansson *)pJansson;

    pJansson = new nJansson::Jansson();

    if(!REGISTER_TYPE(pJansson, "Json", new CJsonHandler(), myself->GetIdentity())
    || !REGISTER_TYPE(pJansson, "JsonError", new CJsonErrorHandler(), myself->GetIdentity()))
    {
        sprintf(error, "Something went wrong on type registration");
        return false;
    }

	return sharesys->AddInterface(myself, pJansson);
}

void CJanssonExtension::SDK_OnUnload()
{
    delete (nJansson::Jansson*) pJansson;
}

void CJanssonExtension::SDK_OnAllLoaded() {
    // pass
}

void CJsonHandler::OnHandleDestroy(SourceMod::HandleType_t type, void *object) {
    delete (nJansson::Json*) object;
}

void CJsonErrorHandler::OnHandleDestroy(SourceMod::HandleType_t type, void *object) {
    // ....
}
