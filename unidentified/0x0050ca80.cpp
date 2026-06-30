// FUN_NAME: TLSManager::setSlotFlag
void TLSManager::setSlotFlag(int slotIndex, int* flagIndexPtr)
{
    // Call a lock or validation function (FUN_0050c9a0)
    threadLock(); // FUN_0050c9a0 - placeholder: acquire lock or check state

    // Get the per-thread data base from TLS (FS:0x2C)
    // The structure at TLS+0x2C points to a TIB or thread-local block.
    // At offset +8 from that block is a pointer to an array of SlotData (0x50 bytes each).
    SlotData* slotArray = *(SlotData**)(*(uint32_t**)__readfsdword(0x2C) + 8);
    SlotData* currentSlot = &slotArray[slotIndex];

    // Within each SlotData, offset 0x54 is a byte array of flags.
    // The flag index is given by the value pointed to by flagIndexPtr.
    uint32_t flagOffset = 0x54; // offset of flag array in SlotData
    byte* flagArray = reinterpret_cast<byte*>(reinterpret_cast<uint8_t*>(currentSlot) + flagOffset);
    uint32_t flagIndex = *flagIndexPtr;
    flagArray[flagIndex] |= 1; // Set the flag (bit 0)

    // Notify/signal that a flag was changed (FUN_0050fdc0)
    signalFlagChanged(flagIndexPtr); // placeholder: update or callback
}