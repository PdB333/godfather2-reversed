// FUNC_NAME: ItemProcessor::processAllItems
void __thiscall ItemProcessor::processAllItems(void) {
    uint count = *(uint *)(this + 0x124); // +0x124: number of items in the list
    if (count != 0) {
        int *itemArray = (int *)(this + 0x24); // +0x24: array of pointers to items
        for (uint i = 0; i < count; ++i) {
            char *dataPtr = *(char **)(itemArray[i] + 0x24); // +0x24 in each item: pointer to data (e.g., name)
            if (dataPtr == (char *)0x0) {
                dataPtr = &DAT_0120546e; // default data string (likely "None" or empty)
            }
            // Calls a function to process the data pointer (e.g., print, update, or register)
            processItemData(dataPtr); // FUN_00565870
        }
    }
}