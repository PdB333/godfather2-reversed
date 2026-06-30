// FUNC_NAME: GameObjectDatabase::setObjectData
void __thiscall GameObjectDatabase::setObjectData(uint key, const uint values[4]) {
    // Global pointer accessed via DAT_01223398
    // At global+8: pointer to hash table descriptor
    void* hashTableDesc = *(void**)((char*)DAT_01223398 + 8);

    // Hash table descriptor: +0x04 = bucket array pointer, +0x08 = number of buckets
    uint** bucketArray = *(uint***)((char*)hashTableDesc + 4);   // Array of HashNode pointers
    uint bucketCount = *(uint*)((char*)hashTableDesc + 8);      // Number of buckets

    // Compute bucket index
    uint index = key % bucketCount;
    uint* node = bucketArray[index];  // HashNode pointer

    // Traverse linked list
    while (node != nullptr) {
        if (*node == key) {  // node->key matches
            uint* valuePtr = node[1]; // node->value (pointer to object)
            // Safety check for valid value pointer (original checks node+1 != null)
            if (node != nullptr && valuePtr != nullptr) {
                // Write 4 dwords to object at offset 0x30
                valuePtr[0x30 / 4] = values[0];   // +0x30
                valuePtr[0x34 / 4] = values[1];   // +0x34
                valuePtr[0x38 / 4] = values[2];   // +0x38
                valuePtr[0x3C / 4] = values[3];   // +0x3C
                // Set flag at offset 0x98 to 1
                *(uint8*)((uint)valuePtr + 0x98) = 1;
            }
            return;
        }
        node = (uint*)node[2]; // node->next
    }
    // If no match found (fallback in original sets null and writes – likely unreachable)
    // Omitting that path as it would cause null dereference
    return;
}