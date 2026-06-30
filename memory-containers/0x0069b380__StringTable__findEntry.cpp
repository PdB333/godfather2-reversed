// FUNC_NAME: StringTable::findEntry

// Function address: 0x0069b380
// Role: Looks up an entry in a string table by hash, returns pointer to entry data (at offset +0x20 from node).
// If not found, allocates a new node (via FUN_0069a730) and returns it.
// Uses RAII-style cleanup for temporary allocations.

int __thiscall StringTable::findEntry(uint hash)
{
    uint originalHash;
    int cmpResult;
    void* pAlloc1 = nullptr;   // local_30
    void (*dtor1)(void*) = nullptr; // local_24
    void* pAlloc2 = nullptr;   // local_20
    void (*dtor2)(void*) = nullptr; // local_14
    void* pAlloc3 = nullptr;   // local_10
    void (*dtor3)(void*) = nullptr; // local_4

    // Compute a hash from the input key (likely a string pointer)
    // FUN_00698c60 takes a pointer to store the result and the key pointer.
    FUN_00698c60(&hash, hash);

    originalHash = hash;

    // Check if the hash matches a sentinel value (this + 4).
    // If not, attempt a fast lookup.
    if (hash != this + 4U)
    {
        cmpResult = FUN_004d4b20(hash + 0x10); // Compare key at node+0x10
        if (cmpResult >= 0)
        {
            return hash + 0x20; // Return pointer to entry data
        }
    }

    // Fast lookup failed; fallback to a slower path (possibly allocation).
    // Initialize cleanup structures.
    pAlloc1 = nullptr;
    dtor1 = nullptr;

    // Clean up the current hash pointer (free temporary?).
    FUN_004d3b50(hash);
    FUN_004d3b50(&pAlloc1); // Note: passing address of pointer, likely a scope guard cleanup.

    // Mask hash to 256-byte alignment (clear low 8 bits).
    hash = hash & 0xFFFFFF00U;

    // Call the allocation/lookup function.
    // Parameters: pointer to hash (modified), originalHash, output pAlloc2, masked hash.
    FUN_0069a730(&hash, originalHash, &pAlloc2, hash);

    // Cleanup temporary allocations using their destructors.
    if (pAlloc3 != nullptr)
    {
        dtor3(pAlloc3);
    }
    if (pAlloc2 != nullptr)
    {
        dtor2(pAlloc2);
    }
    if (pAlloc1 != nullptr)
    {
        dtor1(pAlloc1);
    }

    // Return pointer to entry data (offset +0x20 from the processed hash).
    return hash + 0x20;
}