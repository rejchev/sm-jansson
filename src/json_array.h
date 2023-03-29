#ifndef SM_JANSSON_JSON_ARRAY_H
#define SM_JANSSON_JSON_ARRAY_H

#include "json.h"

namespace SourceMod
{
    class JsonArray : public IJsonArray
    {
    private:
        JsonArray() = default;

    public:
        IJson*  get(const size_t& index) const override;

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
        JsonType type(const size_t& index) const override;
        bool extend(const IJsonArray *another) override;
        bool remove(const size_t& index) override;
        size_t length() const override;
        void clear() override;
    };
}


#endif //SM_JANSSON_JSON_ARRAY_H
