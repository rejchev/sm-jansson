#ifndef _INCLUDE_SOURCEMOD_JANSSON_JSON_H_
#define _INCLUDE_SOURCEMOD_JANSSON_JSON_H_

#include "json_error.h"

namespace SourceMod
{
    class Json : public IJson 
    {
    public:
        explicit Json(const char *, const size_t &flags = 0);
        explicit Json(FILE *, const size_t& flags = 0);
        explicit Json(json_t*);
        virtual ~Json();

    public:
        const char *dump(const size_t &decodingFlags) override;

    public:
        bool equal(const IJson &json) const override;

    public:
        bool get(long long *value) override;
        bool get(double *value) override;
        bool get(bool *value) override;
        const char* get() override;

    public:
        IJsonError  *error() const override;
        JsonType    type() const override;

    public:
//        virtual const json_t *json() const;

    public:
        virtual json_t *json();

    private:
        json_t *m_pJson;
        JsonError m_JsonError;

    };
}

#endif