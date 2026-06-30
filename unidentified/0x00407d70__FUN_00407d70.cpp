#include <cstdint>

struct FUN_00407d70_HashNode
{
    FUN_00407d70_HashNode* next;   // [0x00]
    std::uint32_t field_0x04;      // [0x04]
    std::uint32_t field_0x08;      // [0x08]
    std::uint32_t field_0x0C;      // [0x0C]
    std::uint32_t key;             // [0x10]
};

extern "C" FUN_00407d70_HashNode** DAT_01162380;

extern "C" void __fastcall FUN_00407d70(std::uint32_t* param_1)
{
    FUN_00407d70_HashNode* node =
        DAT_01162380[(*param_1 & 0x0fff)];

    while (node != nullptr && node->key != *param_1) {
        node = node->next;
    }
}