#ifndef SM_JANSSON_CHANDLETYPEMANAGER_H
#define SM_JANSSON_CHANDLETYPEMANAGER_H

#include "CHandleType.h"

namespace nJansson {
    class CHandleTypeManager : public IHandleTypeManager {
    public:
        CHandleTypeManager();
        virtual ~CHandleTypeManager();

    public:
        virtual SourceMod::HandleType_t registerType(const char* name,
                                                     SourceMod::IHandleTypeDispatch *dispatch,
                                                     const SourceMod::HandleType_t& parent,
                                                     SourceMod::TypeAccess* access,
                                                     SourceMod::HandleAccess* handleAccess,
                                                     SourceMod::IdentityToken_t *identityToken);

        virtual SourceMod::HandleType_t registerExistingType(const char* name,
                                                             SourceMod::IHandleTypeDispatch *dispatch,
                                                             const SourceMod::HandleType_t &parent,
                                                             SourceMod::TypeAccess *access,
                                                             SourceMod::HandleAccess *handleAccess,
                                                             SourceMod::IdentityToken_t *identityToken);

        virtual void removeType(const SourceMod::HandleType_t&);

        virtual const IHandleType* getByName(const char* name) const;
        virtual const IHandleType* getById(const SourceMod::HandleType_t& ident) const;
        virtual const IHandleType* getByIndex(const size_t& index) const;

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
