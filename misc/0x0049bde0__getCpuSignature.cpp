// FUNC_NAME: getCpuSignature
// Function at 0x0049bde0: Generates a 64-bit CPU signature based on CPUID leaf 1 feature flags.
// Uses cpuid_basic_info (leaf 0) to check max leaf, then cpuid_Version_info (leaf 1) to get feature bits.
// Returns a composite value: if SSE3 bit 28 is set, returns special value; otherwise returns (ECX<<32)|1.

#include <cstdint>

// Assume these helper functions exist elsewhere.
// They likely execute CPUID instructions and return pointers to static buffers.
struct CpuidBasicInfo {
    uint32_t eax; // max leaf
    uint32_t ebx; // vendor string part
    uint32_t ecx; // vendor string part
    uint32_t edx; // vendor string part
};
const CpuidBasicInfo* cpuid_basic_info(uint32_t leaf = 0);

struct CpuidVersionInfo {
    uint32_t eax; // stepping, model, family
    uint32_t ebx; // brand index, clflush, threads
    uint32_t ecx; // feature flags
    uint32_t edx; // feature flags
};
const CpuidVersionInfo* cpuid_Version_info(uint32_t leaf = 1);

uint64_t getCpuSignature()
{
    uint32_t ecx = 0;       // Will hold ECX from leaf 1
    uint32_t localFlags = 0; // Used for bit test

    // Get basic info (leaf 0) to check CPUID support
    const CpuidBasicInfo* basic = cpuid_basic_info(0);
    ecx = basic->ecx; // Actually this is vendor string ECX, not used later if max leaf > 0

    if (basic->eax != 0) {
        // CPUID leaf 1 is supported, get version info
        const CpuidVersionInfo* ver = cpuid_Version_info(1);
        ecx = ver->ecx;   // Feature flags from ECX
        localFlags = ecx; // Save for bit test
    }

    // Check if bit 28 (AVX or SSE4.1 depending on CPU) is set
    if ((localFlags & 0x10000000) != 0) {
        // Return a composite of ECX and upper word of EBX, then keep low byte of EBX
        // This likely encodes processor stepping/features
        const CpuidVersionInfo* ver = cpuid_Version_info(1);
        // ver->ebx >> 16 gives brand index and logical processor count in low 16 bits
        // ver->ecx is the feature flags
        // Combine: high 32 bits = ECX, low 32 bits = (EBX >> 16), then mask to keep low byte of shifted EBX
        return (static_cast<uint64_t>(ver->ecx) << 32) | 
               (static_cast<uint64_t>(ver->ebx >> 16) & 0xFFFFFFFF) &
               0xffffffff000000ffULL; // Mask: keep high 32 bits (ECX) and low byte of the shifted EBX
    }

    // Default: return (ECX << 32) | 1
    return (static_cast<uint64_t>(ecx) << 32) | 1;
}