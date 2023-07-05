#include <cstring>
#include <smsdk_ext.h>

#include "CHandleTypeManager.h"


namespace nJansson {
    CHandleTypeManager::CHandleTypeManager() :
        m_vecTypes()
    {}

    CHandleTypeManager::~CHandleTypeManager() {
        for(auto& m_vecType : m_vecTypes)
            delete (CHandleType*) m_vecType;
    }

    const std::vector<IHandleType *>& CHandleTypeManager::types() const {
        return m_vecTypes;
    }

    const IHandleType *CHandleTypeManager::getByName(const char *name) const {
        if(name == nullptr)
            return nullptr;

        const auto& iter =
                std::find_if(m_vecTypes.begin(),m_vecTypes.end(),
                             [&](const auto &item) {
           return strcmp(name, item->name()) == 0;
        });

        return ((iter == m_vecTypes.end()) ? nullptr : *iter);
    }

    const IHandleType *CHandleTypeManager::getById(const SourceMod::HandleType_t& id) const {
        if(id == NO_HANDLE_TYPE)
            return nullptr;

        const auto& iter =
                std::find_if(m_vecTypes.begin(),m_vecTypes.end(),
                             [&](const auto &item) {
                                 return item->id() == id;
                             });

        return ((iter == m_vecTypes.end()) ? nullptr : *iter);
    }

    const IHandleType *CHandleTypeManager::getByIndex(const size_t &index) const {
        if(index >= count())
            return nullptr;

        return types()[index];
    }

    size_t CHandleTypeManager::count() const {
        return types().size();
    }

    SourceMod::HandleType_t CHandleTypeManager::registerType(const char *name,
                                                             SourceMod::IHandleTypeDispatch *dispatch,
                                                             const SourceMod::HandleType_t &parent,
                                                             SourceMod::TypeAccess *access,
                                                             SourceMod::HandleAccess *handleAccess,
                                                             SourceMod::IdentityToken_t *identityToken) {
        const auto& hType = std::find_if(
                m_vecTypes.begin(),
                m_vecTypes.end(),
                [&](const auto &item) {
                    return strcmp(name, item->name()) == 0;
                });

        if(hType != m_vecTypes.end())
            return (*hType)->id();

        SourceMod::HandleType_t type = 0;
        SourceMod::HandleError error = SourceMod::HandleError_None;

        if(g_pHandleSys->FindHandleType(name, &type))
        {
            const QHandleType* pTypeInfo;

            if((pTypeInfo = getHandleStruct(name)) == nullptr)
                return NO_HANDLE_TYPE;

            dispatch = pTypeInfo->dispatch;
            access = (SourceMod::TypeAccess *)&pTypeInfo->typeSec;
            handleAccess = (SourceMod::HandleAccess *)&pTypeInfo->hndlSec;
            identityToken = pTypeInfo->typeSec.ident;
        }
        else if((type = g_pHandleSys->CreateType(
                name,
                dispatch,
                parent,
                access,
                handleAccess,
                identityToken,
                &error)) == BAD_HANDLE)
            return NO_HANDLE_TYPE;

        if(error != SourceMod::HandleError_None)
        {
            g_pHandleSys->RemoveType(type, identityToken);
            type = NO_HANDLE_TYPE;
        }

        if(type != NO_HANDLE_TYPE)
            m_vecTypes.push_back(new CHandleType(type, name, dispatch, parent, access, handleAccess, identityToken));

        return type;
    }

    const QHandleType * CHandleTypeManager::getHandleStruct(const char *handleTypeName) {
        QHandleType* pHandleT = nullptr;

        ((HandleSystem*) g_pHandleSys)->m_TypeLookup.retrieve(handleTypeName, &pHandleT);

        return const_cast<QHandleType*>(pHandleT);
    }

    void CHandleTypeManager::removeType(const SourceMod::HandleType_t &id) {
        std::remove_if(m_vecTypes.begin(),
                       m_vecTypes.end(),
                       [&id](const auto &item) {
            return item->id() == id;
        });
    }

} // nJansson