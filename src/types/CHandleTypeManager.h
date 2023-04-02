#ifndef SM_JANSSON_CHANDLETYPEMANAGER_H
#define SM_JANSSON_CHANDLETYPEMANAGER_H

#include "CHandleType.h"

namespace nJansson {
    class CHandleTypeManager : public IHandleTypeManager {
    public:
        CHandleTypeManager();
        virtual ~CHandleTypeManager();

    public:
        void RegisterType(IHandleType* type);

    public:
        size_t FindType(const char* name) const;
        size_t FindType(const SourceMod::HandleType_t& type) const;
        IHandleType* GetType(const char* name) const;

    public:
        std::vector<IHandleType *> Types() const;

    private:
        std::vector<IHandleType *> m_vecTypes;
    };

    using CTypeMgr = CHandleTypeManager;

} // nJansson

#endif //SM_JANSSON_CHANDLETYPEMANAGER_H
