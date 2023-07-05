#ifndef _INCLUDE_SOURCEMOD_JANSSON_H_
#define _INCLUDE_SOURCEMOD_JANSSON_H_

#include <src/types/CHandleTypeManager.h>

#include "json.h"

namespace nJansson
{
    class Jansson : public IJansson
    {
    public:
        explicit Jansson(const CHandleTypeManager& manager = {});
        virtual ~Jansson();

    public:
        IJson *create(const char *,  const size_t &flags) override;
        IJson *create(FILE *input,   const size_t &flags) override;

        IJson *createp(const char*,  const size_t& flags, SourceMod::ISourceMod* utils) override;

    public:
        IHandleTypeManager* typeManager() const override;

    private:
        IHandleTypeManager* m_pHandleTypeManager;
    };
}

#endif