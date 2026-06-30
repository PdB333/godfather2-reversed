// FUNC_NAME: ObjectManager::removeByKey
// Address: 0x00454810
// Role: Removes an entry from a dynamic array based on a two-int key.
//   Structure at this+0x40: pointer to array of Entry (size 0x10 each)
//   Structure at this+0x44: count of entries (uint)
// Entry layout:
//   +0x00: vtable pointer (used to call virtual function at offset 0x30)
//   +0x04: firstID (compared to key[0])
//   +0x08: secondID (compared to key[1])
//   +0x0C: userData (passed to virtual callback)
// When a matching entry is found, calls vtable[0x0C](key, userData)
// then removes the entry by compacting the array (move last entry to the gap).

struct Entry {
    void** vtable;      // +0x00
    int    firstID;     // +0x04
    int    secondID;    // +0x08
    void*  userData;    // +0x0C
};

class ObjectManager {
public:
    Entry* m_entries;     // +0x40
    int    m_entryCount;  // +0x44

    void removeByKey(int* key);
};

void ObjectManager::removeByKey(int* key) {
    int count = m_entryCount;
    if (count == 0) return;

    int index = 0;
    int offset = 0;
    while (index < count) {
        Entry* entry = reinterpret_cast<Entry*>(reinterpret_cast<char*>(m_entries) + offset);
        // Match both IDs
        if (entry->firstID == key[0] && entry->secondID == key[1]) {
            // Call virtual release function (offset 0x30 in vtable)
            void (**vfunc)(int*, void*) = reinterpret_cast<void (**)(int*, void*)>(entry->vtable[0x30 / 4]);
            (*vfunc)(key, entry->userData);

            // If not the last entry, move the last entry into its place
            if (index != count - 1) {
                Entry* lastEntry = reinterpret_cast<Entry*>(
                    reinterpret_cast<char*>(m_entries) + (count - 1) * sizeof(Entry));
                memcpy(entry, lastEntry, sizeof(Entry));
            }
            m_entryCount--;
            // Continue loop with updated count; offset remains same for next iteration? Actually the loop continues with the same index because the swapped element at current position needs re-check. But the decompiled code continues the loop; after decrement, uVar5 is updated and loop continues with uVar6 unchanged? Actually they do: if removal, they decrement count, then set uVar5 = count, and then the while condition checks uVar6 < uVar5. They don't increment uVar6. So the same index is rechecked (since the moved entry might also match?). However, the decompiled code uses uVar6 as index and increments only if no match. So we'll replicate that logic: no increment on match.
            count = m_entryCount; // update count
        } else {
            index++;
            offset += sizeof(Entry);
        }
    }
}