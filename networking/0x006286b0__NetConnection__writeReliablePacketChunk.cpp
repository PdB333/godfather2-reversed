// FUNC_NAME: NetConnection::writeReliablePacketChunk
void __thiscall NetConnection::writeReliablePacketChunk(int param_1, int param_2)
{
    // param_1: this pointer (NetConnection)
    // param_2: some integer value (likely a sequence number or time)
    // in_EAX: member variable at unknown offset, used as sequence index

    // Handle sequence number wrap-around (10000 = 0x2710)
    if (in_EAX + 9999U < 10000) {
        // Update sequence number based on pending chunk count
        // (writePos - readPos) >> 3 gives number of 8-byte chunks in buffer
        in_EAX = in_EAX + 1 + ((*(int *)(param_1 + 8) - *(int *)(param_1 + 0xc)) >> 3);
    }

    // Check if buffer has space (size at +0x20 vs used at +0x24)
    if (*(uint *)(*(int *)(param_1 + 0x10) + 0x20) <= *(uint *)(*(int *)(param_1 + 0x10) + 0x24)) {
        FUN_00627360(); // likely growBuffer()
    }

    // Write chunk type 4 (DataChunk) with string "notify"
    undefined4 *writePtr = *(undefined4 **)(param_1 + 8);
    *writePtr = 4; // chunk type
    undefined4 strId = FUN_00638920(param_1, &DAT_00e4156c, 1); // writeString("notify")
    writePtr[1] = strId;
    *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 8; // advance write pointer

    FUN_00625e70(); // some counter or state update

    int index = FUN_00628380(param_1, 1); // findChunkIndex(1)
    if (index >= 0) {
        // Existing chunk found: rewrite it
        if (*(uint *)(*(int *)(param_1 + 0x10) + 0x20) <= *(uint *)(*(int *)(param_1 + 0x10) + 0x24)) {
            FUN_00627360(); // growBuffer()
        }
        writePtr = *(undefined4 **)(param_1 + 8);
        *writePtr = 4; // chunk type
        strId = FUN_00638920(param_1, &DAT_00e4156c, 1); // writeString("notify")
        writePtr[1] = strId;
        *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 8;

        writePtr = *(undefined4 **)(param_1 + 8);
        *writePtr = 3; // chunk type (NotifyChunk)
        writePtr[1] = (float)param_2; // store param_2 as float
        *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 8;

        int currentWrite = *(int *)(param_1 + 8);
        int srcPtr;
        if (in_EAX < 1) {
            srcPtr = FUN_00625430(); // getReadBufferStart()
        } else {
            srcPtr = *(int *)(param_1 + 0xc) + -8 + in_EAX * 8; // read buffer + offset
        }
        undefined4 *dest = (undefined4 *)FUN_00638020(param_1, *(undefined4 *)(srcPtr + 4)); // allocateWrite()
        *dest = *(undefined4 *)(currentWrite - 8);
        dest[1] = *(undefined4 *)(currentWrite - 4);
        *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + -0x10; // rollback write pointer by 2 chunks
        return;
    }

    // No existing chunk: write new data
    FUN_00628430(); // resetBuffer() or clearPending()
    int srcPtr2;
    if (in_EAX < 1) {
        srcPtr2 = FUN_00625430(); // getReadBufferStart()
    } else {
        srcPtr2 = *(int *)(param_1 + 0xc) + -8 + in_EAX * 8;
    }
    undefined4 *readPtr = *(undefined4 **)(param_1 + 8);
    *readPtr = *(undefined4 *)srcPtr2;
    readPtr[1] = *(undefined4 *)(srcPtr2 + 4);
    *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 8;

    writePtr = *(undefined4 **)(param_1 + 8);
    *writePtr = 3; // chunk type
    writePtr[1] = (float)param_2;
    *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 8;

    int currentWrite2 = *(int *)(param_1 + 8);
    undefined4 *dest2 = (undefined4 *)FUN_00638020(param_1, *(undefined4 *)(currentWrite2 - 0x14)); // allocateWrite()
    *dest2 = *(undefined4 *)(currentWrite2 - 8);
    dest2[1] = *(undefined4 *)(currentWrite2 - 4);
    *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + -0x18; // rollback by 3 chunks
}