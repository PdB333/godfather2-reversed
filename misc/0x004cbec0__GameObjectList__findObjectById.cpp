// FUNC_NAME: GameObjectList::findObjectById
int __thiscall GameObjectList::findObjectById(int id) {
    // Container pointer at this+0x08
    // The container likely has format: +0x00 (unknown), +0x04 (count), +0x08 (pointer to array of object pointers)
    Container* container = *(Container**)(this + 0x08);
    if (container == nullptr)
        return 0;

    uint count = *(uint*)(container + 0x04);
    if (count == 0)
        return 0;

    // Array of object pointers at container+0x08
    int** objectPtrs = *(int***)(container + 0x08);
    for (uint i = 0; i < count; i++) {
        int* obj = objectPtrs[i];
        // Compare object's ID field at offset 0x6c
        if (*(int*)(obj + 0x6c) == id) {
            return (int)obj;
        }
    }
    return 0;
}