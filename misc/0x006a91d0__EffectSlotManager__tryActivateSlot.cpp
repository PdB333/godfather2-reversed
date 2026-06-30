// FUNC_NAME: EffectSlotManager::tryActivateSlot
bool __fastcall EffectSlotManager::tryActivateSlot(int* slotData)
{
    // slotData layout:
    // +0x00: field0 (e.g., position X or start flag)
    // +0x04: field1 (e.g., position Y)
    // +0x08: field2 (e.g., position Z)
    // +0x0C: field3 (e.g., rotation or type)
    // +0x10: field4 (e.g., owner/context ID)
    // +0x14: field5 (e.g., allocated handle, 0 = inactive)
    if (((slotData[0] != 0 || slotData[1] != 0 || slotData[2] != 0 || slotData[3] != 0) &&
         (slotData[5] == 0)))
    {
        int contextValue = FUN_005e3070();                         // Get current frame context or time
        int newHandle = FUN_005e6500(slotData, contextValue);      // Allocate effect resource
        slotData[5] = newHandle;
        if (newHandle != 0)
        {
            FUN_005e67c0(newHandle, slotData[4]);                  // Initialize effect with owner/type
        }
    }
    return slotData[5] != 0;
}