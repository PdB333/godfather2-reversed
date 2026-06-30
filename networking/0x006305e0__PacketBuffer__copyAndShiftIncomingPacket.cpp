// FUNC_NAME: PacketBuffer::copyAndShiftIncomingPacket
// This function is part of the TNL (Torque Network Library) networking layer for The Godfather 2.
// It copies packets from the incoming buffer, handling 32-slot windowing.
// The class has: +0x00 data, +0x08 currentPos (pointer into buffer), +0x0C bufferEnd (end of valid data)
// param_2 = srcSlotIndex (index into window), param_3 = dstSlotIndex (index into window)
// in_EAX = this pointer

int __fastcall PacketBuffer::copyAndShiftIncomingPacket(int thisPtr, int srcSlotIndex, int dstSlotIndex)
{
    int* currentPos;
    int* bufferEnd;
    int* srcPtr;
    int* dstPtr;
    int result;
    
    bufferEnd = *(int**)(thisPtr + 0xC);     // +0x0C: bufferEnd
    currentPos = *(int**)(thisPtr + 0x8);    // +0x08: currentPos
    dstPtr = bufferEnd + 2;                  // points to slot at bufferEnd + 8 bytes

    // If we have room and the source slot is empty, just return the value from helper
    if ( (dstPtr < currentPos) && (dstPtr != (int*)0x0) && (*dstPtr == 0) ) {
        result = FUN_00625950(dstSlotIndex);  // likely getOrCreatePacket
        return result;
    }
    
    // Copy data from src slot (bufferEnd + 8) into currentPos
    *currentPos = *dstPtr;                    // copy packet ID
    currentPos[1] = *(int*)(bufferEnd + 3);   // copy sequence/ACK data
    *(int*)(thisPtr + 0x8) += 8;             // advance currentPos by 8 bytes
    
    // Now reference the src slot for copying
    srcPtr = *(int**)(thisPtr + 0x8);        // new currentPos
    
    // Handle srcSlotIndex -1 (means end of buffer)
    if (srcSlotIndex - 1 < 1) {
        srcPtr = (int*)FUN_00625430();       // probably getEndOfBufferMarker
    } else {
        srcPtr = bufferEnd - 2 + (srcSlotIndex - 1) * 2;  // offset into window
    }
    
    // Copy from src slot into new currentPos
    *srcPtr = *srcPtr;
    srcPtr[1] = srcPtr[1];
    *(int*)(thisPtr + 0x8) += 8;             // advance past copied data
    
    // Handle dstSlotIndex -2 (means end of buffer - reference a slot)
    srcPtr = *(int**)(thisPtr + 0x8);
    if (dstSlotIndex - 2 < 1) {
        dstPtr = (int*)FUN_00625430();       // probably getEndOfBufferMarker
    } else {
        dstPtr = bufferEnd - 2 + (dstSlotIndex - 2) * 2;
    }
    
    *srcPtr = *dstPtr;
    srcPtr[1] = dstPtr[1];
    *(int*)(thisPtr + 0x8) += 8;
    
    FUN_006362d0();                          // some post-processing or validation
    
    // Check if the last slot we wrote is valid and not empty/first-sequence-zero
    currentPos = (int*)(*(int*)(thisPtr + 0x8) - 8);
    if ((currentPos != (int*)0x0) && (*currentPos != 0) &&
        ((*currentPos != 1) || (*(int*)(*(int*)(thisPtr + 0x8) - 4) != 0))) {
        *(int**)(thisPtr + 0x8) = currentPos;
        return 1;    // success - packet was valid
    }
    *(int**)(thisPtr + 0x8) = currentPos;
    return 0;        // failure - packet was empty or invalid
}