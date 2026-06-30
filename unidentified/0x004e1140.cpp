// FUN_NAME: HashTable::rehashBuckets
void HashTable::rehashBuckets() {
    // param_1 (this) points to HashTable structure:
    // +0x00: Entry** buckets (array of bucket heads)
    // +0x04: int numBuckets
    Entry** oldBuckets = reinterpret_cast<Entry**>(this->buckets);
    int oldCount = this->numBuckets;

    int newCount = oldCount * 2 + 1;
    // Allocate new bucket array (size in bytes = newCount * sizeof(Entry*))
    Entry** newBuckets = static_cast<Entry**>(customAlloc(newCount * sizeof(Entry*)));
    memset(newBuckets, 0, newCount * sizeof(Entry*));

    // Rehash all entries from old buckets into new buckets
    for (int i = 0; i < oldCount; i++) {
        Entry* entry = oldBuckets[i];
        while (entry != nullptr) {
            // Save the next pointer before we modify it
            Entry* nextEntry = reinterpret_cast<Entry*>(entry->next);

            // Get the key data for hashing:
            // Entry structure:
            // +0x00: Key* keyObject (pointer to a key struct)
            // +0x04: Entry* next
            // Key struct (at +0x10 in the keyObject) has a byte pointer to actual key data
            Key* keyObject = reinterpret_cast<Key*>(entry->keyObject);
            byte* keyData = reinterpret_cast<byte**>(keyObject)[0x10 / sizeof(byte*)]; // dereference offset +0x10 as byte*
            // keyData is assumed to point to a 16-byte hashable field
            uint hash = 0;
            if (keyData != nullptr) {
                for (int j = 0; j < 16; j++) {
                    hash = hash * 0x1003F + keyData[j];
                }
            }
            uint newBucketIndex = hash % newCount;

            // Prepend entry to the new bucket
            entry->next = reinterpret_cast<int>(newBuckets[newBucketIndex]);
            newBuckets[newBucketIndex] = entry;

            // Move to the next entry in the old bucket
            entry = nextEntry;
        }
    }

    // Free the old bucket array
    customFree(oldBuckets);

    // Update the hash table with new bucket array and count
    this->buckets = reinterpret_cast<int*>(newBuckets);
    this->numBuckets = newCount;
}