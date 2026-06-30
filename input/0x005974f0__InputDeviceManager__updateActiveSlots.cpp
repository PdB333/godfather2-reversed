// FUNC_NAME: InputDeviceManager::updateActiveSlots
void InputDeviceManager::updateActiveSlots(void* arg_unknown)
{
    // Iterate over 16 device slots at DAT_0119a9d0, each 0x1D0 bytes
    byte* slotPtr = (byte*)&g_deviceSlots; // 0x0119a9d0
    for (int i = 0; i < 16; i++)
    {
        // Check if slot is active (bit 0 of first byte)
        if ((*slotPtr & 1) != 0)
        {
            // Process active slot (argument constant 1,0)
            processSlot(1, 0); // FUN_005994c0
        }
        slotPtr += 0x1D0; // stride to next slot
    }
    // Call base class update via vtable at offset 0x14
    (*(void (__thiscall**)(InputDeviceManager*, void*))(*(void**)g_baseInstance + 0x14))(this, arg_unknown);
}