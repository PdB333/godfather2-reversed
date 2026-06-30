// FUNC_NAME: HandleManager::SetFlag
// Address: 0x00605f20
// Role: Sets or clears a flag for a given handle index, updates a 64-bit per-chunk bit array, 
//        maintains a minimum chunk index for quick scanning, and optionally writes a status byte 
//        to a handle data structure (size 0x38) or a direct pointer. Protected by a critical section.

#include <windows.h>
#include <cstdint>

// Global data (defined elsewhere)
extern CRITICAL_SECTION g_criticalSection;
extern uint32_t g_lowBits[];    // +0x8f28, array of low 32 bits per chunk (indexed by chunkIndex*2)
extern uint32_t g_highBits[];   // +0x8f2c, array of high 32 bits per chunk (indexed by chunkIndex*2)
extern int32_t g_minChunkIndex; // +0x9128, tracks chunk with smallest index having any set bits
extern uint8_t g_handleData[];  // +0x8f28? Actually +0x1a0f28, array of structures of size 0x38
extern uint8_t g_statusFallback; // decompiler artifact for address 0 write (likely a global fallback)

void HandleManager::SetFlag(uint32_t handleIndex, char* optionalStatusPtr, bool status)
{
    uint32_t chunkIndex = handleIndex >> 6;        // 64 bits per chunk
    uint32_t bitPos = handleIndex & 0x3F;           // bit within chunk
    uint64_t mask = 1ULL << bitPos;
    uint32_t maskLow = static_cast<uint32_t>(mask);
    uint32_t maskHigh = static_cast<uint32_t>(mask >> 32);

    EnterCriticalSection(&g_criticalSection);

    // Update the 64-bit bitmask for this chunk
    if (status) {
        g_lowBits[chunkIndex * 2] |= maskLow;
        g_highBits[chunkIndex * 2] |= maskHigh;
        // Track minimum chunk with set bits
        if (chunkIndex < g_minChunkIndex) {
            g_minChunkIndex = chunkIndex;
        }
    } else {
        g_lowBits[chunkIndex * 2] &= ~maskLow;
        g_highBits[chunkIndex * 2] &= ~maskHigh;
        // If this chunk was the minimum and is now empty, advance
        if (chunkIndex == g_minChunkIndex && g_lowBits[chunkIndex * 2] == 0 && g_highBits[chunkIndex * 2] == 0) {
            g_minChunkIndex++;
        }
    }

    LeaveCriticalSection(&g_criticalSection);

    // Store the status byte if requested
    if (optionalStatusPtr == nullptr) {
        if (handleIndex < 0x1000) {
            // Write to the first byte of the handle's data structure (size 0x38)
            g_handleData[handleIndex * 0x38] = static_cast<uint8_t>(status);
        } else {
            // Fallback for handles >= 0x1000 (likely to a global variable)
            g_statusFallback = static_cast<uint8_t>(status);
        }
    } else {
        *optionalStatusPtr = static_cast<char>(status);
    }
}