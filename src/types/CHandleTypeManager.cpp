#include "CHandleTypeManager.h"

#include <cstring>

namespace nJansson {
    CHandleTypeManager::CHandleTypeManager() :
        m_vecTypes()
    {}

    CHandleTypeManager::~CHandleTypeManager() {
        for(auto& m_vecType : m_vecTypes)
            delete (CHandleType*) m_vecType;
    }

    void CHandleTypeManager::add(const CHandleType& handleType) {
        if(handleType.type() == BAD_HANDLE)
            return;

        if((get(find(handleType.type()))) != nullptr)
            return;

        m_vecTypes.push_back(new CHandleType(handleType));
    }

    const std::vector<IHandleType *>& CHandleTypeManager::types() const {
        return m_vecTypes;
    }

    size_t CHandleTypeManager::find(const char *name) const{
        size_t pos = 0;

        for(; pos < count(); pos++)
            if(strcmp(name, m_vecTypes[pos]->name()) == 0)
                break;

        return pos;
    }

    size_t CHandleTypeManager::find(const SourceMod::HandleType_t& type) const{
        size_t pos = 0;

        for(; pos < count(); pos++)
            if(type == m_vecTypes[pos]->type())
                break;

        return pos;
    }

    IHandleType *CHandleTypeManager::get(const char *name) const {
        return ((name == nullptr) ? nullptr : get(find(name)));
    }

    IHandleType *CHandleTypeManager::get(const SourceMod::HandleType_t& uType) const {
        return ((uType == 0) ? nullptr : get(find(uType)));
    }

    IHandleType *CHandleTypeManager::get(const size_t &index) const {
        if(index >= count())
            return nullptr;

        return types()[index];
    }

    size_t CHandleTypeManager::count() const {
        return types().size();
    }


} // nJansson