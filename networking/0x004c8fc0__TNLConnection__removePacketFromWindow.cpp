// FUNC_NAME: TNLConnection::removePacketFromWindow

// Removes a packet entry from the 32-slot window by matching a pair of IDs (e.g. sequence number and ack).
// The window is a fixed-size array of 32 slots, each 5 ints (20 bytes). 
// Head of structure: count at offset 0, slots start at offset 4*4 = 16 bytes.
void __fastcall TNLConnection::removePacketFromWindow(void* thisPtr, int* window)
{
    int index = 0;
    int* slotPtr = window + 5;  // start of first slot (skip header of 4 ints? window[4] is slot0 field0)
    // Expected comparison values are passed via ESI (sequenceNum) and EDI (packetID) from caller.
    // These are not formal parameters but set by preceding code.
    
    while ((slotPtr[-1] != unaff_EDI || *slotPtr != unaff_ESI)) // scan until both fields match
    {
        index++;
        slotPtr += 5; // move to next slot (5 ints)
        if (index > 31) // max 32 slots
            return;
    }
    
    // Found matching slot; remove it by zeroing its first two fields
    if (index != -1)
    {
        window[index * 5 + 4] = 0;  // slot[index].field0
        window[index * 5 + 5] = 0;  // slot[index].field1
        *window = *window - 1;      // decrement count
    }
}