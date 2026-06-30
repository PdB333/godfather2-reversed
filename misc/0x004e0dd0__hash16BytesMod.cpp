// FUNC_NAME: hash16BytesMod
// Address: 0x004e0dd0
// Hashes the first 16 bytes of a buffer using a multiplicative hash, then mods by a table size.
// Used for indexing into a hash table with 16-byte keys (e.g., GUIDs or Object IDs).

uint __thiscall hash16BytesMod(const byte* key, const HashTable* table) {
    uint hash = 0;
    if (key != nullptr) {
        const byte* end = key + 16; // hash the first 16 bytes
        while (key < end) {
            hash = hash * 0x1003f + static_cast<uint>(*key);
            ++key;
        }
    }
    // table->size is at offset +0x4 of the HashTable structure
    return hash % table->size;
}