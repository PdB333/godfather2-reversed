// FUNC_NAME: ThreadLocalSlotManager::releaseSlot
void __fastcall releaseSlot(uint* thisPtr)
{
    // thisPtr[2] at offset +8 is a slot index; -1 indicates "no slot"
    int slotIndex = thisPtr[2];
    if (slotIndex >= 0)
    {
        // Fetch per‑thread data (likely a pointer to the owning manager)
        TlsGetValue(DAT_01139810);
        // Release the slot: *thisPtr is a resource handle,
        // slotIndex << 6 = slot offset (each slot = 64 bytes),
        // 0x17 (23) = size of slot data or a control constant.
        FUN_00aa26e0(*thisPtr, slotIndex << 6, 0x17);
    }
}