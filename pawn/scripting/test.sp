#pragma newdecls required

#define JSON_INCLUDE_BUILDER

#include <jansson>

public void OnPluginStart()
{
    Json b;
    Json o = (new JsonBuilder("{}"))
        .SetString("string", "dbc")
        .SetFloat("float", 012.32)
        .SetInt64("int64", "99999999999")
        .SetInt("int", 232)
        .SetBool("bool", true)
        .Set("array", (b = (new JsonBuilder("[]"))
            .PushString("asdada")
            .PushInt(41)
            .PushInt64("99999999999")
            .Build()))
        .Build();

    LogMessage("B type: %d", b.Type);
    LogMessage("O type; %d", o.Type);

    LogMessage("Simple int: %d", asJSONA(asJSONO(o).Get("array")).GetInt(1, true));

    JsonArray keys = asJSONO(o).Keys();

    LogMessage("Keys: %x", keys);

    char buffer[1024];
    if(keys)
    {
        for(int i = 0; i < keys.Size; i++)
        {
            if(!keys.GetString(i, buffer, sizeof(buffer)))
                LogMessage("Fail on get string");

            LogMessage("Key(%d): %s", i + 1, buffer);
        }

        
        delete keys;
    }
    
    if(asJSONA(asJSONO(o).Get("array")).GetInt64(2, buffer, sizeof(buffer), true))
        LogMessage("int64: %s", buffer);

    // char buffer[1024];
    if(b.Dump(buffer, sizeof(buffer), 0, true))
        LogMessage("Array: %s", buffer);

    else delete b;

    if(o.Dump(buffer, sizeof(buffer), JsonPretty(4), true))
        LogMessage("Dump: %s", buffer);

    else delete o;
}