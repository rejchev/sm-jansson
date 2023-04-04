#include "json.h"

using namespace nJansson;

Json::Json(const char *str, const size_t &flags) :
    m_pJson(),
    m_JsonError()
{
    json_error_t error = {};
    if((m_pJson = json_loads(str, flags, &error)) == nullptr
    || json_error_code(&error) != json_error_unknown)
        m_JsonError = error;
}

Json::Json(FILE *input, const size_t &flags) :
    m_pJson(),
    m_JsonError()
{
    json_error_t error = {};
    if((m_pJson = json_loadf(input, flags, &error)) == nullptr
       || json_error_code(&error) != json_error_unknown)
        m_JsonError = error;
}

Json::Json(json_t *json, const JsonError& jsonError, bool increment) :
    m_pJson(json),
    m_JsonError(jsonError)
{
    if(m_pJson != nullptr && IJsonError::null(jsonError) && increment)
        m_pJson = json_incref(m_pJson);
}

Json::~Json()
{
    json_decref(m_pJson);
}

const char *Json::dump(const size_t& decodingFlags)
{
    char *buffer = nullptr;

    if(IJsonError::null(*error()) && (buffer = json_dumps(m_pJson, decodingFlags)) == nullptr)
        m_JsonError = JsonError {
            -1,
            -1,
            -1,
            InvalidFormat,
            "Json::dump",
            "Invalid json format, it must be object or array"
        };

    return buffer;
}

bool Json::equal(const IJson &json) const
{
    Json &link = (Json &) json;

    return m_pJson != nullptr && link.json() == m_pJson;
}

IJsonError *Json::error() const
{
    return const_cast<IJsonError *>((IJsonError *) &m_JsonError);
}

json_t *Json::json()
{
    return m_pJson;
}

JsonType Json::type() const
{
    if(m_pJson == nullptr)
        return JsonType::Invalid;

    if(m_pJson->type & JSON_TRUE || m_pJson->type & JSON_FALSE)
        return JsonType::Boolean;

    if(m_pJson->type == JSON_NULL)
        return JsonType::Null;

    return (JsonType) m_pJson->type;
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