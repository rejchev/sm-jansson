#include "CHandleType.h"

#include <smsdk_ext.h>

namespace nJansson
{
    CHandleType::CHandleType(const SourceMod::HandleType_t& htId,
                             const char *name,
                             SourceMod::IHandleTypeDispatch *dispatch,
                             const SourceMod::HandleType_t &parent,
                             SourceMod::TypeAccess *access,
                             SourceMod::HandleAccess *handleAccess,
                             SourceMod::IdentityToken_t *identityToken) :
                             m_pName(name),
                             m_pDispatch(dispatch),
                             m_Parent(parent),
                             m_MyType(htId),
                             m_pAccess(access),
                             m_pHandleAccess(handleAccess),
                             m_pIdent(identityToken)
    {}

    CHandleType::CHandleType(const CHandleType& copy) :
            m_pName(copy.m_pName),
            m_pDispatch(copy.m_pDispatch),
            m_Parent(copy.m_Parent),
            m_MyType(copy.m_MyType),
            m_pAccess(copy.m_pAccess),
            m_pHandleAccess(copy.m_pHandleAccess),
            m_pIdent(copy.m_pIdent)
    {}

    CHandleType::~CHandleType() = default;

    const char *CHandleType::name() const {
        return m_pName;
    }

    SourceMod::IHandleTypeDispatch *CHandleType::dispatch() const {
        return m_pDispatch;
    }

    SourceMod::HandleType_t CHandleType::parent() const {
        return m_Parent;
    }

    const SourceMod::TypeAccess* CHandleType::access() const {
        return const_cast<SourceMod::TypeAccess *>(m_pAccess);
    }

    const SourceMod::HandleAccess* CHandleType::handleAccess() const {
        return m_pHandleAccess;
    }

    const SourceMod::IdentityToken_t *CHandleType::ident() const {
        return const_cast<SourceMod::IdentityToken_t *>(m_pIdent);
    }

    SourceMod::Handle_t CHandleType::createHandle(void *object,
                                                  SourceMod::IdentityToken_t *owner,
                                                  SourceMod::IdentityToken_t *ident,
                                                  SourceMod::HandleError* handleError) const {
        return g_pHandleSys->CreateHandle(this->id(), object, owner, ident, handleError);
    }

    SourceMod::HandleType_t CHandleType::id() const {
        return m_MyType;
    }

    SourceMod::Handle_t
    CHandleType::createHandle(void *object,
                              const SourceMod::HandleSecurity *sec,
                              const SourceMod::HandleAccess *access,
                              SourceMod::HandleError *error) const {
        return g_pHandleSys->CreateHandleEx(this->id(), object,sec,access,error);
    }
}
