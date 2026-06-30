// FUNC_NAME: DebugManager::recordEvent
// Function at 0x00609950: Stores two 4-byte values and a zero into a fixed-size buffer of 8 entries.
// The buffer consists of three global arrays with byte offsets: first array at 0x01205768, second at 0x0120576c,
// third at 0x01205770. Each entry occupies 6 bytes in the first two arrays and 24 bytes in the third (likely due to alignment or other fields).
// Counter g_debugEventCount tracks number of stored events (max 8).

// Global variables (simulated):
static int g_debugEventCount = 0;                  // DAT_00f15a6c
static char g_debugEventArray1[48] = {0};          // DAT_01205768 (8 entries * 6 bytes = 48)
static char g_debugEventArray2[48] = {0};          // DAT_0120576c (8 entries * 6 bytes = 48)
static char g_debugEventArray3[192] = {0};         // DAT_01205770 (8 entries * 24 bytes = 192)

void DebugManager::recordEvent(uint32_t param1, uint32_t param2)
{
    if (g_debugEventCount < 8)
    {
        int index = g_debugEventCount;
        int offset6 = index * 6;    // offset for first two arrays
        int offset24 = index * 24;  // offset for third array

        // Store param1 at offset6 in first array (4 bytes)
        *(uint32_t*)(g_debugEventArray1 + offset6) = param1;
        // Store param2 at offset6 in second array (4 bytes)
        *(uint32_t*)(g_debugEventArray2 + offset6) = param2;
        // Store 0 at offset24 in third array (4 bytes)
        *(uint32_t*)(g_debugEventArray3 + offset24) = 0;

        // Increment counter
        g_debugEventCount++;
    }
}