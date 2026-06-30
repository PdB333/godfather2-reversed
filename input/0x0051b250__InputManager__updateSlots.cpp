// FUNC_NAME: InputManager::updateSlots
#include <cstdint>

// Class: InputManager
// Offsets:
//   +0x10 : int enableFlag - if non-zero, processing allowed
//   +0x80 : short slotCount - number of controller slots
//   +0xf4 : ControllerSlot slots[?] - array of 20-byte entries
struct ControllerSlot {
    int* pDevice; // +0x00 pointer to a device object
    // ... remaining 16 bytes unknown
};

// Global context accessed via fs:0x2c
// +0x08 : int deviceBaseOffset - offset added to device's base address
struct GlobalContext {
    char pad_00[8];
    int deviceBaseOffset; // +0x08
};

void InputManager::updateSlots() {
    short slotCount = *(short*)((uint8_t*)this + 0x80);
    if (slotCount <= 0) return;

    // Thread-local global context pointer (fs:[0x2c])
    GlobalContext* pGlobalCtx = *(GlobalContext**)__readfsdword(0x2c);
    if (!pGlobalCtx) return;

    // Iterate over slots
    ControllerSlot* pSlot = (ControllerSlot*)((uint8_t*)this + 0xf4);
    for (int i = 0; i < slotCount; i++) {
        // Check global enable flag
        if (*(int*)((uint8_t*)this + 0x10) != 0 && pSlot->pDevice != nullptr) {
            // Device object pointer
            uint8_t* pDevice = (uint8_t*)pSlot->pDevice;

            // Read base address from device at +0x10
            int baseAddr = *(int*)(pDevice + 0x10);

            // Compute target address using global offset
            uint32_t* pTarget = (uint32_t*)(baseAddr + pGlobalCtx->deviceBaseOffset);

            // Set flag 0x08000000 (probably indicates data ready/dirty)
            *pTarget |= 0x8000000;

            // Call device's update function at offset +0x28
            typedef void (*DeviceFunc)(uint8_t*);
            DeviceFunc pFunc = *(DeviceFunc*)(pDevice + 0x28);
            pFunc(pDevice);
        }

        // Advance to next slot (each slot is 20 bytes = 5 ints)
        pSlot = (ControllerSlot*)((int*)pSlot + 5);
    }
}