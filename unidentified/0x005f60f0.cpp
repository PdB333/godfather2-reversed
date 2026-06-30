// FUN_NAME: TileGridMap::getTileData
int __thiscall TileGridMap::getTileData(int thisPtr, int x) {
    byte nibble;
    int y; // in_EAX - second coordinate passed via EAX (fastcall convention)
    uint linearIndex;

    // Check if tile data array exists (offset +0x40: pointer to nibble array)
    if (*(int *)(thisPtr + 0x40) == 0) {
        return 0;
    }

    // Calculate tile grid index: both x and y are divided by tile size (0x24 = 36)
    // baseCoord = *(int *)(thisPtr + 0x20)
    // gridWidth = *(unsigned short *)(thisPtr + 0x0c)
    linearIndex = ((x - *(int *)(thisPtr + 0x20)) / 0x24) * (uint)*(unsigned short *)(thisPtr + 0x0c) +
                  ((y - *(int *)(thisPtr + 0x20)) / 0x24);

    // Extract nibble (4-bit value) from packed byte array
    nibble = *(byte *)((linearIndex >> 1) + *(int *)(thisPtr + 0x40)) >> ((byte)linearIndex & 1) * 4 & 0xf;

    if (nibble == 0) {
        return 0;
    }

    // Combine nibble with a value from x (offset +0x10) to compute final result
    // baseOffset = *(int *)(thisPtr + 0x24)
    return (uint)(unsigned short)(((unsigned short)nibble + *(short *)(x + 0x10)) - 1) * 0x10 + *(int *)(thisPtr + 0x24);
}