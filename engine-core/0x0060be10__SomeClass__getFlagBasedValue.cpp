// FUNC_NAME: SomeClass::getFlagBasedValue
// Address: 0x0060be10
// Returns a 4-byte value. If the flag at offset 0x1C is nonzero, the value is computed by calling a virtual member function (at vtable+0x34) with a stack buffer; otherwise it returns the cached value at offset 0x14.

#include <cstdint>

class SomeClass {
public:
    // Vtable offset 0x34: compute function (returns something in buffer)
    using ComputeFunc = uint32_t (SomeClass::*)(uint8_t* buffer);

    uint32_t getFlagBasedValue() {
        // Flag at +0x1C: indicates whether the value needs (re)computation
        if (m_needsCompute) {
            uint8_t buffer[8]; // stack buffer for computation
            ComputeFunc func = reinterpret_cast<ComputeFunc>(/* vtable+0x34 */);
            // Call the compute function
            uint32_t result = (this->*func)(buffer);
            return result; // The result is whatever the compute function returned (likely from buffer)
        }
        // Otherwise return the cached value at +0x14
        return m_cachedValue;
    }

private:
    // At offset 0x00: vtable pointer (implicit)
    // At offset 0x14: cached value (uint32_t)
    uint32_t m_cachedValue;       // +0x14
    // At offset 0x1C: compute flag (bool, 0 or 1)
    bool m_needsCompute;          // +0x1C
    // (other members omitted)
};