#ifndef _INCLUDE_SOURCEMOD_JANSSON_H_
#define _INCLUDE_SOURCEMOD_JANSSON_H_

#include "json.h"
#include "./types/CHandleTypeManager.h"

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

    public:
        virtual IHandleTypeManager* typeManager() const;

    private:
        IHandleTypeManager* m_pHandleTypeManager;
    };
}

#endif