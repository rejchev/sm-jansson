/**
 * vim: set ts=4 :
 * =============================================================================
 * SourceMod REST in Pawn Extension
 * Copyright 2017-2020 Erik Minekus
 * =============================================================================
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _INCLUDE_SOURCEMOD_EXTENSION_PROPER_H_
#define _INCLUDE_SOURCEMOD_EXTENSION_PROPER_H_

#include <IJansson.h>

#include "smsdk_ext.h"

class CJanssonExtension :
        public SDKExtension
{
public:
	virtual bool SDK_OnLoad(char *error, size_t maxlength, bool late);
	virtual void SDK_OnUnload();
};

class CJsonHandler : public SourceMod::IHandleTypeDispatch
{
public:
    virtual void OnHandleDestroy(SourceMod::HandleType_t type, void* object);
};

class CJsonObjectKeysHandler : public SourceMod::IHandleTypeDispatch
{
public:
    virtual void OnHandleDestroy(SourceMod::HandleType_t type, void* object);
};

extern CJanssonExtension g_JanssonExtension;
extern nJansson::IJansson* pJansson;

#endif // _INCLUDE_SOURCEMOD_EXTENSION_PROPER_H_
