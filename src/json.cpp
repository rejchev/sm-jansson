#include <shared/CellArray.h>
#include <src/utils/utils.h>

#include "json.h"
#include "json_utils.h"

using namespace nJansson;

Json::Json(const char *str, const size_t &flags) :
    m_pJson(),
    m_JsonError()
{
    json_error_t error = {};
    if((m_pJson = json_loads(str, flags, &error)) == nullptr)
        m_JsonError = error;
}

Json::Json(FILE *input, const size_t &flags) :
    m_pJson(),
    m_JsonError()
{
    json_error_t error = {};
    if((m_pJson = json_loadf(input, flags, &error)) == nullptr)
        m_JsonError = error;
}

Json::Json(json_t *json, const JsonError& jsonError, bool increment) :
    m_pJson(json),
    m_JsonError(jsonError)
{
    if(m_pJson == nullptr || !IJsonError::isEmpty(&jsonError))
        return;

    if(increment)
        m_pJson = json_incref(m_pJson);
}

Json::~Json()
{
    json_decref(m_pJson);
}

const char *Json::dump(const size_t& decodingFlags)
{
    if(!isOK())
        return nullptr;

    return json_dumps(json(), decodingFlags);
}

int Json::dump(const char *path, const size_t &flags) {
    if(path == nullptr)
        return -1;

    return json_dump_file(json(), path, flags);
}

bool Json::equal(const IJson &json) const
{
    Json &link = (Json &) json;

    return m_pJson != nullptr && link.json() == m_pJson;
}

IJsonError *Json::error() const
{
    return const_cast<IJsonError *>(((nJansson::IJsonError *) &m_JsonError));
}

json_t *Json::json() const
{
    return m_pJson;
}

JsonType Json::type() const
{
    if(json() == nullptr || !isOK())
        return Invalid;

    switch (m_pJson->type) {

        case JSON_OBJECT:
            return Object;

        case JSON_ARRAY:
            return Array;

        case JSON_STRING:
            return String;

        case JSON_INTEGER:
            return Integer;

        case JSON_REAL:
            return Real;

        case JSON_TRUE:
        case JSON_FALSE:
            return Boolean;

        case JSON_NULL:
            return Null;
    }

    return Invalid;
}

bool Json::get(long long int *value)
{
    if(value == nullptr || type() != JsonType::Integer)
        return false;

    return &(*value = json_integer_value(json())) != nullptr;
}

bool Json::get(bool *value)
{
    if(value == nullptr || type() != JsonType::Boolean)
        return false;

    return &(*value = json_boolean_value(json())) != nullptr;
}

bool Json::get(double *value)
{
    if(value == nullptr || type() != JsonType::Real)
        return false;

    return &(*value = json_real_value(json())) != nullptr;
}

const char* Json::get()
{
    if(type() != JsonType::String)
        return nullptr;

    return json_string_value(json());
}

IJson *Json::get(const char *key) const {
    return new Json(get_t(key), JsonError {}, true);
}

IJson *Json::get(const size_t &index) const {
    return new Json(get_t(index), JsonError {}, true);
}

bool Json::set(const char *key, const IJson *value) {
    return set(key, ((Json *) value)->json(), json_object_set) == 0;
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
    return set(index, ((Json*)value)->json(), json_array_set);
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
    return push(((Json*)value)->json(), json_array_append);
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
    return updateFunc(json(), ((Json *)another)->json()) == 0;
}

bool Json::extend(const IJsonArray *another) {
    return json_array_extend(json(), ((Json*)another)->json()) == 0;
}

JsonType Json::type(const char *key) const {
    return Json(get_t(key), JsonError{}).type();
}

json_t *Json::get_t(const char *key) const {
    return json_object_get(json(), key);
}

json_t *Json::get_t(const size_t &index) const {
    return json_array_get(json(), index);
}

JsonType Json::type(const size_t &index) const {
    return Json(get_t(index), JsonError{}).type();
}

bool Json::exist(const char *key) const {
    return get_t(key) != nullptr;
}

void Json::clear() {
    switch (type()) {
        case Array: json_array_clear(json());
            break;
            
        case Object: json_object_clear(json());
            break;
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
        case Array: pSize = json_array_size;
            break;
            
        case Object: pSize = json_object_size;
            break;

        case String:
            pSize = json_string_size;
            break;

        case Invalid:
            return 0;

        default: return 1;
    }

    return pSize(json());
}

SourceMod::ICellArray *Json::keys() const {
    if(type() != Object || !size())
        return nullptr;

    // 10 * 512 = 5120
    // 20 * 512 = (ノ-_-)ノ~┻━┻
    auto* array = new CellArray(512);

    void* iter = json_object_iter(m_pJson);

    cell_t* block;
    const char* buffer;
    while((buffer = json_object_iter_key(iter)) != nullptr)
    {
        if((block = array->push()) == nullptr)
        {
            delete array;
            return nullptr;
        }

        // https://github.com/alliedmodders/sourcemod/blob/5addaffa5665f353c874f45505914ab692535c24/core/logic/smn_adt_array.cpp#L190
        strncopy((char *)block, buffer, strlen(buffer) + 1);

        iter = json_object_iter_next(m_pJson, iter);
    }

    return array;
}

bool Json::isOK() const {
    return json() != nullptr && IJsonError::isEmpty(error());
}

