// FUN_NAME: PlasmaGameManager::PlasmaGameManager
// Address: 0x00567ee0
// Role: Constructor for the main game manager singleton ("Plasma Game Manager")
// This function initializes the vtable pointers, zeros key fields, and registers the singleton globally.

class PlasmaGameManager {
public:
    // Vtable pointers at offset 0x00 and 0x04 (likely from multiple inheritance)
    void* vtable0;                    // +0x00 - base class vtable (e.g., EARSObject)
    void* vtable1;                    // +0x04 - secondary vtable (interface)
    int32_t field_08;                 // +0x08
    int32_t field_0C;                 // +0x0C
    // ... other members ...
    // Fields at offsets 0x20, 0x28, 0x2C, 0x30, 0x34
    int32_t field_20;                 // +0x20
    int32_t field_28;                 // +0x28
    int32_t field_2C;                 // +0x2C
    int32_t field_30;                 // +0x30
    int32_t field_34;                 // +0x34
    // ... many more fields ...
    // Large offset data: +0x34C (211 dwords)
    void* vtable_large;               // +0x34C - another vtable pointer
    int32_t field_350;                // +0x350
    int32_t field_354;                // +0x354
    int32_t field_358;                // +0x358
    int32_t field_35C;                // +0x35C
};

// Global singleton pointer (stored at DAT_01223484)
PlasmaGameManager* g_plasmaGameManager;

// External functions called in the constructor
void __stdcall FUN_004d3bc0(const char* defaultID); // Sets the default ID string
void __stdcall FUN_00b1a890(void);                   // Secondary initialization

// Constructor implementation
void __thiscall PlasmaGameManager::PlasmaGameManager(void) {
    // Set up vtable pointers
    this->vtable0 = &PTR_FUN_00e3a9e0;      // base class vtable
    this->vtable1 = &PTR_LAB_00e3aa78;      // secondary vtable

    // Register as the global game manager instance
    g_plasmaGameManager = this;

    // Zero initial members
    this->field_08 = 0;
    this->field_0C = 0;

    // Set the default manager ID string
    FUN_004d3bc0("Plasma Game Manager Default ID");

    // Zero more fields (offsets 0x20..0x34)
    this->field_20 = 0;
    this->field_28 = 0;
    this->field_2C = 0;
    this->field_30 = 0;
    this->field_34 = 0;

    // Call second-phase initialization function
    FUN_00b1a890();

    // Initialize large offset region with another vtable pointer and zeros
    this->vtable_large = &PTR_LAB_00e3a9d8;  // +0x34C
    this->field_350 = 0;
    this->field_354 = 0;
    this->field_358 = 0;
    this->field_35C = 0;

    return;
}