#include <cstdint>

extern "C" std::uint8_t DAT_012051f8;

extern "C" void FUN_00401590();
extern "C" void FUN_00ac2090(std::uint32_t value);
extern "C" void FUN_00ac2170(std::uint32_t value);
extern "C" void FUN_00ac33b0();

class Context {
public:
    std::uint32_t& primaryHandle() {
        return *reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(this) + 0x28);
    }

    void*& primaryObject() {
        return *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(this) + 0x2c);
    }

    std::uint32_t& resourceId() {
        return *reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(this) + 0x30);
    }

    void*& handleOwner() {
        return *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(this) + 0x34);
    }

    std::uint32_t& secondaryHandle() {
        return *reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(this) + 0x38);
    }

    std::uint32_t& tertiaryHandle() {
        return *reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(this) + 0x3c);
    }
};

using VFuncReleaseLike = void(__thiscall*)(void*, int);
using VFuncDestroyHandle = void(__thiscall*)(void*, std::uint32_t, int);

extern "C" std::uint32_t __fastcall FUN_00401330(Context* this_) {
    if (DAT_012051f8 != '\0') {
        FUN_00401590();

        const std::uint32_t value = this_->resourceId();
        FUN_00ac2090(value);
        FUN_00ac2170(value);

        if (this_->primaryObject() != nullptr) {
            auto** const vtable = *reinterpret_cast<void***>(this_->primaryObject());
            auto const releaseLike = reinterpret_cast<VFuncReleaseLike>(vtable[0]);
            releaseLike(this_->primaryObject(), 1);
        }

        this_->primaryObject() = nullptr;

        {
            auto** const vtable = *reinterpret_cast<void***>(this_->handleOwner());
            auto const destroyHandle = reinterpret_cast<VFuncDestroyHandle>(vtable[3]);
            destroyHandle(this_->handleOwner(), this_->primaryHandle(), 0);
        }

        this_->primaryHandle() = 0;
        DAT_012051f8 = '\0';
    }

    FUN_00ac33b0();

    {
        auto** const vtable = *reinterpret_cast<void***>(this_->handleOwner());
        auto const destroyHandle = reinterpret_cast<VFuncDestroyHandle>(vtable[3]);
        destroyHandle(this_->handleOwner(), this_->secondaryHandle(), 0);
        destroyHandle(this_->handleOwner(), this_->tertiaryHandle(), 0);
    }

    this_->secondaryHandle() = 0;
    this_->tertiaryHandle() = 0;

    if (this_->handleOwner() != nullptr) {
        auto** const vtable = *reinterpret_cast<void***>(this_->handleOwner());
        auto const releaseLike = reinterpret_cast<VFuncReleaseLike>(vtable[0]);
        releaseLike(this_->handleOwner(), 1);
    }

    this_->handleOwner() = nullptr;
    return 1;
}