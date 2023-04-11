#if defined _jansson_stocks_included_
    #endinput
#endif
#define _jansson_stocks_included_

// Maximum indentation
stock const int JSON_MAX_INDENT = 0x1F;

// Pretty-print the result, identing with n spaces
stock int JSON_INDENT(int n)
{
    return n & JSON_MAX_INDENT;
}

// Output floats with at most n digits of precision
stock int JSON_REAL_PRECISION(int n)
{
    return (n & 0x1F) << 11;
}

// try view as Json
stock Json asJSON(Handle value)
{
    return view_as<Json>(value);
}

// try view as JsonObject
stock JsonObject asJSONO(Handle value)
{
    return view_as<JsonObject>(value);
}

// try view as JsonArray
stock JsonArray asJSONA(Handle value)
{
    return view_as<JsonArray>(value);
}

// try view as JsonKeys
stock JsonObjectKeyIterator asJSONK(Handle value)
{
    return view_as<JsonObjectKeyIterator>(value);
}

// try view as JsonBuilder
stock JsonBuilder asJSONB(Handle value)
{
    return view_as<JsonBuilder>(value);
}