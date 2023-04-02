#include "CHandle.h"

namespace nJansson {
    CHandle::CHandle(void *object,
                     const IHandleType* type,
                     const SourceMod::IdentityToken_t *owner,
                     const SourceMod::IdentityToken_t *ident) :
                     m_pType(type),
                     m_pObject(object),
                     m_pIdent(ident),
                     m_pOwner(owner),
                     m_MyHandle(BAD_HANDLE)
    {
        if(m_pType->type() == 0)
            return;

        SourceMod::HandleError error;
        m_MyHandle = g_pHandleSys->CreateHandle(
                m_pType->type(),
                m_pObject,
                const_cast<IdentityToken_t *>(m_pOwner),
                const_cast<IdentityToken_t *>(m_pIdent),
                &error
        );

        if(error != HandleError_None && m_MyHandle != BAD_HANDLE)
        {
            g_pHandleSys->FreeHandle(m_MyHandle, nullptr);
            m_MyHandle = BAD_HANDLE;
        }
    }

    CHandle::~CHandle() {
        if(m_MyHandle != BAD_HANDLE)
            g_pHandleSys->FreeHandle(m_MyHandle, nullptr);

        if(m_pType == nullptr || m_pObject == nullptr)
            return;

        m_pType->dispatch()->OnHandleDestroy(m_pType->type(), m_pObject);
    }

    const IHandleType *CHandle::type() const {
        return m_pType;
    }

    const void *CHandle::object() const {
        return m_pObject;
    }

    const SourceMod::IdentityToken_t *CHandle::owner() const {
        return m_pOwner;
    }

    const SourceMod::IdentityToken_t *CHandle::ident() const {
        return m_pIdent;
    }

    SourceMod::HandleType_t CHandle::handle() const {
        return m_MyHandle;
    }
} // nJansson