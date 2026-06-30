// FUNC_NAME: ObjectManager::getObjectByIndex
int __thiscall ObjectManager::getObjectByIndex(int *this, int index)
{
    int *arrayBase; // pointer to array element
    int iVar1;

    // The class likely has a member at offset 0 that is a pointer to an array of 8-byte entries.
    // Each entry is a pointer to a member at +0x48 of the actual object.
    arrayBase = *(int **)this; // +0x00: pointer to array
    iVar1 = arrayBase[index * 2]; // each entry is 8 bytes (two ints? or just a pointer array of 8-byte alignment)
    // Actually, the decompiled code shows param_2 * 8, so index * 2 ints == 8 bytes.
    // Typical for a pointer array with size 8 for each pointer? Probably just pointer at offset 0 of the entry.
    if (iVar1 != 0) {
        return iVar1 - 0x48; // subtract the offset to get the containing object
    }
    return 0;
}