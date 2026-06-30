// FUNC_NAME: PacketWriter::getNextWritePosition
char* __fastcall PacketWriter::getNextWritePosition(void* thisPtr)
{
    char* pString = *(char**)((int)thisPtr + 0x84);
    char* pStrEnd = pString + 1; // Start after first char for alignment calculation
    // Find end of string
    while (*pString != '\0') {
        pString++;
    }
    int itemCount = *(int*)((int)thisPtr + 8);

    // Align the buffer position after the string. 0x15 is likely header offset.
    char* pos = pString + (0x15 - (int)pStrEnd)
                + ((itemCount * 4 + 8) - ((uint)(pString + (0x15 - (int)pStrEnd)) & 3));

    // Process array of items (stride 8 ints -> 32 bytes)
    if (itemCount != 0) {
        int* pItem = (int*)(*(int*)((int)thisPtr + 4) + 0x18); // Base of array
        char* itemPos = pos;
        for (int i = 0; i < itemCount; i++) {
            int typeId = pItem[0];
            char* nextPos;
            if (typeId == 0x3afd3141 || typeId == 0x3e55ddf1) {
                // Fixed size for these types
                nextPos = itemPos + 0x14;
            } else if (pItem[1] != 0) {
                if (typeId == 0x3e55ddf1) {
                    nextPos = itemPos + 0x14;
                } else {
                    // Variable size: add previous item's size field (at offset -2 ints)
                    int prevSize = pItem[-2];
                    nextPos = itemPos + prevSize + 0x14 + (4 - ((uint)(itemPos + prevSize + 0x14) & 3));
                }
            } else {
                // Default, size is 0xC
                nextPos = itemPos + 0xC;
            }
            pItem += 8; // Next item
            itemPos = nextPos;
        }
        pos = itemPos;
    }

    // Add fields at +0x24 and +0x38
    int var1 = *(int*)((int)thisPtr + 0x24);
    int var2 = *(int*)((int)thisPtr + 0x38);
    pos += (var1 != 0) + var2 * 4 + 4; // Note: (var1 != 0) is bool -> 0 or 1
    if (var1 != 0) {
        pos += var1 * 4 + 0x18;
    }

    // Add sizes from three helper calls (alignment or checksum sizes)
    // FUN_004ad440 likely returns alignment padding or segment size
    pos += getAlignPad() + getAlignPad() + getAlignPad();
    pos += (*(int*)((int)thisPtr + 0x60) + *(int*)((int)thisPtr + 0x4c)) * 4 + 8;

    return pos;
}