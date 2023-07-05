#include "json_e_natives.h"

cell_t JsonErrorCode(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PluginContextUtils::GetType(pContext, pJansson, "JsonError")) == nullptr)
        return nJansson::Unknown;

    nJansson::IJsonError* jsonError;
    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};
    if((jsonError = static_cast<nJansson::IJsonError *>
            (nJansson::PluginContextUtils::ReadHandle(pContext, g_pHandleSys, pType, &sec, params[1]))) == nullptr)
        return nJansson::Unknown;

    return jsonError->code();
}

cell_t JsonErrorLine(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PluginContextUtils::GetType(pContext, pJansson, "JsonError")) == nullptr)
        return -1;

    nJansson::IJsonError* jsonError;
    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};
    if((jsonError = static_cast<nJansson::IJsonError *>
            (nJansson::PluginContextUtils::ReadHandle(pContext, g_pHandleSys, pType, &sec, params[1]))) == nullptr)
        return -1;

    return jsonError->line();
}

cell_t JsonErrorColumn(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PluginContextUtils::GetType(pContext, pJansson, "JsonError")) == nullptr)
        return -1;

    nJansson::IJsonError* jsonError;
    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};
    if((jsonError = static_cast<nJansson::IJsonError *>
            (nJansson::PluginContextUtils::ReadHandle(pContext, g_pHandleSys, pType, &sec, params[1]))) == nullptr)
        return -1;

    return jsonError->column();
}

cell_t JsonErrorNull(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PluginContextUtils::GetType(pContext, pJansson, "JsonError")) == nullptr)
        return false;

    nJansson::IJsonError* jsonError;
    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};
    if((jsonError = static_cast<nJansson::IJsonError *>
            (nJansson::PluginContextUtils::ReadHandle(pContext, g_pHandleSys, pType, &sec, params[1]))) == nullptr)
        return false;

    return nJansson::IJsonError::isEmpty(jsonError);
}

cell_t JsonErrorsEqual(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PluginContextUtils::GetType(pContext, pJansson, "JsonError")) == nullptr)
        return false;

    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};

    nJansson::IJsonError* jsonError;
    if((jsonError = static_cast<nJansson::IJsonError *>
            (nJansson::PluginContextUtils::ReadHandle(pContext, g_pHandleSys, pType, &sec, params[1]))) == nullptr)
        return false;

    nJansson::IJsonError* jsonError2;
    if((jsonError2 = static_cast<nJansson::IJsonError *>
            (nJansson::PluginContextUtils::ReadHandle(pContext, g_pHandleSys, pType, &sec, params[2]))) == nullptr)
        return false;

    return nJansson::IJsonError::isEqual(jsonError, jsonError2);
}

cell_t JsonErrorText(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PluginContextUtils::GetType(pContext, pJansson, "JsonError")) == nullptr)
        return 0;

    nJansson::IJsonError* jsonError;
    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};
    if((jsonError = static_cast<nJansson::IJsonError *>
            (nJansson::PluginContextUtils::ReadHandle(pContext, g_pHandleSys, pType, &sec, params[1]))) == nullptr)
        return 0;

    pContext->StringToLocalUTF8(params[2], params[3], jsonError->text(), nullptr);
    return true;
}

cell_t JsonErrorSource(IPluginContext *pContext, const cell_t *params) {
    const nJansson::IHandleType* pType;
    if((pType = nJansson::PluginContextUtils::GetType(pContext, pJansson, "JsonError")) == nullptr)
        return 0;

    nJansson::IJsonError* jsonError;
    HandleSecurity sec {pContext->GetIdentity(), myself->GetIdentity()};
    if((jsonError = static_cast<nJansson::IJsonError *>
            (nJansson::PluginContextUtils::ReadHandle(pContext, g_pHandleSys, pType, &sec, params[1]))) == nullptr)
        return 0;

    pContext->StringToLocalUTF8(params[2], params[3], jsonError->source(), nullptr);
    return true;
}

const sp_nativeinfo_t JSON_ERROR_NATIVES[] =
{
        {"JsonError.Code.get", JsonErrorCode},
        {"JsonError.Line.get", JsonErrorLine},
        {"JsonError.Column.get", JsonErrorColumn},
        {"JsonError.Text", JsonErrorText},
        {"JsonError.Source", JsonErrorSource},
        {"JsonError.IsEmpty", JsonErrorNull},
        {"JsonError.IsEquals", JsonErrorsEqual},
        {nullptr, nullptr}
};
