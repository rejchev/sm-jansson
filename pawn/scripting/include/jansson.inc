#if defined _jansson_included_
    #endinput
#endif
#define _jansson_included_

// Maximum indentation
#define JsonMaxIndent 0x1F

// Pretty-print the result, identing with n spaces
stock int JsonPretty(int n, const int max = JsonMaxIndent) {
    return n & max;
}

// Output floats with at most n digits of precision
stock int JsonFloatPrecision(int n, const int mask = JsonMaxIndent) {
    return (n & mask) << 11;
}

enum JsonDecodingFlag
{
    RejectDuplicates        = 0x1,		/**< Error if any JSON object contains duplicate keys */
    DisableEOFCheck         = 0x2,		/**< Allow extra data after a valid JSON array or object */
    DecodeAny               = 0x4,		/**< Decode any value */
    DecodeIntegerAsReal     = 0x8,		/**< Interpret all numbers as floats */
    AllowNull               = 0x10		/**< Allow \u0000 escape inside string values */
};

enum JsonEncodingFlag
{
    Compact                 = 0x20,		    /**< Compact representation */
    EnsureASCII             = 0x40,		    /**< Escape all Unicode characters outside the ASCII range */
    SortKeys                = 0x80,		    /**< Sort object keys */
    EncodeAny               = 0x200,		/**< Encode any value */
    EscapeSlash             = 0x400,		/**< Escape / with \/ */
    Embed                   = 0x10000
};

// Json types
enum JsonType
{
    JInvalidType = -1,
    JObjectType,
    JArrayType,
    JStringType,
    JIntegerType,
    JRealType,
    JBooleanType,
    JNullType
};

// Json object update types
enum JsonObjectUpdateType
{
    UpdDefault = 0,
    UpdExisting,
    UpdMissing,
    UpdRecursive
};

// Generic type for encoding JSON.
methodmap Json < Handle
{
    // Create JSON handle from string
    //
    // @param value      JSON string.
    // @param flags      Encoding flags.
    // @return           JSON handle or NULL.
    // @error            Invalid syntax
    public native Json(const char[] value, int flags = 0);

    // Create JSON handle from path
    //
    // @param path       File to read from.
    // @param flags      Encoding flags.
    // @return           JSON handle or NULL
    // @exception        Invalid syntax
    public static native Json JsonF(const char[] path, int flags = 0);

    // Writes the JSON string representation to a file.
    //
    // @param file       File to write to.
    // @param flags      Encoding flags.
    // @param freeHandle Auto delete handle after call
    // @return           True on success, false on failure.
    public native bool ToFile(const char[] path, int flags = 0, bool freeHandle = false);

    // Is JSON equals
    // 
    // @param obj       Another object
    // @return          True on success
    public native bool Equal(Json obj);

    // Retrieves the JSON string representation.
    //
    // @param buffer     String buffer to write to.
    // @param maxlength  Maximum length of the string buffer.
    // @param flags      Encoding flags.
    // @param freeHandle Auto delete current handle after call successfully end
    //
    // @return           True on success, false on failure.
    public native bool Dump(char[] buffer, int maxlength, int flags = 0, bool freeHandle = false);

    // View Json as bool (must be JsonType::Boolean).
    //
    // @param freeHandle    Auto delete current handle after call successfully end
    //
    // @return              Value
    public native bool AsBool(bool freeHandle = false);

    // View Json as int (must be JsonType::Integer).
    //
    // @param freeHandle    Auto delete current handle after call successfully end
    //
    // @return              Value
    public native int AsInt(bool freeHandle = false);

    // View Json as int64 (must be JsonType::Integer).
    //
    // @param freeHandle    Auto delete current handle after call successfully end
    //
    // @return              Value
    public native bool AsInt64(char[] buffer, int size, bool freeHandle = false);

    // View Json as float (must be JsonType::Real).
    //
    // @param freeHandle    Auto delete current handle after call successfully end
    //
    // @return              Value
    public native float AsFloat(bool freeHandle = false);

    // View Json as string (must be JsonType::String).
    //
    // @param buffer        String buffer
    // @param size          String buffer size
    // @param freeHandle    Auto delete current handle after call successfully end
    //
    // @return              success or not
    public native bool AsString(char[] buffer, int size, bool freeHandle = false);

    public native void Clear();

    // Size by json type
    // 
    // @return          On object - keys count
    //                  On array  - items count
    //                  On string  - string length
    //                  On Invalid - 0
    //                  On Another - 1
    property int Size {
        public native get();
    }

    // Retrieves the type of current object
    property JsonType Type {
        public native get();
    }

    // Is this json valid
    property bool Valid {
        public native get();
    }
};

methodmap JsonObject < Json
{
    // Retrieves a JSON value from the object
    //
    // The JSON must be freed via delete or CloseHandle().
    //
    // @param key           Key string.
    // @param freeHandle    Auto delete current handle after call successfully end
    // @return              Json on success or null then (handle err, this is not an object or key is not exist)
    // @error               On Error() is not empty
    public native Json Get(const char[] key, bool freeHandle = false);

    // Retrieves a boolean value from the object.
    //
    // @param key           Key string.
    // @param freeHandle    Auto delete current handle after call successfully end

    // @return              Value read.
    // @error               Invalid key.
    public native bool GetBool(const char[] key, bool freeHandle = false);

    // Trying to get Boolean value 
    //
    // @param key           Key string
    // @param freeHandle    Auto delete current handle after call successfully end
    // @param value         Bool buffer for storage value
    // @return              True on success
    public bool TryGetBool(const char[] key, bool &value, bool freeHandle = false)
    {
        value = false;

        Json buffer;
        if(!(buffer = this.Get(key, freeHandle)))
            return false;

        value = buffer.AsBool(true);

        bool success;
        if(!(success = buffer == null))
            delete buffer;

        return success;
    }

    // Retrieves a float value from the object.
    //
    // @param key           Key string.
    // @param freeHandle    Auto delete current handle after call successfully end
    //
    // @return              Value read.
    // @error               Invalid key.
    public native float GetFloat(const char[] key, bool freeHandle = false);

    // Trying to get Float value 
    //
    // @param key        Key string
    // @param value      Float buffer for storage value
    // @return           True on success
    public bool TryGetFloat(const char[] key, float &value, bool freeHandle = false)
    {
        value = 0.0;

        Json buffer;
        if(!(buffer = this.Get(key, freeHandle)))
            return false;

        value = buffer.AsFloat(true);

        bool success;
        if(!(success = buffer == null))
            delete buffer;

        return success;
    }

    // Retrieves an integer value from the object.
    //
    // @param key           Key string.
    // @param freeHandle    Auto delete current handle after call successfully end
    //
    // @return              Value read.
    // @error               Invalid key.
    public native int GetInt(const char[] key, bool freeHandle = false)

    // Trying to get Integer value 
    //
    // The JSON must be freed via delete or CloseHandle().
    //
    // @param key        Key string
    // @param value      Integer buffer for storage value
    // @return           True on success
    public bool TryGetInt(const char[] key, int &value, bool freeHandle = false)
    {
        value = 0;

        Json buffer;
        if(!(buffer = this.Get(key, freeHandle)))
            return false;

        value = buffer.AsInt(true);

        bool success;
        if(!(success = buffer == null))
            delete buffer;

        return success;
    }

    // Retrieves a 64-bit integer value from the object.
    //
    // @param key        Key string.
    // @param buffer     String buffer to store value.
    // @param maxlength  Maximum length of the string buffer.
    // @return           True on success, false if the key was not found.
    public native bool GetInt64(const char[] key, char[] buffer, int maxlength, bool freeHandle = false);

    // Trying to get int64 value 
    //
    // @param key        Key string
    // @param value      String buffer for storage value
    // @param size       Buffer size
    // @return           True on success
    public bool TryGetInt64(const char[] key, char[] value, int size, bool freeHandle = false)
    {
        value[0] = '\0';

        Json buffer;
        if(!(buffer = this.Get(key, freeHandle)))
            return false;

        if(!buffer.AsInt64(value, size, true))
            delete buffer;
        
        return value[0] != '\0';
    }

    // Retrieves a string value from the object.
    //
    // @param key           Key string.
    // @param buffer        String buffer to store value.
    // @param maxlength     Maximum length of the string buffer.
    // @param freeHandle    Auto delete current handle after call successfully end
    // @return              True on success. False if the key was not found, or the value is not a string.
    public native bool GetString(const char[] key, char[] buffer, int maxlength, bool freeHandle = false)
    
    // Trying to get string value 
    //
    // @param key        Key string
    // @param value      String buffer for storage value
    // @param size       Buffer size
    // @return           True on success
    public bool TryGetString(const char[] key, char[] value, int size, bool freeHandle = false)
    {
        value[0] = '\0';

        Json buffer;
        if(!(buffer = this.Get(key, freeHandle)))
            return false;

        if(!buffer.AsString(value, size, true))
            delete buffer;
        
        return value[0] != '\0';
    }

    // Retrieves an item type from the array.
    //
    // @param key        Key string
    // @return           JsonType.
    public native JsonType GetType(const char[] key);

    // Returns whether or not a key exists in the object.
    //
    // @param key        Key string.
    // @return           True if the key exists, false otherwise.
    public native bool HasKey(const char[] key);

    // Sets an array or object value in the object, either inserting a new entry or replacing an old one.
    //
    // @param key        Key string.
    // @param value      Value to store at this key (can be NULL to store JSON_NULL).
    // @return           True on success, false on failure.
    public native bool Set(const char[] key, Json value);

    // Sets a boolean value in the object, either inserting a new entry or replacing an old one.
    //
    // @param key        Key string.
    // @param value      Value to store at this key.
    // @return           True on success, false on failure.
    public native bool SetBool(const char[] key, bool value);

    // Sets a float value in the object, either inserting a new entry or replacing an old one.
    //
    // @param key        Key string.
    // @param value      Value to store at this key.
    // @return           True on success, false on failure.
    public native bool SetFloat(const char[] key, float value);

    // Sets an integer value in the object, either inserting a new entry or replacing an old one.
    //
    // @param key        Key string.
    // @param value      Value to store at this key.
    // @return           True on success, false on failure.
    public native bool SetInt(const char[] key, int value);

    // Sets a 64-bit integer value in the object, either inserting a new entry or replacing an old one.
    //
    // @param key        Key string.
    // @param value      Value to store at this key.
    // @return           True on success, false on failure.
    public native bool SetInt64(const char[] key, const char[] value);

    // Sets a string value in the object, either inserting a new entry or replacing an old one.
    //
    // @param key        Key string.
    // @param value      Value to store at this key.
    // @return           True on success, false on failure.
    public native bool SetString(const char[] key, const char[] value);

    // Removes an entry from the object.
    //
    // @param key        Key string.
    // @return           True on success, false if the key was not found.
    public native bool Remove(const char[] key);

    // Update an object keys.
    //
    // @param   obj                 Another object
    // @param   updType             Update type (see JsonUpdateType enum)
    // @param   freeAnotherObject   Auto delete another handle after call successfully end
    //
    // @return            True on success
    public native bool Update(JsonObject obj, JsonObjectUpdateType updType = UpdDefault, bool freeAnotherObject = false);

    // Get an object keys
    //
    // @param   type                Filter based on json type of key (grabbing all keys by default)
    // @param   flags               Encoding flags
    //
    // @return                      null on zero size
    public native JsonArray Keys(JsonType type = JInvalidType, int flags = 0);

    // keys count
    property int Size {
        public native get();
    }
};

methodmap JsonArray < Json
{
    // Retrieves an array or object value from the array.
    //
    // The JSON must be freed via delete or CloseHandle().
    //
    // @param index      Index in the array.
    // @return           Value read (can be JSON_NULL).
    // @error            Invalid index.
    public native Json Get(int index, bool feeHandle = false);

    // Retrieves a boolean value from the array.
    //
    // @param index      Index in the array.
    // @return           Value read.
    // @error            Invalid index.
    public native bool GetBool(int index, bool freeHandle = false);

    // Retrieves a float value from the array.
    //
    // @param index      Index in the array.
    // @return           Value read.
    // @error            Invalid index.
    public native float GetFloat(int index, bool freeHandle = false);

    // Retrieves an integer value from the array.
    //
    // @param index      Index in the array.
    // @return           Value read.
    // @error            Invalid index.
    public native int GetInt(int index, bool freeHandle = false);

    // Retrieves an 64-bit integer value from the array.
    //
    // @param index      Index in the array.
    // @param buffer     Buffer to copy to.
    // @param maxlength  Maximum size of the buffer.
    // @error            Invalid index.
    public native bool GetInt64(int index, char[] buffer, int maxlength, bool freeHandle = false);

    // Retrieves a string value from the array.
    //
    // @param index      Index in the array.
    // @param buffer     Buffer to copy to.
    // @param maxlength  Maximum size of the buffer.
    // @return           True on success, false if the value is not a string.
    // @error            Invalid index.
    public native bool GetString(int index, char[] buffer, int maxlength, bool freeHandle = false);

    // Retrieves an item type from the array.
    //
    // @param index      Index in the array.
    // @return           JsonType.
    public native JsonType GetType(int index);

    // Sets an array or object value in the array.
    //
    // @param index      Index in the array.
    // @param value      Value to set (can be NULL to store JSON_NULL).
    // @return           True on success, false on failure.
    public native bool Set(int index, Json value);

    // Sets a boolean value in the array.
    //
    // @param index      Index in the array.
    // @param value      Value to set.
    // @return           True on success, false on failure.
    public native bool SetBool(int index, bool value);

    // Sets a float value in the array.
    //
    // @param index      Index in the array.
    // @param value      Value to set.
    // @return           True on success, false on failure.
    public native bool SetFloat(int index, float value);

    // Sets an integer value in the array.
    //
    // @param index      Index in the array.
    // @param value      Value to set.
    // @return           True on success, false on failure.
    public native bool SetInt(int index, int value);

    // Sets a 64 bit integer value in the array.
    //
    // @param index      Index in the array.
    // @param value      64-bit integer value to set.
    // @return           True on success, false on failure.
    public native bool SetInt64(int index, const char[] value);

    // Sets a string value in the array.
    //
    // @param index      Index in the array.
    // @param value      String value to set.
    // @return           True on success, false on failure.
    public native bool SetString(int index, const char[] value);

    // Pushes an array or object value onto the end of the array, adding a new index.
    //
    // @param value      Value to push (can be NULL to store JSON_NULL).
    // @return           True on success, false on failure.
    public native bool Push(Json value);

    // Pushes a boolean value onto the end of the array, adding a new index.
    //
    // @param value      Value to push.
    // @return           True on success, false on failure.
    public native bool PushBool(bool value);

    // Pushes a float value onto the end of the array, adding a new index.
    //
    // @param value      Value to push.
    // @return           True on success, false on failure.
    public native bool PushFloat(float value);

    // Pushes an integer value onto the end of the array, adding a new index.
    //
    // @param value      Value to push.
    // @return           True on success, false on failure.
    public native bool PushInt(int value);

    // Pushes a 64-bit integer value onto the end of the array, adding a new index.
    //
    // @param value      64-bit integer value to push.
    // @return           True on success, false on failure.
    public native bool PushInt64(const char[] value);

    // Pushes a string value onto the end of the array, adding a new index.
    //
    // @param value      String value to push.
    // @return           True on success, false on failure.
    public native bool PushString(const char[] value);

    // Appends all elements from another array to the end of this array.
    //
    // @param other      An another json array
    // @return           True on success, false on failure.
    public native bool Extend(JsonArray another, bool freeAnotherHandle = false);

    // Removes an entry from the array.
    //
    // @param index      Index in the array to remove.
    // @return           True on success, false on invalid index.
    public native bool Remove(int index);

    // keys count
    property int Size {
        public native get();
    }
};

#define asJSON(%0) view_as<Json>(%0)
#define asJSONO(%0) view_as<JsonObject>(%0)
#define asJSONA(%0) view_as<JsonArray>(%0)

#if defined JSON_INCLUDE_BUILDER

#define asJSONB(%0) view_as<JsonBuilder>(%0)

methodmap JsonBuilder < Json
{
    public JsonBuilder(const char[] str)
    {
        return view_as<JsonBuilder>(new Json(str));
    }

    public JsonBuilder SetString(const char[] k, const char[] v)
    {
        if(this.Type == JObjectType)
            asJSONO(this).SetString(k, v);

        return this;
    }

    public JsonBuilder Set(const char[] k, Json v)
    {
        if(this.Type == JObjectType)
            asJSONO(this).Set(k, v);

        return this;
    }

    public JsonBuilder SetInt(const char[] k, int v)
    {
        if(this.Type == JObjectType)
            asJSONO(this).SetInt(k, v);

        return this;
    }

    public JsonBuilder SetBool(const char[] k, bool v)
    {
        if(this.Type == JObjectType)
            asJSONO(this).SetBool(k, v);

        return this;
    }

    public JsonBuilder SetInt64(const char[] k, const char[] v)
    {
        if(this.Type == JObjectType)
            asJSONO(this).SetInt64(k, v);

        return this;
    }

    public JsonBuilder SetFloat(const char[] k, float v)
    {
        if(this.Type == JObjectType)
            asJSONO(this).SetFloat(k, v);

        return this;
    }

    public JsonBuilder PushString(const char[] v)
    {
        if(this.Type == JArrayType)
            asJSONA(this).PushString(v);

        return this;
    }

    public JsonBuilder PushInt(int v)
    {
        if(this.Type == JArrayType)
            asJSONA(this).PushInt(v);

        return this;
    }

    public JsonBuilder PushInt64(const char[] v)
    {
        if(this.Type == JArrayType)
            asJSONA(this).PushInt64(v);

        return this;
    }

    public JsonBuilder PushBool(bool v)
    {
        if(this.Type == JArrayType)
            asJSONA(this).PushBool(v);

        return this;
    }

    public JsonBuilder Push(Json v)
    {
        if(this.Type == JArrayType)
            asJSONA(this).Push(v);

        return this;
    }

    public JsonBuilder PushFloat(float v)
    {
        if(this.Type == JArrayType)
            asJSONA(this).PushFloat(v);

        return this;
    }

    public JsonBuilder Clear()
    {
        asJSON(this).Clear();

        return this;
    }

    public Json Build()
    {
        return asJSON(this);
    }
}
#endif

/**
 * Do not edit below this line!
 */
public Extension __ext_jansson =
{
    name = "Jansson in Pawn",
    file = "jansson.ext",
#if defined AUTOLOAD_EXTENSIONS
    autoload = 1,
#else
    autoload = 0,
#endif
#if defined REQUIRE_EXTENSIONS
    required = 1,
#else
    required = 0,
#endif
};