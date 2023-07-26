#include <jansson.h>

#include "jansson.h"

using namespace nJansson;

IJson *Jansson::create(const char *str, const size_t& flags, JsonError_t* pError)
{
    // because [] & {} len = 2
    if(str == nullptr || strlen(str) < 2)
        return nullptr;

    json_t* pJson;
    json_error_t error = {};
    
    if((pJson = json_loads(str, flags, &error)) == nullptr) {

        if(pError != nullptr)
            *pError = ToKnownError(&error);

        return nullptr;
    }

    return new Json(pJson, false);
}

IJson *Jansson::create(FILE *input, const size_t &flags, JsonError_t* pError)
{
    if(input == nullptr)
        return nullptr;

    json_t* pJson;
    json_error_t error = {};

    if((pJson = json_loadf(input, flags, &error)) == nullptr) {

        if(pError != nullptr)
            *pError = ToKnownError(&error);

        return nullptr;
    }

    return new Json(pJson, false);
}

IJson *Jansson::create(const char *fullPath, const size_t &flags, JsonError_t* pError, SourceMod::ISourceMod *utils) {
    if(fullPath == nullptr)
        return nullptr;

    json_t* object;
    json_error_t error = {};
    
    if((object = json_load_file(fullPath, flags, &error)) == nullptr) {

        if(pError != nullptr)
            *pError = ToKnownError(&error);

        return nullptr;
    }

    return new Json(object, false);
}

IHandleTypeManager *Jansson::types() const {
    return m_pHandleTypeManager;
}

Jansson::Jansson(const CHandleTypeManager& manager) :
    m_pHandleTypeManager(new CHandleTypeManager(manager))
{}

Jansson::~Jansson() {
    delete (CHandleTypeManager*) m_pHandleTypeManager;
}

void Jansson::close(IJson *json) {
    delete (Json*) json;
}

JsonError_t Jansson::ToKnownError(const json_error_t *error) {
    JsonError_t buffer {
            error->line,
            error->column,
            error->position
    };

    ke::SafeStrcpyN(buffer.source, PLATFORM_MAX_PATH, error->source, strlen(error->source) + 1);
    ke::SafeStrcpyN(buffer.text, PLATFORM_MAX_PATH, error->text, strlen(error->text));

    return buffer;
}
