// FUNC_NAME: readCpuVersionFields
// Function address: 0x0049c210
// Purpose: Extracts the family, model, stepping, and extended fields from CPUID leaf 1 (Version info).
// Parameters:
//   outFamily         - bits 11:8 (CPU family)
//   outExtendedFamily - bits 27:20 (extended family)
//   outModel          - bits 7:4 (CPU model)
//   outExtendedModel  - bits 19:16 (extended model)
//   outStepping       - bits 3:0 (stepping)
// Returns: true if CPUID is supported and info is available; false otherwise.
// Note: The original x86 code returned a packed 64-bit value; we simplify to bool.

#include <cstdint>

// Forward declarations of helper functions that execute CPUID instructions.
// These are assumed to be implemented separately (e.g., inline assembly or compiler intrinsics).
extern "C" uint32_t* getBasicCpuInfo();   // Returns pointer to results of CPUID leaf 0 (EAX, EBX, ECX, EDX)
extern "C" uint32_t* getVersionCpuInfo(); // Returns pointer to results of CPUID leaf 1 (EAX, EBX, ECX, EDX)

bool readCpuVersionFields(
    uint32_t* outFamily,
    uint32_t* outExtendedFamily,
    uint32_t* outModel,
    uint32_t* outExtendedModel,
    uint32_t* outStepping
) {
    uint32_t* basicInfo = getBasicCpuInfo();
    uint32_t maxLeaf = *basicInfo; // +0x00: EAX of leaf 0 (max input value)

    if (maxLeaf != 0) {
        uint32_t* versionInfo = getVersionCpuInfo();
        uint32_t eax = *versionInfo; // +0x00: EAX of leaf 1

        // Extract fields according to CPUID specification
        *outFamily         = (eax >> 8)  & 0x0F;   // bits 11:8
        *outExtendedFamily = (eax >> 20) & 0xFF;   // bits 27:20
        *outModel          = (eax >> 4)  & 0x0F;   // bits 7:4
        *outExtendedModel  = (eax >> 16) & 0x0F;   // bits 19:16
        *outStepping       =  eax        & 0x0F;   // bits 3:0

        return true;
    }

    // CPUID not supported; basicInfo+2 might contain additional info (e.g., vendor string)
    // In the original code, the return value packed (basicInfo[2] << 32) | 0;
    return false; // simplified
}