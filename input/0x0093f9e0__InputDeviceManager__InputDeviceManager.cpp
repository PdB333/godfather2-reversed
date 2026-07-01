//FUNC_NAME: InputDeviceManager::InputDeviceManager
// Function address: 0x0093f9e0
// Constructor for InputDeviceManager singleton. Sets up vtable pointers, initializes fields, allocates internal buffer.

#include <cstdint>

// Forward declaration of vtable tables (defined elsewhere)
extern void* PTR_FUN_00d8b080;   // Base class vtable
extern void* PTR_LAB_00d8b070;   // Derived class vtable
extern void* PTR_FUN_00e2f19c;   // Another vtable (possibly base class initial)

// Global singleton pointer
extern InputDeviceManager* DAT_0112a560;

// Forward declaration of memory allocation function (size in bytes)
void* allocateMemory(uint32_t size);  // Actually FUN_0093f880

class InputDeviceManager {
public:
    // Vtable pointer at offset 0
    void* vtable0;          // +0x00: Set to &PTR_FUN_00d8b080
    // Vtable pointer at offset 4 (multiple inheritance or second interface)
    void* vtable1;          // +0x04: Set to &PTR_LAB_00d8b070 (overwrites initial &PTR_FUN_00e2f19c)
    // Member variables
    int32_t field_0x08;     // +0x08: Initialized to 1
    int32_t field_0x0C;     // +0x0C: Initialized to 0
    // Padding or other fields up to offset 0x20
    uint8_t pad[0x10];      // +0x10 to +0x1F (unknown)
    void* buffer;           // +0x20: Initialized to 0 (result of allocateMemory? Actually set to 0 after call)
    // Note: The call to allocateMemory(0x10) likely returns a pointer that is stored elsewhere or used internally.
    // The field at +0x20 is set to 0 after the call, so it might be a different field.

    // Constructor
    __fastcall InputDeviceManager(InputDeviceManager* this) {
        // Store this as global singleton
        DAT_0112a560 = this;

        // Initialize vtable pointers (two-stage: base then derived)
        this->vtable1 = &PTR_FUN_00e2f19c;   // Temporary base vtable
        this->field_0x08 = 1;
        this->field_0x0C = 0;
        this->vtable0 = &PTR_FUN_00d8b080;   // Derived class vtable at offset 0
        this->vtable1 = &PTR_LAB_00d8b070;   // Override with derived second vtable

        // Allocate internal buffer of 16 bytes (purpose unknown)
        allocateMemory(0x10);

        // Initialize a pointer field to null
        this->buffer = 0;   // +0x20

        // Return this (implicit in __fastcall)
    }
};