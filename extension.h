#ifndef _INCLUDE_SOURCEMOD_EXTENSION_PROPER_H_
#define _INCLUDE_SOURCEMOD_EXTENSION_PROPER_H_

#include <src/types/CHandleTypeManager.h>

#include "smsdk_ext.h"

class CJsonHandler : public SourceMod::IHandleTypeDispatch
{
public:
    void OnHandleDestroy(SourceMod::HandleType_t type, void* object) override;
};

class CJanssonExtension : public SDKExtension
{
public:
    static void OnHandleTypeDispatchDestroy(const char*, SourceMod::IHandleTypeDispatch*);

public:
	bool SDK_OnLoad(char *error, size_t maxlength, bool late) override;
	void SDK_OnUnload() override;
    void SDK_OnAllLoaded() override;

private:
     const nJansson::CHandleType* m_pJsonType = nullptr;
};

extern CJanssonExtension g_JanssonExtension;

extern nJansson::IJansson* pJansson;

#endif // _INCLUDE_SOURCEMOD_EXTENSION_PROPER_H_
