// FUNC_NAME: EARSConsole::initialize

#include <cstdint>

// Forward declarations of external functions
extern void* GetSingletonInternal(void* ptr);
extern void SubInitA();
extern int LoadResource(int type, int id, int param3, int param4, int param5, int param6);
extern void SubInitB();
extern void ErrorHandler();

// Global command table (12-byte entries, max 32)
struct CommandEntry {
    uint32_t callback1;  // +0x00
    uint32_t callback2;  // +0x04
    uint8_t  typeFlag;   // +0x08 (checked for > 0x80)
    uint8_t  pad[3];     // +0x09
};

static CommandEntry s_commandTable[32];  // DAT_01222330
static uint32_t s_commandCount = 0;      // DAT_012224a8
static bool g_enableDebugConsole;        // DAT_01205359
static int g_resourceParam3;             // DAT_0120587c
static int g_resourceParam4;             // DAT_01205880

void __fastcall EARSConsole::initialize()
{
    // Store a singleton pointer at +0x14
    *(void**)(this + 0x14) = GetSingletonInternal(&PTR_DAT_0110a00c);

    SubInitA();

    if (g_enableDebugConsole) {
        // Load a resource (e.g., font/console texture)
        *(int*)(this + 0x2d0) = LoadResource(6, 0x210098, g_resourceParam3, g_resourceParam4, 1, -1);
    }

    SubInitB();

    // Validate existing command table entries
    uint32_t index = 0;
    uint32_t entryFlags = 0x80; // Low byte set to 0x80 (typeFlag)
    if (s_commandCount != 0) {
        CommandEntry* pEntry = &s_commandTable[0];
        do {
            if (pEntry->typeFlag > 0x80) { // Invalid flag check
                ErrorHandler();
                return;
            }
            index++;
            pEntry++;
        } while (index < s_commandCount);
    }

    // Add a new default command entry if space allows
    if (s_commandCount < 32) {
        uint32_t offset = s_commandCount * 12; // 0xC bytes per entry
        // Write two function pointers as a 64-bit value (little-endian: low=0x4911f0, high=0x491220)
        *(uint64_t*)(&s_commandTable[0].callback1 + offset) = 0x491220004911f0ULL;
        // Set the typeFlag dword (low byte = 0x80)
        *(uint32_t*)(&s_commandTable[0].typeFlag + offset) = entryFlags;
        s_commandCount++;
    }
}