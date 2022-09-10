#if defined _jansson_builder_included_
    #endinput
#endif
#define _jansson_builder_included_

// #include "enums.inc"
// #include "stocks.inc"

methodmap JsonBuilder < Json
{
    public JsonBuilder(const char[] str)
    {
        return view_as<JsonBuilder>(new Json(str));
    }

    public JsonBuilder SetString(const char[] k, const char[] v)
    {
        if(JSON_TYPE_EQUAL(this, JSON_OBJECT))
            asJSONO(this).SetString(k, v);

        return this;
    }

    public JsonBuilder Set(const char[] k, Json v)
    {
        if(JSON_TYPE_EQUAL(this, JSON_OBJECT))
            asJSONO(this).Set(k, v);

        return this;
    }

    public JsonBuilder SetInt(const char[] k, int v)
    {
        if(JSON_TYPE_EQUAL(this, JSON_OBJECT))
            asJSONO(this).SetInt(k, v);

        return this;
    }

    public JsonBuilder SetBool(const char[] k, bool v)
    {
        if(JSON_TYPE_EQUAL(this, JSON_OBJECT))
            asJSONO(this).SetBool(k, v);

        return this;
    }

    public JsonBuilder SetInt64(const char[] k, const char[] v)
    {
        if(JSON_TYPE_EQUAL(this, JSON_OBJECT))
            asJSONO(this).SetInt64(k, v);

        return this;
    }

    public JsonBuilder SetFloat(const char[] k, float v)
    {
        if(JSON_TYPE_EQUAL(this, JSON_OBJECT))
            asJSONO(this).SetFloat(k, v);

        return this;
    }

    public JsonBuilder PushString(const char[] v)
    {
        if(JSON_TYPE_EQUAL(this, JSON_ARRAY))
            asJSONA(this).PushString(v);

        return this;
    }

    public JsonBuilder PushInt(int v)
    {
        if(JSON_TYPE_EQUAL(this, JSON_ARRAY))
            asJSONA(this).PushInt(v);

        return this;
    }

    public JsonBuilder PushInt64(const char[] v)
    {
        if(JSON_TYPE_EQUAL(this, JSON_ARRAY))
            asJSONA(this).PushInt64(v);

        return this;
    }

    public JsonBuilder PushBool(bool v)
    {
        if(JSON_TYPE_EQUAL(this, JSON_ARRAY))
            asJSONA(this).PushBool(v);

        return this;
    }

    public JsonBuilder Push(Json v)
    {
        if(JSON_TYPE_EQUAL(this, JSON_ARRAY))
            asJSONA(this).Push(v);

        return this;
    }

    public JsonBuilder PushFloat(float v)
    {
        if(JSON_TYPE_EQUAL(this, JSON_ARRAY))
            asJSONA(this).PushFloat(v);

        return this;
    }

    public JsonBuilder Clear()
    {
        if(JSON_TYPE_EQUAL(this, JSON_ARRAY))
            asJSONA(this).Clear();
        
        else if(JSON_TYPE_EQUAL(this, JSON_OBJECT))
            asJSONO(this).Clear();

        return this;
    }

    public Json Build()
    {
        return asJSON(this);
    }
}