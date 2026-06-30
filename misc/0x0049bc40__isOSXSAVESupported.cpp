// FUNC_NAME: isOSXSAVESupported
unsigned int isOSXSAVESupported(void)
{
    // CPUID leaf 1 returns information in EAX, EBX, ECX, EDX
    // The cpuid_Version_info function (likely a system wrapper) returns a pointer to a structure
    // containing these 4 values at offsets 0, 4, 8, 12
    int cpuidInfo = cpuid_Version_info(1);

    // Read ECX (offset 8) and extract bit 26 (OSXSAVE flag)
    unsigned int ecx = *(unsigned int *)(cpuidInfo + 8);
    return (ecx >> 0x1a) & 1;
}