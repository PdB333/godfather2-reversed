// FUNC_NAME: InputManager::updateControllerAxes
// Function address: 0x00411320
// Iterates through 16 controller slots, processes analog stick input, applies scaling and sends to game object.

class InputManager {
    // Size of each controller slot: 0x44 bytes
    struct ControllerSlot {
        byte unknown[0x6A];      // +0x00: Unknown data (likely flags, buttons, etc.)
        byte isConnected;        // +0x6A: Non-zero if controller is connected/active
        byte axisX;              // +0x6B: Left stick X axis (unsigned byte?)
        byte axisY;              // +0x6C: Left stick Y axis
        // ... rest of slot (0x44 - 0x6D = 0x? ) - align to 0x44
    } controllerSlots[16];       // offset 0x6A? Possibly this array starts at offset 0x6A within the manager
    // Actually the loop uses pbVar3 = this + 0x6B, so the axisX of first slot is at offset 0x6B.
    // That implies the array might be located at offset 0x6A, with isConnected at offset 0x6A of that slot? 
    // The slot size is 0x44, so slot[i].axisX is at this + 0x6B + i*0x44, slot[i].isConnected is at this + 0x6A + i*0x44.

    byte activeSlotIndex;        // +0x53D: Possibly the slot that currently has focus or is being used.
    // ... other members
};

// External functions (unknown implementations but named based on context)
void lockInputManager();                        // FUN_00b92e50
void* getControllerDevice(int slotIndex);       // FUN_00b94a50
void disableControllerDevice(void* device);     // FUN_00b92d50
void applyMovementToGameObject(int* scaledX);   // FUN_00b92d90 (takes pointer to local_c which is scaledX? Possibly a struct of two ints)

// Global sensitivity multipliers
extern float g_globalSensitivityX;  // DAT_00e44640
extern float g_globalSensitivityY;  // DAT_00e2e22c

void InputManager::updateControllerAxes() {
    lockInputManager();                         // Begin critical section? or lock input

    for (uint i = 0; i < 16; i++) {
        // Guard: skip if activeSlotIndex is set to a different slot,
        // and if this slot's controller is not connected
        if ((this->activeSlotIndex != i) && (this->controllerSlots[i].isConnected == 0))
            continue;

        void* device = getControllerDevice(i);
        if (device == nullptr)
            continue;

        // Read raw axis values (treated as unsigned bytes, but interpreted as 0..255)
        byte rawX = this->controllerSlots[i].axisX;
        byte rawY = this->controllerSlots[i].axisY;

        int scaledX = static_cast<int>(static_cast<float>(rawX) * g_globalSensitivityX * g_globalSensitivityY);
        int scaledY = static_cast<int>(static_cast<float>(rawY) * g_globalSensitivityX * g_globalSensitivityY);

        if ((scaledX == 0) && (scaledY == 0)) {
            // If both axes are zero and the device has a flag (maybe is enabled), disable it
            if (*(char*)(device + 4) != '\0') {
                disableControllerDevice(device);
            }
            applyMovementToGameObject(&scaledX); // pass zero vector
        } else {
            // Non-zero movement: apply with non-zero vector
            applyMovementToGameObject(&scaledX);
        }

        // Reset raw axis values (so they are consumed)
        this->controllerSlots[i].axisX = 0;
        this->controllerSlots[i].axisY = 0;
    }
}