// FUNC_NAME: ObjectManager::findObjectByFourKeys
undefined4 __thiscall ObjectManager::findObjectByFourKeys(int this, int key1, int key2, int key3, int key4)
{
    // +0x148: count of items in the array at +0x80
    uint count = *(uint *)(this + 0x148);
    byte index = 0;

    if (count != 0) {
        do {
            // +0x80: array of pointers to objects
            int* objPtr = *(int **)(this + 0x80 + index * 4);
            // Object fields at offsets 0x20, 0x24, 0x28, 0x2c
            if (objPtr[0x20/4] == key1 && objPtr[0x24/4] == key2 && 
                objPtr[0x28/4] == key3 && objPtr[0x2c/4] == key4) {
                // Found match, return the pointer stored in the array
                return *(undefined4 *)(this + 0x80 + index * 4);
            }
            index++;
        } while ((uint)index < count);
    }
    return 0;
}