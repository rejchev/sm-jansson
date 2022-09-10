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

// is it boolean type (see JsonType enums)
stock bool JSON_TYPE_BOOLEAN(JsonType t)
{
    return (t & JSON_TRUE) || (t & JSON_FALSE);
}

// is it null type ((see JsonType enums))
stock bool JSON_IS_NULL(JsonType t)
{
    return t == JSON_NULL;
}

// is object and some JsonType equal
stock bool JSON_TYPE_EQUAL(Json o, JsonType t) 
{
    return o.Type == t;
}

// is some object key type and JsonType equal
stock bool JSONO_TYPE_EQUAL(Json o, const char[] k, JsonType t)
{
    return asJSONO(o).GetType(k) == t;
}

// is some json array element type and json type equal
stock bool JSONA_TYPE_EQUAL(Json o, const int i, JsonType t)
{
    return asJSONA(o).GetType(i) == t;
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
stock JsonKeys asJSONK(Handle value)
{
    return view_as<JsonKeys>(value);
}

// CLOWN_USE_JANSSON defined in ClownCore (for backward compatibility, must be deprecated)
#if !defined CLOWN_USE_JANSSON 

// Find some string value int json array
stock int FindStringValue_json(JsonArray& array, const char[] value, const int maxValueSize = 512)
{
    if(!array)
        return -1;

    char[] buffer = new char[maxValueSize];

    for(int i, size = array.Length; i < size; i++)
        if(array.GetString(i, buffer, maxValueSize) && !strcmp(value, buffer))
            return i;

    return -1;
}

// find some int value int json array
stock int FindIntValue_json(JsonArray& array, const int value)
{
    if(!array)
        return -1;

    for(int i, size = array.Length; i < size; i++)
        if(array.GetInt(i) == value)
            return i;

    return -1;
}

// getting an array from object safely
stock JsonArray GetArrayFromJsonObject(Json& json, const char[] key)
{
    if(!json 
    || json.Type != JSON_OBJECT 
    || !asJSONO(json).HasKey(key) 
    || asJSONO(json).GetType(key) != JSON_ARRAY)
        return null;

    return asJSONA(asJSONO(json).Get(key));
}

// getting an array from array safely
stock JsonArray GetArrayFromJsonArray(Json& json, const int position)
{
    if(position < 0 
    || !json 
    || json.Type != JSON_ARRAY 
    || asJSONA(json).Length <= position 
    || asJSONA(json).GetType(position) != JSON_ARRAY)
        return null;

    return asJSONA(asJSONA(json).Get(position));
}

// ?
// stock Json JsonAbyssStep(Json json, JsonArray& chain)
// {
//     if(!chain)
//         return null;

//     if(!chain.Length)
//         return json;

//     Json buffer = asJSONA(chain.Get(0));

//     JsonType nextTierType = 
//         view_as<JsonType>(buffer.GetInt(0));

    
// }

#endif