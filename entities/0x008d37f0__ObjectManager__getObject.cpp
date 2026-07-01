// FUNC_NAME: ObjectManager::getObject

int __thiscall ObjectManager::getObject(int this, int handle) {
    int index;

    // First try to find the object by handle in the primary array
    index = findIndexByHandle(handle); // FUN_008d3190
    if (index >= 0) {
        // m_objectsArray is at this+0x18, array entries of size 0x18
        // Array start is at *(int*)(this+0x18) + 4 (skip count field)
        int* slotPtr = *(int**)(this + 0x18) + 4 + index * 0x18;
        if (slotPtr != nullptr) {
            // Return pointer to the object data at slot offset 0xc
            return (int)(slotPtr + 0xc);
        }
    }

    // Fallback: use secondary lookup (FUN_008d35f0) and some init (FUN_008d5df0)
    int fallbackResult = findObjectFallback(handle); // FUN_008d35f0
    globalInit(); // FUN_008d5df0
    return fallbackResult + 0xc;
}