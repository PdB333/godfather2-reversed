// FUNC_NAME: InputControllerManager::initialize
void InputControllerManager::initialize() {
    // This function initializes the global input controller manager singleton.
    // It sets up vtable pointers and creates two sub-managers (likely for keyboard/mouse and gamepad).
    
    // Set initial state: active = 1, something = 0, vtable pointer = &PTR_LAB_00e30b8c
    this->field_0x04 = 1;           // +0x04: active flag
    this->field_0x08 = 0;           // +0x08: unknown (maybe count)
    this->vtable_1 = &PTR_LAB_00e30b8c; // +0x0C: first vtable pointer

    // Second vtable pointer at offset +0x10
    this->vtable_2 = &PTR_LAB_00e30b50; // +0x10

    // Main vtable pointer at offset +0x00
    this->vtable = &PTR_FUN_00e30b64; // +0x00

    // Update vtable pointers again (overwrites previously set)
    this->vtable_1 = &PTR_LAB_00e30b74; // +0x0C
    this->vtable_2 = &PTR_LAB_00e30b78; // +0x10

    // Store pointer to this object's vtable_2 into the main game engine object at offset 0x94
    // DAT_012234a8 is the game engine singleton
    _DAT_012234a8->field_0x94 = &this->vtable_2;

    // Allocate 16 bytes for a controller device object (XInput device?)
    int* pDevice1 = (int*)operator new(0x10);
    if (pDevice1 == nullptr) {
        DAT_012053b0 = 0; // global pointer for first device
    } else {
        DAT_012053b0 = createInputDevice1(); // FUN_00421720 - constructs InputDevice1
    }

    // Allocate another 16 bytes for second controller device object
    int* pDevice2 = (int*)operator new(0x10);
    if (pDevice2 == nullptr) {
        DAT_012053ac = 0; // global pointer for second device
    } else {
        DAT_012053ac = createInputDevice2(); // FUN_00421850 - constructs InputDevice2
    }

    // Handle force feedback / vibration subsystem (DAT_01206778 is a pointer to a resource)
    if (DAT_01206778 != 0) {
        _DAT_0120677c++; // increment reference counter

        int* pVibration = vibrationGetHandle(); // FUN_00407da0
        if (pVibration == nullptr) {
            // Reset vibration resource with max value 0x7fff
            vibrationReset(&DAT_01206778, 0x7fff); // FUN_004084d0
        } else {
            // Toggle a flag at offset 0x14 in the vibration handle
            ushort flag = *(ushort*)(pVibration + 0x14);
            // ( ( (flag * 2) >> 1 ) + 1 ^ flag ) & 0x7fff ^ flag
            // This inverts the low 15 bits with some pattern
            *(ushort*)(pVibration + 0x14) = (( (flag * 2) >> 1 ) + 1 ^ flag) & 0x7fff ^ flag;
        }
    }

    // Check another global resource (DAT_012067b4) and process if non-null
    if (DAT_012067b4 != 0) {
        vibrationProcess(); // FUN_00407e60
    }
}