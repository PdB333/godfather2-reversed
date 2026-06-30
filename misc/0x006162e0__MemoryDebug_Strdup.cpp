// FUNC_NAME: MemoryDebug_Strdup
// Function at 0x006162e0: Tracked string duplication with memory leak detection.
// Uses a custom allocator (pointed by g_AllocFunc) and records the caller's return address
// into a hash table (256 buckets) keyed by the return address's low byte.
// The allocated block contains metadata (12 bytes) followed by the duplicated string.
// Global structures:
//   g_MemoryTracker (DAT_01205960) -> points to struct with hash table at offset 0 and allocation counter at +0x400
//   g_AllocFunc (DAT_01205964) -> function pointer for custom allocation

#include <cstdint>
#include <cstring>

// Assume these globals exist (declared in external headers)
extern void* g_MemoryTracker;
extern void* (*g_AllocFunc)(size_t size, void* outActualPtr);

// Allocator function type (simplified, actual signature may differ)
typedef void* (*AllocFunc_t)(size_t size, void* outPtr);

// Return address intrinsic for MSVC (used in original code)
#define RETURN_ADDRESS reinterpret_cast<uintptr_t>(_ReturnAddress())

uint32_t* TrackedStrdup(const char* source)
{
    // Calculate length of source string (excluding null)
    const char* p = source;
    while (*p) ++p;
    size_t length = p - source;

    // Dummy out parameters (the decompiled code uses local_c, local_8, local_4)
    uint32_t dummyC = 0;
    uint32_t dummy8 = 0;
    void* dummy4 = nullptr;

    // Allocate memory: header size (13 bytes = 0xD) + string length + null terminator
    uint32_t* block = (uint32_t*)((AllocFunc_t)(*g_AllocFunc))(length + 0xD, &dummyC);
    if (!block)
        return nullptr;

    uintptr_t retAddr = RETURN_ADDRESS;

    // Store metadata in the block:
    // offset 0: return address
    // offset 4: next pointer in hash bucket (initialized to 0, then overwritten)
    // offset 8: 2-byte field (maybe flags or something)
    block[0] = retAddr;
    block[1] = 0;
    *(uint16_t*)(block + 2) = 0;

    // Hash table in g_MemoryTracker: 256 entries (uint32), each a head pointer to a linked list.
    uint8_t bucketIndex = retAddr & 0xFF;
    uint32_t* hashTable = (uint32_t*)g_MemoryTracker;
    block[1] = hashTable[bucketIndex];               // link to current bucket head
    hashTable[bucketIndex] = (uint32_t)block;        // new head is this block

    // Increment allocation counter at offset 0x400 from g_MemoryTracker
    *(int*)((uint8_t*)g_MemoryTracker + 0x400) += 1;

    // Copy the source string into the block after the 12-byte header (3 uint32s)
    char* dest = (char*)(block + 3);
    memcpy(dest, source, length);
    dest[length] = '\0';

    // Return pointer to the block (caller may need to offset to get string data)
    return block;
}