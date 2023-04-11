#ifndef SM_JANSSON_PLUGINCONTEXTUTILS_H
#define SM_JANSSON_PLUGINCONTEXTUTILS_H

#include <IJansson.h>
#include <smsdk_ext.h>

namespace nJansson {

    class PluginContextUtils {
    public:
        static const IHandleType* GetType(IPluginContext*, const IJansson*, const char*);

    public:
        static IJson* CreateJson(IPluginContext*,
                                 IJansson*,
                                 const cell_t& addr,
                                 const cell_t& flags = 0);

        static IJson* CreateJsonFromPath(IPluginContext*,
                                         IJansson*,
                                         ISourceMod*,
                                         const cell_t&,
                                         const cell_t& = 0);

        static int DumpJsonToFile(IJson*, const char*, const size_t& = 0);

    public:
        static Handle_t CreateHandle(IPluginContext*,
                                     IHandleSys*,
                                     const IHandleType*,
                                     void*,
                                     SourceMod::IdentityToken_t* = nullptr,
                                     SourceMod::IdentityToken_t* = nullptr);

        static Handle_t CreateHandle(IPluginContext*,
                                     IHandleSys*,
                                     const IHandleType*,
                                     void*,
                                     const SourceMod::HandleSecurity* = nullptr,
                                     const SourceMod::HandleAccess* = nullptr);

        static void FreeHandle(IHandleSys*,
                               const IHandleType*,
                               const Handle_t&,
                               const HandleSecurity*,
                               void *object);

    public:

        static void* ReadHandle(IPluginContext*,
                               IHandleSys*,
                               const IHandleType*,
                               const HandleSecurity*,
                               const cell_t&);

        static nJansson::IJS* ReadJsonHandle(IPluginContext*,
                                IHandleSys*,
                                const IHandleType*,
                                const HandleSecurity*,
                                const cell_t&,
                                bool (*)(nJansson::IJS*) = nullptr);

    public:
        static bool ThrowJsonError(IPluginContext*, IJson*);
    };

    using PCU = PluginContextUtils;

} // nJansson

#endif //SM_JANSSON_PLUGINCONTEXTUTILS_H
