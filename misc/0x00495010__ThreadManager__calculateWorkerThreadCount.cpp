// FUNC_NAME: ThreadManager::calculateWorkerThreadCount
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// Forward declaration of CPU detection helper (address 0x0049bee0)
int getCpuInfo(char* buffer, uint32_t* coreCount, uint32_t* logicalCount);

int __stdcall ThreadManager::calculateWorkerThreadCount()
{
    uint32_t cpuInfo[2] = { 0, 0 };            // [0] = physical cores, [1] = logical processors
    char cpuidBuffer[4] = { 0 };               // Buffer for raw CPUID leaf
    int status = getCpuInfo(cpuidBuffer, &cpuInfo[0], &cpuInfo[1]);

    SYSTEM_INFO sysInfo = {};

    switch (status)
    {
    case 1:   // CPUID not supported, go directly to return 0
    case 3:
    case 5:
        return 0;

    case 8:   // Direct core count from CPUID function
    case 10:
    case 12:  // 0xC
        sysInfo.dwNumberOfProcessors = cpuInfo[0];
        break;

    default:
        // Fallback to Windows API
        GetSystemInfo(&sysInfo);
        break;
    }

    // Reserve 2 cores for OS / main thread overhead
    if (sysInfo.dwNumberOfProcessors > 2)
        return sysInfo.dwNumberOfProcessors - 2;
    else
        return 0;
}