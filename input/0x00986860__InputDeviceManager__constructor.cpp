// FUNC_NAME: InputDeviceManager::constructor
// Function at 0x00986860
// Constructor for the input device manager singleton. Initializes all fields to zero,
// sets vtable pointers, and sets a max count to 6 (likely max controllers/players).

void* g_inputDeviceManager; // DAT_01130048

class InputDeviceManager {
public:
    void** vtable;                      // +0x00
    void* field_0x10;                   // +0x10 (index 4)
    void* field_0x4C;                   // +0x4C (index 0x13)
    int field_0x50;                     // +0x50 (index 0x14)
    // ... many zeroed fields from +0x54 to +0x108 (indices 0x15-0x42)
    int maxCount;                       // +0x10C (index 0x43) set to 6
};

InputDeviceManager* __fastcall InputDeviceManager::constructor(InputDeviceManager* thisPtr) {
    // Call base class constructor (likely sets some vtable entries)
    FUN_005bf9b0();

    // Initial vtable-like pointer at +0x4C (overwritten below)
    thisPtr->field_0x4C = (void*)&PTR_LAB_00d90dec;

    // Store global singleton reference
    g_inputDeviceManager = thisPtr;

    // Clear field at +0x50
    thisPtr->field_0x50 = 0;

    // Set primary vtable at +0x00
    thisPtr->vtable = (void**)&PTR_FUN_00d90e18;

    // Set secondary vtable at +0x10
    thisPtr->field_0x10 = (void*)&PTR_LAB_00d90df4;

    // Override the vtable at +0x4C (final value)
    thisPtr->field_0x4C = (void*)&PTR_LAB_00d90df0;

    // Zero out large block from index 0x15 to 0x42 (offsets 0x54-0x108)
    for (int i = 0x15; i <= 0x42; i++) {
        *((uint32_t*)thisPtr + i) = 0;
    }

    // Zero a single byte within the dword at index 0x1a (offset 0x68)
    *((uint8_t*)thisPtr + 0x1a * 4) = 0;

    // Set final field at index 0x43 to 6 (max players/controllers)
    thisPtr->maxCount = 6;

    return thisPtr;
}