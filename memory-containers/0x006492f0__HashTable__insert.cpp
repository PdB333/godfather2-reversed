// FUNC_NAME: HashTable::insert
// Address: 0x006492f0
// Role: Insert an object into a hash table. The object pointer is passed in EDI, hash table pointer in EAX.
// Fields: this+0x00 = buckets array (int*), this+0x04 = bucketCount (int), this+0x08 = capacity (int), this+0x0C = count (int)
// Object: obj+0x08 = hash key, obj+0x18 = next pointer

void HashTable::insert(void* obj) {
    int bucketCount = *(int*)((char*)this + 0x04);
    int* bucketsArray = *(int**)((char*)this + 0x00);
    int count = *(int*)((char*)this + 0x0C);
    int capacity = *(int*)((char*)this + 0x08);

    // Check load factor: if twice bucket count <= 4*count+4, rehash
    if ((uint)(bucketCount * 2) <= (uint)(count * 4 + 4)) {
        uint newBucketCount = bucketCount * 2 + 1;
        if (newBucketCount < (uint)capacity) {
            newBucketCount = capacity;
        }
        // Reallocate/resize the hash table (FUN_0064a7c0)
        resize(newBucketCount);
    }

    // Hash: use bits 4..31 of obj's key, modulo bucket count
    uint hash = (*(uint*)((char*)obj + 8) >> 4) % bucketCount;
    // Insert at head of chain
    *(int*)((char*)obj + 0x18) = *(int*)((char*)bucketsArray + hash * 4);
    *(int*)((char*)bucketsArray + hash * 4) = (int)obj;
    // Increment count
    *(int*)((char*)this + 0x0C) = count + 1;
}