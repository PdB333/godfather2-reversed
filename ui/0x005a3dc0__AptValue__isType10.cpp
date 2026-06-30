// FUNC_NAME: AptValue::isType10
// Function address: 0x005a3dc0
// Checks if the AptValue's internal type ID equals 10.

#include <cstdint>

// Forward declaration for assertion macro (EASTL style)
#define EA_DEBUG_ASSERT(cond, msg) /* engine debug assertion */

class AptValue {
public:
    // Returns true if the value's type tag is 10.
    bool isType10() const {
        // Null this check for debug builds
        if (this == nullptr) {
            // Debug assertion from apt source
            EA_DEBUG_ASSERT(false, "c:\\packages001_pc\\apt\\0.19.optimized\\source\\apt\\_AptValue.h:415");
            return false; // fallthrough
        }

        // Check internal type field (likely a 16-bit tag at offset 0)
        uint16_t typeTag = *(const uint16_t*)this; // *unaff_EDI
        // The value 10 stored in lower 15 bits, bit 15 must be 0
        return ((typeTag & 0x7FFF) == 10) && ((typeTag >> 15) == 0);
    }
};