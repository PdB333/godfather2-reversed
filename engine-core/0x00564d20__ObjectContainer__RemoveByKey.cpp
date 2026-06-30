// FUNC_NAME: ObjectContainer::RemoveByKey
int __thiscall ObjectContainer::RemoveByKey(int this, Identifiable* keyOwner)
{
    // Get key string from the key owner object via virtual function at vtable+0x14
    byte* targetKey = keyOwner->GetKeyString();

    // Quick check or find? Call internal function FUN_00564de0 (probably a fast path)
    int result = QuickFind(this, targetKey);

    // If quick find returned 0 or the container is empty, return the result
    if (result == 0 || *(int*)(this + 0x1c) == 0) {
        return result;
    }

    // Otherwise, linear search and remove matching element
    int* items = (int*)(this + 8);
    int count = *(int*)(this + 0x1c);
    for (int i = 0; i < count; i++) {
        // Compare keys byte by byte (custom strcmp)
        byte* itemKey = ((Identifiable*)items[i])->GetKeyString();
        int cmp = 0;
        byte* p1 = itemKey;
        byte* p2 = targetKey;
        do {
            if (*p1 != *p2) {
                cmp = (*p1 < *p2) ? -1 : 1;
                break;
            }
            if (*p1 == 0) break;
            p1++;
            p2++;
        } while (true);

        if (cmp == 0) {
            // Found match; remove element at index i
            int removedItem = items[i];
            if (i < count - 1) {
                // Move last element to the gap
                items[i] = items[count - 1];
            }
            *(int*)(this + 0x1c) = count - 1;
            return removedItem;
        }
    }
    // Not found; return the original quick find result
    return result;
}