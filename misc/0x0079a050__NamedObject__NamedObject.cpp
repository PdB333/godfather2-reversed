// FUNC_NAME: NamedObject::NamedObject
// Address: 0x0079a050
// Constructor for a named object that is inserted into a global linked list.
// The object has a vtable pointer, a name string (max 63 chars), three additional parameters,
// and a next pointer for the linked list (at offset 0x70).
// The global head pointer is at DAT_012059ec.

class NamedObject {
public:
    // Vtable pointer at offset 0x00
    void* vtable;

    // Unknown fields at offsets 0x04, 0x08, 0x0C, 0x10, 0x14, 0x18, 0x1C
    // Based on the constructor:
    // param_1[1] = param_3 (offset 0x04)
    // param_1[2] = param_5 (offset 0x08)
    // param_1[3] = param_4 (offset 0x0C)
    // param_1[4] = 0 (offset 0x10)
    // param_1[5] = 0 (offset 0x14)
    // param_1[6] = 0 (offset 0x18)
    // param_1[7] = 0 (offset 0x1C)
    int field_04;
    int field_08;
    int field_0C;
    int field_10;
    int field_14;
    int field_18;
    int field_1C;

    // Name string at offset 0x20 (param_1 + 8, each element is 4 bytes, so 8*4=32=0x20)
    char name[64]; // 0x3f = 63 chars + null terminator

    // Next pointer in linked list at offset 0x70 (param_1[0x1c] = 0x1c * 4 = 0x70)
    NamedObject* next;

    // Constructor
    NamedObject(const char* nameStr, int param3, int param4, int param5) {
        // Call base class constructor (likely initializes vtable and other base members)
        FUN_0064cc90(); // Base constructor

        // Set vtable pointer
        this->vtable = &PTR_LAB_00d6a6bc;

        // Copy name string (max 63 characters)
        strncpy(this->name, nameStr, 0x3f);
        this->name[0x3f] = '\0'; // Ensure null termination

        // Assign parameters
        this->field_04 = param3;
        this->field_0C = param4;
        this->field_08 = param5;

        // Zero out fields at offsets 0x10-0x1C
        this->field_10 = 0;
        this->field_14 = 0;
        this->field_18 = 0;
        this->field_1C = 0;

        // Insert into global linked list (head at DAT_012059ec)
        this->next = (NamedObject*)DAT_012059ec;
        DAT_012059ec = this;
    }
};

// Global head pointer for the linked list
extern NamedObject* DAT_012059ec; // Address: 0x012059ec

// Base constructor (address 0x0064cc90) - assumed to initialize base class members
extern void FUN_0064cc90(); // Base constructor

// Vtable symbol
extern void* PTR_LAB_00d6a6bc; // Address: 0x00d6a6bc