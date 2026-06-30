// FUNC_NAME: StringTable::initHashTable

#include <cstdint>

// Forward declarations for engine memory functions
void* operator_new(uint32_t size);
void* operator_new_array(uint32_t size); // maybe allocateBuffer
void  operator_delete(void* ptr);
void  operator_delete_array(void* ptr); // freeBuffer

// Structure for each string entry in the hash table
struct StringEntry {
    int32_t  keyHash;        // +0x00
    int32_t  valuePtr;       // +0x04
    int32_t  nextEntry;      // +0x08 (linked list index)
    uint16_t dataSize;       // +0x0C (size of data[], not including header)
    uint16_t flags;          // +0x0E (allocation flags)
    char     data[];         // +0x10 (variable‑length string data)
};

// Global state (from DAT_01205a34, etc.)
extern StringEntry** g_stringHashTable;   // DAT_01205a34
extern uint32_t      g_hashTableSize;     // DAT_01205a40
extern void*         g_bufferPoolHead;    // DAT_01205a4c (linked list of buffers)
extern int32_t       g_bufferPoolCount;   // DAT_01205a50

// Caller: 0x0065a440
void StringTable::initHashTable()
{
    void* newPoolNode = operator_new(8);
    void* newBuffer = nullptr;

    if (newPoolNode != nullptr) {
        // +0x04: buffer size
        *(uint32_t*)((uint8_t*)newPoolNode + 4) = 0x3FF8;

        newBuffer = operator_new(12);
        if (newBuffer != nullptr) {
            // +0x04: handle to the actual raw data block
            *(void**)((uint8_t*)newBuffer + 4) = operator_new_array(0x3FF8);
        }
        *(void**)newPoolNode = newBuffer;      // link pool node to buffer object
        *(uint32_t*)newBuffer = 0;              // buffer usage count (or refcount)
        *(uint32_t*)((uint8_t*)newBuffer + 8) = 0; // some internal flag
    }

    // Re‑hash all entries from the old global hash table into the new pool
    uint32_t index = 1;
    int32_t tableBase = reinterpret_cast<int32_t>(g_stringHashTable);

    if (g_hashTableSize > 1) {
        do {
            StringEntry* entry = *reinterpret_cast<StringEntry**>(tableBase + index * 4);
            // Low bit of pointer used as flag (0 = valid entry)
            if (((reinterpret_cast<uintptr_t>(entry) & 1) == 0) && (entry != nullptr)) {
                // Allocate a new entry with room for the data plus a fixed overhead
                uint32_t newSize = entry->dataSize + 0x14;
                StringEntry* newEntry = reinterpret_cast<StringEntry*>(operator_new(newSize));
                if (newEntry != nullptr) {
                    // Copy fixed‑size fields (first 12 bytes)
                    newEntry->keyHash   = entry->keyHash;
                    newEntry->valuePtr  = entry->valuePtr;
                    newEntry->nextEntry = entry->nextEntry;
                    // Copy string length & flags (2+2 bytes at offsets +0x0C and +0x0E)
                    newEntry->dataSize  = entry->dataSize;
                    newEntry->flags     = entry->flags;
                    // Copy the string data (stored at offset +0x10 in both)
                    char* srcData = reinterpret_cast<char*>(entry) + 0x10;
                    char* dstData = reinterpret_cast<char*>(newEntry) + 0x10;
                    do {
                        *dstData = *srcData;
                        srcData++;
                        dstData++;
                    } while (*(srcData - 1) != '\0'); // copy including null
                    // Update hash table slot to point to the new entry
                    *reinterpret_cast<StringEntry**>(tableBase + index * 4) = newEntry;
                }
                tableBase = reinterpret_cast<int32_t>(g_stringHashTable); // reload after potential modification
            }
            index++;
        } while (index < g_hashTableSize);
    }

    // Free the old buffer pool (a singly linked list of pool nodes)
    void* oldPool = g_bufferPoolHead;
    if (oldPool != nullptr) {
        int32_t nextNode = *reinterpret_cast<int32_t*>(oldPool);
        while (nextNode != 0) {
            void* currentNode = *reinterpret_cast<void**>(oldPool);
            nextNode = *reinterpret_cast<int32_t*>(currentNode);
            if (currentNode != nullptr) {
                // Free the buffer handle (the actual data block)
                operator_delete_array(*reinterpret_cast<void**>((uint8_t*)currentNode + 4));
                // Free the pool node itself
                operator_delete(currentNode);
            }
            *reinterpret_cast<int32_t*>(oldPool) = nextNode;
        }
        operator_delete(oldPool);
    }

    // Replace the global pool with the newly allocated one
    g_bufferPoolHead = newPoolNode;
    g_bufferPoolCount = 0;
}