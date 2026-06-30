// FUNC_NAME: HashTable::insertItem

class HashTable {
public:
    void** buckets;       // +0x00: array of bucket ptrs
    int32_t size;         // +0x04: number of buckets
    int32_t count;        // +0x08: number of inserted items
    bool autoResize;      // +0x0C: flag whether to auto-resize when load > 2.0
    // char padding potentially following

    void insertItem(void* item);
};

void HashTable::insertItem(void* item) {
    // Compute hash (seems to use a non‑key based random value)
    uint32_t seed = FUN_0043ab10();
    uint32_t hash = FUN_004209c0(seed);
    uint32_t slot = hash % this->size;

    // If auto‑resizing is enabled and load factor exceeds threshold (size*2 <= count)
    if (this->autoResize && (this->size * 2 <= (uint32_t)this->count)) {
        FUN_00448ea0(this);             // resize or rehash
        seed = FUN_0043ab10();
        hash = FUN_004209c0(seed);
        slot = hash % this->size;       // recompute bucket after resize
    }

    // Classic hash chain insertion: store old head at item+0x18, then link item as new head
    void* oldHead = this->buckets[slot];
    *(void**)((uint8_t*)item + 0x18) = oldHead;
    this->buckets[slot] = item;

    this->count++;
}