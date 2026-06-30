// FUNC_NAME: InputManager::updateControllerActiveFlags
// Address: 0x005974f0
// Scans 16 controller slots (each 0x1D0 bytes) at DAT_0119a9d0.
// If slot's active flag (bit 0) is set, calls FUN_005994c0(1,0) (likely enable rumble/force feedback).
// Then calls base class virtual update (vtable+0x14) with forwarded parameters.

// Global pointer to InputManager singleton
extern InputManager* g_pInputManager; // DAT_012055a4

// Known function: might be setControllerRumble(bool enable, int slotIndex)
void FUN_005994c0(int, int); // placeholder

void InputManager::updateControllerActiveFlags(undefined4 param_1, undefined4 param_2)
{
    byte* pSlot = (byte*)&g_controllerStateArray; // DAT_0119a9d0
    int slotCount = 16;

    do {
        if ((*pSlot & 1) != 0) { // Check active flag (bit 0)
            FUN_005994c0(1, 0); // Enable rumble/force feedback (slot 0? or global)
        }
        pSlot += 0x1D0; // stride to next slot structure
        slotCount--;
    } while (slotCount != 0);

    // Call base class virtual update function (offset 0x14 in vtable)
    (*(void (__thiscall**)(InputManager*, undefined4, undefined4))
        (*(uint32_t*)g_pInputManager + 0x14))(g_pInputManager, param_1, param_2);
}