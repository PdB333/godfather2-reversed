// FUNC_NAME: checkAndResetDataBuffer
// Address: 0x004becf0
// Role: Conditional reset of a data buffer based on a global flag.
// Called from 0x004bed20 (likely part of initialization or state cleanup).

// Globals (names inferred from usage)
extern int g_resetFlag;       // DAT_01223420 - control flag
extern void* g_dataBuffer;    // DAT_01218050 - buffer pointer
extern int g_dataSize;        // DAT_00e2e714 - size or identifier
extern void clearMemoryBlock(void* buffer, int index, int size, int flag, int category); // FUN_00440590

void checkAndResetDataBuffer(void)
{
    if (g_resetFlag != 0) {
        clearMemoryBlock(g_dataBuffer, 0, g_dataSize, 0, 4);
    }
}