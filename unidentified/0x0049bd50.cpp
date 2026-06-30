// FUN_0049bd50: getCPUCacheLineSizeAndInfo
// Returns a 64-bit value:
//   Low 32 bits: cache line size in bytes (from CPUID leaf 4 EAX bits 31:26 +1, or 0 if unavailable)
//   High 32 bits: CPU vendor ECX (leaf 0) or leaf 4 ECX (if leaf 4 available)
#include <cstdint>

extern "C" void* cpuid_basic_info(uint32_t leaf);          // returns pointer to 4-element uint32 array (EAX, EBX, ECX, EDX)
extern "C" void* cpuid_Deterministic_Cache_Parameters_info(uint32_t leaf); // same for leaf 4

uint64_t getCPUCacheLineSizeAndInfo(void)
{
    uint32_t cacheLineSize = 0;
    uint32_t highPart;

    uint32_t* leaf0 = static_cast<uint32_t*>(cpuid_basic_info(0));
    uint32_t maxLeaf = leaf0[0];  // +0x00: EAX = max standard leaf
    highPart = leaf0[2];          // +0x08: ECX (part of vendor string)

    if (maxLeaf != 0) {
        // Re-read leaf0 (redundant but preserved from original)
        leaf0 = static_cast<uint32_t*>(cpuid_basic_info(0));
        maxLeaf = leaf0[0];
        highPart = leaf0[2];

        if (maxLeaf > 3) {
            uint32_t* leaf4 = static_cast<uint32_t*>(cpuid_Deterministic_Cache_Parameters_info(4));
            cacheLineSize = leaf4[0]; // +0x00: EAX
            highPart = leaf4[2];      // +0x08: ECX (e.g., number of sets / associativity)
        }
    }

    // Extract cache line size from bits 31:26 of EAX (+1 to convert to bytes)
    uint32_t lineSize = ((cacheLineSize >> 26) & 0x3F) + 1;
    return (static_cast<uint64_t>(highPart) << 32) | lineSize;
}