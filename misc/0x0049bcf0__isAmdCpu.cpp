// FUNC_NAME: isAmdCpu

bool isAmdCpu()
{
    // CPUID leaf 0 returns vendor string string in ebx:edx:ecx (12 bytes)
    // The helper returns a pointer to a buffer containing the CPUID info.
    int *cpuidData = cpuidBasicInfo(0);
    // Check for "AuthenticAMD" vendor string:
    //   ebx = 0x68747541 ("Auth")
    //   edx = 0x69746e65 ("enti")
    //   ecx = 0x444d4163 ("cAMD")
    if (cpuidData[1] == 0x68747541 &&  // +0x04: first part
        cpuidData[2] == 0x69746e65 &&  // +0x08: second part
        cpuidData[3] == 0x444d4163)    // +0x0C: third part
    {
        return true;
    }
    return false;
}