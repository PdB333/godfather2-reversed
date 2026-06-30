// FUNC_NAME: AptValue::isUnique
// Function address: 0x005a3c40 (EA EARS engine, Apt library)
// Checks if the reference count (lower 15 bits of flags) is 1 and the weak flag (bit 15) is not set.
// If true, the object is uniquely owned (no shared references, not weak).

#include <cassert>

class AptValue {
public:
    // +0x00: flags (bitfield: lower 15 bits = reference count, bit 15 = weak flag)
    uint32_t flags;
    // Other members...
};

int AptValue::isUnique() {
    // Debug assertion: ensure this pointer is not null
    assert(this != nullptr && "AptValue::isUnique called with null this");

    // Check if reference count == 1 and weak flag is 0
    if ((this->flags & 0x7FFF) == 1 && ((this->flags >> 15) & 1) == 0) {
        return 1;   // Unique reference
    }
    return 0;       // Shared or weak reference
}