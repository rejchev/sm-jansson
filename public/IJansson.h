
#ifndef _INCLUDE_SOURCEMOD_JANSSON_IFACE_H_
#define _INCLUDE_SOURCEMOD_JANSSON_IFACE_H_

#include <sm_platform.h>
#include <IShareSys.h>
#include <IHandleSys.h>
#include <ISourceMod.h>
#include <vector>
#include <cstring>

#define SMINTERFACE_JANSSON_NAME        "IJansson"

// xxxxxxxxyyyyyyyyyyzzzzzzzzzzz
// x = 8    bits - major
// y = 12   bits - minor
// z = 12   bits - bugs
//
// on y & z changes guaranteed backward compatibility
#define SMINTERFACE_JANSSON_VERSION	    ((0 << 24) & (0 << 12) & 0)

namespace nJansson
{
    enum JsonType
    {
        jtInvalid = -1,
        jtObject,
        jtArray,
        jtString,
        jtInteger,
        jtReal,
        jtBoolean,
        jtNull
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

    enum JsonObjectUpdateType
    {
        utDefault,
        utExisting,
        utMissing,
        utRecursive
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

    class IJsonObjectKeyIterator;
    using IJSOI = IJsonObjectKeyIterator;

    struct JsonError_t {
        int line;
        int column;
        int position;
        char source[PLATFORM_MAX_PATH];
        char text[PLATFORM_MAX_PATH];

        bool equal(const JsonError_t& another) const {
            return line == another.line
                   && column == another.column
                   && position == another.position
                   && std::strcmp(source, another.source) == 0
                   && std::strcmp(text, another.text) == 0;
        }
    };

    const JsonError_t JSON_ERROR_NULL = {};

    class IJansson : public SourceMod::SMInterface
    {
    public:
        const char *GetInterfaceName() override {
            return SMINTERFACE_JANSSON_NAME;
        }
        unsigned int GetInterfaceVersion() override {
            return SMINTERFACE_JANSSON_VERSION;
        }

        bool IsVersionCompatible(unsigned int version) override {
            return (((GetInterfaceVersion() >> 24) & (version >> 24)) == 1);
        }

    public:
        virtual IHandleTypeManager* types() const =0;

    public:
        // create from string
        virtual IJson *create(const char *str,  const size_t &flags) =0;

        // create from file stream
        virtual IJson *create(FILE *input,   const size_t &flags) =0;

        // create from sm file path
        virtual IJson *create(const char* fullPath,  const size_t& flags, SourceMod::ISourceMod* pUtils) =0;

    public:
        virtual void close(IJson* json) =0;
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
        virtual const char *dump(const size_t &decodingFlags) const =0;
        virtual int dump(const char* path, const size_t& flags) const =0;

    public:
        virtual bool equal(const IJson* json) const =0;

    public:
        virtual bool get(long long *value) =0;
        virtual bool get(double *value) =0;
        virtual bool get(bool *value) =0;
        virtual const char* get() =0;

    public:
        virtual size_t size() const =0;
        virtual void clear() =0;

    public:
        virtual const JsonError_t& error() const =0;
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
        virtual const SourceMod::TypeAccess* typeAccess() const =0;
        virtual const SourceMod::HandleAccess* handleAccess() const =0;
        virtual const SourceMod::IdentityToken_t *identity() const =0;

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
    public:
        virtual SourceMod::HandleType_t add(const IHandleType* pHType) =0;
        virtual void remove(const SourceMod::HandleType_t&) =0;

    public:
        virtual const IHandleType* find(const char* name) const =0;
        virtual const IHandleType* find(const size_t& index) const =0;
        virtual const IHandleType* find_t(const SourceMod::HandleType_t&) const =0;

    public:
        virtual size_t count() const =0;

    protected:
        virtual const std::vector<const IHandleType *>& container() const =0;
    };
};

#endif
