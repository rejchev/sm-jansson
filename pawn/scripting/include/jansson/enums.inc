#if defined _jansson_enums_included_
    #endinput
#endif
#define _jansson_enums_included_

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

// Json types
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

// Json update types
enum JsonUpdateType
{
    JSON_UPDATE = 0, 
    JSON_UPDATE_EXISTING,
    JSON_UPDATE_MISSING,
    JSON_UPDATE_RECURSIVE
};