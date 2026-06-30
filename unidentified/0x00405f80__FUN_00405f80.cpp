#include <cstdint>

struct FUN_00405f80_Object
{
    std::int32_t values[16];        // [0x00] .. [0x3F]
    std::int32_t count;             // [0x40]
    std::int32_t extraValue;        // [0x44]
};

std::int32_t __fastcall FUN_00405f80(FUN_00405f80_Object* self)
{
    return self->values[self->count];
}