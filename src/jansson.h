#ifndef _INCLUDE_SOURCEMOD_JANSSON_H_
#define _INCLUDE_SOURCEMOD_JANSSON_H_

#include <src/types/CHandleTypeManager.h>

#include "json.h"

namespace nJansson
{
    class Jansson : public IJansson
    {
    public:
        Jansson(const CHandleTypeManager& manager = {});
        virtual ~Jansson();

    public:
        IJson *create(const char *, const size_t &flags, JsonError_t* pError) override;
        IJson *create(FILE *input, const size_t &flags, JsonError_t* pError) override;
        IJson *create(const SourceMod::PathType& type, const char*, const size_t& flags, JsonError_t* pError) override;

    public:
        void close(IJson* json) override;

    public:
        IHandleTypeManager* types() const override;

    public:
        static JsonError_t ToKnownError(const json_error_t*);

    private:
        IHandleTypeManager* m_pHandleTypeManager;
    };
}

#endif