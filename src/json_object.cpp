#include "json_object.h"

SourceMod::IJson *SourceMod::JsonObject::get(const char* key) const {
    Json& link = *((Json *)this);

    return (!valid() || !exist(key))
        ? nullptr
        : new Json(json_object_get(link.json(), key));
}

bool SourceMod::JsonObject::exist(const char* key) const {
    Json& link = *((Json *)this);

    return valid() && json_object_get(link.json(), key) != nullptr;
}

bool SourceMod::JsonObject::valid() const {
    return JsonObject::IJson::type() == JsonType::Object;
}


bool SourceMod::JsonObject::set(const char *key, const SourceMod::IJson* value) {
    if(!valid() || value == nullptr)
        return false;

    Json& link = *((Json *)this);

    auto set = (value->type() == JsonType::Null)
            ? json_object_set_new
            : json_object_set;

    return set(link.json(), key, ((Json *) value)->json()) == 0;
}

SourceMod::JsonType SourceMod::JsonObject::type(const char *key) const {
    if(!valid())
        return JsonType::Invalid;

    Json& link = *((Json *)this);

    return Json(json_object_get(link.json(), key)).type();
}

void SourceMod::JsonObject::clear() {
    Json& link = *((Json *)this);

    if(!valid())
        return;

    json_object_clear(link.json());
}

bool SourceMod::JsonObject::set(const char *key, const char *value) {
    Json& link = *((Json *)this);

    if(!valid() || value == nullptr)
        return false;

    return (json_object_set_new(link.json(), key, (json_string(value))) == 0);
}

bool SourceMod::JsonObject::set(const char *key, double value) {
    Json& link = *((Json *)this);

    if(!valid())
        return false;

    return (json_object_set_new(link.json(), key, (json_real(value))) == 0);
}

bool SourceMod::JsonObject::set(const char *key, bool value) {
    Json& link = *((Json *)this);

    if(!valid())
        return false;

    return (json_object_set_new(link.json(), key, (json_boolean(value))) == 0);
}

bool SourceMod::JsonObject::set(const char *key, int value) {
    Json& link = *((Json *)this);

    if(!valid())
        return false;

    return (json_object_set_new(link.json(), key, (json_integer(value))) == 0);
}

bool SourceMod::JsonObject::remove(const char *key) {
    Json& link = *((Json *)this);

    if(!valid())
        return false;

    return (json_object_del(link.json(), key) == 0);
}

