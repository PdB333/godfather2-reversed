// FUNC_NAME: EventQueue::nextEvent
// Reconstructed from 0x00637650 - iterates through two arrays of events/slots, finds next active one, writes to output buffer
// Class layout (offsets assumed):
// +0x00: unknown
// +0x04: unknown
// +0x07: byte m_bitShiftCount - used to compute second array size: 1 << (byte & 0x1f)
// +0x0C: pointer to first array (each entry 8 bytes: int flag, int data)
// +0x10: pointer to second array (each entry 20 bytes: 5 ints: type, data1, data2, data3, flag? - flag checked at offset 8)
// +0x1C: int m_firstArrayCount

int EventQueue::nextEvent(uint32_t* outEvent) // outEvent = buffer of at least 4 uint32
{
    int idx = this->getCurrentIndex(); // FUN_00637590
    int count = *(int*)((char*)this + 0x1C); // m_firstArrayCount
    idx++;
    if (idx < count)
    {
        uint32_t* base = *(uint32_t**)((char*)this + 0x0C);
        uint32_t* pEntry = base + idx * 2; // each entry = 2 uint32 (8 bytes)
        do
        {
            if (*pEntry != 0) // first uint32 of entry is non-zero -> active
            {
                outEvent[0] = 3;
                outEvent[1] = *(uint32_t*)(&(float)(idx + 1)); // write float bits
                outEvent[2] = pEntry[0]; // entry[0]
                outEvent[3] = pEntry[1]; // entry[1]
                return 1;
            }
            idx++;
            pEntry += 2;
        } while (idx < count);
    }
    idx -= count;
    int secondCount = 1 << (*(unsigned char*)((char*)this + 7) & 0x1F);
    if (idx < secondCount)
    {
        uint32_t* base = *(uint32_t**)((char*)this + 0x10);
        uint32_t* pEntry = base + 2 + idx * 5; // skip first 2 uint32 (offset 0 and 4) then stride 5 (20 bytes)
        do
        {
            if (*pEntry != 0) // check uint32 at offset 8 of entry
            {
                int entryOffset = idx * 5;
                outEvent[0] = base[entryOffset + 0]; // type
                outEvent[1] = base[entryOffset + 1]; // data1
                outEvent[2] = base[entryOffset + 2]; // data2
                outEvent[3] = base[entryOffset + 3]; // data3
                return 1;
            }
            idx++;
            pEntry += 5;
        } while (idx < secondCount);
    }
    return 0;
}