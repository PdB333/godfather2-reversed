// FUNC_NAME: compareObjectHeaders
// Function at 0x00622a60: Compares two objects' headers (signature and version).
// Returns packed value: upper 24 bits = high 24 bits of obj1's version, low byte = 1 if versions match else 0.
// Triggers assertion failure if signatures are null or mismatch.

#include <cstdint>

// Forward declaration of assertion failure handler at 0x00b97aea
void __assert();

// __fastcall convention: parameters passed in registers (EDI = obj1, ESI = obj2)
uint32_t __fastcall compareObjectHeaders(int32_t* obj1, int32_t* obj2)
{
    // Check first int (likely a signature/type ID)
    if (obj1[0] == 0 || obj1[0] != obj2[0]) {
        __assert();  // Signature mismatch or null -> assertion
    }

    // Combine high 24 bits of obj1's second int with equality flag of both second ints
    // obj1[1] is likely a version or size field
    uint32_t highPart = static_cast<uint32_t>(obj1[1]) & 0xFFFFFF00; // Keep high 24 bits
    uint32_t lowFlag = (obj1[1] == obj2[1]) ? 1 : 0;                // Low byte = comparison result
    return highPart | lowFlag;
}