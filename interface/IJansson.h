
#ifndef _INCLUDE_SOURCEMOD_JANSSON_IFACE_H_
#define _INCLUDE_SOURCEMOD_JANSSON_IFACE_H_

#include <IShareSys.h>
#include <IHandleSys.h>

#define SMINTERFACE_JANSSON_NAME        "IJansson"
#define SMINTERFACE_JANSSON_VERSION	    1


namespace SourceMod
{

    enum JsonType
    {
        Invalid = -1,
        Object,
        Array,
        String,
        Integer,
        Real,
        Boolean,
        Null
    };

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

    enum JsonErrorCode
    {
        Unknown,
        OutOfMemory,
        StackOverflow,
        CannotOpenFile,
        InvalidArgument,
        InvalidUTF8,
        PrematureEndOfInput,
        EndOfInputExpected,
        InvalidSyntax,
        InvalidFormat,
        WrongType,
        NullCharacter,
        NullValue,
        NullByteInKey,
        DuplicateKey,
        NumericOverflow,
        ItemNotFound,
        IndexOutOfRange
    };

    enum JsonObjectUpdateType
    {
        Default,
        Existing,
        Missing,
        Recursive
    };

    struct HandleTypeDetails
    {
        const char *name;

        const TypeAccess *access;
        const HandleAccess *hndlAccess;
        const IdentityToken_t *ident;
        
        HandleType_t parent;
        HandleType_t type;
    };

    class IJson;

    // TODO: Update, Size, Keys, KeyIterator
    class IJsonObject;
    class IJsonArray;
    class IJsonError;

    class IJansson : SMInterface
    {
        public:
            const char *GetInterfaceName()
            {
                return SMINTERFACE_JANSSON_NAME;
            }
            unsigned int GetInterfaceVersion()
            {
                return SMINTERFACE_JANSSON_VERSION;
            }

        // public:
        //     virtual HandleTypeDetails JsonTypeDetails() const =0;
        //     virtual HandleTypeDetails JsonKeysTypeDetails() const =0;

        public:
            virtual IJson *Create(const char *,  const size_t &flags)    =0;
            virtual IJson *Create(FILE *input,   const size_t &flags)    =0;
    };

    class IJsonError
    {
        public:
            virtual int line() const = 0;
            virtual int column() const =0;
            virtual int position() const =0;

        public:
            virtual const char *source() const =0;
            virtual const char *text() const =0;

        public:
            virtual JsonErrorCode code() const =0;

        public:
            virtual bool equal(const IJsonError &error) const =0;
            virtual void clear() =0;

        public:
            static bool null(const SourceMod::IJsonError &obj)
            {
                return obj.code()       == JsonErrorCode::Unknown
                    && obj.line()       == -1
                    && obj.column()     == -1
                    && obj.position()   == -1
                    && obj.text()       == nullptr
                    && obj.source()     == nullptr;
            };

            static bool equal(const IJsonError &obj1, const IJsonError &obj2)
            {
                return obj1.equal(obj2);
            }
    };

    class IJson
    {
        public:
            virtual const char *dump(const size_t &decodingFlags) =0;

        public:
            virtual bool equal(const IJson &json) const =0;

        public:
            virtual bool get(long long *value) =0;
            virtual bool get(double *value) =0;
            virtual bool get(bool *value) =0;
            virtual const char* get() =0;

        public:
            virtual IJsonError  *error() const =0;
            virtual JsonType    type() const =0;
    };

    class IJsonObject : public IJson
    {
        public:
            virtual IJson*      get(const char *key) const =0;

        public:
            virtual bool        set(const char *key, const IJson *value) =0;
            virtual bool        set(const char *key, const char* value) =0;
            virtual bool        set(const char *key, double value) =0;
            virtual bool        set(const char *key, bool value) =0;
            virtual bool        set(const char *key, int value) =0;
            
        public:
            virtual bool        update(const IJsonObject* another, JsonObjectUpdateType type) =0;
            virtual JsonType    type(const char *key) const =0;
            virtual bool        exist(const char *key) const =0;
            virtual bool        remove(const char *key) =0;
            virtual void        clear() =0;
    };

    class IJsonArray : public IJson
    {
    public:
        virtual IJson   *get(const size_t& index) const =0;

    public:
        virtual bool    set(const size_t& index, const IJson *value) =0;
        virtual bool    set(const size_t& index, const char* value) =0;
        virtual bool    set(const size_t& index, double value) =0;
        virtual bool    set(const size_t& index, bool value) =0;
        virtual bool    set(const size_t& index, int value) =0;

    public:
        virtual bool    push(const IJson *value) =0;
        virtual bool    push(const char* value) =0;
        virtual bool    push(double value) =0;
        virtual bool    push(bool value) =0;
        virtual bool    push(int value) =0;

    public:
        virtual JsonType type(const size_t& index) const =0;
        virtual bool extend(const IJsonArray *another) =0;
        virtual bool remove(const size_t& index) =0;
        virtual size_t length() const =0;
        virtual void clear() =0;
    };
};

#endif
