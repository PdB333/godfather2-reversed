// FUNC_NAME: DynamicArray::addElement
uint __thiscall DynamicArray::addElement(int this, undefined4 elementKey, undefined4 param3, undefined4 param4, undefined4 param5, undefined4 param6, char param7)
{
    int *pElementCount; // pointer to element count at +0x08
    undefined4 *pNewElement;
    uint uVar3;
    int newCount;
    undefined4 uVar5;

    // Check if element key already exists using hash lookup
    uVar3 = FUN_005c0830(elementKey);
    if (-1 < (int)uVar3) {
        // Element already exists, return its index with high byte set
        return uVar3 & 0xffffff00;
    }

    // Get pointer to element count at offset +0x08
    pElementCount = (int *)(this + 8);
    newCount = *(int *)(this + 8) + 1;

    // Check if we need to grow the array (capacity at +0x0C)
    if (*(int *)(this + 0xc) < newCount) {
        // Grow array: reallocate with new capacity
        // +0x04 = data pointer, +0x08 = count, +0x0C = capacity
        uVar5 = FUN_005c27a0(*(undefined4 *)(this + 4), newCount, 0x18, pElementCount, this + 0xc);
        *(undefined4 *)(this + 4) = uVar5;
    }

    // Calculate pointer to new element slot (each element is 0x18 bytes)
    pNewElement = (undefined4 *)(*(int *)(this + 4) + *pElementCount * 0x18);
    // Increment element count
    *pElementCount = *pElementCount + 1;

    // Fill element structure (0x18 bytes = 6 dwords)
    pNewElement[1] = param3;  // +0x04
    pNewElement[3] = param5;  // +0x0C
    pNewElement[2] = param4;  // +0x08
    *pNewElement = elementKey; // +0x00
    pNewElement[4] = param6;  // +0x10
    pNewElement[5] = (uint)(param7 == '\0'); // +0x14 - boolean flag (inverted)

    // Return pointer to new element with low byte set to 1 (success flag)
    return CONCAT31((int3)((uint)pNewElement >> 8), 1);
}