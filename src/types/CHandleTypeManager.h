#ifndef SM_JANSSON_CHANDLETYPEMANAGER_H
#define SM_JANSSON_CHANDLETYPEMANAGER_H

#include <shared/HandleSys.h>

#include "CHandleType.h"

namespace nJansson {
    class CHandleTypeManager : public IHandleTypeManager {
    public:
        CHandleTypeManager();
        virtual ~CHandleTypeManager();

    public:
        SourceMod::HandleType_t registerType(const char* name,
                                             SourceMod::IHandleTypeDispatch *dispatch,
                                             const SourceMod::HandleType_t& parent,
                                             SourceMod::TypeAccess* access,
                                             SourceMod::HandleAccess* handleAccess,
                                             SourceMod::IdentityToken_t *identityToken) override;


        void removeType(const SourceMod::HandleType_t&) override;

        const IHandleType* getByName(const char* name) const override;
        const IHandleType* getById(const SourceMod::HandleType_t& ident) const override;
        const IHandleType* getByIndex(const size_t& index) const override;

    protected:
        const std::vector<IHandleType *>& types() const override;

    private:
        static const QHandleType * getHandleStruct(const char*);

    public:
        size_t count() const override;

    private:
        std::vector<IHandleType *> m_vecTypes;
    };

    using CTypeMgr = CHandleTypeManager;

} // nJansson

#endif //SM_JANSSON_CHANDLETYPEMANAGER_H
