#include <cstdint>

extern void* PTR_DAT_00e2f0c4;

struct FUN_00405f20_Object
{
    void* vftable;                  // [0x00]
    std::int32_t values[0x0F];      // [0x04] .. [0x3C]
    std::int32_t count;             // [0x40]
    std::int32_t extraValue;        // [0x44]
};

void __fastcall FUN_00405f20(FUN_00405f20_Object* self)
{
    self->vftable = &PTR_DAT_00e2f0c4;
    self->count = 0;
    self->extraValue = 0;
}