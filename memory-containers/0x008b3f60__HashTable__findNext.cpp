// FUNC_NAME: HashTable::findNext
// Address: 0x008b3f60
// Iterates through a hash table bucket chain to find an element matching a key.
// The iterator state is stored in the HashTable object itself.
// Structure layout:
//   +0x00: vtable pointer (virtual function getNextElement at index 0)
//   +0x04: currentIndex (position within current bucket)
//   +0x08: currentBucket (pointer to bucket header, or null)
//   +0x0C: keyToMatch (value to compare with first field of each element)
void __fastcall HashTable::findNext(HashTable* this) {
    int* bucket;
    int* element;

    while (true) {
        bucket = (int*)this->currentBucket; // +0x08
        if (bucket != nullptr) {
            this->currentIndex++; // +0x04
            // Check if we've exhausted the current bucket (bucket[2] = count at offset 8)
            if ((uint)this->currentIndex >= *(uint*)(bucket + 2)) {
                this->currentIndex = 0;
                this->currentBucket = nullptr;
                return; // No match found in this bucket chain
            }
        }
        // If no bucket and index is 0, we've finished all buckets
        if (this->currentIndex == 0 && bucket == nullptr) break;

        // Call virtual function to get next element pointer
        element = (int*)((void*(__thiscall*)(HashTable*))(this->vtable[0]))(this);
        if (*element == this->keyToMatch) { // +0x0C
            return; // Found matching element
        }
    }
    return;
}