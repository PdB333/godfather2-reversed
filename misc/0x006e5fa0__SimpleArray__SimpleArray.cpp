// FUNC_NAME: SimpleArray::SimpleArray
// Function address: 0x006e5fa0
// Purpose: Constructor for a simple dynamic array of 4-byte elements.
// Allocates a buffer of (param_2 * 4) bytes and initializes it to zero.
// Stores a byte flag at offset +0x0C.
// TODO: Determine actual class name from game symbols.

#include <cstring> // for memset

// Forward declaration of custom allocator function
void* __cdecl operator_new(size_t size); // actual: FUN_009c8e80

class SimpleArray {
public:
    // +0x00: pointer to allocated buffer
    void* m_pData;
    // +0x04: count (number of elements)
    uint32_t m_count;
    // +0x08: (unused?) set to 0
    uint32_t m_unknown0;
    // +0x0C: byte flag (e.g., owns memory, sorted flag, etc.)
    uint8_t m_flags;

    // Constructor: initializes array with given count and flag
    // param_2 = count, param_3 = flags
    SimpleArray(uint32_t count, uint8_t flags) {
        m_flags = flags;                // +0x0C
        m_count = count;                // +0x04
        m_pData = nullptr;              // +0x00
        m_unknown0 = 0;                 // +0x08

        // Calculate allocation size: count * 4 (4 bytes per element)
        // Overflow protection: if multiplication overflows 32-bit, size becomes 0xFFFFFFFF
        uint64_t size64 = (uint64_t)count * 4;
        uint32_t sizeLow = (uint32_t)size64;
        uint32_t sizeHigh = (uint32_t)(size64 >> 32);
        uint32_t allocSize = (sizeHigh != 0) ? 0xFFFFFFFF : sizeLow;
        // Equivalent to: -(uint32_t)(int32_t)(size64 >> 32 != 0) | sizeLow

        m_pData = operator_new(allocSize);
        if (m_pData) {
            // Zero-initialize the buffer
            memset(m_pData, 0, m_count * 4);
        }
        // Note: If allocation failed (0xFFFFFFFF or null), m_pData is null or invalid.
    }
};