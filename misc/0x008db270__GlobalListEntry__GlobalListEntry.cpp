// FUNC_NAME: GlobalListEntry::GlobalListEntry

// __thiscall constructor for a global linked list node
// Address: 0x008db270
// Each node holds a string name, three integer values, four zero fields, and a pointer to the next node.
// The node is inserted at the head of a global singly linked list.
// Fields:
// +0x00: vtable pointer
// +0x04: field04 (param3)
// +0x08: field08 (param5)
// +0x0C: field0C (param4)
// +0x10-0x1C: four zero ints
// +0x20: name[64] (copied with strncpy, max 63 chars)
// +0x70: next pointer

#include <cstring> // for strncpy

class GlobalListEntry {
public:
    void* vtable;                    // 0x00
    int field04;                     // 0x04
    int field08;                     // 0x08
    int field0C;                     // 0x0C
    int field10;                     // 0x10
    int field14;                     // 0x14
    int field18;                     // 0x18
    int field1C;                     // 0x1C
    char name[64];                   // 0x20 (32 bytes)
    // 0x60-0x6C: possibly padding
    GlobalListEntry* next;           // 0x70

    // Constructor – initializes fields and adds to global list
    GlobalListEntry(char* nameStr, int param3, int param4, int param5) {
        // Base initializer
        FUN_0064cc90();

        this->vtable = &PTR_LAB_00d7e098;
        _strncpy(this->name, nameStr, 0x3F);

        this->field04 = param3;   // param1[1]
        this->field0C = param4;   // param1[3]
        this->field08 = param5;   // param1[2]

        this->field10 = 0;
        this->field14 = 0;
        this->field18 = 0;
        this->field1C = 0;

        // Prepend to global list
        this->next = gGlobalListHead;
        gGlobalListHead = this;
    }
};

// Global head of the list
static GlobalListEntry* gGlobalListHead = nullptr;