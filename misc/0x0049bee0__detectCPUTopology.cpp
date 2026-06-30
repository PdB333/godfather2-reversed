// FUNC_NAME: detectCPUTopology
// Function at 0x0049bee0: Detects CPU topology using APIC ID and thread affinity masks.
// Returns a byte encoding topology type (1,5,12, etc.)
// Input: pNumLogicalProcs, pNumCores, pNumPackages (output pointers)
// Uses CPUID leaf 1 to get APIC ID, extracts Physical/Core/SMT IDs based on frequencies.
// Then groups logical processors by (physical+core) ID -> cores, and by physical ID -> packages.
// Logic: if numPackages <= numCores -> topology (single core, dual core, etc.)
// else -> topology with multiple packages.

char __cdecl detectCPUTopology(uint *pNumLogicalProcs, uint *pNumCores, uint *pNumPackages)
{
    byte bSmtId;
    short sTmp;
    int iCpuIndex;
    byte bCoreId;
    ushort uFreqRatio;
    HANDLE hThread;
    uint uApicId;
    DWORD_PTR dwPrevAffinity;
    uint uAffinityMask;
    uint uCombinedId;
    uint uNumLogical;
    int iLoop;
    uint uBitMask;
    DWORD_PTR *lpSystemAffMask;
    DWORD_PTR *lpProcAffMask;
    uint aCoreIdGroups[256]; // Unique core IDs (physical+core composite)
    byte aCoreIdList[256];   // Core ID per logical proc
    byte aSmtIdList[256];   // SMT ID per logical proc
    byte aPackageIdList[256]; // Physical package ID per logical proc
    uint uNumCoreSmtBits;   // bits for SMT within APIC
    uint uNumPackagebits;   // bits for package
    uint uNumCoreBits;      // bits for core
    uint uNumTmpBits;
    uint uCoreShift;
    uint uApicHighShift;
    byte bPackageIdHigh;
    uint uCoreGroupCount;
    uint uPackageGroupCount;

    lpSystemAffMask = (DWORD_PTR*)&dwPrevAffinity; // Stack variables for GetProcessAffinityMask
    lpProcAffMask = (DWORD_PTR*)&uCoreGroupCount; // Actually just unused

    iCpuIndex = 0;
    *pNumCores = 1;   // Initially assume 1 core
    uNumLogical = 0;
    *pNumPackages = 1;

    hThread = GetCurrentProcess();
    GetProcessAffinityMask(hThread, lpProcAffMask, lpSystemAffMask);
    if (*lpProcAffMask != *lpSystemAffMask) {
        // System supports more processors than process affinity allows? Unusual.
        return 0;
    }

    // Assume helper functions return CPU frequency in MHz and bus speed in MHz.
    uApicHighShift = getCpuFrequency();          // FUN_0049bd50 - likely CPU base frequency
    uCoreShift = getCpuBusSpeed();               // FUN_0049bde0 - likely bus speed
    uCoreShift = uCoreShift / uApicHighShift;    // Ratio (e.g., multiplier)

    uAffinityMask = 1;
    do {
        if (*lpProcAffMask < uAffinityMask) break; // No more processors
        uBitMask = 1 << (iCpuIndex & 0x1f);
        uAffinityMask = uBitMask;
        uNumTmpBits = uBitMask;

        hThread = GetCurrentThread();
        dwPrevAffinity = SetThreadAffinityMask(hThread, uBitMask);
        if (dwPrevAffinity != 0) {
            Sleep(0);
            iCpuIndex = cpuid_Version_info(1);  // Returns pointer? Actually function returns something.
            uApicId = *(uint *)(iCpuIndex + 4); // CPUID[1].ebx -> APIC ID (bits 31:24)

            // Compute number of bits needed for SMT ID extraction
            uNumCoreSmtBits = 0;
            uFreqRatio = (ushort)(uCoreShift & 0xff) - 1;
            sTmp = 0xf;
            if (uFreqRatio != 0) {
                while ((uFreqRatio >> sTmp) == 0) {
                    sTmp--;
                }
            }
            if (uFreqRatio != 0) {
                uNumCoreSmtBits = (uint)(ushort)(sTmp + 1);
            }

            uCoreShift = uCoreShift;
            byte bApicHigh = (byte)(uApicId >> 0x18);
            // SMT ID mask = low uNumCoreSmtBits bits of APIC high
            bSmtId = ~(-1 << (uNumCoreSmtBits & 0x1f)) & bApicHigh;
            aSmtIdList[iCpuIndex] = bSmtId;

            // Compute number of bits needed for core ID (from divisor ratio)
            uCoreGroupCount = 0;
            uFreqRatio = (short)(uCoreShift) - 1;
            sTmp = 0xf;
            if (uFreqRatio != 0) {
                while ((uFreqRatio >> sTmp) == 0) {
                    sTmp--;
                }
            }
            if (uFreqRatio != 0) {
                uCoreGroupCount = (uint)(ushort)(sTmp + 1);
            }

            uNumPackagebits = uCoreGroupCount;
            uCoreShift = getCpuFrequency();  // FUN_0049bd50 again (different context)
            uCoreShift = uCoreShift & 0xff;
            uPackageGroupCount = 0;
            uFreqRatio = (short)uCoreShift - 1;
            sTmp = 0xf;
            if (uFreqRatio != 0) {
                while ((uFreqRatio >> sTmp) == 0) {
                    sTmp--;
                }
            }
            if (uFreqRatio != 0) {
                uPackageGroupCount = (uint)(ushort)(sTmp + 1);
            }

            // Core ID mask: bits between SMT and package
            int nBitsCore = (char)uPackageGroupCount + (byte)uNumPackagebits;
            bCoreId = (-1 << (nBitsCore & 0x1f) ^ (-1 << (uNumPackagebits & 0x1f))) & bApicHigh;
            aCoreIdList[iCpuIndex] = bCoreId;

            uNumTmpBits = getCpuBusSpeed();  // FUN_0049bde0
            uApicHighShift = 0;
            uFreqRatio = (short)uNumTmpBits - 1;
            sTmp = 0xf;
            if (uFreqRatio != 0) {
                while ((uFreqRatio >> sTmp) == 0) {
                    sTmp--;
                }
            }
            if (uFreqRatio != 0) {
                uApicHighShift = (uint)(ushort)(sTmp + 1);
            }

            // Package ID mask: high bits of APIC (above core)
            bPackageIdHigh = (-1 << (uApicHighShift & 0x1f)) & bApicHigh;
            aPackageIdList[iCpuIndex] = bPackageIdHigh;

            // Debug print
            wprintf("  AffinityMask = %d; Initial APIC = %d; Physical ID = %d, Core ID = %d,  SMT ID = %d\n",
                    uBitMask, uApicId >> 0x18, (uint)bPackageIdHigh, (uint)bCoreId, (uint)bSmtId);

            uNumLogical++;
            uBitMask = uNumTmpBits;
        }
        iCpuIndex++;
        uAffinityMask = uNumTmpBits;
    } while (uBitMask != 0);

    // Restore original thread affinity
    hThread = GetCurrentThread();
    SetThreadAffinityMask(hThread, *lpProcAffMask);
    Sleep(0);

    *pNumLogicalProcs = uNumLogical;

    // Group logical processors into unique (package+core) combinations -> cores
    uBitMask = 1;
    aCoreIdGroups[0] = aCoreIdList[0] | aPackageIdList[0];
    aCoreIdGroups[0] = 1; // Actually store bitmask in a separate array? The code uses local_734 for bitmasks.
    // In original decompile: local_234[0] = local_334[0] | local_134[0]; local_734[0]=1;
    // So we need two arrays: one for group identifiers (core+package), one for bitmasks.
    // We'll introduce appropriate arrays.
    uint aGroupBitmask[256];
    byte aGroupId[256];
    aGroupId[0] = aCoreIdList[0] | aPackageIdList[0];
    aGroupBitmask[0] = 1;

    if (1 < uNumLogical) {
        iCpuIndex = 0;
        uApicHighShift = uNumLogical - 1;
        do {
            uBitMask = *pNumCores;
            uAffinityMask = uAffinityMask * 2;  // uAffinityMask tracks bitmask shift
            uCombinedId = 0;
            if (uBitMask != 0) {
                while ((aCoreIdList[iCpuIndex+1] | aPackageIdList[iCpuIndex+1]) != aGroupId[uCombinedId]) {
                    uCombinedId++;
                    if (uCombinedId >= uBitMask) break;
                }
            }
            if (uCombinedId == uBitMask) {
                // New core found
                aGroupId[uCombinedId] = aCoreIdList[iCpuIndex+1] | aPackageIdList[iCpuIndex+1];
                aGroupBitmask[uCombinedId] = uAffinityMask;
                *pNumCores = uBitMask + 1;
            } else {
                // Existing core, update bitmask
                aGroupBitmask[uCombinedId] = aGroupBitmask[uCombinedId] | uAffinityMask;
            }
            iCpuIndex++;
            uApicHighShift--;
        } while (uApicHighShift != 0);
    }

    // Group by physical package alone -> number of packages
    aGroupId[0] = aPackageIdList[0];
    aGroupBitmask[0] = 1;
    uAffinityMask = 1;
    uBitMask = 1;
    if (1 < uNumLogical) {
        do {
            uCombinedId = *pNumPackages;
            uAffinityMask = uAffinityMask * 2;
            uCoreGroupCount = 0;
            if (uCombinedId != 0) {
                while (aPackageIdList[uBitMask] != aGroupId[uCoreGroupCount]) {
                    uCoreGroupCount++;
                    if (uCoreGroupCount >= uCombinedId) break;
                }
            }
            if (uCoreGroupCount == uCombinedId) {
                // New package
                aGroupId[uCoreGroupCount] = aPackageIdList[uBitMask];
                aGroupBitmask[uCoreGroupCount] = uAffinityMask;
                *pNumPackages = uCombinedId + 1;
            } else {
                // Existing package
                aGroupBitmask[uCoreGroupCount] = aGroupBitmask[uCoreGroupCount] | uAffinityMask;
            }
            uBitMask++;
        } while (uBitMask < uNumLogical);
    }

    uint numCores = *pNumCores;
    uint numPackages = *pNumPackages;
    if (numCores <= numPackages) {
        // Packages <= cores (single package or package=1)
        if (uCoreShift == 1) {
            return 5;   // Example: single core HT? Or dual core?
        }
        return ( (numCores < uNumLogical) ? 2 : 0 ) + 1;
    } else {
        // More packages than cores? Unusual.
        if (uCoreShift == 1) {
            return 12;
        }
        return ( (numCores < uNumLogical) ? 2 : 0 ) + 8;
    }
}