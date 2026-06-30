// FUNC_NAME: delayByByte
// Function address: 0x0061d380
// Identified role: Spin-loop delay using lower byte of argument, likely for hardware timing or synchronization.
// Called from: FUN_0061d720 (unconditional call)

#include <cstdint>

void __fastcall delayByByte(uint32_t delayCount)
{
    // Only the lower 8 bits are used; the loop counts down to zero.
    delayCount = delayCount & 0xff;
    while (delayCount != 0) {
        delayCount--;
    }
}