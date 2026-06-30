// FUNC_NAME: HashTable::resize
// This function rehashes the hash table by doubling the number of buckets (newSize = oldCapacity * 2 + 1).
// It allocates a new bucket array, redistributes all existing entries, frees the old array, and updates the structure.
void __thiscall HashTable::resize(HashTable *this) // __fastcall in asm, but it's a __thiscall
{
    uint newCapacity; // new number of buckets
    uint *newBuckets; // pointer to new bucket array (holds head pointers for each bucket)
    uint *oldBuckets;
    uint *entry;
    uint *nextEntry;
    uint index;

    // New capacity = old capacity * 2 + 1 (ensures odd number, good for hashing)
    newCapacity = this->bucketCount * 2 + 1; // param_1[1] is bucketCount, new size
    // Allocate memory for new bucket array (each entry is a pointer, 4 bytes)
    newBuckets = (uint *)heapAlloc(-(uint)((int)((ulonglong)newCapacity * 4 >> 0x20) != 0) | (uint)((ulonglong)newCapacity * 4));
    memset(newBuckets, 0, newCapacity * 4);

    // Iterate over all old buckets
    for (index = 0; index < this->bucketCount; index++)
    {
        // Get the head of the linked list in this bucket
        entry = *(uint **)(this->buckets + index * 4); // param_1[0] is buckets pointer (array of uint*)
        while (entry != nullptr)
        {
            // Save next pointer before modifying
            nextEntry = (uint *)entry[3]; // entry[3] is the 'next' pointer (offset +0x0C)
            // Prepend this entry to the new bucket (using key modulo newCapacity)
            entry[3] = *(uint *)(newBuckets + (entry[0] % newCapacity) * 4); // entry[0] is the key
            *(uint **)(newBuckets + (entry[0] % newCapacity) * 4) = entry;
            entry = nextEntry;
        }
    }

    // Free old bucket array
    heapFree(this->buckets);

    // Update hash table structure
    this->buckets = (uint *)newBuckets;
    this->bucketCount = newCapacity;
}