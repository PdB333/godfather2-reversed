// FUN_00439c10: SortedRingBuffer::findInsertionIndex
// Sorts an array of floats stored in a global ring buffer (DAT_010c2680)
// Param_1 (ECX) is unused; Param_2 (EDX) points to a descriptor with:
//   +0x04: startIndex - starting index for search (current count + bias)
//   +0x08: capacity  - maximum element count
//   +0x0C: value     - float to insert (compared against existing values)
// Global: DAT_012054b4 - current write head index (incremented during search)
// Global: DAT_010c2678 - mask for ring buffer indexing (power of two - 1)
// Returns the index (0..n) where 'value' should be inserted to maintain sorted order.

#include <cstdint>

struct SortedRingBufferDescriptor {
    int     field_0;          // +0x00: unknown/unused
    uint32_t startIndex;      // +0x04: base index (often current element count + 2)
    uint32_t capacity;        // +0x08: max elements in ring buffer
    float    insertValue;     // +0x0C: value to insert
};

// Global state
extern uint32_t g_writeHead;         // DAT_012054b4
extern uint32_t g_ringMask;          // DAT_010c2678  (power-of-two mask)
extern float    g_ringBuffer[];      // DAT_010c2680

uint32_t __fastcall findInsertionIndex(int ecx_unused, SortedRingBufferDescriptor* desc) {
    uint32_t searchCount = desc->startIndex + 2;
    if (desc->capacity < searchCount) {
        searchCount = desc->capacity;
    }

    uint32_t idx = 0;
    uint32_t currentHead = g_writeHead;

    // Loop unrolled: process 4 elements at a time
    if (searchCount > 3) {
        do {
            if (desc->insertValue <= g_ringBuffer[g_ringMask & currentHead]) {
                g_writeHead = currentHead + 1;
                return idx;
            }
            g_writeHead = currentHead + 2;
            if (desc->insertValue <= g_ringBuffer[g_ringMask & (currentHead + 1)]) {
                return idx + 1;
            }
            g_writeHead = currentHead + 3;
            if (desc->insertValue <= g_ringBuffer[g_ringMask & (currentHead + 2)]) {
                return idx + 2;
            }
            currentHead += 4;
            if (desc->insertValue <= g_ringBuffer[g_ringMask & currentHead]) {
                g_writeHead = currentHead;
                return idx + 3;
            }
            idx += 4;
            g_writeHead = currentHead;
        } while (idx < searchCount - 3);
    }

    // Remaining 0..3 elements
    if (idx < searchCount) {
        while (true) {
            uint32_t masked = g_ringMask & g_writeHead;
            g_writeHead = g_writeHead + 1;
            if (desc->insertValue <= g_ringBuffer[masked]) {
                break;
            }
            idx++;
            if (searchCount <= idx) {
                return idx;
            }
        }
    }

    return idx;
}