// FUNC_NAME: EARS::Framework::HashTable::rehash
// Address: 0x004e1140
// Rebuilds the hash table with new bucket count = oldCount * 2 + 1.
// Rehashes all entries using a 16-byte key (or fixed-size string) hash.
// The hash table has linked-list buckets.

void HashTable::rehash() { // __thiscall
    // this structure: +0x00 : int* m_Buckets  (array of bucket heads)
    //                 +0x04 : int  m_NumBuckets
    uint newBucketCount = this->m_NumBuckets * 2 + 1;

    // Allocate new bucket array (size: newBucketCount * 4 bytes)
    int* newBuckets = new int[newBucketCount]; // FUN_009c8e80
    memset(newBuckets, 0, newBucketCount * 4);

    uint bucketIndex = 0;
    if (this->m_NumBuckets != 0) {
        do {
            // Get the first node in the current old bucket
            int* node = reinterpret_cast<int*>(this->m_Buckets[bucketIndex]);
            while (node != nullptr) {
                // Node structure (int*): 
                //   +0x00 : (unknown/int key?)
                //   +0x04 : next pointer
                //   +0x10 : byte* key pointer (assumed 16-byte key)
                byte* keyPtr = reinterpret_cast<byte*>(node[0x10 / 4]); // offset +0x10
                int* nextNode = reinterpret_cast<int*>(node[1]);       // next link

                // Compute hash over 16 bytes starting at keyPtr
                uint hash = 0;
                if (keyPtr != nullptr) {
                    byte* end = keyPtr + 16;
                    for (; keyPtr < end; keyPtr++) {
                        hash = hash * 0x1003f + *keyPtr;
                    }
                }

                // Insert node into new bucket linked list (head insertion)
                uint targetBucket = hash % newBucketCount;
                node[1] = newBuckets[targetBucket];  // node->next = old head
                newBuckets[targetBucket] = reinterpret_cast<int>(node); // bucket head = node

                node = nextNode;
            }
            bucketIndex++;
        } while (bucketIndex < static_cast<uint>(this->m_NumBuckets));
    }

    // Free old bucket array and update table
    delete[] reinterpret_cast<void*>(this->m_Buckets); // FUN_009c8f10
    this->m_Buckets = newBuckets;
    this->m_NumBuckets = static_cast<int>(newBucketCount);
}