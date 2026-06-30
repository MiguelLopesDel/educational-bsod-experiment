#include "raise_hard_error.hpp"

#include <iostream>
#include <string_view>

namespace {

constexpr std::string_view kConfirmFlag = "--i-understand-this-will-crash";

bool has_confirmation_flag(int argc, char* argv[]) {
    for (int i = 1; i < argc; ++i) {
        if (std::string_view{argv[i]} == kConfirmFlag) {
            return true;
        }
    }

    return false;
}

FARPROC load_ntdll_proc(HMODULE ntdll, const char* name) {
    auto* proc = GetProcAddress(ntdll, name);
    if (proc == nullptr) {
        std::cerr << "Could not resolve " << name << '\n';
    }

    return proc;
}

int raise_system_hard_error() {
    auto* ntdll = GetModuleHandleW(L"ntdll.dll");
    if (ntdll == nullptr) {
        std::cerr << "Could not get ntdll.dll handle\n";
        return ERROR_BAD_ENVIRONMENT;
    }

    auto* adjust_privilege_proc = load_ntdll_proc(ntdll, "RtlAdjustPrivilege");
    auto* raise_hard_error_proc = load_ntdll_proc(ntdll, "NtRaiseHardError");
    if (adjust_privilege_proc == nullptr || raise_hard_error_proc == nullptr) {
        return ERROR_PROC_NOT_FOUND;
    }

    auto* adjust_privilege =
        reinterpret_cast<bsod_lab::RtlAdjustPrivilegeFn>(adjust_privilege_proc);
    auto* raise_hard_error =
        reinterpret_cast<bsod_lab::NtRaiseHardErrorFn>(raise_hard_error_proc);

    BOOLEAN was_enabled = FALSE;
    const auto privilege_status = adjust_privilege(
        bsod_lab::kShutdownPrivilege,
        TRUE,
        FALSE,
        &was_enabled);

    if (privilege_status != 0) {
        std::cerr << "Could not enable shutdown privilege: 0x" << std::hex
                  << privilege_status << '\n';
        return ERROR_ACCESS_DENIED;
    }

    bsod_lab::HardErrorResponse response = bsod_lab::HardErrorResponse::ReturnToCaller;
    return static_cast<int>(raise_hard_error(
        bsod_lab::kNotImplementedStatus,
        0,
        nullptr,
        nullptr,
        bsod_lab::HardErrorResponseOption::ShutdownSystem,
        &response));
}

void print_usage(const char* program_name) {
    std::cout
        << "Educational BSOD experiment\n\n"
        << "This program intentionally requests a system shutdown hard error.\n"
        << "Run it only inside an isolated lab or disposable VM.\n\n"
        << "Usage:\n"
        << "  " << program_name << ' ' << kConfirmFlag << "\n";
}

}  // namespace

int main(int argc, char* argv[]) {
    if (!has_confirmation_flag(argc, argv)) {
        print_usage(argv[0]);
        return ERROR_CANCELLED;
    }

    return raise_system_hard_error();
}
