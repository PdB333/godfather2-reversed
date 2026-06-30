// FUNC_NAME: InputDeviceManager::removeControllerDevice
// Function at 0x0060b4c0: Releases a controller device from all input slots and cleans up its resources.
// Uses global arrays and objects from the EARS input framework.

struct ControllerSlot {
    int active;      // +0x00: Whether the slot is active (1 = active)
    int deviceId;    // +0x04: Pointer to the controller device object (cast to int)
};

// Global input device manager (vtable at base)
extern class InputDeviceManager* g_inputDeviceManager; // DAT_01205750

// Global controller list manager (used to remove from list)
extern class ControllerList* g_controllerList; // DAT_01205868

// Global array of 16 controller slots (each 8 bytes). The array base is at DAT_011da7f4,
// and slots are laid out as [active, deviceId] contiguously. The loop uses a pointer
// to the deviceId field of each slot to simplify iteration.
extern ControllerSlot g_controllerSlots[16]; // Actually starts at DAT_011da7f4, but we offset

void InputDeviceManager::removeControllerDevice(int* controllerDevice) // __cdecl
{
    int slotIndex;
    int* pDeviceIdPtr; // pointer to deviceId in current slot

    slotIndex = 0;
    // Start pointer at the deviceId of the first slot. The decompiler shows &DAT_011da7f4
    // but that is actually the base of the active field; we adjust for clarity.
    pDeviceIdPtr = &g_controllerSlots[0].deviceId;
    do {
        // Check if this slot's deviceId matches the controller being removed
        if (*pDeviceIdPtr == (int)controllerDevice) {
            // If the slot is not already active, mark it active and notify the manager
            if (pDeviceIdPtr[-1] != 1) {
                // Call method at offset 0x198: probably notifySlotActiveChanged(slotIndex, 1)
                (*(void (__thiscall**)(InputDeviceManager*, int, int))(*g_inputDeviceManager + 0x198))
                    (g_inputDeviceManager, slotIndex, 1);
                pDeviceIdPtr[-1] = 1;
            }
            // Clear the deviceId for this slot (release assignment)
            if (*pDeviceIdPtr != 0) {
                // Call method at offset 400 (0x190): probably clearSlot(slotIndex, 0, 0, 0)
                (*(void (__thiscall**)(InputDeviceManager*, int, int, int, int))(*g_inputDeviceManager + 400))
                    (g_inputDeviceManager, slotIndex, 0, 0, 0);
                *pDeviceIdPtr = 0;
            }
        }
        slotIndex++;
        pDeviceIdPtr += 4; // Move to next slot's deviceId (skip over the active+deviceId pair)
    } while (slotIndex < 16);

    // Release the controller device object itself
    int* deviceObject = (int*)*controllerDevice; // *controllerDevice is the object pointer
    if (deviceObject != (int*)0x0) {
        // Call virtual function at offset 8 (likely Release or Delete)
        (*(void (__thiscall**)(int*))(*deviceObject + 8))(deviceObject);
        *controllerDevice = 0;
    }

    // Remove the controller from the global list (controllerDevice[2] is a list node)
    int* listNode = (int*)controllerDevice[2];
    if (listNode != (int*)0x0) {
        if (g_controllerList != (ControllerList*)0x0) {
            // Call virtual function at offset 4: probably removeFromList(listNode, 0)
            (*(void (__thiscall**)(ControllerList*, int*, int))(*g_controllerList + 4))(g_controllerList, listNode, 0);
        }
        if (controllerDevice != listNode) {
            controllerDevice[2] = 0;
        }
    }
}