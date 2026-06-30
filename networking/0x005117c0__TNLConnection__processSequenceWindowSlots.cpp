// FUNC_NAME: TNLConnection::processSequenceWindowSlots
void TNLConnection::processSequenceWindowSlots()
{
    // +0x5c: short mWindowSize
    // +0x74: ushort mNumToProcess
    // +0x76: ushort mStartSeq
    // +0xb0: PacketSlot mSlotArray[] (8 bytes each)
    ushort numToProcess = *(ushort*)(this + 0x74);
    ushort startSeq = *(ushort*)(this + 0x76);
    short windowSize = *(short*)(this + 0x5c);

    for (ushort i = numToProcess; i != 0; i--)
    {
        // Each slot is 8 bytes, indexed by (startSeq >> 3)
        PacketSlot* slot = (PacketSlot*)(this + 0xb0 + ((int)startSeq >> 3) * 8);
        FUN_0050fdc0(slot); // process the slot (likely handle ACK/timeout)
        startSeq++;
        if ((int)startSeq >= windowSize)
        {
            startSeq -= windowSize;
        }
    }
    // Update the stored start sequence? (not shown, but caller might)
}