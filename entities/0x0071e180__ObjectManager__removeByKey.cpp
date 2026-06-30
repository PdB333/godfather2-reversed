// FUNC_NAME: ObjectManager::removeByKey
void __thiscall ObjectManager::removeByKey(int this, int key)
{
    int count = *(int *)(this + 0x74); // +0x74: number of entries
    int idx = 0;
    if (count > 0) {
        int *entryPtr = (int *)(this + 0x14); // +0x14: start of array (each entry 12 bytes)
        while (true) {
            int storedValue = *entryPtr;
            int entryKey;
            if (storedValue == 0) {
                entryKey = 0;
            } else {
                entryKey = storedValue - 0x48; // stored value is key + 0x48 (offset encoding)
            }
            if (entryKey == key) break;
            idx++;
            entryPtr += 3; // each entry is 3 ints (12 bytes)
            if (count <= idx) {
                return;
            }
        }
        // Found entry with matching key
        *(int *)(this + 0x10) = -1; // +0x10: current selection index, cleared
        FUN_0071de90(idx); // Remove entry at index idx
    }
}