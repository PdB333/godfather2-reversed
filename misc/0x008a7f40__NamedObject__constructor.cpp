// FUNC_NAME: NamedObject::constructor

#include <cstring>

// Global head of the linked list of named objects
extern NamedObject* g_namedObjectListHead;

// Vtable symbol (likely from data section)
extern void* PTR_LAB_00d79c20;

// Constructor for a named object that gets registered in a global linked list
// Offsets:
// +0x00: vtable pointer
// +0x04: unknown field (stores param3)
// +0x08: unknown field (stores param5)
// +0x0C: unknown field (stores param4)
// +0x10-0x1C: zeroed fields (4 ints)
// +0x20: name buffer (63 chars, 0x3F bytes)
// +0x70: next pointer in linked list

class NamedObject {
public:
    void* vtable;            // +0x00
    int field_0x04;          // +0x04
    int field_0x08;          // +0x08
    int field_0x0C;          // +0x0C
    int field_0x10;          // +0x10
    int field_0x14;          // +0x14
    int field_0x18;          // +0x18
    int field_0x1C;          // +0x1C
    char name[0x3F];         // +0x20
    // padding (likely to align next pointer)
    NamedObject* next;       // +0x70
};

NamedObject* __thiscall NamedObject::constructor(NamedObject* this, const char* name, int arg1, int arg2, int arg3) {
    // Call base class constructor (unknown base class)
    baseConstructor();   // FUN_0064cc90

    // Set vtable
    this->vtable = &PTR_LAB_00d79c20;

    // Copy name, up to 63 characters (0x3F bytes)
    strncpy(this->name, name, 0x3F);
    this->name[0x3E] = '\0'; // ensure null-termination (strncpy may not if name is 63+ chars)

    // Store the three integer parameters
    // Note: The order of storage differs from the parameter order:
    //   param_1[1] = param3 (arg1)
    //   param_1[2] = param5 (arg3)
    //   param_1[3] = param4 (arg2)
    this->field_0x04 = arg1;  // param3
    this->field_0x08 = arg3;  // param5
    this->field_0x0C = arg2;  // param4

    // Zero out fields at offsets +0x10 through +0x1C
    this->field_0x10 = 0;
    this->field_0x14 = 0;
    this->field_0x18 = 0;
    this->field_0x1C = 0;

    // Insert this object into the global linked list (head insertion)
    this->next = g_namedObjectListHead;
    g_namedObjectListHead = this;

    return this;
}