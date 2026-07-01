// FUNC_NAME: SystemManager::SystemManager
// Function address: 0x008b1e10
// Constructor for a global system manager singleton. Initializes vtable pointers, member variables,
// and calls sub-initializers. Stores 'this' in global pointer g_systemManager (DAT_0112988c).
// Also initializes a memory buffer (0x8000 bytes) if a global pointer (g_someBuffer) is non-null,
// and registers another buffer with ID 0x8001.

#include <cstdint>

// Forward declarations of external functions called
void __cdecl sub_4814B0(); // FUN_004814b0
void __cdecl sub_481530(); // FUN_00481530
void __fastcall sub_408900(void* dest, void* src, uint32_t size); // FUN_00408900
void __fastcall sub_4086B0(void* buffer, uint32_t id); // FUN_004086b0

// Global variables (from data references)
extern SystemManager* g_systemManager; // DAT_0112988c
extern void* g_someBuffer; // DAT_01206760
extern uint8_t g_otherBuffer[]; // DAT_01206778 (size unknown)

// Vtable pointers (external symbols)
extern void* vtable_00d7abfc; // PTR_FUN_00d7abfc
extern void* vtable_00d7abec; // PTR_LAB_00d7abec
extern void* vtable_00d7ab88; // PTR_FUN_00d7ab88

class SystemManager {
public:
    // Constructor (__fastcall, this in ecx)
    SystemManager* __fastcall SystemManager(SystemManager* this);

    // Member variables (offsets relative to this)
    // +0x00: vtable pointer 1
    // +0x04: vtable pointer 2 (base class?)
    // +0x08: someFlag (int32) - initialized to 1
    // +0x0C: someCounter (int32) - initialized to 0
    // +0x10: field_10 (int32) - initialized to 0
    // +0x14: field_14 (int32) - initialized to 0
    // +0x18: field_18 (int32) - initialized to 0
    // +0x1C: vtable pointer 3
    // +0x20-0x28: field_20, field_24, field_28 (int32) - initialized to 0
    // +0x2C: field_2C (int32) - initialized to 0
    // +0x30: field_30 (int32) - initialized to 0
    // +0x34: field_34 (int32) - initialized to 0
    // +0x38: field_38 (int32) - initialized to 0
};

SystemManager* __fastcall SystemManager::SystemManager(SystemManager* this) {
    // puVar1 points to the second vtable slot (offset +0x04)
    void** basePtr = reinterpret_cast<void**>(this) + 1;

    // Store this globally
    g_systemManager = this;

    // Set vtable pointers
    *basePtr = &vtable_00d7abec; // second vtable
    this->field_08 = 1;           // +0x08
    this->field_0C = 0;           // +0x0C

    // First vtable pointer at offset 0
    *reinterpret_cast<void**>(this) = &vtable_00d7abfc;

    // Overwrite second vtable again? (same as above)
    *basePtr = &vtable_00d7abec;

    // Initialize more fields
    this->field_10 = 0; // +0x10
    this->field_14 = 0; // +0x14
    this->field_18 = 0; // +0x18

    // Call sub-initializer
    sub_4814B0();

    // Set third vtable pointer at offset +0x1C
    *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(this) + 0x1C) = &vtable_00d7ab88;

    // Initialize fields at offsets 0x2C to 0x38
    this->field_2C = 0; // +0x2C
    this->field_30 = 0; // +0x30
    this->field_34 = 0; // +0x34
    this->field_38 = 0; // +0x38

    // Call another sub-initializer
    sub_481530();

    // If global buffer pointer is non-null, copy 0x8000 bytes from it to basePtr (offset +0x04)
    if (g_someBuffer != nullptr) {
        sub_408900(basePtr, &g_someBuffer, 0x8000);
    }

    // Register another buffer with ID 0x8001
    sub_4086B0(&g_otherBuffer, 0x8001);

    return this;
}