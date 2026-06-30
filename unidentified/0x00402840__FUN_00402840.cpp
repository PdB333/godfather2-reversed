#include <cstdint>

struct FUN_00402840_Node
{
    FUN_00402840_Node* next; // +0x00
};

struct FUN_00402840_Object
{
    std::uint8_t pad_00[0x10];
    std::int32_t availableCount; // +0x10
    std::int32_t acquiredCount;  // +0x14
    std::uint8_t pad_18[0x10];
    std::uint8_t flags;          // +0x28
    std::uint8_t pad_29[0x0b];
    std::int32_t unk_34;         // +0x34
    FUN_00402840_Node* head;     // +0x38
};

extern void FUN_004de190();
extern void FUN_004024a0();

FUN_00402840_Node* __thiscall FUN_00402840(FUN_00402840_Object* self)
{
    if ((self->head == nullptr) && ((self->unk_34 == 0 || ((self->flags & 1) == 0)))) {
        FUN_004de190();
    }

    FUN_00402840_Node* node = self->head;
    if (node == nullptr) {
        return nullptr;
    }

    self->acquiredCount = self->acquiredCount + 1;
    self->availableCount = self->availableCount + -1;
    self->head = node->next;

    FUN_004024a0();
    return node;
}