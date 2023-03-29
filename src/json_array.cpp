#include "json_array.h"

bool SourceMod::JsonArray::set(const size_t &index, const SourceMod::IJson *value) {
    Json &link = *((Json*) this);

    return json_array_set(link.json(), index, ((Json*) value)->json()) == 0;
}

bool SourceMod::JsonArray::set(const size_t &index, const char *value) {
    Json &link = *((Json*) this);

    return json_array_set_new(link.json(), index, json_string(value)) == 0;
}

bool SourceMod::JsonArray::set(const size_t &index, double value) {
    Json &link = *((Json*) this);

    return json_array_set_new(link.json(), index, json_real(value)) == 0;
}

bool SourceMod::JsonArray::set(const size_t &index, bool value) {
    Json &link = *((Json*) this);

    return json_array_set_new(link.json(), index, json_boolean(value)) == 0;
}

bool SourceMod::JsonArray::set(const size_t &index, long long value) {
    Json &link = *((Json*) this);

    return json_array_set_new(link.json(), index, json_integer(value)) == 0;
}

bool SourceMod::JsonArray::push(const SourceMod::IJson *value) {
    return json_array_append(
            (*((Json *)this)).json(),
            ((Json *) value)->json()
    ) == 0;
}

bool SourceMod::JsonArray::push(const char *value) {
    return json_array_append_new(
            (*((Json *)this)).json(),
            json_string(value)
    ) == 0;
}

bool SourceMod::JsonArray::push(double value) {
    return json_array_append_new(
            (*((Json *)this)).json(),
            json_real(value)
    ) == 0;
}

bool SourceMod::JsonArray::push(bool value) {
    return json_array_append_new(
            (*((Json *)this)).json(),
            json_boolean(value)
    ) == 0;
}

bool SourceMod::JsonArray::push(long long value) {
    return json_array_append_new(
            (*((Json *)this)).json(),
            json_integer(value)
    ) == 0;
}

SourceMod::JsonType SourceMod::JsonArray::type(const size_t &index) const {
    return Json(json_array_get((*((Json *)this)).json(), index)).type();
}

SourceMod::IJson *SourceMod::JsonArray::get(const size_t &index) const {
    return (length() >= index)
        ? nullptr
        : new Json(json_array_get((*((Json *)this)).json(), index));
}

bool SourceMod::JsonArray::extend(const SourceMod::IJsonArray *another) {
    return json_array_extend(
            (*((Json *)this)).json(),
            ((Json *) another)->json()
    ) == 0;
}

bool SourceMod::JsonArray::remove(const size_t &index) {
    return json_array_remove((*((Json *)this)).json(), index) == 0;
}

size_t SourceMod::JsonArray::length() const {
    return json_array_size((*((Json *)this)).json());
}

void SourceMod::JsonArray::clear() {
    json_array_clear((*((Json *)this)).json());
}



