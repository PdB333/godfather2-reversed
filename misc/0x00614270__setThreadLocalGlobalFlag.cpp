// FUNC_NAME: setThreadLocalGlobalFlag
// Address: 0x00614270
// Role: Sets a global flag based on a thread-local indication.
// Accesses the Thread Local Storage (TLS) via FS segment at offset 0x2C (TlsSlots).
// The first TLS slot is interpreted as a pointer to a per-thread structure.
// If the int at offset 0x34 in that structure is non-zero, index 1 is used; otherwise index 0.
// The provided value is stored into a global array at that index.

#include <intrin.h> // For __readfsdword

// Global array sized at least 2 (based on usage). Named to reflect its purpose.
extern int g_threadFlag[2]; // originally DAT_011f6be8

void __cdecl setThreadLocalGlobalFlag(int value)
{
    // Get pointer to TlsSlots array from TEB (FS:[0x2C])
    int** tlsSlots = (int**)__readfsdword(0x2C);
    // First TLS slot holds a pointer to thread-specific data
    int* threadData = tlsSlots[0];
    // Check condition at offset +0x34 (index = 0x34 / 4 = 13)
    int condition = threadData[13]; // equivalent to *(int*)(threadData + 0x34)
    int index = (condition != 0) ? 1 : 0;
    g_threadFlag[index] = value;
}