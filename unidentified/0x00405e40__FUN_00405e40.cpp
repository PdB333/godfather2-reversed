#include <cstdint>

struct FUN_00405e40_Object
{
    void* vftable;              // [0x00]
    std::int32_t value04;       // [0x04]
    std::int32_t value08;       // [0x08]
    std::int32_t value0C;       // [0x0C]
    std::int32_t value10;       // [0x10]
    std::int32_t value14;       // [0x14]
    std::int32_t value18;       // [0x18]
    std::int32_t value1C;       // [0x1C]
    std::int32_t value20;       // [0x20]
    std::int32_t value24;       // [0x24]
    std::int32_t value28;       // [0x28]
    std::int32_t value2C;       // [0x2C]
    std::int32_t value30;       // [0x30]
    std::int32_t value34;       // [0x34]
    std::int32_t value38;       // [0x38]
    std::int32_t value3C;       // [0x3C]
    std::int32_t count;         // [0x40]
    std::int32_t extraValue;    // [0x44]
};

struct FUN_00405e40_Source
{
    std::uint8_t pad00[0x18];
    std::int32_t extraValue;    // [0x18]
};

extern void* PTR_DAT_00e2f0c4;
extern FUN_00405e40_Source* FUN_004025a0(std::uint32_t param_2);

FUN_00405e40_Object* __fastcall FUN_00405e40(
    FUN_00405e40_Object* self,
    std::uint32_t param_2,
    std::int32_t param_3)
{
    self->vftable = &PTR_DAT_00e2f0c4;
    self->count = 0;
    self->extraValue = param_3;

    FUN_00405e40_Source* source = FUN_004025a0(param_2);
    if ((source != nullptr) && (source->extraValue != 0)) {
        self->value04 = source->extraValue;
        self->count = self->count + 1;
    }

    return self;
}