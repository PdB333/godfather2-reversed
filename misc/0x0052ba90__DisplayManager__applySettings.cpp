// FUNC_NAME: DisplayManager::applySettings
// Address 0x0052ba90
// Adjusts display/framerate settings and handles device changes.
// Takes two parameters: displayModeIndex (param_1) and persist (param_2).
// Also uses EAX as a device index for input device reconfiguration.

undefined4 DisplayManager::applySettings(uint param_1, char param_2) // param_1 may be in ECX? actual entry EAX used separately.
{
    int currentMonitorId;
    int primaryMonitorId;
    uint uVar1;
    int iVar2;
    uint uVar3;
    
    currentMonitorId = DAT_011f38f0; // g_currentMonitorId
    iVar2 = DAT_012058a4; // g_primaryMonitorId
    if (DAT_012054dc != 0) { // g_hWindow != null
        iVar2 = *(int *)(DAT_012054dc + 0x16c); // window->monitorId
    }
    
    // Toggle reference count if applying to primary monitor
    if (currentMonitorId == iVar2) {
        g_refCountMonitorUsage = g_refCountMonitorUsage + 1; // _DAT_01205500
    }
    
    // Clamp frame rate limits to minimums
    if (g_frameRateMin < 0x16) g_frameRateMin = 0x16; // 22 FPS
    if (0x16 < g_frameRateMax) g_frameRateMax = 0x16;
    g_frameRateLow = 1; // _DAT_011f3a30
    
    if (g_frameRateMin < 0xe) g_frameRateMin = 0xe; // 14 FPS
    if (0xe < g_frameRateMax) g_frameRateMax = 0xe;
    g_frameRateMedium = 0; // _DAT_011f3a10
    
    if (g_frameRateMin < 7) g_frameRateMin = 7;
    if (7 < g_frameRateMax) g_frameRateMax = 7;
    g_frameRateHigh = 0; // _DAT_011f39f4
    
    if (g_frameRateMin < 0x19) g_frameRateMin = 0x19; // 25 FPS
    if (0x19 < g_frameRateMax) g_frameRateMax = 0x19;
    g_frameRateUltra = 5; // _DAT_011f3a3c
    
    if (g_frameRateMin < 0x18) g_frameRateMin = 0x18; // 24 FPS
    if (0x18 < g_frameRateMax) g_frameRateMax = 0x18;
    g_frameRateCustom = 0; // _DAT_011f3a38
    
    if (g_frameRateMin < 0xf) g_frameRateMin = 0xf; // 15 FPS
    if (0xf < g_frameRateMax) g_frameRateMax = 0xf;
    g_frameRateVSR = 0; // _DAT_011f3a14
    
    // Reconfigure an input device if given via EAX
    if ((in_EAX != 0xffffffff) && (in_EAX < 0x1000)) {
        uVar1 = in_EAX * 0x38; // each device block is 0x38 bytes
        byte* deviceBlock = &g_inputDeviceTable + uVar1; // DAT_011a0f28
        if (deviceBlock != (byte*)0x0 && (byte)(*deviceBlock) < 4) {
            int* deviceHandle = *(int**)(deviceBlock + 0x1c); // +0x1c: pointer to device data
            if (deviceHandle != (int*)0x0) {
                FUN_00606e60(deviceHandle, 0x100000); // Release device resources?
            }
            *(uint*)(deviceBlock + 0xc) = *(uint*)(deviceBlock + 0xc) & 0xfc9c8fff | 0x100000; // Set some flags
            FUN_006189c0(); // Notify device change?
        }
    }
    
    // Apply first display mode (low quality)
    FUN_00417cf0(1, 2, 1); // SetDisplayMode(1, 2, 1) – low quality?
    
    // Clamp again after mode change
    if (g_frameRateMin < 0x1b) g_frameRateMin = 0x1b; // 27 FPS
    if (0x1a < g_frameRateMax) g_frameRateMax = 0x1b;
    g_frameRateLowest = 0; // _DAT_011f3a44
    
    FUN_0052be20(param_1, 0, param_2); // Apply resolution? param_1 is mode index, param_2 persist
    FUN_00606470(); // Update something (swap buffers?)
    
    // Now set high quality limits
    if (g_frameRateMin < 0x16) g_frameRateMin = 0x16;
    if (0x16 < g_frameRateMax) g_frameRateMax = 0x16;
    g_frameRateLow = 1;
    
    if (g_frameRateMin < 7) g_frameRateMin = 7;
    if (7 < g_frameRateMax) g_frameRateMax = 7;
    g_frameRateHigh = 1;
    
    if (g_frameRateMin < 0x19) g_frameRateMin = 0x19;
    if (0x19 < g_frameRateMax) g_frameRateMax = 0x19;
    g_frameRateUltra = 7;
    
    if (g_frameRateMin < 0x18) g_frameRateMin = 0x18;
    if (0x18 < g_frameRateMax) g_frameRateMax = 0x18;
    g_frameRateCustom = 0;
    
    if (g_frameRateMin < 0xf) g_frameRateMin = 0xf;
    if (0xf < g_frameRateMax) g_frameRateMax = 0xf;
    g_frameRateVSR = 0;
    
    // Apply second display mode (high quality)
    FUN_00417cf0(1, 5, 6); // SetDisplayMode(1, 5, 6)
    
    // More clamping for high quality
    if (g_frameRateMin < 0x1b) g_frameRateMin = 0x1b;
    if (0x1a < g_frameRateMax) g_frameRateMax = 0x1b;
    g_frameRateLowest = 0;
    
    if (g_frameRateMin < 0xe) g_frameRateMin = 0xe;
    if (0xe < g_frameRateMax) g_frameRateMax = 0xe;
    g_frameRateMedium = 1;
    
    // Update monitor tracking list
    uVar3 = 0;
    do {
        if (g_monitorIdList[uVar3] == currentMonitorId) { // DAT_01218e50 (array of 0x14 ints)
            if (uVar3 < 0x14) {
                g_monitorFlagsList[uVar3] = g_monitorFlagsList[uVar3] & 0xfffffffc; // clear low 2 bits
            }
            break;
        }
        uVar3 = uVar3 + 1;
    } while (uVar3 < 0x14);
    
    // Finalize and notify
    int oldMonitorId = DAT_011f38f4; // g_previousMonitorId
    DAT_011f38f4 = 0;
    DAT_011f38f0 = currentMonitorId;
    FUN_00609340(0, currentMonitorId, oldMonitorId); // Notify change to new monitor
    FUN_0060db60(0, 0, 0, 0x3f800000, 0x3f800000); // Set viewport (float 1.0,1.0)
    
    // Decrement reference count if we incremented earlier
    iVar2 = DAT_012058a4; // g_primaryMonitorId
    if (DAT_012054dc != 0) {
        iVar2 = *(int*)(DAT_012054dc + 0x16c);
    }
    if (currentMonitorId == iVar2) {
        g_refCountMonitorUsage = g_refCountMonitorUsage - 1;
    }
    
    // Return a flag from global array based on persist parameter
    // Index: (-(uint)(param_2 != 0) & 0xfffffffd) * 2  → effectively either 0 or a large negative? This is likely a decompiler artifact.
    // Probably returns g_monitorChangedFlag array[param_2 ? 0 : 1]
    return (&g_monitorChangedFlag)[(-(uint)((char)param_2 != '\0') & 0xfffffffd) * 2];
}