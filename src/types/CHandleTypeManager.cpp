#include "CHandleTypeManager.h"

namespace nJansson {
    CHandleTypeManager::CHandleTypeManager() :
        m_vecTypes()
    {}

    CHandleTypeManager::~CHandleTypeManager() {
        for(auto& m_vecType : m_vecTypes)
            delete (CHandleType*) m_vecType;
    }

    void CHandleTypeManager::RegisterType(IHandleType *type) {
        if(type->type() == BAD_HANDLE)
            return;

        size_t index = FindType(type->name());

        if(index >= m_vecTypes.size())
            return;

        m_vecTypes.push_back(type);
    }

    std::vector<IHandleType *> CHandleTypeManager::Types() const {
        return m_vecTypes;
    }

    size_t CHandleTypeManager::FindType(const char *name) const{
        size_t pos = 0;

        for(; pos < m_vecTypes.size(); pos++)
            if(strcmp(name, m_vecTypes[pos]->name()) == 0)
                break;

        return pos;
    }

    size_t CHandleTypeManager::FindType(const SourceMod::HandleType_t &type) const{
        size_t pos = 0;

        for(; pos < m_vecTypes.size(); pos++)
            if(type == m_vecTypes[pos]->type())

        return pos;
    }

    IHandleType *CHandleTypeManager::GetType(const char *name) const {
        if(name == nullptr)
            return nullptr;

        size_t pos = FindType(name);

        return (pos >= m_vecTypes.size()) ? nullptr : m_vecTypes[pos];
    }


} // nJansson