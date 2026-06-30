// FUNC_NAME: SimManager::containsEntry
bool SimManager::containsEntry(int key) const {
    uint count = *(uint*)((char*)this + 0x81a4); /* +0x81a4: number of entries */
    if (count == 0) return false;

    // Array of 8-byte entries (key + value/pointer)
    struct Pair { int key; int value; };
    Pair* entries = *(Pair**)((char*)this + 0x81a0); /* +0x81a0: pointer to entry array */

    for (uint i = 0; i < count; ++i) {
        if (entries[i].key == key) return true;
    }
    return false;
}