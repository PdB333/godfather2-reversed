// FUNC_NAME: HashTable::insert
void __thiscall HashTable::insert(HashTable* this, uint* key, uint* value, uint hashIndex)
{
    // Check if table is initialized and if load factor exceeds threshold
    // this->flags[0x14] is a byte indicating table is active
    // this->bucketCount is at +0x04, this->threshold at +0x0C
    if (((char)this->flags[0x14] != '\0') && ((uint)(this->bucketCount * 2) <= (uint)this->threshold)) {
        // Resize/rehash the table
        resize();
        // Recalculate hash index after resize
        hashIndex = *key % (uint)this->bucketCount;
    }

    // Allocate a new node (3 uint32s: key, value, next)
    uint* newNode = (uint*)allocateNode();
    newNode[1] = *value;   // +0x04: value
    newNode[0] = *key;     // +0x00: key
    // Link to existing bucket head
    newNode[2] = *(uint*)(this->buckets + hashIndex * 4);  // +0x08: next pointer
    // Update bucket head to new node
    *(uint**)(this->buckets + hashIndex * 4) = newNode;
}