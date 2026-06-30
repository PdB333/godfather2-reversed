// FUNC_NAME: NetworkUtil::enumerateLocalIPAddresses
// Address: 0x006588a0
// The function enumerates all local IP addresses using the IPHLPAPI GetIpAddrTable,
// increments a counter for each non-loopback address, and calls a helper function (FUN_00657ab0)
// to process each valid address.

#include <windows.h>
#include <iphlpapi.h> // for MIB_IPADDRTABLE, GetIpAddrTable

// Global function pointer for GetIpAddrTable, lazily loaded
static FARPROC g_pfnGetIpAddrTable = nullptr;

// Global counter for number of IP addresses processed (may be a reference count)
static int g_ipAddressCount = 0;

// Forward declaration of the helper that processes an IP address
void processIPAddress(void); // FUN_00657ab0

void enumerateLocalIPAddresses(void)
{
    // Load iphlpapi.dll and get GetIpAddrTable on first call
    if (g_pfnGetIpAddrTable == nullptr)
    {
        HMODULE hModule = LoadLibraryA("iphlpapi.dll");
        if (hModule == nullptr)
            return;
        g_pfnGetIpAddrTable = GetProcAddress(hModule, "GetIpAddrTable");
        if (g_pfnGetIpAddrTable == nullptr)
            return;
    }

    DWORD bufSize = 0;
    // First attempt with a small buffer to determine required size
    MIB_IPADDRTABLE *pTable = (MIB_IPADDRTABLE *)malloc(0);
    if (pTable == nullptr)
        return;

    int result = ((DWORD (WINAPI *)(MIB_IPADDRTABLE *, DWORD *, BOOL))g_pfnGetIpAddrTable)(pTable, &bufSize, FALSE);
    if (result == ERROR_INSUFFICIENT_BUFFER)
    {
        free(pTable);
        pTable = (MIB_IPADDRTABLE *)malloc(bufSize);
        if (pTable == nullptr)
            return;
    }

    // Now call with the correctly sized buffer
    result = ((DWORD (WINAPI *)(MIB_IPADDRTABLE *, DWORD *, BOOL))g_pfnGetIpAddrTable)(pTable, &bufSize, FALSE);
    if (result == NO_ERROR && pTable->dwNumEntries > 0)
    {
        // Iterate through IP addresses in the table
        // Each entry is sizeof(MIB_IPADDRROW) = 6 DWORDs? Actually 24 bytes, but the table is compact.
        // The code iterates using pointer arithmetic: puVar4 = puVar1 + 1 (skip the count), then steps by 6 (each entry is 6 DWORDs? 
        // MIB_IPADDRROW contains: dwAddr, dwIndex, dwMask, dwBCastAddr, dwReasmSize, dwType, dwAddr is first.
        // So each row is 6 DWORDs (24 bytes). So the decompiled code's +6 is correct.
        DWORD *pEntry = (DWORD *)(pTable + 1); // first entry
        for (DWORD i = 0; i < pTable->dwNumEntries; i++)
        {
            g_ipAddressCount++; // +0x01205a30
            DWORD ipAddr = htonl(pEntry[0]); // network byte order to host
            // Also call htonl(0) which does nothing? Probably a decompiler artifact of a dummy call.
            // The condition: if ipAddr != 0 && ipAddr != 0x7f000001 (127.0.0.1)
            if (ipAddr != 0 && ipAddr != 0x7f000001)
            {
                processIPAddress(); // FUN_00657ab0
            }
            g_ipAddressCount--; // decrement after processing
            pEntry += 6; // advance to next entry (6 DWORDs per row)
        }
    }

    free(pTable);
}