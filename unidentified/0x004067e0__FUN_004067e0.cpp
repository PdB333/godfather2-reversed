#include <cstddef>
#include <cstdint>

struct FUN_004067e0_Object
{
    std::byte pad00[0x9C];
    std::int32_t referenceCount; // [0x9C]
};

extern "C" void __thiscall FUN_004067e0(FUN_004067e0_Object* this_, char param_2)
{
    if (param_2 != '\0') {
        this_->referenceCount = this_->referenceCount + 1;
        return;
    }

    this_->referenceCount = this_->referenceCount + -1;
    return;
}