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

IHandleTypeManager *Jansson::typeManager() const {
    return m_pHandleTypeManager;
}

Jansson::Jansson(const CHandleTypeManager& manager) :
    m_pHandleTypeManager(new CHandleTypeManager(manager))
{}

Jansson::~Jansson() {
    delete (CHandleTypeManager*) m_pHandleTypeManager;
}
