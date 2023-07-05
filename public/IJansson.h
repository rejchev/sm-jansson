
#ifndef _INCLUDE_SOURCEMOD_JANSSON_IFACE_H_
#define _INCLUDE_SOURCEMOD_JANSSON_IFACE_H_


#include <IShareSys.h>
#include <IHandleSys.h>
#include <ISourceMod.h>
#include <vector>
#include <cstring>

#define SMINTERFACE_JANSSON_NAME        "IJansson"
#define SMINTERFACE_JANSSON_VERSION	    05072023

namespace nJansson
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

    class IHandleType;
    using IHT = IHandleType;

    class IHandleTypeManager;
    using UHTM = IHandleTypeManager;

    class IJson;
    using IJS = IJson;

    class IJsonObject;
    using IJSO = IJsonObject;

    class IJsonArray;
    using IJSA = IJsonArray;

    class IJsonError;
    using IJSE = IJsonError;

    class IJsonObjectKeyIterator;
    using IJSOI = IJsonObjectKeyIterator;

    class IJansson : public SourceMod::SMInterface
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

        public:
            virtual IHandleTypeManager* typeManager() const =0;

        public:
            // create from string
            virtual IJson *create(const char *,  const size_t &flags)    =0;

            // create from file stream
            virtual IJson *create(FILE *input,   const size_t &flags)    =0;

        public:
            // create from sm file path
            virtual IJson *createp(const char*,  const size_t& flags, SourceMod::ISourceMod* utils) =0;
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
            virtual bool isEqual(const IJsonError* error) const =0;
            virtual void clear() =0;

        public:
            static bool isEmpty(const IJsonError* obj)
            {
                if(obj == nullptr)
                    return true;

                return obj->line() == -1
                    && obj->column() == -1
                    && obj->position() == -1
                    && strlen(obj->text()) == 0
                    && strlen(obj->source()) == 0;
            };

            static bool isEqual(const IJsonError* obj1, const IJsonError* obj2)
            {
                return obj1->isEqual(obj2);
            }

    };

    class IJsonObject
    {
        public:
            virtual IJson*      get(const char *key) const =0;

        public:
            virtual bool        set(const char *key, const IJson *value) =0;
            virtual bool        set(const char *key, const char* value) =0;
            virtual bool        set(const char *key, double value) =0;
            virtual bool        set(const char *key, bool value) =0;
            virtual bool        set(const char *key, long long value) =0;
            
        public:
            virtual bool        update(const IJsonObject* another, JsonObjectUpdateType type) =0;
            virtual JsonType    type(const char *key) const =0;
            virtual bool        exist(const char *key) const =0;
            virtual bool        remove(const char *key) =0;

        public:
            virtual IJsonArray* keys(const JsonType& type, const size_t& flags) const =0;
    };

    class IJsonArray
    {
    public:
        virtual IJson   *get(const size_t& index) const =0;

    public:
        virtual bool    set(const size_t& index, const IJson *value) =0;
        virtual bool    set(const size_t& index, const char* value) =0;
        virtual bool    set(const size_t& index, double value) =0;
        virtual bool    set(const size_t& index, bool value) =0;
        virtual bool    set(const size_t& index, long long value) =0;

    public:
        virtual bool    push(const IJson *value) =0;
        virtual bool    push(const char* value) =0;
        virtual bool    push(double value) =0;
        virtual bool    push(bool value) =0;
        virtual bool    push(long long value) =0;

    public:
        virtual JsonType type(const size_t& index) const =0;
        virtual bool extend(const IJsonArray *another) =0;
        virtual bool remove(const size_t& index) =0;
    };

    class IJson : public IJsonArray, public IJsonObject
    {
    public:
        virtual const char *dump(const size_t &decodingFlags) =0;
        virtual int dump(const char* path, const size_t& flags) = 0;

    public:
        virtual bool equal(const IJson &json) const =0;

    public:
        virtual bool get(long long *value) =0;
        virtual bool get(double *value) =0;
        virtual bool get(bool *value) =0;
        virtual const char* get() =0;

    public:
        virtual size_t size() const =0;
        virtual void clear() =0;

    public:
        virtual IJsonError* error() const =0;
        virtual JsonType    type() const =0;

    public:
        virtual bool isOK() const =0;
    };


    class IHandleType
    {
    public:
        virtual const char *name() const =0;
        virtual SourceMod::IHandleTypeDispatch* dispatch() const =0;
        virtual SourceMod::HandleType_t parent() const =0;
        virtual const SourceMod::TypeAccess* access() const =0;
        virtual const SourceMod::HandleAccess* handleAccess() const =0;
        virtual const SourceMod::IdentityToken_t *ident() const =0;

    public:
        virtual SourceMod::Handle_t createHandle(void *object,
                               SourceMod::IdentityToken_t* pOwner,
                               SourceMod::IdentityToken_t* pIdent,
                               SourceMod::HandleError* pHandleError) const =0;

        virtual SourceMod::Handle_t createHandle(void *object,
                                                 const SourceMod::HandleSecurity* owner,
                                                 const SourceMod::HandleAccess* access,
                                                 SourceMod::HandleError* error) const =0;

    public:
        virtual SourceMod::HandleType_t id() const =0;
    };

    class IHandleTypeManager
    {
    protected:
        virtual const std::vector<IHandleType *>& types() const =0;

    public:
        virtual SourceMod::HandleType_t registerType(const char* name,
                                              SourceMod::IHandleTypeDispatch *dispatch  = nullptr,
                                              const SourceMod::HandleType_t& parent     = 0,
                                              SourceMod::TypeAccess* access             = nullptr,
                                              SourceMod::HandleAccess* handleAccess     = nullptr,
                                              SourceMod::IdentityToken_t *identityToken = nullptr) =0;

        // because HandleType_t an unique
        virtual void removeType(const SourceMod::HandleType_t&) =0;

    public:
        virtual const IHandleType* getByName(const char* name) const =0;
        virtual const IHandleType* getById(const SourceMod::HandleType_t& ident) const =0;
        virtual const IHandleType* getByIndex(const size_t& index) const =0;

    public:
        virtual size_t count() const =0;
    };
};

#endif
