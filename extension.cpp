#include <src/jansson.h>
#include <src/natives.h>

#include "extension.h"

CJanssonExtension g_JanssonExtension;

nJansson::IJansson* pJansson;

SMEXT_LINK(&g_JanssonExtension)

void CJanssonExtension::OnHandleTypeDispatchDestroy(const char* type, SourceMod::IHandleTypeDispatch* pDispatch) {
    if(strcmp(type, "Json") == 0)
        delete (CJsonHandler*) pDispatch;
}

bool CJanssonExtension::SDK_OnLoad(char *error, size_t maxlength, bool late)
{
    m_pJsonType = new nJansson::CHandleType (
            "Json",
            new CJsonHandler(),
            OnHandleTypeDispatchDestroy,
            0,
            nullptr,
            nullptr,
            myself->GetIdentity()
    );

	sharesys->AddNatives(myself, JSON_NATIVES);
    sharesys->AddNatives(myself, JSON_OBJECT_NATIVES);
    sharesys->AddNatives(myself, JSON_ARRAY_NATIVES);
	sharesys->RegisterLibrary(myself, "jansson");

    if(pJansson != nullptr)
        delete (nJansson::Jansson *)pJansson;

    pJansson = new nJansson::Jansson();

    if(!pJansson->types()->add(m_pJsonType))
    {
        sprintf(error, "Failed on type '%s' registration", m_pJsonType->name());
        return false;
    }

    smutils->LogMessage(myself, "Add type: done");

	return sharesys->AddInterface(myself, pJansson);
}

void CJanssonExtension::SDK_OnUnload()
{
    delete m_pJsonType;

    delete (nJansson::Jansson*) pJansson;
}

void CJanssonExtension::SDK_OnAllLoaded() {
    // pass
}

void CJsonHandler::OnHandleDestroy(SourceMod::HandleType_t type, void *object) {
    delete (nJansson::Json*) object;
}