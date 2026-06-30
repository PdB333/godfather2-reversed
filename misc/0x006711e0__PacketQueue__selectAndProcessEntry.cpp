// FUNC_NAME: PacketQueue::selectAndProcessEntry
void PacketQueue::selectAndProcessEntry(uint this, uint sequenceNum, int *srcPacketData, int remainingSize, undefined4 param_5, undefined4 param_6, undefined4 param_7, uint flags, int *outResult)
{
    int cumulativeSize;
    int index;
    short count;
    int result;
    uint currentIndex;
    uint localFlags;
    int baseSlot;

    baseSlot = this + (sequenceNum & 0x7f) * 0x3c;
    // Verify that the slot's stored sequence matches the expected one
    if (*(short *)(this + 0x1e + (sequenceNum & 0x7f) * 0x3c) != (short)sequenceNum) {
        *outResult = 0x4e23; // Error code: sequence mismatch
        return;
    }

    // Current index is the last valid entry (count - 1)
    currentIndex = (uint)(ushort)(*(short *)(baseSlot + 0x48) - 1);
    // Set current packet object pointer from the entry array
    *(undefined4 *)(this + 0x1e20) = *(undefined4 *)(*(int *)(baseSlot + 0x4c) + currentIndex * 4);

    localFlags = flags & 8;
    if ((localFlags == 0) || (*(short *)(baseSlot + 0x48) < 2)) {
        // Descending loop: iterate from currentIndex down to 0
        while (true) {
            index = (currentIndex & 0xffff) * 4;
            *(undefined4 *)(this + 0x1e20) = *(undefined4 *)(index + *(int *)(baseSlot + 0x4c));
            index = *(int *)(index + *(int *)(baseSlot + 0x50));
            *(int *)(this + 0x1e24) = index;
            if ((*(int *)(this + 0x1e20) == 0) || (index == 0)) goto LAB_006714ea;
            // Copy packet fields from source to the current packet object
            *(undefined4 *)(*(int *)(this + 0x1e20) + 0x20) = *(undefined4 *)(*srcPacketData + 0x20);
            *(undefined4 *)(*(int *)(this + 0x1e20) + 0x24) = *(undefined4 *)(*srcPacketData + 0x24);
            *(undefined4 *)(*(int *)(this + 0x1e20) + 0x40) = *(undefined4 *)(*srcPacketData + 0x40);
            *(undefined4 *)(*(int *)(this + 0x1e20) + 0x44) = *(undefined4 *)(*srcPacketData + 0x44);
            *(undefined4 *)(*(int *)(this + 0x1e20) + 0x48) = *(undefined4 *)(*srcPacketData + 0x48);
            *(undefined4 *)(*(int *)(this + 0x1e20) + 0x4c) = *(undefined4 *)(*srcPacketData + 0x4c);
            *(undefined2 *)(*(int *)(this + 0x1e20) + 0x60) = *(undefined2 *)(*srcPacketData + 0x60);
            *(undefined2 *)(*(int *)(this + 0x1e20) + 0x62) = *(undefined2 *)(*srcPacketData + 0x62);
            // Determine if we should invoke the processing callback
            if ((short)localFlags == 0) {
                count = FUN_00675740(); // Some check returning short
            } else {
                count = (short)remainingSize; // Use remainingSize as flag
            }
            if ((count != 0) || ((short)currentIndex == 0)) {
                // Invoke packet processing
                FUN_00674d40(remainingSize, param_5, param_6, &result);
            }
            if ((count != 0) || ((short)currentIndex == 0)) break;
            if (result != 0) goto LAB_006714cf;
            currentIndex = currentIndex + 0xffff; // decrement
        }
        if (result != 0) {
LAB_006714cf:
            index = (currentIndex & 0xffff) * 4;
            *(undefined4 *)(index + *(int *)(baseSlot + 0x4c)) = 0;
            *(undefined4 *)(index + *(int *)(baseSlot + 0x50)) = 0;
        }
    } else {
        // Ascending loop with weighted selection using cummulative sizes
        this = 0;
        cumulativeSize = 0;
        while (true) {
            currentIndex = this & 0xffff;
            *(undefined4 *)((int)baseSlot + 0x1e20) = *(undefined4 *)(*(int *)(baseSlot + 0x4c) + currentIndex * 4);
            index = *(int *)(*(int *)(baseSlot + 0x50) + currentIndex * 4);
            *(int *)((int)baseSlot + 0x1e24) = index;
            index = cumulativeSize + *(int *)(index + 0xbc); // Assume +0xbc is size/weight
            if (remainingSize < index) break; // Found entry that fits
            if (*(short *)(baseSlot + 0x48) - 1 <= (int)currentIndex) {
                // No suitable entry found; use source packet data as fallback
                *(int *)((int)baseSlot + 0x1e20) = *srcPacketData;
                FUN_00674d40(0, param_5, param_6, &result);
                goto LAB_006714ea;
            }
            this = this + 1;
            cumulativeSize = index;
        }
        // Copy packet fields to the selected entry
        *(undefined4 *)(*(int *)((int)baseSlot + 0x1e20) + 0x20) = *(undefined4 *)(*srcPacketData + 0x20);
        *(undefined4 *)(*(int *)((int)baseSlot + 0x1e20) + 0x24) = *(undefined4 *)(*srcPacketData + 0x24);
        *(undefined4 *)(*(int *)((int)baseSlot + 0x1e20) + 0x40) = *(undefined4 *)(*srcPacketData + 0x40);
        *(undefined4 *)(*(int *)((int)baseSlot + 0x1e20) + 0x44) = *(undefined4 *)(*srcPacketData + 0x44);
        *(undefined4 *)(*(int *)((int)baseSlot + 0x1e20) + 0x48) = *(undefined4 *)(*srcPacketData + 0x48);
        *(undefined4 *)(*(int *)((int)baseSlot + 0x1e20) + 0x4c) = *(undefined4 *)(*srcPacketData + 0x4c);
        *(undefined2 *)(*(int *)((int)baseSlot + 0x1e20) + 0x60) = *(undefined2 *)(*srcPacketData + 0x60);
        *(undefined2 *)(*(int *)((int)baseSlot + 0x1e20) + 0x62) = *(undefined2 *)(*srcPacketData + 0x62);
        FUN_00674d40(remainingSize - cumulativeSize, param_5, param_6, &result);
    }
LAB_006714ea:
    *srcPacketData = *(int *)(this + 0x1e20);
    *outResult = result;
    return;
}