#include <cstdint>

struct FUN_004056b0_Node
{
    FUN_004056b0_Node* next;  // [0x00]
    std::uint32_t      field_4;
    std::uint32_t      field_8;
    std::uint32_t      field_C;
    std::uint32_t      field_10;
    std::uint32_t      field_14;
    std::uint32_t      field_18;
    std::uint32_t      field_1C;
    std::uint32_t      field_20;
    std::uint32_t      field_24;
    std::uint32_t      field_28;
    std::uint32_t      key;   // [0x2C] == [0xb]
};

void __fastcall FUN_004056b0(FUN_004056b0_Node** in_EAX, std::uint32_t param_1)
{
    FUN_004056b0_Node* node = *in_EAX;

    while ((node != nullptr) && (node->key != param_1)) {
        node = node->next;
    }
}