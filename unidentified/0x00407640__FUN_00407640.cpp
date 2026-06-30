#include <cstdint>

struct FUN_00407640_Node
{
    FUN_00407640_Node* owner; // [0x00]
    FUN_00407640_Node* next;  // [0x04]
};

extern "C" void __fastcall FUN_00407640(FUN_00407640_Node* param_1)
{
    FUN_00407640_Node* piVar2;
    FUN_00407640_Node* piVar3;

    if (param_1->owner != nullptr) {
        piVar2 = param_1->owner->next;

        if (piVar2 == param_1) {
            param_1->owner->next = param_1->next;
            param_1->owner = nullptr;
            return;
        }

        piVar3 = piVar2->next;
        while (piVar3 != param_1) {
            piVar2 = piVar2->next;
            piVar3 = piVar2->next;
        }

        piVar2->next = param_1->next;
        param_1->owner = nullptr;
    }

    return;
}