// FUNC_NAME: TNLConnection::buildNextReliablePacket
// Address: 0x00625f80
// Role: Builds the next reliable packet from the pending list into the send buffer.
// Uses __fastcall: ECX = this (but compiler saved to ESI), EDX = packetIndex (0-based? if <1 uses first pending)

bool __fastcall TNLConnection::buildNextReliablePacket(void* this, int packetIndex)
{
    int* pendingEntry; // pointer to a pending packet entry (8 bytes: type + dataPtr)
    int dataValue;     // value extracted from the pending entry's data pointer +0x08
    int* sendBufferPtr; // current write position in send buffer

    // If index < 1, get the first pending packet from a queue (via helper)
    if (packetIndex < 1) {
        pendingEntry = (int*)FUN_00625430(); // likely getNextPendingPacket()
    } else {
        // Compute address of the pending entry: base at this+0x0C, entry size 8 bytes, 1-based index?
        // Formula: base + (packetIndex-1)*8
        pendingEntry = (int*)(*(int*)((char*)this + 0x0C) - 8 + packetIndex * 8);
        // Check if the computed entry is beyond the current send buffer pointer
        if (pendingEntry <= *(int**)((char*)this + 0x08)) {
            return false;
        }
    }

    if (pendingEntry != nullptr) {
        // Only handle packet types 5 (reliable data?) or 7 (ack?)
        if (*pendingEntry == 5 || *pendingEntry == 7) {
            // Extract the value from the data pointer's +0x08 field
            dataValue = *(int*)(*(int*)((char*)pendingEntry[1] + 0x08));
            // Check if value is non-zero and differs from some expected value at this+0x10->+0x38
            if (dataValue != 0 && dataValue != *(int*)(*(int*)((char*)this + 0x10) + 0x38)) {
                // Write packet header (type 5) and the value into the send buffer
                sendBufferPtr = *(int**)((char*)this + 0x08);
                *sendBufferPtr = 5;          // packet type
                sendBufferPtr[1] = dataValue; // packet data
                // Advance send buffer pointer by 8 bytes
                *(int*)((char*)this + 0x08) = (int)(sendBufferPtr + 2);
                return true;
            }
        }
    }
    return false;
}