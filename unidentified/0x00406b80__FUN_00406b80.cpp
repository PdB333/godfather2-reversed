#include <cstdint>

extern "C" void* PTR_FUN_00e2f0d4;
extern "C" void __thiscall FUN_004de130(void);
extern "C" void FUN_009c8eb0(void* ptr);

extern "C" void* __thiscall FUN_00406b80(void* this_, std::uint8_t flags)
{
    *static_cast<void**>(this_) = &PTR_FUN_00e2f0d4;

    FUN_004de130();

    if ((flags & 1) != 0) {
        FUN_009c8eb0(this_);
    }

    return this_;
}