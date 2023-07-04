#include <jansson>

public void OnPluginStart()
{
    Json b;
    Json o = (new JsonBuilder("{}"))
        .SetString("abc", "dbc")
        .SetFloat("ab", 012.32)
        .SetInt("ada", 232)
        .SetBool("asdada", true)
        .Set("array", (b = (new JsonBuilder("[]"))
            .PushString("asdada")
            .PushInt(41)
            .Build()))
        .Build();

    LogMessage("B type: %d", b.Type);
    LogMessage("O type; %d", o.Type);

    LogMessage("Simple int: %d", asJSONA(asJSONO(o).Get("array")).GetInt(1, true));

    ArrayList keys = asJSONO(o).Keys;

    LogMessage("Keys: %x", keys);

    char buffer[1024];
    if(keys)
    {
        for(int i = 0; i < keys.Length; i++)
        {
            keys.GetString(i, buffer, sizeof(buffer));
            LogMessage("Key(%d): %s", i + 1, buffer);
        }
    }
        
    delete keys;

    // char buffer[1024];
    if(b.Dump(buffer, sizeof(buffer), JSON_INDENT(44), true))
        LogMessage("Array: %s", buffer);

    else delete b;

    if(o.Dump(buffer, sizeof(buffer), JSON_INDENT(4), true))
        LogMessage("Dump: %s", buffer);

    else delete o;
}