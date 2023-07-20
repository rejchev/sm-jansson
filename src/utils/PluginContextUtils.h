#ifndef SM_JANSSON_PLUGINCONTEXTUTILS_H
#define SM_JANSSON_PLUGINCONTEXTUTILS_H

#include <public/IJansson.h>
#include <smsdk_ext.h>

namespace nJansson {

    class PluginContextUtils {
    public:
        static const IHandleType* GetType(const char *typeName, const IJansson *face);

    public:
        static IJson* CreateJson(const char*, const cell_t &, IJansson *);

    public:
        static Handle_t CreateHandle(void*,
                                     const IHandleType*,
                                     SourceMod::IdentityToken_t* = nullptr,
                                     SourceMod::IdentityToken_t* = nullptr);

        static Handle_t CreateHandle(void*,
                                     const IHandleType*,
                                     const SourceMod::HandleSecurity*,
                                     const SourceMod::HandleAccess* = nullptr);

        static void* FreeHandle(const Handle_t &,
                                void *,
                                const IHandleType *,
                                const HandleSecurity*);

    public:

        static void* ReadHandle(const cell_t &, const IHandleType *, const HandleSecurity*);

        static nJansson::IJS* ReadJsonHandle(
                const cell_t&,
                const IHandleType*,
                const HandleSecurity*,
                bool (*)(nJansson::IJS*) = nullptr);

    public:
        static bool LogJsonError(const char* on, const JsonError_t&);
    };

    using PCU = PluginContextUtils;

} // nJansson

#endif //SM_JANSSON_PLUGINCONTEXTUTILS_H
