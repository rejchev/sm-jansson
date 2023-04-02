#ifndef _INCLUDE_SOURCEMOD_JANSSON_H_
#define _INCLUDE_SOURCEMOD_JANSSON_H_

#include "json.h"
#include "./types/CHandleTypeManager.h"

namespace nJansson
{
    class Jansson : public IJansson
    {
    public:
        explicit Jansson(IHandleTypeManager* manager = nullptr);
        virtual ~Jansson();

    public:
        IJson *Create(const char *,  const size_t &flags) override;
        IJson *Create(FILE *input,   const size_t &flags) override;

    public:
        virtual const IHandleTypeManager* GetTypeManager() const;

    private:
        IHandleTypeManager* m_pHandleTypeManager;
    };
}

#endif