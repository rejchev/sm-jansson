#ifndef SM_JANSSON_CHANDLETYPEMANAGER_H
#define SM_JANSSON_CHANDLETYPEMANAGER_H

#include "CHandleType.h"

namespace nJansson {
    class CHandleTypeManager : public IHandleTypeManager {
    public:
        CHandleTypeManager();
        virtual ~CHandleTypeManager();

    public:
        SourceMod::HandleType_t add(const IHandleType* pHType) override;
        void remove(const SourceMod::HandleType_t&) override;

    public:
        const IHandleType* find(const char* name) const override;
        const IHandleType* find(const size_t& index) const override;
        const IHandleType* find_t(const SourceMod::HandleType_t& ident) const override;

    protected:
        const std::vector<const IHandleType *>& container() const override;

    public:
        size_t count() const override;

    private:
        std::vector<const IHandleType *> m_vecTypes;
    };

    using CTypeMgr = CHandleTypeManager;

} // nJansson

#endif //SM_JANSSON_CHANDLETYPEMANAGER_H
