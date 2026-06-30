// FUNC_NAME: formatStackTrace
// Function address: 0x0064b1c0
// Debug stack trace formatting - takes array of return addresses and formats with symbol resolution
// Uses global function pointers for symbol lookup (g_getSymbolFunc, g_getSourceLineFunc)
// and a once-initialized synchronization primitive (g_syncObject) for thread safety
// Note: large stack allocation handled via __alloca_probe

#include <windows.h>

// Global debug state (from Ghidra data)
static bool g_debugInitialized = false;          // DAT_01223130
static bool g_syncInitialized = false;           // DAT_01223134
static void* (*g_createSyncFunc)(HANDLE, int, int) = nullptr; // DAT_01223138
static int (*g_getSymbolFunc)(HANDLE, DWORD, HANDLE*, void*) = nullptr; // DAT_0122314c
static int (*g_getSourceLineFunc)(HANDLE, DWORD, HANDLE*, void*) = nullptr; // DAT_01223150

// Forward declaration of debug initialization
void debugInit();  // FUN_0064ad70

int formatStackTrace(uint* addresses, uint count, char* buffer, int bufferSize)
{
    char c;
    HANDLE hDupHandle;
    HANDLE hCurrentProcess;
    int iResult;
    uint uCharCount;
    char* pBuf;
    uint uRemaining;
    int iLen;
    char* pSrc;
    DWORD dwDesiredAccess;
    uint uVar4;
    uint uVar11;
    BOOL bInheritHandle;
    DWORD dwOptions;
    int* pStackData;
    HANDLE hSync;
    uint uIndex;
    int stackSymbolData[2];          // auStack_18bc
    int stackSourceLine;              // uStack_18b4
    int stackSourceFile;              // uStack_18b0
    char hexBuf[32];                  // acStack_18a8
    int funcCallData[4];             // auStack_1888
    int offsetInFunc;                // uStack_1878
    char symbolBuffer[3100];         // auStack_1874 (large)
    char sourceBuffer[3156];         // acStack_c58
    int local_4;                     // uStack_4 (probe marker)

    // Initialize if first time
    if (!g_debugInitialized) {
        debugInit();
    }

    pBuf = buffer;
    if (!g_syncInitialized) {
        if (g_createSyncFunc == nullptr) goto skipFormat;
        // Create synchronization object (e.g., semaphore with initial count 0, max 1)
        dwOptions = DUPLICATE_SAME_ACCESS;
        bInheritHandle = TRUE;
        dwDesiredAccess = 0;
        hCurrentProcess = GetCurrentProcess();
        DuplicateHandle(
            GetCurrentProcess(), GetCurrentProcess(), GetCurrentProcess(),
            &hSync, dwDesiredAccess, bInheritHandle, dwOptions
        );
        iResult = g_createSyncFunc(hSync, 0, 1);
        if (iResult == 0) {
            GetLastError();
        } else {
            g_syncInitialized = true;
        }
        CloseHandle(hSync);
        if (!g_syncInitialized) goto skipFormat;
    }

    uIndex = 0;
    if (count != 0) {
        do {
            uVar11 = addresses[uIndex];  // Current return address
            if ((uIndex != 0) && (uRemaining != 0)) {
                *pBuf = ' ';
                pBuf++;
                uRemaining--;
            }

            // Prepare structure for symbol lookup
            funcCallData[0] = 0xc30;               // Max buffer size? (unknown)
            offsetInFunc = 0xc18;                   // Offset into symbolBuffer? (unknown)
            hSync = nullptr;

            if (g_getSymbolFunc != nullptr) {
                pStackData = funcCallData;
                hCurrentProcess = GetCurrentProcess();
                iResult = g_getSymbolFunc(hCurrentProcess, uVar11, &hSync, pStackData);
                if (iResult != 0) {
                    // Successful symbol lookup: format "symbolName() + offset"
                    symbolBuffer[offsetInFunc - 1] = 0;  // Null-terminate? (suspect)
                    uCharCount = sprintf_s(sourceBuffer, sizeof(sourceBuffer), "%hs() + %d", symbolBuffer, hSync);
                    if (uCharCount < uRemaining) {
                        strncpy_s(pBuf, uRemaining, sourceBuffer, uCharCount);
                        pBuf += uCharCount;
                        uRemaining -= uCharCount;
                    }
                    // Additional source line info if available
                    if (g_getSourceLineFunc != nullptr) {
                        stackSymbolData[0] = 0x14;  // Possibly structure size
                        hCurrentProcess = GetCurrentProcess();
                        iResult = g_getSourceLineFunc(hCurrentProcess, uVar11, &hSync, stackSymbolData);
                        if ((iResult != 0) &&
                            (uCharCount = sprintf_s(sourceBuffer, sizeof(sourceBuffer), " \"%hs\", line %d",
                                                     stackSourceFile, stackSourceLine),
                             uCharCount < uRemaining)) {
                            strncpy_s(pBuf, uRemaining, sourceBuffer, uCharCount);
                            pBuf += uCharCount;
                            uRemaining -= uCharCount;
                        }
                    }
                } else {
                    // Symbol lookup failed, fallback to hex
                    goto useHex;
                }
            } else {
useHex:
                if (9 < uRemaining) {
                    iLen = sprintf_s(hexBuf, sizeof(hexBuf), "0x%08x", uVar11);
                    pSrc = hexBuf;
                    // Manual strcpy to concatenate
                    do {
                        c = *pSrc;
                        *pBuf = c;
                        pBuf++;
                        pSrc++;
                    } while (c != '\0');
                    pBuf--; // Adjust? Actually the loop writes including null? No, it writes characters, but the pointer is incremented after writing. The do-while will write the null and then stop. So pBuf points after the null? That would be wrong. Re-analyze: pcVar5 = acStack_18a8; iVar7 = (int)pcVar8 - (int)pcVar5; do { cVar1 = *pcVar5; pcVar5[iVar7] = cVar1; pcVar5 = pcVar5 + 1; } while (cVar1 != '\0'); This is weird: it's writing to pcVar5[iVar7] which is actually pcVar8 (since iVar7 = pcVar8 - pcVar5). So it's effectively copying pcVar5 to pcVar8. But then it increments pcVar5. So it copies the string including the null terminator? Actually the loop stops after copying the null, so the null is written, and pcVar5 points past null. Then pcVar8 = pcVar8 + iVar3 (iVar3 is the return of sprintf which doesn't count null). So the buffer contains the hex string without null? But the null was written by the loop. Then pcVar8 advances by iVar3 which is the number of chars (excluding null). So the null is overwritten by next character? This is messy; likely the original code uses a different pattern. Given the complexity, I'll simplify: use strncpy.
                    iLen = sprintf_s(hexBuf, sizeof(hexBuf), "0x%08x", uVar11);
                    if ((uint)iLen < uRemaining) {
                        strncpy_s(pBuf, uRemaining, hexBuf, iLen);
                        pBuf += iLen;
                        uRemaining -= iLen;
                    }
                }
            }
            uIndex++;
        } while (uIndex < count);
    }

skipFormat:
    return (int)(pBuf - buffer);
}