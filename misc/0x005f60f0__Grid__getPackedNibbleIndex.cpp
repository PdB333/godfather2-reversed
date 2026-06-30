// FUNC_NAME: Grid::getPackedNibbleIndex
int Grid::getPackedNibbleIndex(int worldY, int worldX) // worldX passed in EAX, worldY as param_2
{
    byte nibble;
    uint flatIndex;

    // Check if grid data exists
    if (*(int*)(this + 0x40) != 0)
    {
        // Compute grid cell index: (worldY - gridOrigin) / cellSize * gridWidth + (worldX - gridOrigin) / cellSize
        // cellSize = 0x24 (36 units)
        // gridWidth is a ushort at +0x0c
        flatIndex = ((worldY - *(int*)(this + 0x20)) / 0x24) * (uint)*(ushort*)(this + 0x0c) +
                     ((worldX - *(int*)(this + 0x20)) / 0x24);

        // Extract 4-bit nibble from packed byte array at +0x40
        nibble = *(byte*)((flatIndex >> 1) + *(int*)(this + 0x40)) >> ((flatIndex & 1) * 4) & 0x0f;

        if (nibble != 0)
        {
            // Return a computed index: ((nibble + param_2->heightValue - 1) * 0x10 + baseOffset)
            // param_2+0x10 is a short used as height or layer base
            return (uint)(ushort)(((ushort)nibble + *(short*)(worldY + 0x10)) - 1) * 0x10 +
                   *(int*)(this + 0x24);
        }
    }
    return 0;
}