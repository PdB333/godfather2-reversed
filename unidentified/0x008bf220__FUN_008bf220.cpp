// FUNC_NAME: SomeManager::findIndexByFourInts
uint __thiscall SomeManager::findIndexByFourInts(int *key) {
    uint index = 0;
    if (*(uint *)(this + 0x1a8) != 0) { // count of items
        int **itemPtrArray = *(int ***)(this + 0x1a4); // array of pointers to items
        do {
            int *item = *itemPtrArray;
            int *data = *(int **)(item + 8); // pointer to data block at offset +8
            if (data != nullptr &&
                data[0x20/4] == key[0] && // +0x20
                data[0x24/4] == key[1] && // +0x24
                data[0x28/4] == key[2] && // +0x28
                data[0x2c/4] == key[3])   // +0x2c
            {
                return index;
            }
            index++;
            itemPtrArray++;
        } while (index < *(uint *)(this + 0x1a8));
    }
    return 0xffffffff;
}