#ifndef _INCLUDE_SOURCEMOD_EXTENSION_PROPER_H_
#define _INCLUDE_SOURCEMOD_EXTENSION_PROPER_H_

#include <public/IJansson.h>

#include "smsdk_ext.h"

class CJanssonExtension : public SDKExtension
{
public:
	virtual bool SDK_OnLoad(char *error, size_t maxlength, bool late);
	virtual void SDK_OnUnload();

    void SDK_OnAllLoaded() override;
};

class CJsonHandler : public SourceMod::IHandleTypeDispatch
{
public:
    virtual void OnHandleDestroy(SourceMod::HandleType_t type, void* object);
};

class CJsonErrorHandler : public SourceMod::IHandleTypeDispatch
{
public:
    virtual void OnHandleDestroy(SourceMod::HandleType_t type, void* object);
};

extern CJanssonExtension g_JanssonExtension;
extern nJansson::IJansson* pJansson;

#endif // _INCLUDE_SOURCEMOD_EXTENSION_PROPER_H_
