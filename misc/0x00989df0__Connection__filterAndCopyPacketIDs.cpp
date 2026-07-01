// FUNC_NAME: Connection::filterAndCopyPacketIDs

int __thiscall Connection::filterAndCopyPacketIDs(int this, void* destBuffer, short* sourceIDs, int count)
{
    short currentID;
    int filteredCount;
    int remainingSpace;
    int i;

    if (count == 0) {
        // No source IDs to process
        return 0;
    }

    // Save original this pointer (may be used later)
    int thisSaved = this;

    // If the callback (validate function) is set, filter the list
    if (*(int*)(this + 0x3C) != 0) {
        filteredCount = 0;
        // Variable-sized buffer for filtered IDs (allocated via alloca)
        short* filterBuffer = (short*)alloca(count * 2);

        // Iterate over source IDs and keep only valid ones
        for (i = 0; i < count; i++) {
            short currentID = sourceIDs[i];
            // Call validation function (virtual? offset +0x3C)
            short result = (*(short(__thiscall**)(int, short))(*(int*)(this + 0x3C)))(this, currentID);
            if (result != 0) {
                filterBuffer[filteredCount] = currentID;
                filteredCount++;
            }
        }

        // Update count to filtered count and set buffer pointer to filter buffer
        count = filteredCount;
        this = thisSaved;
        sourceIDs = filterBuffer;

        // Null-terminate the filtered list (only if the destination expects it)
        filterBuffer[count] = 0;
    }

    // Calculate remaining space in destination buffer (capacity - current position)
    // Offsets: +0x14 = capacity/total size, +0x28 = current write position
    remainingSpace = *(int*)(this + 0x14) - *(int*)(this + 0x28) - 1;
    if (remainingSpace < count) {
        // Not enough space, truncate to available space
        count = remainingSpace;
    }

    if (count > 0) {
        // Copy filtered IDs to destination buffer
        FUN_004dbc50(destBuffer, sourceIDs, 0, count); // memcpy? (dest, src, offset, count)
        // Update current write position to max size
        *(int*)(this + 0x28) = *(int*)(this + 0x1C); // +0x1C = buffer limit/max size

        // Log success (?) – global string at DAT_011301c0
        int logMsg[] = { DAT_011301c0, 0, 0 };
        FUN_00408a00(logMsg, 0);

        return count;
    }

    // Log failure (?) – global string at DAT_011302c0
    int logMsg2[] = { DAT_011302c0, 0, 0 };
    FUN_00408a00(logMsg2, 0);

    return 0;
}