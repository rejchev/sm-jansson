#include "json_array.h"

bool nJansson::JsonArray::set(const size_t &index, const nJansson::IJson *value) {
    Json &link = *((Json*) this);

    return json_array_set(link.json(), index, ((Json*) value)->json()) == 0;
}

bool nJansson::JsonArray::set(const size_t &index, const char *value) {
    Json &link = *((Json*) this);

    return json_array_set_new(link.json(), index, json_string(value)) == 0;
}

bool nJansson::JsonArray::set(const size_t &index, double value) {
    Json &link = *((Json*) this);

    return json_array_set_new(link.json(), index, json_real(value)) == 0;
}

bool nJansson::JsonArray::set(const size_t &index, bool value) {
    Json &link = *((Json*) this);

    return json_array_set_new(link.json(), index, json_boolean(value)) == 0;
}

bool nJansson::JsonArray::set(const size_t &index, long long value) {
    Json &link = *((Json*) this);

    return json_array_set_new(link.json(), index, json_integer(value)) == 0;
}

bool nJansson::JsonArray::push(const nJansson::IJson *value) {
    return json_array_append(
            (*((Json *)this)).json(),
            ((Json *) value)->json()
    ) == 0;
}

bool nJansson::JsonArray::push(const char *value) {
    return json_array_append_new(
            (*((Json *)this)).json(),
            json_string(value)
    ) == 0;
}

bool nJansson::JsonArray::push(double value) {
    return json_array_append_new(
            (*((Json *)this)).json(),
            json_real(value)
    ) == 0;
}

bool nJansson::JsonArray::push(bool value) {
    return json_array_append_new(
            (*((Json *)this)).json(),
            json_boolean(value)
    ) == 0;
}

bool nJansson::JsonArray::push(long long value) {
    return json_array_append_new(
            (*((Json *)this)).json(),
            json_integer(value)
    ) == 0;
}

nJansson::JsonType nJansson::JsonArray::type(const size_t &index) const {
    return Json(json_array_get((*((Json *)this)).json(), index), JsonError {}).type();
}

nJansson::IJson *nJansson::JsonArray::get(const size_t &index) const {
    return (length() >= index)
        ? nullptr
        : new Json(json_array_get((*((Json *)this)).json(), index), JsonError {});
}

bool nJansson::JsonArray::extend(const nJansson::IJsonArray *another) {
    return json_array_extend(
            (*((Json *)this)).json(),
            ((Json *) another)->json()
    ) == 0;
}

bool nJansson::JsonArray::remove(const size_t &index) {
    return json_array_remove((*((Json *)this)).json(), index) == 0;
}

size_t nJansson::JsonArray::length() const {
    return json_array_size((*((Json *)this)).json());
}

void nJansson::JsonArray::clear() {
    json_array_clear((*((Json *)this)).json());
}



