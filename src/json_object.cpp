#include "json_object.h"

nJansson::IJson *nJansson::JsonObject::get(const char* key) const {
     return (!exist(key))
        ? nullptr
        : new Json(json_object_get((*((Json *)this)).json(), key), JsonError {});
}

bool nJansson::JsonObject::exist(const char* key) const {
    return json_object_get((*((Json *)this)).json(), key) != nullptr;
}

bool nJansson::JsonObject::set(const char *key, const nJansson::IJson* value) {

    auto set = (value->type() == JsonType::Null)
            ? json_object_set_new
            : json_object_set;

    return set((*((Json *)this)).json(), key, ((Json *) value)->json()) == 0;
}

nJansson::JsonType nJansson::JsonObject::type(const char *key) const {
    return Json(json_object_get((*((Json *)this)).json(), key), JsonError {}).type();
}

void nJansson::JsonObject::clear() {
    json_object_clear((*((Json *)this)).json());
}

bool nJansson::JsonObject::set(const char *key, const char *value) {
    if(value == nullptr)
        return false;

    return (json_object_set_new((*((Json *)this)).json(), key, (json_string(value))) == 0);
}

bool nJansson::JsonObject::set(const char *key, double value) {
    return (json_object_set_new((*((Json *)this)).json(), key, (json_real(value))) == 0);
}

bool nJansson::JsonObject::set(const char *key, bool value) {
    return (json_object_set_new((*((Json *)this)).json(), key, (json_boolean(value))) == 0);
}

bool nJansson::JsonObject::set(const char *key, long long value) {
    return (json_object_set_new((*((Json *)this)).json(), key, (json_integer(value))) == 0);
}

bool nJansson::JsonObject::remove(const char *key) {
    return (json_object_del((*((Json *)this)).json(), key) == 0);
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

