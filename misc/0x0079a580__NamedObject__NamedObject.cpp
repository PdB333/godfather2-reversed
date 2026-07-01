// FUNC_NAME: NamedObject::NamedObject
// Constructor for a named object that is inserted into a global linked list.
// Address: 0x0079a580
// Parameters:
//   this - pointer to object (__thiscall)
//   name - string to copy (max 63 chars)
//   arg3 - stored at offset 0x04
//   arg4 - stored at offset 0x0C
//   arg5 - stored at offset 0x08
// Global head pointer: DAT_012059ec (g_namedObjectHead)

class NamedObject {
public:
    // Vtable pointer at +0x00
    void* vtable;

    // +0x04: some value (arg3)
    int field_04;

    // +0x08: some value (arg5)
    int field_08;

    // +0x0C: some value (arg4)
    int field_0C;

    // +0x10 to +0x1C: zeroed (4 ints)
    int field_10;
    int field_14;
    int field_18;
    int field_1C;

    // +0x20: name buffer (64 bytes)
    char name[64];

    // +0x70: pointer to next node in global list
    NamedObject* next;

    // Constructor
    NamedObject(const char* nameStr, int arg3, int arg4, int arg5) {
        // Call base class constructor (likely initializes vtable and other base members)
        BaseClassConstructor(); // FUN_0064cc90

        // Set vtable pointer
        this->vtable = &PTR_LAB_00d6a73c;

        // Copy name (max 63 chars + null)
        strncpy(this->name, nameStr, 63);
        this->name[63] = '\0';

        // Store parameters
        this->field_04 = arg3;
        this->field_0C = arg4;
        this->field_08 = arg5;

        // Zero out fields at +0x10 to +0x1C
        this->field_10 = 0;
        this->field_14 = 0;
        this->field_18 = 0;
        this->field_1C = 0;

        // Link into global list (prepend)
        this->next = g_namedObjectHead;
        g_namedObjectHead = this;
    }
};

// Global head pointer for the linked list of NamedObject instances
extern NamedObject* g_namedObjectHead; // DAT_012059ec