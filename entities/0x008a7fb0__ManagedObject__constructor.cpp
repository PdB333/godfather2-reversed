// FUNC_NAME: ManagedObject::constructor
// Function address: 0x008a7fb0
// Role: Constructor for a named object that registers itself in a global linked list.
// The object stores a 63-character name, three integer parameters, and links to a global head pointer.

#include <cstring>

// Forward declaration of vtable symbol (external)
extern void* VTABLE_ManagedObject;  // PTR_LAB_00d79c28

// Global linked list head
extern ManagedObject* g_managedObjectHead;  // DAT_012059ec

class ManagedObject {
public:
    // Vtable pointer at offset 0x00
    void* vtable;                 // +0x00

    // Fields at offsets 0x04, 0x08, 0x0C (order based on code)
    int32_t field_04;             // param_3
    int32_t field_08;             // param_5
    int32_t field_0C;             // param_4

    // Zeroed fields at offsets 0x10, 0x14, 0x18, 0x1C
    int32_t field_10;
    int32_t field_14;
    int32_t field_18;
    int32_t field_1C;

    // Name buffer at offset 0x20 (since param_1+8 on 4-byte pointer gives +32 bytes)
    char name[64];                // +0x20, 0x3F max chars + null

    // Next pointer in linked list at offset 0x70 (0x1C * 4 = 0x70)
    ManagedObject* next;          // +0x70

    // Constructor
    ManagedObject(const char* str, int32_t a, int32_t b, int32_t c) {
        // Call base constructor (likely initializes some base members)
        BaseConstructor();  // FUN_0064cc90

        // Set vtable
        this->vtable = &VTABLE_ManagedObject;

        // Copy name (max 63 characters)
        strncpy(this->name, str, 0x3F);
        this->name[0x3F] = '\0';  // ensure null termination (though strncpy may pad with nulls)

        // Assign integer parameters
        this->field_04 = a;  // param_3
        this->field_0C = b;  // param_4
        this->field_08 = c;  // param_5

        // Clear the next four fields
        this->field_10 = 0;
        this->field_14 = 0;
        this->field_18 = 0;
        this->field_1C = 0;

        // Link into global list (new node becomes head)
        this->next = g_managedObjectHead;
        g_managedObjectHead = this;
    }

private:
    void BaseConstructor();  // stub for FUN_0064cc90
};

// Global definition for the vtable symbol (to be resolved by linker)
void* VTABLE_ManagedObject = nullptr;

// Global head pointer (initialized to 0)
ManagedObject* g_managedObjectHead = nullptr;