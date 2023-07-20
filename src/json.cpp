#include <amtl/am-string.h>

#include "json.h"
#include "json_utils.h"

using namespace nJansson;

Json::Json(const char *str, const size_t &flags) :
    m_pJson(),
    m_JsonError()
{
    json_error_t error = {};
    if((m_pJson = json_loads(str, flags, &error)) == nullptr)
        m_JsonError = convertNativeErrorStruct(&error);
}

Json::Json(FILE *input, const size_t &flags) :
    m_pJson(),
    m_JsonError()
{
    json_error_t error = {};
    if((m_pJson = json_loadf(input, flags, &error)) == nullptr)
        m_JsonError = convertNativeErrorStruct(&error);
}

Json::Json(json_t *json, const JsonError_t& jsonError, bool increment) :
    m_pJson(json),
    m_JsonError(jsonError)
{
    if(m_pJson == nullptr || !jsonError.equal(JSON_ERROR_NULL))
        return;

    if(increment)
        m_pJson = json_incref(m_pJson);
}

Json::~Json()
{
    json_decref(m_pJson);
}

bool Json::dump(char* buff, const size_t& maxl, const size_t &decodingFlags) const {
    if(!isOK())
        return false;

    const char* value;

    if((value = json_dumps(json(), decodingFlags)) == nullptr)
        return false;

    ke::SafeStrcpyN(buff, maxl, value, strlen(value) + 1);

    // TODO jansson/src/memory.c :: do_free
    //
    free((void *) value); // unsafe

    return true;
}

int Json::dump(const char *path, const size_t &flags) const {
    if(path == nullptr)
        return -1;

    return json_dump_file(json(), path, flags);
}

bool Json::equal(const IJson* json) const {
    return json_equal(this->json(), ((Json*)json)->json());
}

const JsonError_t& Json::error() const {
    return m_JsonError;
}

json_t *Json::json() const {
    return m_pJson;
}

JsonType Json::type() const
{
    if(!isOK())
        return jtInvalid;

    switch (m_pJson->type) {

        case JSON_OBJECT:
            return jtObject;

        case JSON_ARRAY:
            return jtArray;

        case JSON_STRING:
            return jtString;

        case JSON_INTEGER:
            return jtInteger;

        case JSON_REAL:
            return jtReal;

        case JSON_TRUE:
        case JSON_FALSE:
            return jtBoolean;

        case JSON_NULL:
            return jtNull;
    }

    return jtInvalid;
}

bool Json::get(long long int *value)
{
    if(value == nullptr || !isOK() || type() != JsonType::jtInteger)
        return false;

    return &(*value = json_integer_value(json())) != nullptr;
}

bool Json::get(bool *value)
{
    if(value == nullptr || !isOK() || type() != JsonType::jtBoolean)
        return false;

    return &(*value = json_boolean_value(json())) != nullptr;
}

bool Json::get(double *value)
{
    if(value == nullptr || !isOK() || type() != JsonType::jtReal)
        return false;

    return &(*value = json_real_value(json())) != nullptr;
}

const char* Json::get()
{
    if(!isOK() || type() != JsonType::jtString)
        return nullptr;

    return json_string_value(json());
}

IJson *Json::get(const char *key) const {
    json_t* pointer;

    if((pointer = get_t(key)) == nullptr)
        return nullptr;

    return new Json(pointer, JSON_ERROR_NULL, true);
}

IJson *Json::get(const size_t &index) const {
    json_t* pointer;

    if((pointer = get_t(index)) == nullptr)
        return nullptr;

    return new Json(pointer, JSON_ERROR_NULL, true);
}

bool Json::set(const char *key, const IJson *value) {
    return set(key, ((value != nullptr) ? ((Json*)value)->json() : json_null()), json_object_set) == 0;
}

bool Json::set(const char *key, const char *value) {
    return set(key, json_string(value), json_object_set_new) == 0;
}

bool Json::set(const char *key, json_t *value, int (*pSet)(json_t *, const char *, json_t *)) {
    return pSet(m_pJson, key, value) == 0;
}

bool Json::set(const size_t &index, json_t *value, int (*pSet)(json_t *, size_t, json_t *)) {
    return pSet(m_pJson, index, value) == 0;
}

bool Json::set(const char *key, double value) {
    return set(key, json_real(value), json_object_set_new);
}

bool Json::set(const char *key, bool value) {
    return set(key, json_boolean(value), json_object_set_new);
}

bool Json::set(const char *key, long long int value) {
    return set(key, json_integer(value), json_object_set_new);
}

bool Json::set(const size_t &index, const IJson *value) {
    return set(index, ((value != nullptr) ? ((Json*)value)->json() : json_null()), json_array_set);
}

bool Json::set(const size_t &index, const char *value) {
    return set(index, json_string(value), json_array_set_new);
}

bool Json::set(const size_t &index, double value) {
    return set(index, json_real(value), json_array_set_new);
}

bool Json::set(const size_t &index, bool value) {
    return set(index, json_boolean(value), json_array_set_new);
}

bool Json::set(const size_t &index, long long int value) {
    return set(index, json_integer(value), json_array_set_new);
}

bool Json::push(const IJson *value) {
    return push(((value != nullptr) ? ((Json*)value)->json() : json_null()), json_array_append);
}

bool Json::push(json_t *value, int (*pSet)(json_t *, json_t *)) {
    return pSet(m_pJson, value) == 0;
}

bool Json::push(const char *value) {
    return push(json_string(value), json_array_append_new);
}

bool Json::push(double value) {
    return push(json_real(value), json_array_append_new);
}

bool Json::push(bool value) {
    return push(json_boolean(value), json_array_append_new);
}

bool Json::push(long long int value) {
    return push(json_integer(value), json_array_append_new);
}

bool Json::update(const IJsonObject *another, JsonObjectUpdateType type) {
    int (*updateFunc) (json_t*, json_t*) = nullptr;

    switch(type)
    {
        case utDefault:
            updateFunc = json_object_update;
            break;
        case utExisting:
            updateFunc = json_object_update_existing;
            break;
        case utMissing:
            updateFunc = json_object_update_missing;
            break;
        case utRecursive:
            updateFunc = json_object_update_recursive;
            break;
    }

    if(updateFunc == nullptr)
        return false;

    // unsafe :/
    return updateFunc(json(), ((Json *)another)->json()) == 0;
}

bool Json::extend(const IJsonArray *another) {
    return json_array_extend(json(), ((Json*)another)->json()) == 0;
}

JsonType Json::type(const char *key) const {
    json_t* pointer;

    if((pointer = get_t(key)) == nullptr)
        return jtInvalid;

    return Json(pointer, JSON_ERROR_NULL).type();
}

json_t *Json::get_t(const char *key) const {
    return json_object_get(json(), key);
}

json_t *Json::get_t(const size_t &index) const {
    return json_array_get(json(), index);
}

JsonType Json::type(const size_t &index) const {
    json_t* pointer;

    if((pointer = get_t(index)) == nullptr)
        return jtInvalid;

    return Json(pointer, JSON_ERROR_NULL).type();
}

bool Json::exist(const char *key) const {
    return get_t(key) != nullptr;
}

void Json::clear() {
    switch (type()) {
        case jtArray: json_array_clear(json());
            break;
            
        case jtObject: json_object_clear(json());
            break;

        default: break;
    }
}

bool Json::remove(const char *key) {
    return json_object_del(json(), key) == 0;
}

bool Json::remove(const size_t &index) {
    return json_array_remove(json(), index) == 0;
}

size_t Json::size() const {
    size_t (*pSize) (const json_t*);
    
    switch (type()) {
        case jtArray: pSize = json_array_size;
            break;
            
        case jtObject: pSize = json_object_size;
            break;

        case jtString:
            pSize = json_string_size;
            break;

        case jtInvalid:
            return 0;

        default: return 1;
    }

    return pSize(json());
}

IJsonArray* Json::keys(const JsonType& type, const size_t& flags) const {
    if(this->type() != jtObject || !size())
        return nullptr;

    const char* buffer;
    Json *keys = new Json {"[]", flags };

    for(void* iter = json_object_iter(m_pJson);
        (buffer = json_object_iter_key(iter));
        iter = json_object_iter_next(m_pJson, iter))
        if(type == jtInvalid || this->type(buffer) == type)
            keys->push(buffer);

    return keys;
}

bool Json::isOK() const {
    return m_pJson != nullptr && m_JsonError.equal(JSON_ERROR_NULL);
}

JsonError_t Json::convertNativeErrorStruct(const json_error_t *error) {
    JsonError_t buffer {
        error->line,
        error->column,
        error->position
    };

    ke::SafeStrcpyN(buffer.source, PLATFORM_MAX_PATH, error->source, strlen(error->source) + 1);
    ke::SafeStrcpyN(buffer.text, PLATFORM_MAX_PATH, error->text, strlen(error->text));

    return buffer;
}

