#ifndef SM_JANSSON_JSON_OBJECT_ITER_H
#define SM_JANSSON_JSON_OBJECT_ITER_H

#include <IJansson.h>
#include <jansson.h>

namespace nJansson {

    class JsonObjectKeyIterator: public IJsonObjectKeyIterator {
    public:
        JsonObjectKeyIterator(json_t*);
        virtual ~JsonObjectKeyIterator();

    public:
        virtual const char* key() const;

    public:
        virtual void next();

    private:
        json_t* m_pJson;
        void* m_pIter;
    };

} // nJansson

#endif //SM_JANSSON_JSON_OBJECT_ITER_H
