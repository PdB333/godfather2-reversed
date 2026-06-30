// FUNC_NAME: SimManager::SimManager
/**
 * Constructor for the simulation manager (SimManager).
 * Address: 0x006b7190
 * Role: Initializes simulation manager with vtable pointers, state machine tables, and optional script data.
 * Known class: SimManager (EA EARS engine).
 * This constructor sets up multiple function tables/vectors at specific offsets, loads an optional script blob into the first state table, and sets a global flag.
 */

class SimManager {
public:
    SimManager(void* initData);  // Constructor

    // Virtual function table pointer at +0x00
    // Offset 0x3C (0x0F * 4) - likely a state machine vtable or function pointer array
    // Offset 0x48 (0x12 * 4) - another function table
    // Offset 0x50 (0x14 * 4)
    // Offset 0x54 (0x15 * 4)
    // Offset 0x58 (0x16 * 4)
    // Offset 0x180 (0x60 * 4) - large table pointer
    // Offset 0x290 (0xA4 * 4) - counter or pointer (zeroed)
    // Offset 0x264 (0x99 * 4) - flags (bitwise OR with 0x20000)

private:
    // Start of member layout (inferred from offsets)
    // +0x00: void* vtable; // VTable pointer for SimManager
    // +0x3C: void* stateTable0; // First state machine function table
    // +0x48: void* stateTable1;
    // +0x50: void* stateTable2;
    // +0x54: void* stateTable3;
    // +0x58: void* stateTable4;
    // +0x180: void* largeTable; // Possibly AI or script table
    // +0x290: int field_0xA4; // Zeroed on construction
    // +0x264: int flags; // Bitfield, ORed with 0x20000

    // Base class (unknown, but called via FUN_008ba220)
};

// External global variable (script data blob) - possibly a pointer to an init script structure
extern void* gScriptDataBlob;  // DAT_0120e93c

// Memory copy function (may be memcpy or a EARS-specific copy)
void memcpy(void* dest, void* src, size_t size); // Placeholder for FUN_00408900

// Base class constructor (unknown, taking initData)
void BaseClassConstructor(void* thisPtr, void* initData); // Placeholder for FUN_008ba220

SimManager::SimManager(void* initData) {
    // Call base class constructor
    BaseClassConstructor(this, initData); // FUN_008ba220

    // Set vtable pointer to class's virtual function table
    this->vtable = &__SimManager_vtable; // PTR_FUN_00d5e3e8

    // Initialize state machine tables (pointers to static function arrays)
    this->stateTable0 = &__stateTable0; // PTR_LAB_00d5e3d8
    this->stateTable1 = &__stateTable1; // PTR_LAB_00d5e3d4
    this->stateTable2 = &__stateTable2; // PTR_LAB_00d5e3d0
    this->stateTable3 = &__stateTable3; // PTR_LAB_00d5e370
    this->stateTable4 = &__stateTable4; // PTR_LAB_00d5e308
    this->largeTable  = &__largeTable;  // PTR_LAB_00d5e2f0

    // Zero out field at +0x290 (0xA4)
    this->field_0xA4 = 0;

    // If a global script data blob is present, copy 0x8000 bytes into the first state table (stateTable0)
    if (gScriptDataBlob != nullptr) {
        memcpy(this->stateTable0, gScriptDataBlob, 0x8000); // FUN_00408900
    }

    // Set flags at offset +0x264 (0x99) - OR with 0x20000 (likely enables some feature)
    this->flags |= 0x20000;
}

// Static function table definitions (actual addresses from the binary)
// These are typically arrays of function pointers for state machine transitions.
static const void* __SimManager_vtable = (void*)0x00d5e3e8; // Actual vtable address
static const void* __stateTable0 = (void*)0x00d5e3d8;
static const void* __stateTable1 = (void*)0x00d5e3d4;
static const void* __stateTable2 = (void*)0x00d5e3d0;
static const void* __stateTable3 = (void*)0x00d5e370;
static const void* __stateTable4 = (void*)0x00d5e308;
static const void* __largeTable  = (void*)0x00d5e2f0;