// FUNC_NAME: HashTable::find
// Address: 0x004508e0
// Role: Lookup a value in a custom quad-key hash table with chaining.
// Structure of this:
//   +0x00: vtable? (not used here)
//   +0x04: uint32_t tableSize (modulo divisor)
//   +0x08: int** buckets (array of bucket head pointers, each entry is a pointer to first node)
// Node layout (linked list):
//   +0x00: key0 (int)
//   +0x04: key1 (int)
//   +0x08: key2 (int)
//   +0x0C: key3 (int)
//   +0x10: value (int)
//   +0x14: next (pointer to next node, null if end)
int __thiscall HashTable::find(int this, int key0, int key1, int key2, int key3)
{
    // Compute bucket index: (key0 + key3) % tableSize
    uint32_t tableSize = *(uint32_t*)(this + 4);
    int** buckets = *(int***)(this + 8);
    int* node = buckets[(uint32_t)(key0 + key3) % tableSize];

    while (node != nullptr)
    {
        // Check all four key components
        if (node[0] == key0 && node[1] == key1 && node[2] == key2 && node[3] == key3)
        {
            return node[4]; // value
        }
        node = (int*)node[5]; // next pointer
    }
    return 0;
}