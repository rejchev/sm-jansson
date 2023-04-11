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
        virtual IJson* get(const char *key) const;
        virtual IJson* get(const size_t& index) const;

    protected:
        virtual bool set(const char*, json_t* value, int (*pSet) (json_t*, const char*, json_t*));
        virtual bool set(const size_t&, json_t*, int (*pSet) (json_t*, size_t, json_t*));
        virtual bool push(json_t*, int (*pSet) (json_t*, json_t*));

    public:
        virtual bool    set(const char *key, const IJson* value);
        virtual bool    set(const char *key, const char* value);
        virtual bool    set(const char *key, double value);
        virtual bool    set(const char *key, bool value);
        virtual bool    set(const char *key, long long value);

    public:
        virtual bool    set(const size_t& index, const IJson *value);
        virtual bool    set(const size_t& index, const char* value);
        virtual bool    set(const size_t& index, double value);
        virtual bool    set(const size_t& index, bool value);
        virtual bool    set(const size_t& index, long long value);

    public:
        virtual bool    push(const IJson *value);
        virtual bool    push(const char* value);
        virtual bool    push(double value);
        virtual bool    push(bool value);
        virtual bool    push(long long value);

    public:
        virtual bool update(const IJsonObject* another, JsonObjectUpdateType type);
        virtual bool extend(const IJsonArray *another);

        virtual JsonType type(const char *key) const;
        virtual JsonType type(const size_t& index) const;

        virtual bool exist(const char *key) const;

        virtual void clear();

        bool remove(const char *key) override;
        bool remove(const size_t& index) override;

    public:
        virtual IJsonObjectKeyIterator* keys() const;
        virtual size_t size() const;

    public:
        virtual bool isOK() const;

    public:
        virtual json_t *json() const;

    private:
        json_t *m_pJson;
        JsonError m_JsonError;
    };
}

#endif