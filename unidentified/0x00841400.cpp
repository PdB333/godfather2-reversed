// FUN_00841400: InputDeviceManager::deactivateDevice
// Deactivates a device slot, zeroes out state fields, and triggers cleanup.
// Global g_pCurrentDeviceSlot points to a slot structure inside a device block (offset 0x48).
void __thiscall InputDeviceManager::deactivateDevice(void* thisPtr)
{
    int* pSlot = g_pCurrentDeviceSlot; // DAT_0112dcb4

    if ((pSlot != 0) && (pSlot != (int*)0x48)) {
        // Clear device state fields at +0x10, +0x14, +0x18
        pSlot[0x10/sizeof(int)] = 0;
        pSlot[0x14/sizeof(int)] = 0;
        pSlot[0x18/sizeof(int)] = 0;

        int deviceBase;
        if (pSlot == 0) {
            deviceBase = 0;
        } else {
            deviceBase = (int)((char*)pSlot - 0x48); // base of device block
        }

        // Call cleanup (likely device removal)
        FUN_00424df0(*(int*)((char*)thisPtr + 0xb0), deviceBase, 0, 0, 1, 0);
    }

    g_bDeviceActive = 0; // DAT_0112dcb0
}