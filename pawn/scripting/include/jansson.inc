#if defined _jansson_included_
    #endinput
#endif
#define _jansson_included_

#include "jansson/enums.inc"

methodmap JsonError < Handle
{
    public static native bool IsEquals(JsonError obj1, JsonError obj2);

    property JsonErrorCode Code {
        public native get();
    }

    property int Line {
        public native get();
    }

    property int Column {
        public native get();
    }

    public native bool Text(char[] buffer, int size);
    public native bool Source(char[] buffer, int size);
    public native bool IsEmpty();
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

    // ....
    // 
    // @return          size in bytes or -1 on failure
    property int Size {
        public native get();
    }

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

    // Retrieves the type of current object
    property JsonType Type {
        public native get();
    }

    // Retrieves error object
    property JsonError Error {
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

        JsonType type;
        if((type = buffer.Type) == JBooleanType)
            value = buffer.AsBool(true);

        delete buffer;
        return type == JBooleanType;
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

        JsonType type;
        if((type = buffer.Type) == JRealType)
            value = buffer.AsFloat(true);

        delete buffer;
        return type == JRealType;
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

        JsonType type;
        if((type = buffer.Type) == JIntegerType)
            value = buffer.AsBool(true);

        delete buffer;
        return type == JIntegerType;
    }

    // Retrieves a 64-bit integer value from the object.
    //
    // @param key        Key string.
    // @param buffer     String buffer to store value.
    // @param maxlength  Maximum length of the string buffer.
    // @return           True on success, false if the key was not found.
//    public native bool GetInt64(const char[] key, char[] buffer, int maxlength);

    // Retrieves a string value from the object.
    //
    // @param key           Key string.
    // @param buffer        String buffer to store value.
    // @param maxlength     Maximum length of the string buffer.
    // @param freeHandle    Auto delete current handle after call successfully end
    // @return              True on success. False if the key was not found, or the value is not a string.
    public native bool GetString(const char[] key, char[] buffer, int maxlength, bool freeHandle = false)
    
    // Trying to get a Json value 
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

        JsonType type;
        if((type = buffer.Type) == JStringType)
            buffer.AsString(value, size, true);

        delete buffer;
        return type == JStringType;
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
//    public native bool SetInt64(const char[] key, const char[] value);

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
//    public native bool Remove(const char[] key);

    // Update an object keys.
    //
    // @param   obj                 Another object
    // @param   updType             Update type (see JsonUpdateType enum)
    // @param   freeAnotherObject   Auto delete another handle after call successfully end
    //
    // @return            True on success
    public native bool Update(JsonObject obj, JsonObjectUpdateType updType = UpdDefault, bool freeAnotherObject = false);

    // ...
    public native JsonObjectKeyIterator Keys();
};

/**
 * A JSONObjectKeys is created via JSONObject.Keys(). It allows the keys of an
 * object to be iterated. The JSONObjectKeys must be freed with delete or
 * CloseHandle().
 */
methodmap JsonObjectKeyIterator < Handle
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
//    public native bool GetInt64(int index, char[] buffer, int maxlength);

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
//    public native bool SetInt64(int index, const char[] value);

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
//    public native bool PushInt64(const char[] value);

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
};

#include "jansson/stocks.inc"
#include "jansson/builder.inc"

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