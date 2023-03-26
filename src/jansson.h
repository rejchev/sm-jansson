#ifndef _INCLUDE_SOURCEMOD_JANSSON_H_
#define _INCLUDE_SOURCEMOD_JANSSON_H_

#include "json.h"

namespace SourceMod
{
    class Jansson : public IJansson
    {
        public:
            IJson *Create(const char *,  const size_t &flags) override;
            IJson *Create(FILE *input,   const size_t &flags) override;
    };
}

#endif