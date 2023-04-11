#if defined _jansson_enums_included_
    #endinput
#endif
#define _jansson_enums_included_

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

// Json update types
enum JsonObjectUpdateType
{
    UpdDefault = 0,
    UpdExisting,
    UpdMissing,
    UpdRecursive
};

enum JsonErrorCode
{
    jecUnknown,
    jecOutOfMemory,
    jecStackOverflow,
    jecCannotOpenFile,
    jecInvalidArgument,
    jecInvalidUTF8,
    jecPrematureEndOfInput,
    jecEndOfInputExpected,
    jecInvalidSyntax,
    jecInvalidFormat,
    jecWrongType,
    jecNullCharacter,
    jecNullValue,
    jecNullByteInKey,
    jecDuplicateKey,
    jecNumericOverflow,
    jecItemNotFound,
    jecIndexOutOfRange
};