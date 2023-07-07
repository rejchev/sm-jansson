#include <smsdk_ext.h>

#include "CHandleTypeManager.h"

namespace nJansson {
    CHandleTypeManager::CHandleTypeManager() :
        m_vecTypes()
    {}

    CHandleTypeManager::~CHandleTypeManager()  = default;

    const std::vector<const IHandleType *>& CHandleTypeManager::container() const {
        return m_vecTypes;
    }

    const IHandleType *CHandleTypeManager::find(const char *name) const {
        if(name == nullptr)
            return nullptr;

        const auto& iter =
                std::find_if(m_vecTypes.begin(),m_vecTypes.end(),
                             [&](const auto &item) {
           return strcmp(name, item->name()) == 0;
        });

        return ((iter == m_vecTypes.end()) ? nullptr : *iter);
    }

    const IHandleType *CHandleTypeManager::find(const size_t &index) const {
        if(index >= count())
            return nullptr;

        return container()[index];
    }

    const IHandleType *CHandleTypeManager::find_t(const SourceMod::HandleType_t& id) const {
        if(id == NO_HANDLE_TYPE)
            return nullptr;

        const auto& iter =
                std::find_if(m_vecTypes.begin(),m_vecTypes.end(),
                             [&](const auto &item) {
                                 return item->id() == id;
                             });

        return ((iter == m_vecTypes.end()) ? nullptr : *iter);
    }

    size_t CHandleTypeManager::count() const {
        return container().size();
    }

    SourceMod::HandleType_t CHandleTypeManager::add(const IHandleType* pHType) {

        SourceMod::HandleType_t type = 0;
        if(pHType == nullptr
        || !g_pHandleSys->FindHandleType(pHType->name(), &type)
        || type != pHType->id())
            return NO_HANDLE_TYPE;

        const auto& hType = std::find_if(
                m_vecTypes.begin(),
                m_vecTypes.end(),
                [&](const auto &item) {
                    return item->id() == pHType->id();
                });

        if(hType == m_vecTypes.end())
            m_vecTypes.push_back(pHType);

        return type;
    }

    void CHandleTypeManager::remove(const SourceMod::HandleType_t &id) {
        std::remove_if(m_vecTypes.begin(),
                       m_vecTypes.end(),
                       [&id](const auto &item) {
            return item->id() == id;
        });
    }

} // nJansson