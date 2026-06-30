// FUNC_NAME: isIntelCPU
// Address: 0x0049bc90
// Role: CPU vendor detection - returns true if processor is genuine Intel

#include <cstdint>

// External function: returns pointer to CPUID info buffer for given leaf
extern "C" uint32_t* cpuid_basic_info(uint32_t leaf);

bool isIntelCPU()
{
    uint32_t* info = cpuid_basic_info(0);
    // CPUID leaf 0 returns vendor string in bytes 4-11 (ebx, edx, ecx)
    // These constants are ASCII little-endian: "GenuineIntel"
    if (info[1] == 0x756e6547 &&   // "Genu"
        info[2] == 0x49656e69 &&   // "ineI"
        info[3] == 0x6c65746e)     // "ntel"
    {
        return true;
    }
    return false;
}