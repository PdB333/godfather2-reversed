#include <cstdint>
#include <cstdlib>

struct FUN_0064b440_Node {
    FUN_0064b440_Node* unknown00; // 0x00
    std::uint32_t unknown04;      // 0x04
    FUN_0064b440_Node* next;      // 0x08
};

struct FUN_0064b440_Object {
    void* vftable;                    // 0x00
    FUN_0064b440_Node* head;          // 0x04
    std::uint32_t ownedBuffer;        // 0x0c
    std::uint8_t pad_10[0x04];
    std::uint8_t hasOwnedBuffer;      // 0x14
};

extern "C" void* PTR_LAB_00e42d64;
extern "C" void* PTR_LAB_00e42de4;

extern "C" void __thiscall FUN_0064b440(FUN_0064b440_Object* this_)
{
    this_->vftable = &PTR_LAB_00e42d64;

    if (this_->hasOwnedBuffer != 0) {
        std::free(reinterpret_cast<void*>(this_->ownedBuffer));
    }

    this_->vftable = &PTR_LAB_00e42de4;

    FUN_0064b440_Node* node = this_->head;
    while (node != nullptr) {
        FUN_0064b440_Node* const next = node->next;
        node->unknown00 = nullptr;
        node->unknown04 = 0;
        node->next = nullptr;
        node = next;
    }
}