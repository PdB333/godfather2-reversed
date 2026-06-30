#include <cstdint>

struct FUN_00405ec0_Object
{
    void* vftable;                  // [0x00]
    std::int32_t values[0x0F];      // [0x04] .. [0x3C]
    std::int32_t count;             // [0x40]
    std::int32_t extraValue;        // [0x44]
};

struct FUN_00405ec0_Node
{
    std::uint8_t pad00[0x08];
    std::uint8_t extraCount;        // [0x08]
    std::uint8_t pad09[0x01];
    std::uint8_t flags0A;           // [0x0A]
    std::uint8_t pad0B[0x05];
    std::int32_t children;          // [0x10]
};

extern std::int32_t __cdecl FUN_00405fd0(std::int32_t node, std::int32_t child);

FUN_00405ec0_Object* __fastcall FUN_00405ec0(FUN_00405ec0_Object* self)
{
    self->count = self->count + -1;

    const std::int32_t value = self->values[self->count];
    auto* const node = reinterpret_cast<FUN_00405ec0_Node*>(value);

    std::uint32_t childCount = static_cast<std::uint32_t>(node->flags0A & 1);
    if ((static_cast<std::uint8_t>(self->extraValue) & 1) == 0) {
        childCount = childCount + static_cast<std::uint32_t>(node->extraCount);
    }

    std::uint32_t childIndex = 0;
    if (childCount != 0) {
        do {
            const std::int32_t childValue =
                FUN_00405fd0(value, *(reinterpret_cast<std::int32_t*>(node->children) + childIndex));
            self->values[self->count] = childValue;
            self->count = self->count + 1;
            childIndex = childIndex + 1;
        } while (childIndex < childCount);
    }

    return self;
}