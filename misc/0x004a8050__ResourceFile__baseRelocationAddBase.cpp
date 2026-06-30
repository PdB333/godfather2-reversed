// FUNC_NAME: ResourceFile::baseRelocationAddBase
uint __fastcall ResourceFile::baseRelocationAddBase(int *thisPtr)
{
    uint eaxIn = 0; // placeholder for implicit in_EAX (unknown)
    uint result;
    int *groupPtr;
    int *entryPtr;
    ushort groupIndex;
    ushort entryIndex;
    ushort singleIndex;

    result = eaxIn & 0xffffff00;
    // Magic check: 0x9CBA7528 = -0x634584D8
    if ((thisPtr[0] == 0x9CBA7528) && (thisPtr[1] == 10)) {
        // First array: 'groups' with two fixup pointers each, stride 5 ints (20 bytes)
        // Count at offset +8 (2 bytes)
        groupIndex = 0;
        if (*(short *)&thisPtr[2] != 0) {
            do {
                // Pointer at index thisPtr[groupIndex*5 + 4] (offset 16 relative to group start)
                groupPtr = thisPtr + groupIndex * 5 + 4;
                if (thisPtr[groupIndex * 5 + 4] != 0) {
                    *groupPtr = thisPtr[groupIndex * 5 + 4] + (int)thisPtr;
                }
                // Second pointer at index thisPtr[groupIndex*5 + 8] (offset 32 relative to group start)
                if (groupPtr[4] != 0) {
                    groupPtr[4] = groupPtr[4] + (int)thisPtr;
                }
                groupIndex += 1;
            } while (groupIndex < *(ushort *)(thisPtr + 2));
        }

        // Second array: 'entries' with single fixup each, stride 2 ints (8 bytes)
        // Count at offset +10 (2 bytes)
        entryIndex = 0;
        int baseGroupCount = *(ushort *)(thisPtr + 2); // needed for calculation
        if (*(short *)((int)thisPtr + 10) != 0) {
            do {
                entryPtr = thisPtr + baseGroupCount * 5 + entryIndex * 2 + 5;
                if (thisPtr[baseGroupCount * 5 + entryIndex * 2 + 5] != 0) {
                    *entryPtr = thisPtr[baseGroupCount * 5 + entryIndex * 2 + 5] + (int)thisPtr;
                }
                entryIndex += 1;
            } while (entryIndex < *(ushort *)((int)thisPtr + 10));
        }

        // Third array: 'singles' one fixup each, stride 1 int (4 bytes)
        // Count at offset +12 (2 bytes)
        singleIndex = 0;
        ushort entryCount = *(ushort *)((int)thisPtr + 10);
        if (*(short *)&thisPtr[3] != 0) {
            do {
                int *singlePtr = thisPtr + baseGroupCount * 5 + entryCount * 2 + singleIndex + 4;
                if (thisPtr[baseGroupCount * 5 + entryCount * 2 + singleIndex + 4] != 0) {
                    *singlePtr = thisPtr[baseGroupCount * 5 + entryCount * 2 + singleIndex + 4] + (int)thisPtr;
                }
                singleIndex += 1;
            } while (singleIndex < *(ushort *)&thisPtr[3]);
        }
        // Final return computation (original logic, likely preserves low byte)
        result = ((uint)((int)entryPtr >> 8) << 8) | 1; // CONCAT31((int3)((uint)entryPtr >> 8), 1)
    }
    return result;
}