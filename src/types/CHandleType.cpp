#include <smsdk_ext.h>

#include "CHandleType.h"

namespace nJansson
{
    CHandleType::CHandleType(const char *name,
                             SourceMod::IHandleTypeDispatch *dispatch,
                             void (*pHandler) (const char*, SourceMod::IHandleTypeDispatch*),
                             const SourceMod::HandleType_t &parent,
                             SourceMod::TypeAccess *access,
                             SourceMod::HandleAccess *handleAccess,
                             SourceMod::IdentityToken_t *identityToken) :
                             m_pName(name),
                             m_pDispatch(dispatch),
                             m_pTypDispatchHandler(pHandler),
                             m_Parent(parent),
                             m_MyType(),
                             m_pAccess(access),
                             m_pHandleAccess(handleAccess),
                             m_pIdent(identityToken),
                             m_pUnique(false)
    {
        SourceMod::HandleType_t type = NO_HANDLE_TYPE;
        SourceMod::HandleError error = SourceMod::HandleError_None;

        if(g_pHandleSys->FindHandleType(name, &type))
        {
            const QHandleType* pTypeInfo;

            if((pTypeInfo = getHandleStruct(name)) == nullptr)
            {
                // unsec thing

                m_MyType = type;
                return;
            }

            m_pDispatch         = pTypeInfo->dispatch;
            *m_pAccess          = pTypeInfo->typeSec;
            *m_pHandleAccess    = pTypeInfo->hndlSec;
            m_pIdent            = pTypeInfo->typeSec.ident;
        }
        else {
            type = g_pHandleSys->CreateType(
                    m_pName,
                    m_pDispatch,
                    m_Parent,
                    m_pAccess,
                    m_pHandleAccess,
                    m_pIdent,
                    &error);

            if(type != NO_HANDLE_TYPE)
                m_pUnique = true;
        }

        m_MyType = type;
    }

    CHandleType::~CHandleType() {

        if(m_pTypDispatchHandler != nullptr)
            m_pTypDispatchHandler(m_pName, m_pDispatch);

        if(m_pUnique)
            g_pHandleSys->RemoveType(m_MyType, m_pIdent);
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

    const SourceMod::TypeAccess* CHandleType::typeAccess() const {
        return const_cast<SourceMod::TypeAccess *>(m_pAccess);
    }

    const SourceMod::HandleAccess* CHandleType::handleAccess() const {
        return m_pHandleAccess;
    }

    const SourceMod::IdentityToken_t *CHandleType::identity() const {
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

    const QHandleType * CHandleType::getHandleStruct(const char *handleTypeName) {
        QHandleType* pHandleT = nullptr;

        ((HandleSystem*) g_pHandleSys)->m_TypeLookup.retrieve(handleTypeName, &pHandleT);

        return const_cast<QHandleType*>(pHandleT);
    }


}
