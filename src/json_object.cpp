#include "json_object.h"

nJansson::IJson *nJansson::JsonObject::get(const char* key) const {
    Json& link = *((Json *)this);

    return (!exist(key))
        ? nullptr
        : new Json(json_object_get(link.json(), key));
}

bool nJansson::JsonObject::exist(const char* key) const {
    Json& link = *((Json *)this);

    return json_object_get(link.json(), key) != nullptr;
}

bool nJansson::JsonObject::set(const char *key, const nJansson::IJson* value) {
    Json& link = *((Json *)this);

    auto set = (value->type() == JsonType::Null)
            ? json_object_set_new
            : json_object_set;

    return set(link.json(), key, ((Json *) value)->json()) == 0;
}

nJansson::JsonType nJansson::JsonObject::type(const char *key) const {
    Json& link = *((Json *)this);

    return Json(json_object_get(link.json(), key)).type();
}

void nJansson::JsonObject::clear() {
    Json& link = *((Json *)this);

    json_object_clear(link.json());
}

bool nJansson::JsonObject::set(const char *key, const char *value) {
    Json& link = *((Json *)this);

    if(value == nullptr)
        return false;

    return (json_object_set_new(link.json(), key, (json_string(value))) == 0);
}

bool nJansson::JsonObject::set(const char *key, double value) {
    Json& link = *((Json *)this);

    return (json_object_set_new(link.json(), key, (json_real(value))) == 0);
}

bool nJansson::JsonObject::set(const char *key, bool value) {
    Json& link = *((Json *)this);

    return (json_object_set_new(link.json(), key, (json_boolean(value))) == 0);
}

bool nJansson::JsonObject::set(const char *key, long long value) {
    Json& link = *((Json *)this);

    return (json_object_set_new(link.json(), key, (json_integer(value))) == 0);
}

bool nJansson::JsonObject::remove(const char *key) {
    Json& link = *((Json *)this);

    return (json_object_del(link.json(), key) == 0);
}

bool nJansson::JsonObject::update(const nJansson::IJsonObject *another, nJansson::JsonObjectUpdateType type) {
    int (*updateFunc) (json_t*, json_t*) = nullptr;

    switch(type)
    {
        case Default:
            updateFunc = json_object_update;
            break;
        case Existing:
            updateFunc = json_object_update_existing;
            break;
        case Missing:
            updateFunc = json_object_update_missing;
            break;
        case Recursive:
            updateFunc = json_object_update_recursive;
            break;
    }

    if(updateFunc == nullptr)
        return false;

    // unsafe :/
    return updateFunc(((Json *)this)->json(), ((Json *)another)->json()) == 0;
}

