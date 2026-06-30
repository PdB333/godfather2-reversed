// FUNC_NAME: BitWindow::shiftWindow

#include <cstdint>

class BitWindow {
public:
    // +0x00 low 32 bits of 64-bit window mask
    // +0x04 high 32 bits
    uint32_t low;
    uint32_t high;

    // Shifts the 64‑bit mask using two left shifts (by amounts encoded elsewhere).
    // Result is stored back and a status value (low byte = 1) is returned.
    // This is used for sliding window updates in the networking layer.
    uint32_t shiftWindow() {
        // Assume 64-bit value is in EDX:EAX before each __allshl call.
        // Shift amounts come from ECX or other registers (not visible in this decompilation).
        uint64_t shiftResult1 = __allshl();    // first shift of the original mask
        uint64_t shiftResult2 = __allshl();    // second shift of the original mask

        // New low word:
        //   ~(low32(shift1)) & original_low  |  low32(shift2)
        low = ~((uint32_t)shiftResult1) & low | (uint32_t)shiftResult2;

        // New high word:
        //   ~(high32(shift1)) & original_high | high32(shift2)
        high = ~((uint32_t)(shiftResult1 >> 32)) & high | (uint32_t)(shiftResult2 >> 32);

        // Return value: (high >> 8) & 0xFFFFFF | 1
        return ((high >> 8) & 0x00FFFFFF) | 1;
    }
};