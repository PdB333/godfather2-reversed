// FUNC_NAME: HashTable::findNode
void __thiscall HashTable::findNode(void *this, undefined4 *outEntryAndBucket, uint *key)
{
    uint hashIndex = *key % *(uint *)((int)this + 8);                         // +0x8 = m_bucketCount
    int bucketArray = *(int *)((int)this + 4);                                // +0x4 = m_buckets
    undefined4 *bucket = (undefined4 *)(bucketArray + hashIndex * 4);
    
    for (uint *entry = *(uint **)(bucketArray + hashIndex * 4); 
         entry != (uint *)0x0; 
         entry = (uint *)entry[2])                                            // [2] = next pointer
    {
        if (*key == *entry)                                                   // match found
            goto found;
    }
    
    // Not found: return the sentinel bucket (at index m_bucketCount)
    bucket = (undefined4 *)(bucketArray + *(uint *)((int)this + 8) * 4);
    uint *entry = (uint *)*bucket;
    
found:
    outEntryAndBucket[0] = (undefined4)entry;                                 // the entry node (or sentinel head)
    outEntryAndBucket[1] = (undefined4)bucket;                                // the bucket containing the entry
    return;
}