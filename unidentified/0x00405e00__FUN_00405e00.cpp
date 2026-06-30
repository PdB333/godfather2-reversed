#include <cstdint>

struct FUN_00405e00_Object
{
    void* vftable;                  // [0x00]
    std::int32_t values[0x0F];      // [0x04] .. [0x3C]
    std::int32_t count;             // [0x40]
    std::int32_t extraValue;        // [0x44]
};

struct FUN_00405e00_Source
{
    std::uint8_t pad00[0x40];
    std::int32_t count;             // [0x40]
    std::int32_t extraValue;        // [0x44]
};

extern void* PTR_DAT_00e2f0c4;

void __fastcall FUN_00405e00(FUN_00405e00_Source* source, FUN_00405e00_Object* self)
{
    self->vftable = &PTR_DAT_00e2f0c4;

    const std::int32_t count = source->count;
    self->count = count;
    self->extraValue = source->extraValue;

    std::uint32_t index = 0;
    if (count != 0) {
        std::int32_t* dst = &self->values[0];
        do {
            *dst = *reinterpret_cast<std::int32_t*>(
                reinterpret_cast<std::uintptr_t>(dst) +
                (reinterpret_cast<std::uintptr_t>(source) - reinterpret_cast<std::uintptr_t>(self)));
            index = index + 1;
            dst = dst + 1;
        } while (index < static_cast<std::uint32_t>(self->count));
    }
}