// FUNC_NAME: enumerateOtherThreads
#include <windows.h>

// Globals resolved by FUN_0064ad70 (initialization)
extern int g_bThreadEnumInitialized;   // DAT_01223130
extern void* g_pfnThreadEnumFunc;      // DAT_01223140
extern void* g_dword_01223144;         // DAT_01223144
extern void* g_dword_01223148;         // DAT_01223148

uint enumerateOtherThreads(uint* outArray, uint maxCount)
{
    uint count = 0;
    if (g_bThreadEnumInitialized == 0) {
        // Initialize global function pointers (resolve NtQuerySystemInformation etc.)
        FUN_0064ad70();
    }

    if (g_pfnThreadEnumFunc != NULL) {
        HANDLE hProcess = GetCurrentProcess();
        HANDLE hThread = GetCurrentThread();

        // Buffer for system thread information (size 0x2CC bytes)
        uint8_t systemInfoBuffer[0x2CC];
        memset(systemInfoBuffer, 0, sizeof(systemInfoBuffer));

        // First dword of the buffer is set: 0x10001 (probably version or size)
        *(uint*)systemInfoBuffer = 0x10001;

        // Second dword: address of a constant data block (0x64b0C4)
        // This might be a pointer to the thread entry structure or a callback.
        uint32_t entryPointer = 0x64b0C4;
        uint8_t* pEntryBuffer = (uint8_t*)&stackBuffer; // Points to stack location (likely a temporary structure)
        // The following assignments are based on Ghidra output, but stack offsets may be misrepresented.
        // The actual assembly likely builds an initial structure for the API call.

        uint8_t enumBuffer[0xA4];
        memset(enumBuffer, 0, sizeof(enumBuffer));
        *(uint*)enumBuffer = entryPointer;          // +0x00: pointer to entry function or data
        *(uint*)(enumBuffer + 4) = 3;               // +0x04: size/count?
        *(uint*)(enumBuffer + 0x08) = (uint)pEntryBuffer; // pointer to thread entry buffer
        *(uint*)(enumBuffer + 0x0C) = 3;               // +0x0C: another size
        *(uint*)(enumBuffer + 0x10) = (uint)&stackBuffer2; // pointer to another buffer
        *(uint*)(enumBuffer + 0x14) = 3;               // +0x14: size

        int iteration = 0;
        while (count < maxCount - 1) {
            int result = ((int (__stdcall*)(uint, HANDLE, HANDLE, void*, void*, uint, void*, void*, uint))
                g_pfnThreadEnumFunc)(0x14C, hProcess, hThread, enumBuffer, systemInfoBuffer, 0,
                                     g_dword_01223144, g_dword_01223148, 0);

            if (result == 0)
                break;

            // Check if the pointer from enumBuffer is still valid
            if (*(void**)enumBuffer == NULL)
                break;

            if (iteration > 0) {
                outArray[count] = *(uint*)enumBuffer; // Store the thread identifier/pointer
                count++;
            }
            iteration++;
        }
    }

    // Terminate the array with 0
    outArray[count] = 0;
    return count;
}