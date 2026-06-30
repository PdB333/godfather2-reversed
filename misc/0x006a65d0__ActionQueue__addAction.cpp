// FUNC_NAME: ActionQueue::addAction
void __fastcall ActionQueue::addAction(ActionQueue* this)
{
    int slotIndex = 0;
    int* slotTypePtr = reinterpret_cast<int*>(this + 0x6bc); // +0x6bc: first slot's type field

    do {
        if (*slotTypePtr == 0) { // free slot found
            // Calculate slot base address (each slot is 0x18 bytes)
            int slotBase = reinterpret_cast<int>(this) + slotIndex * 0x18;
            
            // Copy command type from member at +0x6a4
            *reinterpret_cast<int*>(slotBase + 0x6bc) = *reinterpret_cast<int*>(this + 0x6a4);
            
            // Copy two 8-byte data blocks from members at +0x6a8 and +0x6b0
            // Data starts at slotBase + 0x6c0 (4 bytes after slot type)
            unsigned long long* dataPtr = reinterpret_cast<unsigned long long*>(slotBase + 0x6c0);
            dataPtr[0] = *reinterpret_cast<unsigned long long*>(this + 0x6a8);
            dataPtr[1] = *reinterpret_cast<unsigned long long*>(this + 0x6b0);
            
            // Local buffer for command processing
            int localBuffer[2] = {0, 0};
            
            // Process the command and store result byte at slot offset +0x14 (0x6d0 - 0x6bc)
            unsigned char result = FUN_006a62a0(*reinterpret_cast<int*>(this + 0x6a4), localBuffer, 0, 0);
            *reinterpret_cast<unsigned char*>(slotBase + 0x6d0) = result;
            
            // Cleanup if buffer was allocated
            if (localBuffer[0] != 0) {
                FUN_004daf90(localBuffer);
            }
            return;
        }
        slotIndex++;
        slotTypePtr += 6; // advance to next slot (6 ints = 0x18 bytes)
    } while (slotIndex < 32);
    // No free slot found; silently ignore
}