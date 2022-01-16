#if defined _jansson_included_
    #endinput
#endif
#define _jansson_included_



// Decoding flags
enum
{
    JSON_REJECT_DUPLICATES  = 0x1,		/**< Error if any JSON object contains duplicate keys */
    JSON_DISABLE_EOF_CHECK  = 0x2,		/**< Allow extra data after a valid JSON array or object */
    JSON_DECODE_ANY         = 0x4,		/**< Decode any value */
    JSON_DECODE_INT_AS_REAL = 0x8,		/**< Interpret all numbers as floats */
    JSON_ALLOW_NUL          = 0x10		/**< Allow \u0000 escape inside string values */
};

// Encoding flags
enum
{
    JSON_COMPACT      = 0x20,		/**< Compact representation */
    JSON_ENSURE_ASCII = 0x40,		/**< Escape all Unicode characters outside the ASCII range */
    JSON_SORT_KEYS    = 0x80,		/**< Sort object keys */
    JSON_ENCODE_ANY   = 0x200,		/**< Encode any value */
    JSON_ESCAPE_SLASH = 0x400,		/**< Escape / with \/ */
    JSON_EMBED        = 0x10000		/**< Omit opening and closing braces of the top-level object */
};

enum JsonType
{
    JSON_OBJECT = 0,
    JSON_ARRAY,
    JSON_STRING,
    JSON_INTEGER,
    JSON_REAL,
    JSON_TRUE,
    JSON_FALSE,
    JSON_NULL
};

// Maximum indentation
static const int JSON_MAX_INDENT = 0x1F;

// Pretty-print the result, indenting with n spaces
stock int JSON_INDENT(int n)
{
    return n & JSON_MAX_INDENT;
}

stock bool JSON_TYPE_BOOLEAN(JsonType t)
{
    return (t & JSON_TRUE) || (t & JSON_FALSE);
}

stock bool JSON_IS_NULL(JsonType t)
{
    return t == JSON_NULL;
}

// Output floats with at most n digits of precision
stock int JSON_REAL_PRECISION(int n)
{
    return (n & 0x1F) << 11;
}

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
    // @return           True on success, false on failure.
    public native bool ToFile(const char[] path, int flags = 0);

    // Retrieves the JSON string representation.
    //
    // @param buffer     String buffer to write to.
    // @param maxlength  Maximum length of the string buffer.
    // @param flags      Encoding flags.
    // @return           True on success, false on failure.
    public native bool ToString(char[] buffer, int maxlength, int flags = 0);

    // Retrieves the type of current object
    property JsonType Type {
        public native get();
    }
};

methodmap JsonObject < Json
{
    // Retrieves a JSON value from the object 
    //
    // The JSON must be freed via delete or CloseHandle().
    //
    // @param key        Key string.
    // @return           Value read (can be JSON_NULL).
    // @error            Invalid key.
    public native Json Get(const char[] key);

    // Retrieves a boolean value from the object.
    //
    // @param key        Key string.
    // @return           Value read.
    // @error            Invalid key.
    public native bool GetBool(const char[] key);

    // Retrieves a float value from the object.
    //
    // @param key        Key string.
    // @return           Value read.
    // @error            Invalid key.
    public native float GetFloat(const char[] key);

    // Retrieves an integer value from the object.
    //
    // @param key        Key string.
    // @return           Value read.
    // @error            Invalid key.
    public native int GetInt(const char[] key);

    // Retrieves a 64-bit integer value from the object.
    //
    // @param key        Key string.
    // @param buffer     String buffer to store value.
    // @param maxlength  Maximum length of the string buffer.
    // @return           True on success, false if the key was not found.
    public native bool GetInt64(const char[] key, char[] buffer, int maxlength);

    // Retrieves a string value from the object.
    //
    // @param key        Key string.
    // @param buffer     String buffer to store value.
    // @param maxlength  Maximum length of the string buffer.
    // @return           True on success. False if the key was not found, or the value is not a string.
    public native bool GetString(const char[] key, char[] buffer, int maxlength);
    
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

    // Sets a null value in the object, either inserting a new entry or replacing an old one.
    //
    // @param key        Key string.
    // @return           True on success, false on failure.
    #pragma deprecated Use JsonObject.Set() instead
    public bool SetNull(const char[] key) {
        return this.Set(key, null);
    }

    #pragma deprecated Use JsonObject.GetType() instead
    public bool IsNull(const char[] key) {
        return JSON_IS_NULL(this.GetType(key));
    }

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

    // Clears the object of all entries.
    // @return           True on success, false on failure.
    public native bool Clear();

    // Returns an iterator for the object's keys. See JSONObjectKeys.
    public native JsonKeys Keys();

    // Retrieves the size of the object.
    property int Size {
        public native get();
    }
};

/**
 * A JSONObjectKeys is created via JSONObject.Keys(). It allows the keys of an
 * object to be iterated. The JSONObjectKeys must be freed with delete or
 * CloseHandle().
 */
methodmap JsonKeys < Handle
{
    // Reads an object key, then advances to the next key if any.
    //
    // @param buffer     String buffer to store key.
    // @param maxlength  Maximum length of the string buffer.
    // @return           True on success, false if there are no more keys.
    public native bool Next(char[] buffer, int maxlength);
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
    public native Json Get(int index);

    // Retrieves a boolean value from the array.
    //
    // @param index      Index in the array.
    // @return           Value read.
    // @error            Invalid index.
    public native bool GetBool(int index);

    // Retrieves a float value from the array.
    //
    // @param index      Index in the array.
    // @return           Value read.
    // @error            Invalid index.
    public native float GetFloat(int index);

    // Retrieves an integer value from the array.
    //
    // @param index      Index in the array.
    // @return           Value read.
    // @error            Invalid index.
    public native int GetInt(int index);

    // Retrieves an 64-bit integer value from the array.
    //
    // @param index      Index in the array.
    // @param buffer     Buffer to copy to.
    // @param maxlength  Maximum size of the buffer.
    // @error            Invalid index.
    public native bool GetInt64(int index, char[] buffer, int maxlength);

    // Retrieves a string value from the array.
    //
    // @param index      Index in the array.
    // @param buffer     Buffer to copy to.
    // @param maxlength  Maximum size of the buffer.
    // @return           True on success, false if the value is not a string.
    // @error            Invalid index.
    public native bool GetString(int index, char[] buffer, int maxlength);

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

    // Sets a null value in the array.
    //
    // @param index      Index in the array.
    // @return           True on success, false on failure.
    #pragma deprecated Use JsonArray.Set() instead
    public bool SetNull(int index) {
        return this.Set(index, null);
    }

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

    // Pushes a null value onto the end of the array, adding a new index.
    // @return           True on success, false on failure.
    #pragma deprecated Use JsonArray.Push() instead
    public bool PushNull() {
        return this.Push(null);
    }

    // Pushes a string value onto the end of the array, adding a new index.
    //
    // @param value      String value to push.
    // @return           True on success, false on failure.
    public native bool PushString(const char[] value);

    // Removes an entry from the array.
    //
    // @param index      Index in the array to remove.
    // @return           True on success, false on invalid index.
    public native bool Remove(int index);

    // Clears the array of all entries.
    // @return           True on success, false on failure.
    public native bool Clear();

    // Retrieves the size of the array.
    property int Length {
        public native get();
    }
};

#define asJSON(%1)  view_as<Json>(%1)
#define asJSONO(%1) view_as<JsonObject>(%1)
#define asJSONA(%1) view_as<JsonArray>(%1)
#define asJSONK(%1) view_as<JsonKeys>(%1)

stock bool JSON_TYPE_EQUAL(Json o, JsonType t) 
{
    return o.Type == t;
}

stock bool JSONO_TYPE_EQUAL(Json o, const char[] k, JsonType t)
{
    return asJSONO(o).GetType(k) == t;
}

stock bool JSONA_TYPE_EQUAL(Json o, const int i, JsonType t)
{
    return asJSONA(o).GetType(i) == t;
}

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