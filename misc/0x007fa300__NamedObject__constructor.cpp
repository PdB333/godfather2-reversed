// FUNC_NAME: NamedObject::constructor
// Function address: 0x007fa300
// Role: Constructor for a named object that is inserted into a global linked list.
// The object stores a name string (max 63 chars), three integer parameters, and a pointer to the previous head of the list.
// The global head pointer (DAT_012059ec) is updated to point to this new object.

#include <cstring> // for strncpy

// Forward declaration of base class constructor (called at start)
void __thiscall baseConstructor(void *this);

// Global head of the linked list
extern NamedObject *g_listHead; // DAT_012059ec

// Vtable pointer for this class (from PTR_LAB_00d71d5c)
extern void *g_NamedObjectVtable; // PTR_LAB_00d71d5c

class NamedObject {
public:
    // Vtable pointer at offset 0x00
    void *vtable;

    // Fields at offsets 0x04, 0x08, 0x0C (param_3, param_5, param_4)
    int field_0x04; // param_3
    int field_0x08; // param_5
    int field_0x0C; // param_4

    // Zeroed fields at offsets 0x10, 0x14, 0x18, 0x1C
    int field_0x10;
    int field_0x14;
    int field_0x18;
    int field_0x1C;

    // Name string at offset 0x20 (32 bytes), max 63 chars + null
    char name[64]; // +0x20

    // Next pointer in linked list at offset 0x70 (112 bytes)
    NamedObject *next; // +0x70

    // Constructor
    __thiscall NamedObject(const char *nameStr, int param3, int param4, int param5) {
        // Call base class constructor
        baseConstructor(this);

        // Set vtable pointer
        this->vtable = &g_NamedObjectVtable;

        // Copy name string (max 63 characters)
        strncpy(this->name, nameStr, 0x3F);
        this->name[0x3F] = '\0'; // Ensure null termination

        // Store parameters
        this->field_0x04 = param3;
        this->field_0x0C = param4;
        this->field_0x08 = param5;

        // Zero out fields at offsets 0x10-0x1C
        this->field_0x10 = 0;
        this->field_0x14 = 0;
        this->field_0x18 = 0;
        this->field_0x1C = 0;

        // Link into global list: set next pointer to current head, then update head to this
        this->next = g_listHead; // +0x70 = DAT_012059ec
        g_listHead = this;
    }
};