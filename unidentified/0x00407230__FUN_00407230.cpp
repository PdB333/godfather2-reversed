#include <cstdint>

struct FUN_00407230_ListLink
{
    FUN_00407230_ListLink* next; // [0x00]
    FUN_00407230_ListLink* prev; // [0x04]
};

extern "C" void __fastcall FUN_00407230(FUN_00407230_ListLink* in_EAX, FUN_00407230_ListLink** param_2)
{
    if (in_EAX->prev == nullptr) {
        FUN_00407230_ListLink* const iVar1 = in_EAX->next;
        *param_2 = iVar1;

        if (iVar1 == nullptr) {
            goto LAB_00407260;
        }

        iVar1->prev = nullptr;
    }
    else {
        in_EAX->prev->next = in_EAX->next;
    }

    if (in_EAX->next != nullptr) {
        in_EAX->next->prev = in_EAX->prev;
        in_EAX->prev = nullptr;
        in_EAX->next = nullptr;
        return;
    }

LAB_00407260:
    param_2[1] = in_EAX->prev;

    if (in_EAX->prev != nullptr) {
        in_EAX->prev->next = nullptr;
    }

    in_EAX->prev = nullptr;
    in_EAX->next = nullptr;
}