#ifndef SM_JANSSON_CHANDLE_H
#define SM_JANSSON_CHANDLE_H

#include "../../extension.h"

namespace nJansson {

    class CHandle : public IHandle {
    public:
        CHandle(void *object,
                const IHandleType* type,
                const SourceMod::IdentityToken_t* owner = nullptr,
                const SourceMod::IdentityToken_t* ident = nullptr);

        virtual ~CHandle();

    public:
        const IHandleType *type() const;
        const void *object() const;
        const SourceMod::IdentityToken_t *owner() const;
        const SourceMod::IdentityToken_t *ident() const;

    public:
        SourceMod::HandleType_t handle() const;

    private:
        void *m_pObject;
        SourceMod::Handle_t m_MyHandle;
        const IHandleType* m_pType;
        const SourceMod::IdentityToken_t* m_pOwner;
        const SourceMod::IdentityToken_t* m_pIdent;
    };

} // nJansson

#endif //SM_JANSSON_CHANDLE_H
