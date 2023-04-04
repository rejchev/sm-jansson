#ifndef SM_JANSSON_CHANDLETYPEMANAGER_H
#define SM_JANSSON_CHANDLETYPEMANAGER_H

#include "CHandleType.h"

namespace nJansson {
    class CHandleTypeManager : public IHandleTypeManager {
    public:
        CHandleTypeManager();
        virtual ~CHandleTypeManager();

    public:
        virtual void add(const CHandleType& type);
        virtual IHandleType* get(const char* name) const;
        virtual IHandleType* getByHandleType(const SourceMod::HandleType_t& ident) const;
        virtual IHandleType* getByIndex(const size_t& index) const;

    public:
        virtual size_t find(const char* name) const;
        virtual size_t find(const SourceMod::HandleType_t& type) const;

    protected:
        virtual const std::vector<IHandleType *>& types() const;

    public:
        virtual size_t count() const;

    private:
        std::vector<IHandleType *> m_vecTypes;
    };

    using CTypeMgr = CHandleTypeManager;

} // nJansson

#endif //SM_JANSSON_CHANDLETYPEMANAGER_H
