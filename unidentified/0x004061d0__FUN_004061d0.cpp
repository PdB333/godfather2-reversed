#include <cstdint>

extern "C" std::int32_t FUN_004025a0(std::int32_t value);

struct FUN_004025a0_Object
{
    std::byte pad00[0x60];
    std::uint32_t flags; // [0x60]
};

void FUN_004061d0(std::int32_t param_1)
{
    auto* const object =
        reinterpret_cast<FUN_004025a0_Object*>(FUN_004025a0(param_1));
    if (object != nullptr) {
        object->flags = object->flags | 0x40000000u;
    }
}