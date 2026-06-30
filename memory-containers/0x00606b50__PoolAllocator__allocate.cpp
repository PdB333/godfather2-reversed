// FUNC_NAME: PoolAllocator::allocate
// Function at 0x00606b50: Allocates a slot from a fixed-size pool (4096 entries of 0x38 bytes each). 
// Uses a per-group 64-bit bitmap to track free entries. Thread-safe via critical section.
// If requestedIndex == 0xFFFFFFFF, performs a linear search starting from hintIndex.
// Returns allocated index on success, 0xFFFFFFFF on failure.

#include <windows.h>

// Global pool data
static LPCRITICAL_SECTION s_criticalSection = reinterpret_cast<LPCRITICAL_SECTION>(0x011d917c);
static uint32_t s_groupBitmapLow[64];    // low dword of per-group bitmap, base at 0x011d8f28
static uint32_t s_groupBitmapHigh[64];   // high dword, base at 0x011d8f2c
static uint32_t s_hintIndex;             // next group hint, at 0x011d9128
static char s_pool[4096 * 0x38];          // pool of 4096 entries, each 0x38 bytes, base at 0x011a0f28

// Entry layout:
// offset 0x00: char used (0 = free, 1 = allocated)
// offset 0x10: uint32 cleared on allocation (likely some data field)

uint poolAllocate(uint requestedIndex)
{
    uint index = requestedIndex;
    
    // If no specific index requested, find a free slot
    if (index == 0xFFFFFFFF)
    {
        EnterCriticalSection(s_criticalSection);
        LeaveCriticalSection(s_criticalSection);
        
        // Search for a group with at least one free entry
        uint group = s_hintIndex;
        while (group < 64 && 
               (s_groupBitmapLow[group] == 0 && s_groupBitmapHigh[group] == 0))
        {
            group++;
        }
        
        index = group * 64; // start of group
        if (index < 0x1000)
        {
            char* entry = s_pool + group * 0xE00; // group start
            bool isWithinLimit = (index < 0x1000);
            do
            {
                if (*entry == '\0')
                    break;
                index++;
                entry += 0x38;
                isWithinLimit = (index < 0x1000);
            }
            while (isWithinLimit);
        }
        
        if (index >= 0x1000)
        {
            return 0xFFFFFFFF;
        }
    }
    
    // Attempt to allocate the specific slot
    if (index < 0x1000)
    {
        char* entry = s_pool + index * 0x38;
        if (entry != nullptr && *entry == '\0')
        {
            uint group = index >> 6;
            EnterCriticalSection(s_criticalSection);
            LeaveCriticalSection(s_criticalSection);
            
            // Compute 64-bit mask for the bit to clear (bit position = index & 0x3F)
            uint64_t bitMask = __allshl(1ULL, index & 0x3F); // 64-bit shift
            uint32_t lowMask = static_cast<uint32_t>(bitMask);
            uint32_t highMask = static_cast<uint32_t>(bitMask >> 32);
            
            s_groupBitmapLow[group] &= ~lowMask;
            s_groupBitmapHigh[group] &= ~highMask;
            
            // Update hint if this group becomes empty
            if (group == s_hintIndex && 
                s_groupBitmapLow[group] == 0 && s_groupBitmapHigh[group] == 0)
            {
                s_hintIndex = group + 1;
            }
            
            // Mark entry as used
            *entry = '\x01';
            *(uint32_t*)(entry + 0x10) = 0;
            
            return index;
        }
    }
    
    return 0xFFFFFFFF;
}