#ifndef SM_JANSSON_HANDLES_H
#define SM_JANSSON_HANDLES_H

#include <public/IJansson.h>

namespace nJansson {

    extern SourceMod::Handle_t
    CreateHandle(void*, const IHandleType*, const SourceMod::HandleSecurity*, const SourceMod::HandleAccess* = nullptr);

    void* ReadHandle(const cell_t&, const IHandleType *, const SourceMod::HandleSecurity*);

    void* FreeHandle(const SourceMod::Handle_t&, void *, const IHandleType *, const SourceMod::HandleSecurity*);

    IJson*
    ReadJsonHandle( const cell_t&, const IHandleType*, const SourceMod::HandleSecurity*, bool (*)(nJansson::IJS*) = nullptr);
}

#endif //SM_JANSSON_HANDLES_H
