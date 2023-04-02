#include "jansson.h"

using namespace nJansson;

IJson *Jansson::Create(const char *str, const size_t& flags)
{
    return new Json(str, flags);
}

IJson *Jansson::Create(FILE *input, const size_t &flags)
{
    return new Json(input, flags);
}

const IHandleTypeManager *Jansson::GetTypeManager() const {
    return nullptr;
}

Jansson::Jansson(IHandleTypeManager *manager) :
    m_pHandleTypeManager(manager)
{
    if(m_pHandleTypeManager == nullptr)
        m_pHandleTypeManager = new CHandleTypeManager();
}

Jansson::~Jansson() {
    delete (CHandleTypeManager* )m_pHandleTypeManager;
}
