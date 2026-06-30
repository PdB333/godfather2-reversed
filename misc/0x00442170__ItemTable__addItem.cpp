// FUNC_NAME: ItemTable::addItem
int ItemTable::addItem(int item) {
    int *entryPtr;
    int count;
    int index;

    index = -1;
    if (item != 0) {
        index = FUN_004420f0(item); // Check if item already exists
        if (index == -1) {
            count = this->count; // +0x28: current number of items
            if (count < this->capacity) { // +0x20: maximum capacity
                this->count = count + 1;
                entryPtr = (int *)(this->arrayBase[count * 0x14]); // +0x24: pointer to item array (each entry 20 bytes)
                *entryPtr = item;
                entryPtr[1] = 0; // offset 0x04
                *(char *)(&entryPtr[3]) = 0; // offset 0x0C (byte)
                *(short *)((int)entryPtr + 0x0E) = 0; // offset 0x0E (short)
                entryPtr[2] = 0; // offset 0x08
                // Trigger callback after adding
                FUN_00441d30(); // Possibly notify or update something
                index = count;
            }
        }
    }
    return index;
}