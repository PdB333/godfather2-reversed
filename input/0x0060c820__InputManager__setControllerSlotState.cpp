// FUNC_NAME: InputManager::setControllerSlotState
// Address: 0x0060c820
// Updates cached controller state for a given slot and notifies the input manager if changed.
// Uses global state arrays:
//   gInputManager (0x01205750) - pointer to InputManager singleton
//   gCachedControllersState (0x011da7f0) - array of uint[16] (byte offset per slot: 4)
//   gCachedControllersEnable (0x011da7f4) - array of int[16] (byte offset 4)
//   gCachedControllersExtra1 (0x011da7f8) - array of int[16] with stride 0x10 per slot (field at +0x00)
//   gCachedControllersExtra2 (0x011da7fc) - array of int[16] with stride 0x10 per slot (field at +0x04)

void __thiscall InputManager::setControllerSlotState(uint combinedFlagsParam, int slotIndex, int* pEnableState, int param4, int param5)
{
    uint combinedFlags;
    int iVar1;
    uint in_EAX; // register EAX, possibly return of previous call or context

    iVar1 = slotIndex * 0x10; // stride for extra arrays

    // Combine flags: if in_EAX is not 0x40000000, force combinedFlagsParam to 1 then OR with in_EAX.
    // Otherwise just OR with in_EAX.
    if (in_EAX != 0x40000000) {
        combinedFlagsParam = 1;
    }
    combinedFlags = combinedFlagsParam | in_EAX;

    // Update combined state if changed
    if (gCachedControllersState[slotIndex] != combinedFlags) {
        // Call InputManager virtual function at vtable offset 0x198 (likely setControllerState)
        (*(void (__thiscall**)(InputManager*, int, uint))(*gInputManager + 0x198))(gInputManager, slotIndex, combinedFlags);
        gCachedControllersState[slotIndex] = combinedFlags;
    }

    // Update enable and extra values
    if (pEnableState == nullptr) {
        // If null, disable the slot
        if (gCachedControllersEnable[slotIndex] != 0) {
            (*(void (__thiscall**)(InputManager*, int, int, int, int))(*gInputManager + 400))(gInputManager, slotIndex, 0, 0, param4);
            gCachedControllersEnable[slotIndex] = 0;
        }
    } else {
        // If non-null, compare all three cached values
        if ((gCachedControllersEnable[slotIndex] != *pEnableState) ||
            (*(int*)(&gCachedControllersExtra1 + iVar1) != param5) ||
            (*(int*)(&gCachedControllersExtra2 + iVar1) != param4)) {
            (*(void (__thiscall**)(InputManager*, int, int, int, int))(*gInputManager + 400))(gInputManager, slotIndex, *pEnableState, param5, param4);
            // Update caches
            gCachedControllersEnable[slotIndex] = *pEnableState;
            *(int*)(&gCachedControllersExtra1 + iVar1) = param5;
            *(int*)(&gCachedControllersExtra2 + iVar1) = param4;
        }
    }
    return;
}