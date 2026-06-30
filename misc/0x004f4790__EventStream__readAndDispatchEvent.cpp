// FUNC_NAME: EventStream::readAndDispatchEvent
// Function at 0x004f4790: Reads a 32-bit identifier and two 64-bit values from a packed buffer,
// then calls the first virtual method of a handler object with these values.
// The buffer pointer is stored at offset +0x18 of the EventStream object.
// Data layout: 4-byte leading value, optional padding to 4-byte alignment, then two 8-byte values.

#include <cstdint>

class EventStream {
public:
    // Current read pointer into the internal buffer (offset +0x18)
    uint8_t* m_current;  // +0x18

    void readAndDispatchEvent(class Handler* handler) {
        // Read the first 32-bit value (identifier/type)
        uint32_t id = *(uint32_t*)m_current;

        // Align current pointer to the next 4-byte boundary (round up)
        uint32_t alignedAddr = ((uint32_t)m_current + 7) & ~3;
        uint8_t* alignedPtr = (uint8_t*)alignedAddr;
        m_current = alignedPtr;

        // Read two 64-bit values from the aligned position
        uint64_t val1 = *(uint64_t*)m_current;
        m_current += 8;
        uint64_t val2 = *(uint64_t*)m_current;
        m_current += 8;

        // Split 64-bit values into low and high 32-bit parts
        uint32_t val1_lo = (uint32_t)(val1);
        uint32_t val1_hi = (uint32_t)(val1 >> 32);
        uint32_t val2_lo = (uint32_t)(val2);
        uint32_t val2_hi = (uint32_t)(val2 >> 32);

        // Call the first virtual method of the handler object
        // (The handler pointer is passed as the second parameter; the vtable pointer is at offset 0)
        // The virtual function receives: id, low(val1), high(val1), low(val2), high(val2)
        handler->onEvent(id, val1_lo, val1_hi, val2_lo, val2_hi);
    }
};

// Abstract handler interface (first virtual function is onEvent)
class Handler {
public:
    virtual void onEvent(uint32_t id, uint32_t arg1_lo, uint32_t arg1_hi, uint32_t arg2_lo, uint32_t arg2_hi) = 0;
};