#include "json_i_natives.h"

using eIter =           nJansson::IJsonObjectKeyIterator;
using eContext =        nJansson::PluginContextUtils;

cell_t JsonObjectKeyIteratorNext(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = eContext ::GetType(pContext, pJansson, "JsonObjectKeyIterator")) == nullptr)
        return 0;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    eIter* iter;
    if((iter = (eIter *) eContext::ReadHandle(
            pContext,
            g_pHandleSys,
            pType,
            &sec,
            params[1])) == nullptr)
        return 0;

    const char *key;
    if ((key = iter->key()) == nullptr)
        return 0;

    pContext->StringToLocalUTF8(params[2], params[3], key, nullptr);

    iter->next();
    return 1;
}

const sp_nativeinfo_t JSON_OBJECT_KEY_ITERATOR_NATIVES[] =
{
        {"JsonObjectKeyIterator.Next", JsonObjectKeyIteratorNext},
        {nullptr, nullptr}
};
