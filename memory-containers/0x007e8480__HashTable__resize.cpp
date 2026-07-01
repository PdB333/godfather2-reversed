// FUNC_NAME: HashTable::resize
void __thiscall HashTable::resize(uint *this)
{
    uint oldSize = this[1]; // +0x04: number of buckets
    uint newSize = oldSize * 2 + 1;
    // Allocate new bucket array
    uint **newBuckets = (uint **)FUN_009c8e80(newSize * 4);
    _memset(newBuckets, 0, newSize * 4);
    
    uint bucketIndex = 0;
    if (oldSize != 0) {
        do {
            uint *node = *(uint **)(*this + bucketIndex * 4); // +0x00: bucket array pointer
            while (node != nullptr) {
                uint *nextNode = (uint *)node[2]; // +0x08: next pointer
                uint hash = node[0] % newSize; // +0x00: key
                node[2] = (uint)newBuckets[hash];
                newBuckets[hash] = node;
                node = nextNode;
            }
            bucketIndex++;
        } while (bucketIndex < oldSize);
    }
    
    FUN_009c8f10(*this); // free old bucket array
    *this = (uint)newBuckets;
    this[1] = newSize;
}