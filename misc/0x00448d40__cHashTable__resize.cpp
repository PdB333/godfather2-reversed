// FUNC_NAME: cHashTable::resize
void __thiscall cHashTable::resize(int* this)
{
    int oldSize = this[1]; // +0x04: number of buckets
    int newSize = oldSize * 2 + 1; // new bucket count (prime-like)

    // Allocate new bucket array (size = newSize * 4)
    uint* newBuckets = (uint*)AllocateMemory(newSize * sizeof(uint*));
    memset(newBuckets, 0, newSize * sizeof(uint*));

    // Rehash existing nodes into new buckets
    if (oldSize > 0)
    {
        for (int i = 0; i < oldSize; i++)
        {
            uint* node = *(uint**)(this[0] + i * 4); // +0x00: bucket array
            while (node != nullptr)
            {
                uint* next = (uint*)node[6]; // node+0x18: next pointer
                uint hash = node[0] % newSize; // node+0x00: key/hash value
                node[6] = *(uint*)((int)newBuckets + hash * 4);
                *(uint**)((int)newBuckets + hash * 4) = node;
                node = next;
            }
        }
    }

    // Free old bucket array
    FreeMemory((void*)this[0]);

    // Update table
    this[0] = (int)newBuckets; // +0x00: pointer to new bucket array
    this[1] = newSize;         // +0x04: new bucket count
}