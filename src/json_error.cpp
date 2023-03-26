#include "json_error.h"

using namespace SourceMod;

JsonError::JsonError(const json_error_t &error) :
    m_error(error)
{}

JsonError::JsonError(int line,
                     int column,
                     int position,
                     const char *source,
                     const char *text) :
        m_error()
{
    this->line(line);
    this->column(column);
    this->position(position);
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
    if(value != nullptr)
        strcpy_s(m_error.source, value);
    else
        m_error.source[0] = '\0';
}

void JsonError::text(const char *value)
{
    if(value != nullptr)
        strcpy_s(m_error.text, value);
    else
        m_error.text[0] = '\0';
}

bool JsonError::equal(const SourceMod::IJsonError &another) const
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