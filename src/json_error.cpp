#include "json_error.h"

using namespace nJansson;

JsonError::JsonError(const json_error_t &error) :
    m_error(error)
{}

JsonError::JsonError(int line,
                     int column,
                     int position,
                     JsonErrorCode code,
                     const char *source,
                     const char *text) :
        m_error()
{
    this->line(line);
    this->column(column);
    this->position(position);
    this->code(code);
    this->source(source);
    this->text(text);
}

JsonError::~JsonError() = default;

void JsonError::line(int value)
{
    m_error.line = value;
}

void JsonError::column(int value)
{
    m_error.column = value;
}

void JsonError::position(int value)
{
    m_error.position = value;
}

int JsonError::line() const 
{
    return m_error.line;
}

int JsonError::column() const 
{
    return m_error.column;
} 

int JsonError::position() const 
{
    return m_error.position;
}

// TODO: Re
JsonErrorCode JsonError::code() const
{
    return (JsonErrorCode) m_error.text[JSON_ERROR_TEXT_LENGTH - 1];
}

const char *JsonError::source() const
{
    return m_error.source;
}

const char *JsonError::text() const
{
    return m_error.text;
}

void JsonError::source(const char *value)
{
    if(!value)
    {
        m_error.text[0] = '\0';
        return;
    }

    size_t size = strlen(value);

    if(size > JSON_ERROR_SOURCE_LENGTH)
        size = JSON_ERROR_SOURCE_LENGTH;

    strncpy(m_error.source, value, size);
}

void JsonError::text(const char *value)
{
    if(!value)
    {
        m_error.text[0] = '\0';
        return;
    }

    size_t size = strlen(value);

    if(size > JSON_ERROR_TEXT_LENGTH - 2)
        size = JSON_ERROR_TEXT_LENGTH - 2;

    strncpy(m_error.text, value, size);
}

bool JsonError::equal(const IJsonError &another) const
{
    return another.code() == code()
        && another.line() == line()
        && another.position() == position()
        && strcmp(another.text(), text()) == 0
        && strcmp(another.source(), source()) == 0;
}

void JsonError::clear()
{
    position(-1);
    line(-1);
    column(-1);
    text(nullptr);
    source(nullptr);
}

void JsonError::code(JsonErrorCode code) {
    m_error.text[JSON_ERROR_TEXT_LENGTH - 1] = code;
}
