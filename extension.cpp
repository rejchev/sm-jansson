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

#include "extension.h"
#include "natives.h"
#include "src/jansson.h"
#include "src/json_object_iter.h"
#include "src/types/CHandleTypeManager.h"

/**< Global singleton for extension's main interface */
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
    sharesys->AddNatives(myself, JSON_OBJECT_KEY_ITERATOR_NATIVES);
	sharesys->RegisterLibrary(myself, "jansson");

    if(pJansson != nullptr)
        delete (nJansson::Jansson *)pJansson;

    pJansson = new nJansson::Jansson();

    if(!REGISTER_TYPE(pJansson, "Json", new CJsonHandler(), myself->GetIdentity())
    || !REGISTER_TYPE(pJansson, "JsonObjectKeyIterator", new CJsonObjectKeysHandler(), myself->GetIdentity())
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

void CJsonHandler::OnHandleDestroy(SourceMod::HandleType_t type, void *object)
{
    delete (nJansson::Json*) object;
}

void CJsonObjectKeysHandler::OnHandleDestroy(SourceMod::HandleType_t type, void *object) {
    delete (nJansson::JsonObjectKeyIterator*) object;
}

void CJsonErrorHandler::OnHandleDestroy(SourceMod::HandleType_t type, void *object) {
    // ....
}
