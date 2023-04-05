#ifndef _INCLUDE_SOURCEMOD_JANSSON_JSON_ERROR_H_
#define _INCLUDE_SOURCEMOD_JANSSON_JSON_ERROR_H_

#include <IJansson.h>
#include <jansson.h>
#include <cstring>

namespace nJansson
{
    class JsonError : public IJsonError
    {
    public:
        explicit JsonError(int line = -1,
                            int column = -1,
                            int position = -1,
                            JsonErrorCode code = Unknown,
                            const char* source = nullptr,
                            const char* text = nullptr);

        JsonError(const json_error_t &);

        virtual ~JsonError();

    public:
        void line(int value);
        int line() const override;

        void column(int value);
        int column() const override;

        void position(int value);
        int position() const override;

    public:
        void source(const char *);
        const char *source() const override;

        void text(const char *);
        const char *text() const override;
    
    public:
        JsonErrorCode code() const override;
        void code(JsonErrorCode code);

    public:
        bool equal(const IJsonError* another) const override;
        void clear() override;

    private:
        json_error_t m_error;
    };
}


#endif