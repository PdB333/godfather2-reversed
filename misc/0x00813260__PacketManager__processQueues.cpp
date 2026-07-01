// FUNC_NAME: PacketManager::processQueues
void __thiscall PacketManager::processQueues(uint thisPtr, byte flags)
{
    int* itemPtr;
    int item;
    uint combinedId;
    int idx;
    uint localId;

    if ((flags & 1) == 0) {
        // Non-immediate path (likely queued sends)
        idx = 0;
        localId = thisPtr;
        if (*(char *)(thisPtr + 0x66) != '\0') {
            do {
                item = *(int *)(*(int *)(thisPtr + 0x60) + idx * 4);
                if (item != 0) {
                    // Build command byte: bit0 comes from inverse of (flags+0x64)>>2
                    localId = (localId & 0xffffff00) | (~(*(byte *)(thisPtr + 100) >> 2) & 0x01);
                    if ((flags & 2) != 0) {
                        localId = (localId & 0xffffff00) | 1;
                    }
                    // Combine high word of item with byte at +0x65 to form 32-bit ID
                    combinedId = (((uint)item >> 16) << 16) | (ushort)*(byte *)(thisPtr + 0x65);
                    FUN_00814550(combinedId, item, 1, localId);
                }
                idx++;
            } while (idx < *(byte *)(thisPtr + 0x66));
        }

        // Process second set (lower priority/unreliable)
        idx = 0;
        if (*(char *)(thisPtr + 0x67) != '\0') {
            do {
                int setIdx = *(byte *)(thisPtr + 0x66) + idx;
                item = *(int *)(*(int *)(thisPtr + 0x60) + setIdx * 4);
                if (item != 0) {
                    combinedId = (((uint)setIdx >> 16) << 16) | (ushort)*(byte *)(thisPtr + 0x65);
                    FUN_00814550(combinedId, item, 0, ~(*(byte *)(thisPtr + 100) >> 2) & 1);
                }
                idx++;
            } while (idx < *(byte *)(thisPtr + 0x67));
        }
    }
    else {
        // Immediate path (likely direct send/ack)
        idx = 0;
        if (*(char *)(thisPtr + 0x66) != '\0') {
            do {
                itemPtr = (int *)(*(int *)(thisPtr + 0x60) + idx * 4);
                item = *itemPtr;
                if (item != 0) {
                    uint cmd = FUN_008142f0(*(byte *)(thisPtr + 0x65), item, 1, ~*(byte *)(thisPtr + 100) & 1);
                    FUN_00813170(*itemPtr, cmd);
                }
                idx++;
            } while (idx < *(byte *)(thisPtr + 0x66));
        }

        // Second set immediate
        idx = 0;
        if (*(char *)(thisPtr + 0x67) != '\0') {
            do {
                int setIdx = *(byte *)(thisPtr + 0x66) + idx;
                item = *(int *)(*(int *)(thisPtr + 0x60) + setIdx * 4);
                if (item != 0) {
                    combinedId = (((uint)item >> 16) << 16) | (ushort)*(byte *)(thisPtr + 0x65);
                    FUN_008142f0(combinedId, item, 0, ~(*(byte *)(thisPtr + 100) >> 1) & 1);
                }
                idx++;
            } while (idx < *(byte *)(thisPtr + 0x67));
            return;
        }
    }
    return;
}