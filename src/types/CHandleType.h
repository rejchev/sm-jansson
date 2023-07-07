#ifndef SM_JANSSON_CHANDLETYPE_H
#define SM_JANSSON_CHANDLETYPE_H

#include <public/IJansson.h>
#include <shared/HandleSys.h>

namespace nJansson
{
    class CHandleType : public IHandleType
    {
    public:
        explicit CHandleType(const char* name = "",
                    SourceMod::IHandleTypeDispatch *dispatch = nullptr,
                    void (*) (const char*, SourceMod::IHandleTypeDispatch*) = nullptr,
                    const SourceMod::HandleType_t& parent = 0,
                    SourceMod::TypeAccess* access = nullptr,
                    SourceMod::HandleAccess* handleAccess = nullptr,
                    SourceMod::IdentityToken_t *identityToken = nullptr);
    public:
        virtual ~CHandleType();


    public:
        SourceMod::HandleType_t id() const override;
        const char *name() const override;
        SourceMod::IHandleTypeDispatch* dispatch() const override;
        SourceMod::HandleType_t parent() const override;
        const SourceMod::TypeAccess* typeAccess() const override;
        const SourceMod::HandleAccess* handleAccess() const override;
        const SourceMod::IdentityToken_t *identity() const override;

    public:
        SourceMod::Handle_t createHandle(void *, SourceMod::IdentityToken_t*,
                                                 SourceMod::IdentityToken_t*,
                                                 SourceMod::HandleError*) const override;

        SourceMod::Handle_t createHandle(void *, const SourceMod::HandleSecurity*,
                                                 const SourceMod::HandleAccess*,
                                                 SourceMod::HandleError*) const override;

    private:
        static const QHandleType * getHandleStruct(const char*);

    private:
        const char *m_pName;
        SourceMod::IHandleTypeDispatch *m_pDispatch;
        void (*m_pTypDispatchHandler) (const char*, SourceMod::IHandleTypeDispatch*);
        SourceMod::HandleType_t m_Parent;
        SourceMod::HandleType_t m_MyType;
        SourceMod::TypeAccess* m_pAccess;
        SourceMod::HandleAccess* m_pHandleAccess;
        SourceMod::IdentityToken_t *m_pIdent;

        bool m_pUnique;
    };
}


#endif //SM_JANSSON_CHANDLETYPE_H
