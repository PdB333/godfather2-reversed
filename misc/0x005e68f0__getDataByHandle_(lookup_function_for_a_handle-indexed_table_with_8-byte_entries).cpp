// FUNC_NAME: getDataByHandle (lookup function for a handle-indexed table with 8-byte entries)

// Global pointer to base structure: array of 0x30-sized elements starts at offset 0x10
extern void* g_TableBase; // DAT_012234bc

/**
 * Given a 32-bit handle, returns a pointer to an 8-byte data entry.
 * The lower 16 bits of the handle are used as an index (max 0x1FF).
 * The table element at index must contain the full handle for validation.
 * Additional checks on secondary pointers and a byte flag at +0x66 ensure validity.
 * Returns pointer to entry at *(secondary+0x50) + index*8.
 */
int* __cdecl getDataByHandle(int handle)
{
    uint32_t idx = (uint32_t)handle & 0xFFFF;
    if (idx >= 0x200)
        return 0;

    // Element at base + 0x10 + idx*0x30
    uint8_t* elem = (uint8_t*)g_TableBase + 0x10 + idx * 0x30;
    if (!elem)
        return 0;

    // Validate stored handle at +0x2c
    if (*(uint32_t*)(elem + 0x2c) != (uint32_t)handle)
        return 0;

    // Secondary pointer at +0x10
    void* secondary = *(void**)(elem + 0x10);
    if (!secondary)
        return 0;

    // Check something at secondary+8 (non-zero)
    if (!*(int*)((uint8_t*)secondary + 8))
        return 0;

    // Nested pointer (dereference secondary)
    void* nested = *(void**)secondary;
    if (!nested)
        return 0;

    // Byte flag at elem+0x66 must not be 0xFF
    if (*(uint8_t*)(elem + 0x66) == 0xFF)
        return 0;

    // Return pointer to array at secondary+0x50, indexed by idx*8
    return (int*)(*(int*)((uint8_t*)secondary + 0x50) + idx * 8);
}