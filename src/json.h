#ifndef _INCLUDE_SOURCEMOD_JANSSON_JSON_H_
#define _INCLUDE_SOURCEMOD_JANSSON_JSON_H_

#include "json_error.h"

namespace nJansson
{
    class Json : public IJson 
    {
    public:
        Json(const char * = nullptr,  const size_t& = 0);
        Json(FILE *,        const size_t& = 0);
        Json(json_t*,       const JsonError&, bool = true);
        Json(const Json&) = default;

        virtual ~Json();

    public:
        const char *dump(const size_t &decodingFlags) override;
        int dump(const char* path, const size_t& flags) override;

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

    protected:
        virtual json_t* get_t(const char*) const;
        virtual json_t* get_t(const size_t&) const;

    public:
        IJson* get(const char *key) const override;
        IJson* get(const size_t& index) const override;

    protected:
        virtual bool set(const char*, json_t* value, int (*pSet) (json_t*, const char*, json_t*));
        virtual bool set(const size_t&, json_t*, int (*pSet) (json_t*, size_t, json_t*));
        virtual bool push(json_t*, int (*pSet) (json_t*, json_t*));

    public:
        bool    set(const char *key, const IJson* value) override;
        bool    set(const char *key, const char* value) override;
        bool    set(const char *key, double value) override;
        bool    set(const char *key, bool value) override;
        bool    set(const char *key, long long value) override;

    public:
        bool    set(const size_t& index, const IJson *value) override;
        bool    set(const size_t& index, const char* value) override;
        bool    set(const size_t& index, double value) override;
        bool    set(const size_t& index, bool value) override;
        bool    set(const size_t& index, long long value) override;

    public:
        bool    push(const IJson *value) override;
        bool    push(const char* value) override;
        bool    push(double value) override;
        bool    push(bool value) override;
        bool    push(long long value) override;

    public:
        bool update(const IJsonObject* another, JsonObjectUpdateType type) override;
        bool extend(const IJsonArray *another) override;

        JsonType type(const char *key) const override;
        JsonType type(const size_t& index) const override;

        bool exist(const char *key) const override;

        void clear() override;

        bool remove(const char *key) override;
        bool remove(const size_t& index) override;

    public:
        IJsonArray* keys(const JsonType& type, const size_t& flags) const override;
        size_t size() const override;

    public:
        bool isOK() const override;

    public:
        virtual json_t *json() const;

    private:
        json_t *m_pJson;
        JsonError m_JsonError;
    };
}

#endif