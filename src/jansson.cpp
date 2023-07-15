#include "jansson.h"

using namespace nJansson;

IJson *Jansson::create(const char *str, const size_t& flags)
{
    return new Json(str, flags);
}

IJson *Jansson::create(FILE *input, const size_t &flags)
{
    return new Json(input, flags);
}

IJson *Jansson::create(const char *fullPath, const size_t &flags, SourceMod::ISourceMod *utils) {
    if(utils == nullptr || fullPath == nullptr)
        return nullptr;

    json_t* object;
    json_error_t error = {};
    object = json_load_file(fullPath, flags, &error);

    return new Json(object, Json::convertNativeErrorStruct(&error), false);
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
