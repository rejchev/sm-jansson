#pragma newdecls required

#define JSON_INCLUDE_BUILDER

#include <jansson>

#define TEST_DUMP(%1,%2,%3) TestDump(%1(%2, sizeof(%2)), %3)
#define TEST_FIND_FIRST(%1,%2,%3,%4) TestFindFirst(%1(%2, sizeof(%2)), %3, %4)

public void OnMapStart()
{
    char error[512];

    if(!TEST_DUMP(MakeJsonObject, error, JsonPretty(4)|JsonFloatPrecision(7)) && error[0])
        LogError(error);

    if(!TEST_DUMP(MakeJsonArray, error, JsonPretty(4)|JsonFloatPrecision(7)) && error[0])
        LogError(error);

    if(!TEST_FIND_FIRST(MakeJsonObject, error, StringObjectExpected, JStringType) && error[0])
        LogError(error);

    if(!TEST_FIND_FIRST(MakeJsonArray, error, StringObjectExpected, JStringType) && error[0])
        LogError(error);
        
}

bool TestDump(Json json, int flags = 0)
{
    if(!json)
        return false;

    int size;
    
    if((size = Json.SizeOf(json, flags) + 1) < 2) 
    {
        LogError("[TestDump]: Invalid size '%d'", size);

        delete json;
        return false;
    }

    char[] buffer = new char[size];
    
    bool success;
    if(!(success = json.Dump(buffer, size, flags, true)))
        delete json;

    if(success)
        LogMessage("[TestDump] done: \n%s", buffer);

    return success;
}

void TestFindFirst(Json json, JsonValidator cond, JsonType type = JInvalidType)
{
    if(!json) return;

    Json buffer;

    if(!(buffer = json.FindFirst(cond, type)))
        LogMessage("[TestFindFirst]: item not found");

    if(buffer)
        LogMessage("[TestFindFirst] %x: type: %d", buffer, buffer.Type);

    delete buffer;
}

stock Json MakeJsonArray(char[] error = NULL_STRING, int len = 0)
{
    return (new JsonBuilder("[]", error, len))
        .PushString("Hello, Jansson!")
        .PushFloat(3.4444)
        .PushInt(3)
        .PushInt64("123123213123123")
        .PushBool(false)
        .Push(null)
        .Build();
}

stock Json MakeJsonObject(char[] error = NULL_STRING, int len = 0)
{
    return (new JsonBuilder("{}", error, len))
        .SetString("version", "1.7.x")
        .SetFloat("float", 3.4444)
        .SetInt("integer", 3)
        .SetInt64("int64", "12321321312321312")
        .SetBool("bool", true)
        .Set("null", null)
        .Build();
}

stock bool StringObjectExpected(const Json json)
{
    return json.Type == JStringType;
}