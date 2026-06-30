// FUN_00421550: NameEntry::addToGlobalTable
void NameEntry::addToGlobalTable()
{
    HashTable* table = reinterpret_cast<HashTable*>(DAT_012053ac);
    
    // Check if entry is not already in table (bit0 clear) and marked for insertion (bit1 set)
    if ((flags & 0x0001) == 0 && (flags & 0x0002) != 0)
    {
        int numBuckets = table->numBuckets;
        unsigned int hashIndex = hashString(keyString) % numBuckets;
        
        // If resize enabled and load factor >= 2 (count >= 2 * numBuckets), grow table
        if (table->resizeEnabled && numBuckets * 2 <= table->count)
        {
            growHashTable(table);
            hashIndex = hashString(keyString) % table->numBuckets;
        }
        
        // Insert entry at head of bucket chain
        hashNext = table->buckets[hashIndex];
        table->buckets[hashIndex] = this;
        table->count++;
        
        // Mark entry as present in table
        flags |= 0x0001;
    }
    
    // Set global dirty flag
    *reinterpret_cast<byte*>(DAT_0122337c + 0x8a) = 1;
    
    // Finalize insertion (e.g., notify observers)
    finalizeInsertion();
    
    // Increment reference count
    refCount++;
}