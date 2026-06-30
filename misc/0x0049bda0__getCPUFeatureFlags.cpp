// FUNC_NAME: getCPUFeatureFlags
ulonglong getCPUFeatureFlags(void)
{
    // Initialize result components
    uint32_t highPart;    // Will hold either vendor data or ECX from CPUID leaf 1
    uint32_t lowPart = 0; // Low part will hold bit 28 (AVX flag) if available

    // Execute CPUID with EAX=0 to get basic info: max standard function number and vendor string
    int *basicInfo = (int *)cpuid_basic_info(0);
    uint32_t maxStandardFn = basicInfo[0]; // [0x00] Maximum standard CPUID function number
    uint32_t vendorThirdDword = basicInfo[2]; // [0x08] Third dword of the vendor string (e.g., "ntel" for Intel)

    if (maxStandardFn != 0) {
        // CPUID leaf 1 is available: get version information including feature flags
        int *versionInfo = (int *)cpuid_Version_info(1);
        uint32_t ecxFlags = versionInfo[2]; // [0x08] ECX register from leaf 1

        // Both high and low parts become the full ECX feature word
        highPart = ecxFlags;
        // Low part will later be masked to isolate bit 28 (AVX flag)
        lowPart = ecxFlags;
    } else {
        // No standard CPUID leaves beyond 0; use vendor string data as placeholder
        highPart = vendorThirdDword;
        lowPart = 0; // No feature flags available
    }

    // Combine high (32-bit) and low (32-bit) into a 64-bit value,
    // then mask so that only bit 28 of the low part is retained
    // (bit 28 of ECX = AVX support for processors supporting it)
    return ( ((uint64_t)highPart << 32) | (uint64_t)lowPart ) & 0xffffffff10000000ULL;
}