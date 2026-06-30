// FUNC_NAME: EntityArrayManager::findItemByID
int __thiscall EntityArrayManager::findItemByID(int this, int id) {
    int arrayPtr = *(int *)(this + 0x20);   // +0x20: pointer to array of items (each 0x24 bytes)
    int metaPtr = *(int *)(this + 0x1c);    // +0x1c: pointer to metadata header
    if (arrayPtr != 0 && metaPtr != 0 &&
        *(int *)(metaPtr + 4) != 0 &&       // +0x4: possibly a pointer or flag
        *(short *)(metaPtr + 2) != 0)       // +0x2: number of items in the array
    {
        int index = findIndexByID(id, *(short *)(metaPtr + 2));
        if (index != -1) {
            return arrayPtr + index * 0x24;  // each item is 0x24 bytes
        }
    }
    return 0;
}