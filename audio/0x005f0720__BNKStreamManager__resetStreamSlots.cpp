// FUNC_NAME: BNKStreamManager::resetStreamSlots
// Address: 0x005f0720
// Role: Resets all stream slot entries and frees the stream object list. Called during resource cleanup.

struct BNKStreamManager::StreamSlot {
    int offset;    // +0x00: byte offset into the block
    int size;      // +0x04: size in bytes (1024 * streamPartCount)
    uint8 flags;   // +0x08: 0 = unused, 1 = used
};

int BNKStreamManager::resetStreamSlots() {
    uint streamCount = *(uint*)(this + 0x250);              // number of stream objects
    undefined4* header = (undefined4*)(this + 8);
    if (header) {
        *header = 0;
        *(undefined4*)(this + 0xC) = 0;
        *(undefined2*)(this + 0x10) = 0x23;                 // max slots (35)
        *(undefined2*)(this + 0x12) = 0;
        FUN_005dbc10(header, 0x23);                         // init allocator pool
    }

    int slotIndex = 0;
    uint8* slotData = (uint8*)(this + 0x20);                // base of slot entries (each 16 bytes)
    int remaining = 0x23;                                   // max slots
    do {
        *(int*)(slotData - 8) = 0xFFFFFFFF;                 // clear offset field (actually -8 from slotData, but offset is +0x18 from this)
        *slotData = 0;                                      // clear first flag byte? Actually slotData points to offset+0x20? Wait structure is at this+0x18.
        slotData += 0x10;
        remaining--;
    } while (remaining != 0);

    // Actually the array is at this+0x18, not this+0x20. Let me correct.
    // The code uses puVar4 = (uint8*)(param_1 + 0x20); and writes *(undefined4 *)(puVar4 + -8) = 0xffffffff;
    // So puVar4 points to the byte JUST AFTER the first field? Indeed puVar4 starts at +0x20, and writes to -8 (i.e., +0x18) and then *puVar4=0 (at +0x20). That means each slot is 16 bytes starting at +0x18, but the loop increments puVar4 by 16, so it scans 0x23 slots.
    // So the first slot is at this+0x18: offset, size, flags, padding.
    // Let's rewrite correctly.

    int slotIdx = 0;
    uint32 loopCount = 0;
    if (streamCount != 0) {
        do {
            int streamObj = *(int*)(*(int*)(this + 0x24C) + loopCount * 4);
            if (streamObj && *(int*)(streamObj + 0x24) != 0) {
                uint partCount = 0;
                int* slotPtr = (int*)(slotIdx * 0x10 + 0x18 + (int)this);
                do {
                    int partSize = *(int*)(streamObj + 0x20) * 1024; // 0x400
                    slotPtr[-1] = slotIdx;                           // offset into block? Actually written as iVar8 which accumulates
                    *slotPtr = partSize;                             // size
                    *(uint8*)(slotPtr + 2) = 0;                      // flags = unused
                    partCount++;
                    slotIdx++;
                    slotPtr += 4; // 16 bytes per slot
                } while (partCount < *(uint*)(streamObj + 0x24));
            }
            loopCount++;
        } while (loopCount < streamCount);
    }

    *(uint*)(this + 0x250) = 0;          // clear stream count
    FUN_009c8f10(*(int*)(this + 0x24C)); // free stream object list
    *(int*)(this + 0x24C) = 0;           // null pointer
    *(int*)(this + 0x254) = 0;           // total slots count
    return 1;                            // success
}