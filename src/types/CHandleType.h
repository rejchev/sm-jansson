#ifndef SM_JANSSON_CHANDLETYPE_H
#define SM_JANSSON_CHANDLETYPE_H

#include <IJansson.h>

namespace nJansson
{
    class CHandleType : public IHandleType
    {
    public:
        CHandleType(const SourceMod::HandleType_t&,
                    const char* name,
                    SourceMod::IHandleTypeDispatch *dispatch,
                    const SourceMod::HandleType_t& parent,
                    SourceMod::TypeAccess* access,
                    SourceMod::HandleAccess* handleAccess,
                    SourceMod::IdentityToken_t *identityToken);

        CHandleType(const CHandleType&);

    public:
        virtual ~CHandleType();

    public:
        virtual SourceMod::HandleType_t id() const;
        virtual const char *name() const;
        virtual SourceMod::IHandleTypeDispatch* dispatch() const;
        virtual SourceMod::HandleType_t parent() const;
        virtual const SourceMod::TypeAccess* access() const;
        virtual const SourceMod::HandleAccess* handleAccess() const;
        virtual const SourceMod::IdentityToken_t *ident() const;

    public:
        virtual SourceMod::Handle_t createHandle(void *,
                                                 SourceMod::IdentityToken_t*,
                                                 SourceMod::IdentityToken_t*,
                                                 SourceMod::HandleError*) const;

        virtual SourceMod::Handle_t createHandle(void *,
                                                 const SourceMod::HandleSecurity*,
                                                 const SourceMod::HandleAccess*,
                                                 SourceMod::HandleError*) const;

    private:
        const char *m_pName;
        SourceMod::IHandleTypeDispatch *m_pDispatch;
        SourceMod::HandleType_t m_Parent;
        SourceMod::HandleType_t m_MyType;
        SourceMod::TypeAccess* m_pAccess;
        SourceMod::HandleAccess* m_pHandleAccess;
        SourceMod::IdentityToken_t *m_pIdent;
    };
}


#endif //SM_JANSSON_CHANDLETYPE_H
