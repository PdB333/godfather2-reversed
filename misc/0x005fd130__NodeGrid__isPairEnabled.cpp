// FUNC_NAME: NodeGrid::isPairEnabled
bool __thiscall NodeGrid::isPairEnabled(int this, int ptr1, int ptr2)
{
    int* nodeArrayBase = *(int**)(this + 0x20);  // +0x20: base pointer to array of Node objects (each 0x24 bytes)
    unsigned short nodeCount = *(unsigned short*)(this + 0x0C);  // +0x0C: number of nodes in the array

    unsigned int index1 = (ptr1 - nodeArrayBase) / 0x24;
    unsigned int index2 = (ptr2 - nodeArrayBase) / 0x24;

    if (index1 == index2)
        return true;

    unsigned int pairKey;  // will encode the unordered pair (min, max) in a triangular matrix
    if (index1 < index2)
    {
        // offset = (2*nodeCount - index1 - 1) * index1 / 2
        int baseOffset = ((2 * (int)nodeCount - (int)index1 - 1) * (int)index1) >> 1;
        // then add (index2 - index1 - 1) to get linear index
        signed char charOffset = (signed char)(baseOffset) - (signed char)index1 - 1 + (signed char)index2;
        pairKey = (unsigned int)(charOffset);
    }
    else
    {
        int baseOffset = ((2 * (int)nodeCount - (int)index2 - 1) * (int)index2) >> 1;
        signed char charOffset = (signed char)(baseOffset) - (signed char)index2 - 1 + (signed char)index1;
        pairKey = (unsigned int)(charOffset);
    }

    unsigned char globalByte = getPairEnabledByte();  // FUN_005fca80 - returns a global 8-bit flag set
    // Check bit (pairKey & 7) in the global byte
    return (1 << (pairKey & 7) & globalByte) != 0;
}