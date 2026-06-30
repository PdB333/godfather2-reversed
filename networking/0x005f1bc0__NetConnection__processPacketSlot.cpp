// FUNC_NAME: NetConnection::processPacketSlot
// Address: 0x005f1bc0
// Role: Processes a packet slot from an array, given a slot index extracted from a data pointer (EAX).
// The array at this+0x30 has a 2-byte count at its base, followed by entries of size 0x4A.
// The slot index is read from byte at EAX+3. After validation, calls two routines:
//   - FUN_005dbc10: likely dispatches slot index as signed char.
//   - FUN_005f3590: processes the entry data (offset +2 within the entry).
// Note: This function uses __thiscall with 'this' in EDI and a pointer in EAX.

class NetConnection {
public:
    // +0x30: pointer to array of packet slots (first element is packet count)
    // Array element size: 0x4A bytes (74). Offset +2 is used as entry data pointer.

    void processPacketSlot(int dataPtr) {
        unsigned char slotIndex = *(unsigned char*)(dataPtr + 3);                 // Extract slot index from data
        unsigned short* arrayPtr = *(unsigned short**)((char*)this + 0x30);       // Get array base

        if (arrayPtr != (unsigned short*)0xdeadbeef &&                            // Check if initialized
            (unsigned short)slotIndex < *arrayPtr)                               // Slot index within range
        {
            unsigned short* entryDataPtr = arrayPtr + (unsigned int)(unsigned short)slotIndex * 0x4A + 2;
            if (entryDataPtr != (unsigned short*)0x0)                            // Entry data pointer valid
            {
                // Process the slot using its index (cast to signed char then to int)
                FUN_005dbc10((int)(char)slotIndex);
                // Process the entry data (pointer to structure after 2-byte header)
                FUN_005f3590(entryDataPtr);
            }
        }
    }
};