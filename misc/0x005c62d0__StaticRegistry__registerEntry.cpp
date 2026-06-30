// FUNC_NAME: StaticRegistry::registerEntry

#include <cstdint>

// Global registration tables (addresses from Ghidra)
// Table A: 8-byte entries (function pointers?) at 0x01222328
// Table B: 12-byte entries (status/flags?) at 0x01222330
// Count: uint32_t at 0x012224a8

extern uint32_t g_registeredCount;              // 0x012224a8
extern uint8_t  g_registryA[0x20 * 8];          // 0x01222328, each entry 8 bytes
extern uint8_t  g_registryB[0x20 * 12];         // 0x01222330, each entry 12 bytes

// Forward declarations of called functions
void onHighByteDetected(void);                  // FUN_00609bf0
void finalizeRegistration(void);                // FUN_005c5d10

void __cdecl registerEntry(void)
{
    uint32_t count = g_registeredCount;
    uint32_t localFlag = 0x80; // Set low byte to 0x80 (upper bytes from uninitialized local, but assumed zero)

    // Check existing entries for a high first byte (> 0x80)
    if (count != 0)
    {
        uint8_t* entry = g_registryB;
        for (uint32_t i = 0; i < count; i++)
        {
            if (entry[0] > 0x80)
            {
                onHighByteDetected();
                finalizeRegistration();
                return;
            }
            entry += 12; // each entry is 12 bytes
        }
    }

    // Add new entry if space permits (max 32)
    if (count < 32)
    {
        // Write 8 bytes at offset count*3 in registryA (stores a function pointer + zeros)
        uint64_t funcData = 0x00000000005c62c0ULL; // Low 32 bits = 0x005c62c0 (likely function address)
        *reinterpret_cast<uint64_t*>(&g_registryA[count * 3]) = funcData;

        // Write 4 bytes at offset count*12 in registryB (stores the flag with low byte 0x80)
        *reinterpret_cast<uint32_t*>(&g_registryB[count * 12]) = localFlag;

        g_registeredCount++;
    }

    finalizeRegistration();
}