// FUNC_NAME: lookupGameTypeHandler
// Function at 0x0066bad0: Maps a game type ID to a handler function pointer, using a sorted lookup table.
// param_1 is unused (presumably padding or legacy this pointer), param_2 is the type ID.
// Returns a function pointer from one of two arrays based on exact match or fallback range.

#include <cstdint>

// Assumed types:
// The arrays are global and likely defined elsewhere.
// Using a struct to represent the key-value pair for clarity.
struct KeyValuePair {
    int32_t key;   // sorted ascending
    void* value;   // pointer (function or data)
};

// These arrays are defined in the .data section at the given addresses.
extern KeyValuePair g_typeMap[0x20]; // starting at 0x00e274c0? Actually the original code indexes as (&DAT_00e274c0)[iVar2*2] so each pair is two dwords:
// key at [iVar2*2], value at [iVar2*2 + 1]. So we can treat it as array of struct.
// Similarly, PTR_FUN_00e274bc is an array of function pointers (void*).
extern void* g_fallbackHandlers[0x20]; // starting at 0x00e274bc

// The function uses __fastcall, but since param_1 is unused, it's effectively a static function.
// However, to match the original calling convention, we'll declare it as such.
void* __fastcall lookupGameTypeHandler(int32_t unused, int32_t typeId) {
    int32_t index = 0;
    const int32_t maxIndex = 0x1F; // 32 entries

    while (true) {
        int32_t key = g_typeMap[index].key; // equivalent to (&DAT_00e274c0)[index*2]
        if (key == typeId) {
            // Exact match found, return the associated value.
            return g_typeMap[index].value; // (&DAT_00e274c4)[index*2]
        }
        // If key != typeId and typeId <= key, break out of loop.
        if (typeId <= key) {
            break;
        }
        ++index;
        if (index > maxIndex) {
            // Exceeded table size, return default (1).
            return reinterpret_cast<void*>(1);
        }
    }

    // No exact match found; fallback logic.
    if (index == 0) {
        // typeId is less than the first key, return 0x1c (28 decimal) as a sentinel.
        return reinterpret_cast<void*>(0x1c);
    }
    // Otherwise, return the function pointer from the fallback table at position index*2.
    // Note: The original code uses (&PTR_FUN_00e274bc)[index*2], meaning the fallback table is indexed by 2*index?
    // Actually in the decompiled code: return (&PTR_FUN_00e274bc)[iVar2 * 2];
    // So it's an array of pointers but accessed with a step of 2? That seems odd.
    // It might be that PTR_FUN_00e274bc is an array of 2-byte elements? But typically pointers are 4 bytes.
    // Possibly it's an array of unknown size and the multiplication by 2 is due to the original being a char* or short*.
    // Given the pattern, it's likely that the fallback table is also a key-value pair but we return the value part.
    // However, the original code uses the same index*2. Let's assume g_fallbackHandlers is an array of void* and the index is directly used (i.e., index*2 is a mistake in decompilation?).
    // Actually, looking at the first array: (&DAT_00e274c0)[iVar2*2] suggests two dwords per entry, so addressing is iVar2*2.
    // For PTR_FUN_00e274bc, it's also indexed by iVar2*2, so it might be a separate array of same size.
    // But if it's a pointer array, each element is 4 bytes, so index*2 would be index*8? That doesn't fit.
    // More likely, the decompiler inferred multiplication due to pointer arithmetic on an array of unknown base type.
    // For simplicity, we'll assume the fallback table is a simple array of void* and the index is direct.
    // We'll trust the decompiler's intent: return g_fallbackHandlers[index * 2]? That seems wrong.
    // Given the ambiguity, I'll implement as: return g_fallbackHandlers[index]; but note the original code used [index*2].
    // To be faithful, I'll use [index*2] as written.
    return g_fallbackHandlers[index * 2];
}