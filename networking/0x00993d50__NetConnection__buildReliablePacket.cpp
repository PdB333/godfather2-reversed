//FUNC_NAME: NetConnection::buildReliablePacket
void NetConnection::buildReliablePacket(int connectionId, uint32_t sequence, void* dataBuffer1, void* dataBuffer2)
{
    int* writePtr;
    int adjustedId;

    // Adjust connection ID: if zero, keep zero; otherwise add offset to some table?
    if (connectionId == 0) {
        adjustedId = 0;
    } else {
        adjustedId = connectionId + 0x54; // +0x54: offset into connection table?
    }

    // Get the current write pointer from the global packet stream buffer (DAT_01206880 + 0x14)
    writePtr = (int*)(*(int*)(DAT_01206880 + 0x14)); // Dereference to get current buffer pointer

    // Write vtable pointer for the packet header
    *(void**)writePtr = (void*)&PTR_LAB_00e576f8; // vtable for ReliablePacketHeader
    writePtr = writePtr + 1; // Advance by 4 bytes

    // Write adjusted connection ID
    *writePtr = adjustedId;
    writePtr = writePtr + 1;

    // Write sequence number
    *writePtr = sequence;
    writePtr = writePtr + 1;

    // Update the global write pointer
    *(int*)(DAT_01206880 + 0x14) = (int)writePtr;

    // Initialize the two data buffers (likely memset to 0x10 fill pattern)
    FUN_0049c430(dataBuffer1, 0x40, 0x10); // size 0x40, fill byte 0x10
    FUN_0049c430(dataBuffer2, 0x10, 0x10); // size 0x10, fill byte 0x10
}