#include "json_object_iter.h"

namespace nJansson {
    JsonObjectKeyIterator::JsonObjectKeyIterator(json_t *json) :
        m_pJson(json),
        m_pIter(json_object_iter(json))
    {
        if(json != nullptr)
            m_pJson = json_incref(json);
    }

    const char *JsonObjectKeyIterator::key() const {
        return json_object_iter_key(m_pIter);
    }

    void JsonObjectKeyIterator::next() {
        m_pIter = json_object_iter_next(m_pJson, m_pIter);
    }

    JsonObjectKeyIterator::~JsonObjectKeyIterator() {
        json_decref(m_pJson);
    };
} // nJansson