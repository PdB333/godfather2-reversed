// FUNC_NAME: StreamBufferManager::updateAllSlots
// Function at 0x008d2b40: Updates all 4 stream slots based on accumulated data counters.
// Each slot is 40 bytes (10 ints) starting at this+0x18.
// Slot layout (offsets from slot base):
//   0x00: field0 (countA)
//   0x04: field1 (countB)
//   0x08: field2 (bufferHandle/pointer)
//   0x0C: field3 (dataSourcePtr)
//   0x10: field4 (unused?)
//   0x14: field5 (dataTargetPtr)
//   0x18: field6 (copyDestPtr)
//   0x1C: field7 (unused?)
//   0x20: field8 (copySrcPtr)
//   0x24: field9 (byte flag: readyState)

void __fastcall StreamBufferManager::updateAllSlots(int thisPtr)
{
    for (uint slotIdx = 0; slotIdx < 4; ++slotIdx)
    {
        // Calculate base pointer for this slot: each slot is 10 ints (40 bytes)
        int *slot = (int *)(thisPtr + 0x18) + (slotIdx * 10);
        int countA = slot[-2];   // offset 0x00
        int countB = slot[-1];   // offset 0x04
        uint totalCount = countA + countB;

        // Check ready flag (byte at offset 0x24)
        char *readyFlag = ((char *)slot) + 0x24; // slot[7] as byte
        if (*readyFlag == 0)
        {
            // Not ready: if totalCount > 2, set ready flag
            if (totalCount > 2)
            {
                *readyFlag = 1;
            }
        }
        else if (totalCount < 3)
        {
            // Ready but insufficient data: free buffer if allocated
            if (slot[0] != 0) // field2 (bufferHandle)
            {
                FUN_006ff6c0(slot[0]); // release/free
                slot[0] = 0;
            }
            *readyFlag = 0;
        }
        else if (slot[0] == 0)
        {
            // Need to allocate a buffer
            int param2;
            if (countA == 0)
            {
                param2 = 0;
            }
            else
            {
                param2 = 2 - (uint)(countB != 0);
            }
            // Allocate buffer for this slot, passing pointer to field3 (dataSourcePtr) as output
            int newHandle = FUN_008d2a90(slotIdx, param2, slot + 1);
            slot[0] = newHandle; // field2
        }
        else
        {
            // Buffer exists: update it with data from field3 (dataSourcePtr)
            FUN_006ff440(slot[0], slot + 1); // memcpy or process
        }

        // Copy 8 bytes from field3 (offset 0x0C) to field6 (offset 0x18)
        *(undefined8 *)(slot + 4) = *(undefined8 *)(slot + 1);
        // Copy field5 (offset 0x14) to field8 (offset 0x20)
        slot[6] = slot[3]; // field8 = field5
        // Reset counters
        slot[-2] = 0; // countA
        slot[-1] = 0; // countB
    }
}