// FUNC_NAME: InputDeviceManager::InputDeviceManager
// Address: 0x006bf7e0
// Role: Constructor for InputDeviceManager class. Initializes vtable pointers and checks for gamepad device.

// Note: The structure layout includes multiple vtable pointers at specific offsets, suggesting multiple inheritance or interface implementation.
// Offsets: +0x00 (primary vtable), +0x3C, +0x48, +0x50, +0x54, +0x58 are set to static function tables.
// +0x180 (param_1[0x60]) holds a pointer to a device object (likely a gamepad).

#include <cstdint>

class InputDeviceManager {
public:
    // Vtable pointer at offset 0 (primary)
    // Additional vtable pointers at offsets 0x3C, 0x48, 0x50, 0x54, 0x58 (for base classes/interfaces)
    // Member at offset 0x180 points to a device object

    // Constructor
    void __thiscall constructor() {
        // Set primary vtable
        *(void**)this = &PTR_FUN_00d5ecb0; // Vtable for InputDeviceManager

        // Set secondary vtable pointers (for multiple inheritance/interface implementations)
        *(void**)((uint8_t*)this + 0x3C) = &PTR_LAB_00d5eca0; // Interface 1 vtable
        *(void**)((uint8_t*)this + 0x48) = &PTR_LAB_00d5ec9c; // Interface 2 vtable
        *(void**)((uint8_t*)this + 0x50) = &PTR_LAB_00d5ec98; // Interface 3 vtable
        *(void**)((uint8_t*)this + 0x54) = &PTR_LAB_00d5ec38; // Interface 4 vtable
        *(void**)((uint8_t*)this + 0x58) = &PTR_LAB_00d5ebd0; // Interface 5 vtable

        // Check if a device (e.g., gamepad) is connected at offset 0x180
        if (checkDeviceStatus(*(void**)((uint8_t*)this + 0x180)) != 0) {
            // If device present, initialize it
            initDevice();
        }

        // Register or finalize initialization
        registerInputDevice();
    }

private:
    // Check if the device pointer at offset 0x180 indicates a valid device
    // Returns non-zero if device is connected
    int __fastcall checkDeviceStatus(void* devicePtr); // FUN_006b07e0

    // Initialize the device (e.g., gamepad)
    void __fastcall initDevice(); // FUN_006ae600

    // Global registration/housekeeping
    void __fastcall registerInputDevice(); // FUN_0046ea20
};