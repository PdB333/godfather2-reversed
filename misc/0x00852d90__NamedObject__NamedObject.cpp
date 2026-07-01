// FUNC_NAME: NamedObject::NamedObject
// Function address: 0x00852d90
// Constructor for a named object with linked list insertion.

class NamedObject {
public:
    // Vtable pointer at offset 0
    // Fields:
    // +0x04: int field1 (param3)
    // +0x08: int field2 (param5)
    // +0x0C: int field3 (param4)
    // +0x10: int field4 (initialized to 0)
    // +0x14: int field5 (initialized to 0)
    // +0x18: int field6 (initialized to 0)
    // +0x1C: int field7 (initialized to 0)
    // +0x20: char name[64] (max 63 chars + null)
    // +0x70: NamedObject* next (offset 0x1C * 4 = 0x70)
    // Size: at least 0x74 bytes

    NamedObject(const char* name, int param3, int param4, int param5);
    // ... other methods
};

// Global head of linked list
extern NamedObject* g_namedObjectListHead; // DAT_012059ec

NamedObject::NamedObject(const char* name, int param3, int param4, int param5) {
    // Call base constructor (likely initializes vtable pointer)
    FUN_0064cc90(); // Base constructor

    // Set vtable pointer
    this->vtable = &PTR_LAB_00d75178;

    // Copy name (max 63 characters)
    strncpy(this->name, name, 63);
    this->name[63] = '\0'; // Ensure null termination

    // Set integer fields
    this->field1 = param3;   // offset +0x04
    this->field3 = param4;   // offset +0x0C
    this->field2 = param5;   // offset +0x08

    // Initialize zero fields
    this->field4 = 0;        // offset +0x10
    this->field5 = 0;        // offset +0x14
    this->field6 = 0;        // offset +0x18
    this->field7 = 0;        // offset +0x1C

    // Insert into global linked list (head insertion)
    this->next = g_namedObjectListHead; // offset +0x70
    g_namedObjectListHead = this;
}