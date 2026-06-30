// FUNC_NAME: HashTable::findOrInsert

// Hash table with open addressing, using a buffer header structure.
// Struct HashTable: 
//   +0x00: uint32_t key          (the key to look up or insert)
//   +0x04: uint32_t _pad
//   +0x08: BufferHeader* buffer  (pointer to dynamic buffer)
// Struct BufferHeader:
//   +0x00: uint32_t* data        (array of entries, each entry is a key+value? Or just flags?)
//   +0x04: uint32_t capacity     (max number of slots)

uint32_t HashTable::findOrInsert(uint32_t key)
{
    uint32_t hash = this->hashFunction(key);  // FUN_00641940, returns hash (likely 1-based)
    
    if (hash == 0) {
        return 0;
    }

    BufferHeader* buffer = reinterpret_cast<BufferHeader*>(this->bufferPtr);  // param_1[2]
    if (buffer->capacity < hash) {
        uint32_t newSize = (hash < 0x20) ? 0x20 : hash;
        uint32_t* newData = reinterpret_cast<uint32_t*>(this->reallocateBuffer(buffer->capacity, newSize));  // FUN_006279a0
        buffer->data = newData;
        buffer->capacity = newSize;
    }

    uint32_t* data = buffer->data;
    
    // Check if slot at index 'hash' is occupied
    if (this->findEntry(data, hash)) {  // FUN_006385a0
        return this->getEntryValue();   // FUN_00641890
    } else {
        // Insert key into slot (hash-1) – note the off-by-one, likely to convert 1-based hash to 0-based index
        return this->insertEntry(key, data, hash - 1);  // FUN_00638920
    }
}