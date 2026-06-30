// FUNC_NAME: ListNode::ListNode

#include <cstdint>

class ListNode {
public:
    int* vtable;           // +0x00: pointer to vtable (set to &PTR_FUN_00d5f5b0)
    int field_4[1];        // +0x04: possibly unused or reserved (set to 0)
    char field_8;          // +0x08: declared as byte, set to 0
    int field_C;           // +0x0C: set to 0xFF
    int* prev;             // +0x10: pointer to previous node in linked list
    int* next;             // +0x14: pointer to next node in linked list (set to 0)
    int field_1C;          // +0x1C: set to 0
    int field_20;          // +0x20: initialized from global DAT_00d5e288
    int field_24;          // +0x24: initialized from _DAT_00d5780c
    int field_28;          // +0x28: initialized from _DAT_00d5cf70
    int field_2C;          // +0x2C: also from _DAT_00d5cf70
    int field_30;          // +0x30: set to 0
    int field_34;          // +0x34: set to 0
    int field_38;          // +0x38: set to 0
    int field_3C;          // +0x3C: set to 0
    int field_40;          // +0x40: set to 0
    int field_44;          // +0x44: set to 0
    int field_48;          // +0x48: set to 0
    int field_4C;          // +0x4C: set to 0
    int field_50;          // +0x50: set to 0
    int field_54;          // +0x54: set to 0
    int field_58;          // +0x58: set to copy from field_24
    int field_5C;          // +0x5C: set to _DAT_00d5780c (again)
    int field_60;          // +0x60: set to 0
};

// External global data (likely static members of ListNode or globals)
extern int* PTR_FUN_00d5f5b0;     // vtable pointer
extern int DAT_00d5e288;          // some constant
extern int _DAT_00d5780c;         // some static value
extern int _DAT_00d5cf70;         // another static value

// Forward declaration of helper function (likely initializes something)
void FUN_006da2b0(void);

ListNode* __thiscall ListNode::ListNode(ListNode* this, int* param_2)
{
    int* piVar1;
    int uVar2;
    int uVar3;

    uVar2 = DAT_00d5e288;

    // Initialize basic fields
    this->field_4[0] = 0;
    this->field_8 = 0;
    this->field_C = 0xFF;
    this->vtable = &PTR_FUN_00d5f5b0;
    this->prev = 0;          // +0x10
    this->next = 0;          // +0x14
    this->field_20 = uVar2;  // +0x20
    piVar1 = &this->prev;    // used as list head pointer

    // Set fields from globals
    this->field_24 = _DAT_00d5780c;
    uVar2 = _DAT_00d5cf70;
    this->field_28 = _DAT_00d5cf70;
    this->field_2C = uVar2;

    // Clear some fields
    this->field_30 = 0;
    this->field_34 = 0;
    this->field_38 = 0;
    this->field_3C = 0;
    this->field_40 = 0;

    // Handle linked list insertion
    if (param_2 == 0) {
        param_2 = 0;
    } else {
        param_2 = (int*)((char*)param_2 + 0x48);  // advance by 72 bytes
    }

    if (*piVar1 != param_2) {
        if (*piVar1 != 0) {
            FUN_004daf90(piVar1);   // deallocation or removal?
        }
        *piVar1 = param_2;
        if (param_2 != 0) {
            this->next = *(int**)(param_2 + 4);  // next = param_2->next
            *(int**)(param_2 + 4) = piVar1;       // param_2->next = this->prev
        }
    }

    uVar3 = 0;
    FUN_006da2b0();  // some initialization routine

    uVar2 = _DAT_00d5780c;
    this->field_58 = this->field_24;   // copy from +0x24 to +0x58
    this->field_8 = 0;
    this->field_5C = uVar2;
    this->field_60 = uVar3;

    return this;
}