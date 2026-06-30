#ifndef EDUCATIONAL_BSOD_EXPERIMENT_RAISE_HARD_ERROR_HPP
#define EDUCATIONAL_BSOD_EXPERIMENT_RAISE_HARD_ERROR_HPP

#ifndef NOMINMAX
#define NOMINMAX
#endif

#include <windows.h>
#include <subauth.h>

namespace bsod_lab {

constexpr NTSTATUS kNotImplementedStatus = static_cast<NTSTATUS>(0xC0000002);
constexpr ULONG kShutdownPrivilege = 0x13;

enum class HardErrorResponseOption : ULONG {
    AbortRetryIgnore = 0,
    Ok = 1,
    OkCancel = 2,
    RetryCancel = 3,
    YesNo = 4,
    YesNoCancel = 5,
    ShutdownSystem = 6,
};

enum class HardErrorResponse : ULONG {
    ReturnToCaller = 0,
    NotHandled = 1,
    Abort = 2,
    Cancel = 3,
    Ignore = 4,
    No = 5,
    Ok = 6,
    Retry = 7,
    Yes = 8,
};

using RtlAdjustPrivilegeFn = NTSTATUS(NTAPI*)(
    ULONG privilege,
    BOOLEAN enable,
    BOOLEAN current_thread,
    PBOOLEAN was_enabled);

using NtRaiseHardErrorFn = NTSTATUS(NTAPI*)(
    NTSTATUS error_status,
    ULONG parameter_count,
    PUNICODE_STRING unicode_string_parameter_mask,
    PULONG_PTR parameters,
    HardErrorResponseOption response_option,
    HardErrorResponse* response);

}  // namespace bsod_lab

#endif  // EDUCATIONAL_BSOD_EXPERIMENT_RAISE_HARD_ERROR_HPP
