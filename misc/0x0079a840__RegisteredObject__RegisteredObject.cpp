// FUNC_NAME: RegisteredObject::RegisteredObject
// Address: 0x0079a840
// Role: Constructor for a registered object that inserts itself into a global linked list.
// The object has a vtable, a name string (max 63 chars), three integer fields, and a next pointer for the list.

#include <cstring>

// Forward declaration of global head pointer
extern RegisteredObject* g_registeredObjectHead;

// Base class constructor (unknown, likely sets up vtable or other base data)
void BaseClass::BaseClass(); // FUN_0064cc90

class RegisteredObject {
public:
    // Vtable pointer at offset 0x00
    void* vtable;

    // Fields at offsets:
    // +0x04: field1 (param_3)
    int field1;
    // +0x08: field2 (param_5)
    int field2;
    // +0x0C: field3 (param_4)
    int field3;
    // +0x10: field4 (zeroed)
    int field4;
    // +0x14: field5 (zeroed)
    int field5;
    // +0x18: field6 (zeroed)
    int field6;
    // +0x1C: field7 (zeroed)
    int field7;
    // +0x20: name buffer (63 chars + null)
    char name[64];
    // ... other fields ...
    // +0x70: next pointer for linked list
    RegisteredObject* next;

    // Constructor
    __thiscall RegisteredObject(const char* nameStr, int param3, int param4, int param5) {
        // Call base class constructor
        BaseClass::BaseClass();

        // Set vtable pointer (global symbol)
        this->vtable = &PTR_LAB_00d6a77c;

        // Copy name string (max 63 characters)
        strncpy(this->name, nameStr, 63);
        this->name[63] = '\0'; // Ensure null termination

        // Assign parameters to fields (note order: param3 -> field1, param5 -> field2, param4 -> field3)
        this->field1 = param3;
        this->field3 = param4;   // param_4 goes to field3 (offset 0x0C)
        this->field2 = param5;   // param_5 goes to field2 (offset 0x08)

        // Zero out fields 4-7
        this->field4 = 0;
        this->field5 = 0;
        this->field6 = 0;
        this->field7 = 0;

        // Insert into global linked list (head insertion)
        this->next = g_registeredObjectHead; // DAT_012059ec
        g_registeredObjectHead = this;       // Update global head

        // Return this pointer (implicit in __thiscall)
    }
};