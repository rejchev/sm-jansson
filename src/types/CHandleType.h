#ifndef SM_JANSSON_CHANDLETYPE_H
#define SM_JANSSON_CHANDLETYPE_H

#include <IJansson.h>

namespace nJansson
{
    class CHandleType : public IHandleType
    {
    public:
        CHandleType(const char* name,
                    SourceMod::IHandleTypeDispatch *dispatch,
                    const SourceMod::HandleType_t& parent,
                    const SourceMod::TypeAccess& access,
                    const SourceMod::HandleAccess& handleAccess,
                    const SourceMod::IdentityToken_t *identityToken);

        virtual ~CHandleType();

    public:
        virtual const char *name() const;
        virtual SourceMod::IHandleTypeDispatch* dispatch() const;
        virtual SourceMod::HandleType_t parent() const;
        virtual const SourceMod::TypeAccess& access() const;
        virtual const SourceMod::HandleAccess& handleAccess() const;
        virtual const SourceMod::IdentityToken_t *ident() const;

    public:
        virtual SourceMod::Handle_t createHandle(void *,
                                                 SourceMod::IdentityToken_t*,
                                                 SourceMod::IdentityToken_t*,
                                                 SourceMod::HandleError*) const;

    public:
        virtual SourceMod::HandleType_t type() const;

    private:
        const char *m_pName;
        SourceMod::IHandleTypeDispatch *m_pDispatch;
        SourceMod::HandleType_t m_Parent;
        SourceMod::HandleType_t m_MyType;
        SourceMod::TypeAccess m_Access;
        SourceMod::HandleAccess m_HandleAccess;
        const SourceMod::IdentityToken_t *m_pIdent;
    };
}


#endif //SM_JANSSON_CHANDLETYPE_H
