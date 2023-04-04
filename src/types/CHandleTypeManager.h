#ifndef SM_JANSSON_CHANDLETYPEMANAGER_H
#define SM_JANSSON_CHANDLETYPEMANAGER_H

#include "CHandleType.h"

namespace nJansson {
    class CHandleTypeManager : public IHandleTypeManager {
    public:
        CHandleTypeManager();
        virtual ~CHandleTypeManager();

    public:
        void add(const CHandleType& type);
        IHandleType* get(const char* name) const;
        IHandleType* get(const SourceMod::HandleType_t& ident) const;
        IHandleType* get(const size_t& index) const;

    public:
        size_t find(const char* name) const;
        size_t find(const SourceMod::HandleType_t& type) const;

    protected:
        const std::vector<IHandleType *>& types() const;

    public:
        size_t count() const;

    private:
        std::vector<IHandleType *> m_vecTypes;
    };

    using CTypeMgr = CHandleTypeManager;

} // nJansson

#endif //SM_JANSSON_CHANDLETYPEMANAGER_H
