#include "CHandleType.h"

#include <smsdk_ext.h>

namespace nJansson
{
    CHandleType::CHandleType(const char *name,
                             SourceMod::IHandleTypeDispatch *dispatch,
                             const SourceMod::HandleType_t &parent,
                             const SourceMod::TypeAccess &access,
                             const SourceMod::HandleAccess &handleAccess,
                             const SourceMod::IdentityToken_t *identityToken) :
                             m_pName(name),
                             m_pDispatch(dispatch),
                             m_Parent(parent),
                             m_Access(access),
                             m_HandleAccess(handleAccess),
                             m_pIdent(identityToken)
    {
        SourceMod::HandleError error;
        m_MyType = g_pHandleSys->CreateType(
                m_pName,
                m_pDispatch,
                m_Parent,
                &m_Access,
                &m_HandleAccess,
                const_cast<IdentityToken_t *>(m_pIdent),
                &error
        );

        if(error != HandleError_None && m_MyType != 0)
        {
            g_pHandleSys->RemoveType(m_MyType, const_cast<IdentityToken_t *>(m_pIdent));
            m_MyType = 0;
        }
    }

    CHandleType::~CHandleType() {
        if(!m_MyType)
            return;

        g_pHandleSys->RemoveType(m_MyType, const_cast<IdentityToken_t *>(m_pIdent));
    }

    const char *CHandleType::name() const {
        return m_pName;
    }

    SourceMod::IHandleTypeDispatch *CHandleType::dispatch() const {
        return m_pDispatch;
    }

    SourceMod::HandleType_t CHandleType::parent() const {
        return m_Parent;
    }

    const SourceMod::TypeAccess &CHandleType::access() const {
        return m_Access;
    }

    const SourceMod::HandleAccess &CHandleType::handleAccess() const {
        return m_HandleAccess;
    }

    const SourceMod::IdentityToken_t *CHandleType::ident() const {
        return const_cast<SourceMod::IdentityToken_t *>(m_pIdent);
    }

    SourceMod::Handle_t CHandleType::createHandle(void *object,
                                                  SourceMod::IdentityToken_t *owner,
                                                  SourceMod::IdentityToken_t *ident,
                                                  SourceMod::HandleError* handleError) const {
        Handle_t handle;

        if((handle = g_pHandleSys->CreateHandle(this->type(), object, owner, ident, handleError)) != BAD_HANDLE
        && handleError != nullptr && *handleError != HandleError_None)
        {
            g_pHandleSys->FreeHandle(handle, nullptr);
            handle = BAD_HANDLE;
        }

        return handle;
    }

    SourceMod::HandleType_t CHandleType::type() const {
        return m_MyType;
    }

    SourceMod::Handle_t
    CHandleType::createHandle(void *object,
                              const SourceMod::HandleSecurity *sec,
                              const SourceMod::HandleAccess *access,
                              SourceMod::HandleError *error) const {
        Handle_t handle;

        if((handle = g_pHandleSys->CreateHandleEx(
                this->type(),
                object,
                sec,
                access,
                error)) != BAD_HANDLE
        && error != nullptr
        && *error != HandleError_None)
        {
            g_pHandleSys->FreeHandle(handle, sec);
            handle = BAD_HANDLE;
        }

        return handle;
    }
}
