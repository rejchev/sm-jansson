#include "jansson.h"

using namespace SourceMod;

IJson *Jansson::Create(const char *str, const size_t& flags)
{
    return new Json(str, flags);
}

IJson *Jansson::Create(FILE *input, const size_t &flags)
{

}