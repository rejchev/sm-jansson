#ifndef SM_JANSSON_JSON_OBJECT_H
#define SM_JANSSON_JSON_OBJECT_H

#include "json.h"

namespace SourceMod
{
    class JsonObject : public IJsonObject
    {
    private:
        JsonObject() = default;

    public:
        IJson   *get(const char *key) const override;

    public:
        bool    set(const char *key, const IJson* value) override;
        bool    set(const char *key, const char* value) override;
        bool    set(const char *key, double value) override;
        bool    set(const char *key, bool value) override;
        bool    set(const char *key, int value) override;

    public:
        bool update(const IJsonObject* another, JsonObjectUpdateType type) override;
        JsonType type(const char *key) const override;
        bool exist(const char *key) const override;
        void clear() override;
        bool remove(const char *key) override;
    };
}

#endif //SM_JANSSON_JSON_OBJECT_H
