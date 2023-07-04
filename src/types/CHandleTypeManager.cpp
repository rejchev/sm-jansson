#include "CHandleTypeManager.h"

#include <smsdk_ext.h>
#include <cstring>

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
                                                             const SourceMod::HandleType_t &parent = 0,
                                                             SourceMod::TypeAccess *access = nullptr,
                                                             SourceMod::HandleAccess *handleAccess = nullptr,
                                                             SourceMod::IdentityToken_t *identityToken = nullptr) {
        SourceMod::HandleType_t type = 0;
        if(g_pHandleSys->FindHandleType(name, &type))
            return NO_HANDLE_TYPE;

        SourceMod::HandleError error = SourceMod::HandleError_None;
        if((type = g_pHandleSys->CreateType(name,
                                            dispatch,
                                            parent,
                                            access,
                                            handleAccess,
                                            identityToken,
                                            &error)) == BAD_HANDLE)
            return NO_HANDLE_TYPE;

        if(error != SourceMod::HandleError_None)
            g_pHandleSys->RemoveType(type, identityToken);

        type = NO_HANDLE_TYPE;
        if(g_pHandleSys->FindHandleType(name, &type))
            m_vecTypes.push_back(new CHandleType(type, name, dispatch, parent, access, handleAccess, identityToken));

        return type;
    }

    SourceMod::HandleType_t CHandleTypeManager::registerExistingType(const char* name,
                                                                     SourceMod::IHandleTypeDispatch *dispatch,
                                                                     const SourceMod::HandleType_t &parent,
                                                                     SourceMod::TypeAccess *access,
                                                                     SourceMod::HandleAccess *handleAccess,
                                                                     SourceMod::IdentityToken_t *identityToken) {

        SourceMod::HandleType_t type = NO_HANDLE_TYPE;
        if(!(g_pHandleSys->FindHandleType(name, &type)))
            return NO_HANDLE_TYPE;

        const auto& alreadyIn = (std::find_if(m_vecTypes.begin(), m_vecTypes.end(),
                                       [&](const auto &item) {
            return item->id() == type;
        }) != m_vecTypes.end());

        if(!alreadyIn)
            m_vecTypes.push_back(new CHandleType(type, name, dispatch, parent, access, handleAccess, identityToken));

        return type;
    }

    void CHandleTypeManager::removeType(const SourceMod::HandleType_t &id) {
        std::remove_if(m_vecTypes.begin(),
                       m_vecTypes.end(),
                       [&id](const auto &item) {
            return item->id() == id;
        });
    }


} // nJansson