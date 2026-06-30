#include <cstdint>

struct FUN_00405e80_Object
{
    void* vftable;                  // [0x00]
    std::int32_t values[0x0F];      // [0x04] .. [0x3C]
    std::int32_t count;             // [0x40]
    std::int32_t extraValue;        // [0x44]
};

extern void* PTR_DAT_00e2f0c4;

extern std::int32_t __cdecl FUN_00405720(std::int32_t value, std::int32_t unused);

FUN_00405e80_Object* __fastcall FUN_00405e80(
    FUN_00405e80_Object* self,
    std::int32_t param_2,
    std::int32_t param_3)
{
    self->extraValue = param_3;
    self->vftable = &PTR_DAT_00e2f0c4;
    self->count = 0;

    const std::int32_t value = FUN_00405720(param_2, 0);
    if (value != 0) {
        self->values[self->count] = value;
        self->count = self->count + 1;
    }

    return self;
}