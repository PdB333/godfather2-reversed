// Xbox PDB: TNL::Socket::getInterfaceAddresses
// FUNC_NAME: enumerateLocalInterfaces
#include <windows.h>
#include <iphlpapi.h>

// Global function pointer for GetIpAddrTable (cached)
static FARPROC gGetIpAddrTableFunc = nullptr;

// Global counter for IP enumeration (used as reentrancy guard?)
static int gIpEnumerationCount = 0;

// External function to register a local IP address
extern void networkRegisterIP(uint32_t ipAddr);

void enumerateLocalInterfaces(void)
{
    PMIB_IPADDRTABLE pIpAddrTable;
    ULONG ulSize;
    DWORD dwResult;
    uint32_t ipAddr;
    uint32_t i;

    // Load iphlpapi.dll and cache GetIpAddrTable if not already done
    if (gGetIpAddrTableFunc == nullptr) {
        HMODULE hModule = LoadLibraryA("iphlpapi.dll");
        if (hModule == nullptr) {
            return;
        }
        gGetIpAddrTableFunc = GetProcAddress(hModule, "GetIpAddrTable");
        if (gGetIpAddrTableFunc == nullptr) {
            return;
        }
    }

    // First call: determine required buffer size
    ulSize = 0;
    pIpAddrTable = (PMIB_IPADDRTABLE)malloc(0); // Initial dummy allocation? Actually just zero size
    dwResult = ((DWORD (WINAPI *)(PMIB_IPADDRTABLE, PULONG, BOOL))gGetIpAddrTableFunc)(pIpAddrTable, &ulSize, FALSE);
    if (dwResult == ERROR_INSUFFICIENT_BUFFER) {
        free(pIpAddrTable);
        pIpAddrTable = (PMIB_IPADDRTABLE)malloc(ulSize);
        if (pIpAddrTable == nullptr) {
            return;
        }
    }

    // Second call: actually fill the table
    dwResult = ((DWORD (WINAPI *)(PMIB_IPADDRTABLE, PULONG, BOOL))gGetIpAddrTableFunc)(pIpAddrTable, &ulSize, FALSE);
    if (dwResult == NO_ERROR && pIpAddrTable->dwNumEntries > 0) {
        // Iterate over all IP addresses in the table
        for (i = 0; i < pIpAddrTable->dwNumEntries; i++) {
            // MIB_IPADDRROW structure: dwAddr (4 bytes), dwIndex (4), dwMask (4), dwBCastAddr (4), dwReasmSize (4), wType (2), wPadding (2) = 24 bytes
            // Pointer to current row: base + 4 (skip count) + i * 24
            uint32_t* pRow = (uint32_t*)((uint8_t*)pIpAddrTable + 4 + i * 24);
            ipAddr = htonl(*pRow); // Convert from network byte order to host byte order
            gIpEnumerationCount++;
            // Skip 0.0.0.0 and loopback (127.0.0.1)
            if (ipAddr != 0 && ipAddr != 0x7f000001) {
                networkRegisterIP(ipAddr);
            }
            gIpEnumerationCount--;
        }
    }

    free(pIpAddrTable);
}