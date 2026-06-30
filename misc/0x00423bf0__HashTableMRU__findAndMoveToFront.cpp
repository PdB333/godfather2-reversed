// FUNC_NAME: HashTableMRU::findAndMoveToFront
int HashTableMRU::findAndMoveToFront(uint key)
{
    // Hash table bucket array: this->buckets (uint**) at +0x00
    // Bucket count: this->bucketCount (int) at +0x04
    // MRU list head: this->mruHead (Node*) at +0x08
    // MRU count: this->mruCount (int) at +0x0c (decrement appears incorrect for move)
    // Node structure: +0x00 key (uint), +0x04 value (uint), +0x08 next (Node*)

    uint index = key % this->bucketCount;
    uint* bucketHead = this->buckets[index];
    uint* prev = nullptr;
    uint* curr = bucketHead;

    while (curr != nullptr) {
        if (*curr == key) {
            // Remove current node from bucket chain
            if (prev == nullptr) {
                this->buckets[index] = (uint*)curr[2]; // next becomes new head
            } else {
                prev[2] = curr[2]; // bypass current
            }

            // Move current node to front of MRU list
            curr[2] = (uint)this->mruHead; // previous MRU head becomes next of current
            this->mruHead = (uint*)curr;   // current becomes new MRU head
            this->mruCount--;               // NOTE: decrement seems wrong for a move; should be no change in count
            return 0;                       // success
        }
        prev = curr;
        curr = (uint*)curr[2];
    }
    return 1; // not found
}