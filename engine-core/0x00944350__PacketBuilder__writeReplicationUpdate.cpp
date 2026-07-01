// FUNC_NAME: PacketBuilder::writeReplicationUpdate
void __thiscall PacketBuilder::writeReplicationUpdate(void *this,
                                                      int packetType,             // param_2: type of packet (e.g., normal, delta)
                                                      void *dataBlock1,           // param_3: pointer to 16-byte block 1 (e.g., transform)
                                                      void *dataBlock2,           // param_4: pointer to 16-byte block 2 (e.g., velocity)
                                                      void *matrixBlock,          // param_5: pointer to 64-byte block (e.g., 4x4 matrix)
                                                      int flags,                  // param_6: bitfield flags
                                                      int timestamp,              // param_7: timestamp or sequence number
                                                      int objectId,               // param_8: network object ID
                                                      void *extraData,            // param_9: pointer to variable-length array (elements of size 0x30)
                                                      int elementCount,           // param_10: number of elements in extraData array
                                                      int extraFlags)             // param_11: additional flag/stride for extra data write
{
    unsigned int *writePtr;   // current write pointer (lives at this+0x14)

    // Write first integer (packet type) into buffer
    **(unsigned int **)((char *)this + 0x14) = packetType;
    *(int *)((char *)this + 0x14) = *(int *)((char *)this + 0x14) + 4; // advance pointer

    // Write three fixed-size chunks of data using internal helper (copies 'size' * 'count' bytes)
    // Here count is 0x10 (16) for first two, and 0x10 for third (but size differs)
    FUN_0049c430(dataBlock1, 0x10, 0x10);  // writes 16 * 16 = 256 bytes (likely a 16-element array of 16-byte data)
    FUN_0049c430(dataBlock2, 0x10, 0x10);  // writes another 256 bytes
    FUN_0049c430(matrixBlock, 0x40, 0x10); // writes 64 * 16 = 1024 bytes (e.g., 16 4x4 matrices)

    // Write next four integers sequentially
    writePtr = *(unsigned int **)((char *)this + 0x14);
    *writePtr = flags;
    writePtr = writePtr + 1;
    *(int *)((char *)this + 0x14) = (int)writePtr; // update pointer after writing flags

    **((int **)((char *)this + 0x14)) = timestamp;
    *(int *)((char *)this + 0x14) = *(int *)((char *)this + 0x14) + 4;

    **(unsigned int **)((char *)this + 0x14) = objectId;
    *(int *)((char *)this + 0x14) = *(int *)((char *)this + 0x14) + 4;

    **(int **)((char *)this + 0x14) = elementCount;   // number of elements
    *(int *)((char *)this + 0x14) = *(int *)((char *)this + 0x14) + 4;

    **(unsigned int **)((char *)this + 0x14) = extraFlags; // additional info for the extra block
    *(int *)((char *)this + 0x14) = *(int *)((char *)this + 0x14) + 4;

    // Write variable-length extra data block (each element is 0x30 bytes)
    // Total size = elementCount * 0x30, count = extraFlags (likely number of additional chunks or stride)
    FUN_0049c430(extraData, elementCount * 0x30, extraFlags);
    return;
}