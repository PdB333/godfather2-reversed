// FUNC_NAME: SetFlag
// Function address: 0x00605f20
// Role: Sets or clears a bit in a global bit array (64-bit chunks) with critical section protection. Also handles writing a byte to a separate array or pointer.
// The bit array tracks some global flags; maintains the lowest set chunk index for optimization.

#include <windows.h> // For CRITICAL_SECTION, EnterCriticalSection, etc.

void SetFlag(uint bitIndex, char *outByte, char value)
{
    LPCRITICAL_SECTION lpCriticalSection;
    uint chunkIndex;
    uint highBits;
    unsigned long long mask;

    // Global variables (defined elsewhere)
    extern CRITICAL_SECTION *g_flagCriticalSection;    // DAT_011d917c
    extern uint g_flagBitsLow[];                       // DAT_011d8f28
    extern uint g_flagBitsHigh[];                      // DAT_011d8f2c
    extern uint g_lowestSetChunk;                      // DAT_011d9128
    extern char g_someStructArray[];                   // DAT_011a0f28 (stride 0x38)

    lpCriticalSection = g_flagCriticalSection;
    chunkIndex = bitIndex >> 6; // divide by 64 to get chunk index

    // Critical section to ensure atomicity
    EnterCriticalSection(g_flagCriticalSection);
    LeaveCriticalSection(lpCriticalSection); // This looks suspicious; possibly a mistake in decompilation? But we keep it.

    // Create a 64-bit mask with bit set at position (bitIndex & 63)
    mask = __allshl(1, (int)(bitIndex & 0x3F)); // returns 64-bit value; upper 32 in EDX, lower in EAX
    highBits = (uint)(mask >> 32); // upper 32 bits

    if (value == '\0') {
        // Clear the bit
        g_flagBitsLow[chunkIndex * 2] &= (uint)mask;
        g_flagBitsHigh[chunkIndex * 2] &= highBits;
        // If cleared chunk becomes zero and it was the lowest, update lowest
        if (chunkIndex == g_lowestSetChunk && g_flagBitsLow[chunkIndex * 2] == 0 && g_flagBitsHigh[chunkIndex * 2] == 0) {
            g_lowestSetChunk++;
        }
    } else {
        // Set the bit
        g_flagBitsLow[chunkIndex * 2] |= (uint)mask;
        g_flagBitsHigh[chunkIndex * 2] |= highBits;
        // Update lowest set chunk if needed
        if ((int)chunkIndex < (int)g_lowestSetChunk) {
            g_lowestSetChunk = chunkIndex;
        }
    }

    // Handle the output byte if provided
    if (outByte == NULL) {
        if (bitIndex < 0x1000) {
            // Write to array with stride 0x38 (likely part of a struct)
            g_someStructArray[bitIndex * 0x38] = value;
            return;
        }
        // Otherwise write to address 0 (likely a placeholder)
        *(volatile char *)0 = value;
        return;
    }
    *outByte = value;
}