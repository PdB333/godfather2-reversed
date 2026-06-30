// FUNC_NAME: CachedValueOwner::getCachedValue
// Address: 0x43AAF0
// Role: Returns a cached value at offset 0x28. If the value is not yet computed (bit 0 of byte at +0x1c is clear), calls a computation function to initialize it.

int __thiscall CachedValueOwner::getCachedValue() {
    // Check the dirty flag: bit 0 of byte at +0x1c indicates whether the cached value is valid
    if (*(byte*)(this + 0x1c) & 1) {
        // Value already computed; return it directly
        return *(int*)(this + 0x28);   // +0x28: cached value (int, could be a float or pointer)
    }

    // Compute and cache the value, then return it
    return FUN_004dafd0(this + 0x28);  // Computation function takes address of cached value slot
}