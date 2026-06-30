#include <cstddef>
#include <cstdint>

extern "C" void FUN_00406a00();

struct FUN_004062c0_VTable
{
    void (*unknown_0)(); // [0x00]
    void (*unknown_4)(); // [0x04]
};

struct FUN_004062c0_Object
{
    std::int32_t field_0x00;
    FUN_004062c0_VTable* vtable; // [0x04]
    std::byte pad08[0x54];
    std::int32_t field_0x5c;     // [0x5C]
};

void FUN_004062c0(std::int32_t param_1)
{
    auto* const self = reinterpret_cast<FUN_004062c0_Object*>(param_1);

    self->vtable->unknown_4();

    if (self->field_0x5c == 0) {
        FUN_00406a00();
    }
}