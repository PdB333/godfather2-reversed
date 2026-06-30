// FUNC_NAME: setConfigProfile
void __fastcall setConfigProfile(int profile)
{
    // Global configuration handles (likely pointers to resource blocks)
    g_configHandleA = g_configDefaultA;  // DAT_01219954 = DAT_012198f8
    g_configHandleB = g_configDefaultB;  // DAT_01219950 = DAT_01219908

    switch(profile)
    {
    case 0:
    case 1:
        g_configHandleA = g_configProfile0A; // DAT_012198f0
        g_configHandleB = g_configProfile0B; // DAT_012198f4
        break;
    case 2:
        g_configHandleA = g_configProfile2A; // DAT_01219a48
        g_configHandleB = g_configProfile0B; // DAT_012198f4
        break;
    case 3:
        g_configHandleB = g_configProfile3B; // DAT_01219900
        break;
    case 4:
        g_configHandleA = g_configProfile4A; // DAT_012198fc
        g_configHandleB = g_configProfile3B; // DAT_01219900
        break;
    case 5:
        g_configHandleA = g_configProfile5A; // DAT_01219a58
        g_configHandleB = g_configProfile3B; // DAT_01219900
        break;
    case 6:
        break;
    case 7:
        g_configHandleA = g_configProfile7A; // DAT_01219904
        g_configHandleB = g_configProfile3B; // DAT_01219900
        break;
    case 8:
        g_configHandleA = g_configProfile8A; // DAT_01219a68
        break;
    case 9:
        g_configHandleA = g_configProfile9A; // DAT_01219a50
        break;
    case 10:
        g_configHandleA = g_configProfile10A; // DAT_01219a4c
        break;
    default:
        profile = 0xb; // 11
        g_configHandleA = g_configDefaultFallbackA; // DAT_01219a54
        g_configHandleB = g_configProfile3B; // DAT_01219900
    }
    g_currentProfile = profile; // _DAT_01219a6c

    // If an initialization sentinel is set, release previous handles before swapping
    if (g_initializedFlag == &g_sentinelValue) // DAT_01219940 is some base address
    {
        releaseResource(g_configHandleA); // FUN_0060a460
        releaseResource(g_configHandleB);
    }
}