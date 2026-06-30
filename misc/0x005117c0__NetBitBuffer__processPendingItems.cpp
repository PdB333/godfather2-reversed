// FUNC_NAME: NetBitBuffer::processPendingItems

void NetBitBuffer::processPendingItems(void)
{
    // +0x74: number of items remaining to process (ushort)
    unsigned short itemsRemaining = *(unsigned short *)(this + 0x74);
    // +0x76: current bit index in the buffer (ushort)
    unsigned short currentBitIndex = *(unsigned short *)(this + 0x76);

    while (itemsRemaining != 0)
    {
        // Process the 8-byte item at the current byte-aligned offset (bits >> 3)
        // +0xb0: start of an array of 8-byte structures
        processItem(this + 0xb0 + ((currentBitIndex >> 3) * 8));

        currentBitIndex++;
        // +0x5c: maximum bit index (signed short)
        short maxBitIndex = *(short *)(this + 0x5c);
        if (maxBitIndex <= (int)currentBitIndex)
        {
            currentBitIndex = (unsigned short)((int)currentBitIndex - (int)maxBitIndex);
        }

        itemsRemaining--;
    }
    return;
}