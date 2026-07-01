// FUNC_NAME: BNKStream::BNKStream

// Reconstructed constructor for BNKStream class at address 0x008a8270
// Initializes a BNKStream object with a name, two integer parameters, and links it into a global list.

#include <cstring>

// Forward declaration of base class constructor
extern void __fastcall BaseConstructor(); // FUN_0064cc90 - presumably initializes base class fields

class BNKStream {
public:
    BNKStream(char* name, int arg1, int arg2, int arg3);

private:
    void* vtable;               // +0x00: vtable pointer (set to &PTR_LAB_00d79c58)
    int field_04;                // +0x04: first parameter (arg1)
    int field_08;                // +0x08: third parameter (arg3)
    int field_0C;                // +0x0C: second parameter (arg2)
    int field_10;                // +0x10: cleared to 0
    int field_14;                // +0x14: cleared to 0
    int field_18;                // +0x18: cleared to 0
    int field_1C;                // +0x1C: cleared to 0
    BNKStream* next;             // +0x70 (0x1C * 4): next in global list (linked list pointer)
    char name[64];               // +0x20: name buffer (max 0x3F + null)
    // ... additional members would follow after name if any
};

// Global head of the linked list of BNKStream objects
extern BNKStream* g_StreamList; // DAT_012059ec

BNKStream::BNKStream(char* name, int arg1, int arg2, int arg3)
{
    // Call base class constructor (likely EARS::Object or similar)
    BaseConstructor();

    // Set vtable pointer to this specific class's vtable
    this->vtable = (void*)0x00d79c58; // &PTR_LAB_00d79c58

    // Copy the provided name with a maximum of 63 characters (plus null terminator)
    strncpy(this->name, name, 0x3F);

    // Store the three integer parameters. Note: order of assignment is unusual:
    // param_1[1] = arg1 (offset +0x04)
    // param_1[3] = arg2 (offset +0x0C)
    // param_1[2] = arg3 (offset +0x08)
    this->field_04 = arg1;
    this->field_0C = arg2;
    this->field_08 = arg3;

    // Initialize four consecutive fields to 0 (offsets +0x10, +0x14, +0x18, +0x1C)
    this->field_10 = 0;
    this->field_14 = 0;
    this->field_18 = 0;
    this->field_1C = 0;

    // Link this object to the global linked list (head updated)
    this->next = g_StreamList;       // previous head becomes our next
    g_StreamList = this;             // we become the new head
}