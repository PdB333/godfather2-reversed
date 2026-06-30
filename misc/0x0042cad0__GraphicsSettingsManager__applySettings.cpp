// FUNC_NAME: GraphicsSettingsManager::applySettings
void __thiscall GraphicsSettingsManager::applySettings(void)
{
    char soundEnabled;  // DAT_01205358 - global sound enabled flag
    uint *thisPtr;      // in_EAX
    uint newIndex;
    int bitFlag;
    int finalValue;

    thisPtr = (uint *)this;  // this pointer in EAX
    // Call some function with this[0xe7e] (offset 0x39F8)
    FUN_0042da70(thisPtr[0xe7e]);  // likely a sound/video init

    soundEnabled = g_SoundEnabled;  // DAT_01205358
    if ((g_SoundEnabled != 0) && (thisPtr[0xe7e] != 1)) {
        newIndex = (thisPtr[0] + 1) & 3;
        thisPtr[0] = newIndex;
        // Set status code at this[newIndex + 5] and this[this[0] + 0xe]
        thisPtr[newIndex + 5] = 0xe1001;
        thisPtr[thisPtr[0] + 0xe] = 0xe1001;
        // Set byte flag at offset 0x48 + thisPtr[0] from this base
        *(byte *)(thisPtr[0] + 0x48 + (int)thisPtr) = (byte)((thisPtr[0xebe] >> 4) & 1);
    }

    // Extract bit from this[0xebe] (offset 0x2EF8) for use later
    bitFlag = ((thisPtr[0xebe] >> 3) & 1) << 10;

    g_IsFullscreen = 1;  // DAT_0120546c
    // Clamp resolution width to at least 0x34 (maybe 52? or 16:9 scale?)
    if (g_ResolutionWidth < 0x34) {
        g_ResolutionWidth = 0x34;
    }
    // Clamp resolution height to at most 0x34
    if (0x34 < g_ResolutionHeight) {
        g_ResolutionHeight = 0x34;
    }
    // Set another flag
    g_SomeBufferFlag = 1;  // _DAT_011f3aa8

    // Call video/graphics init with parameters (3,1,1)
    FUN_0041e4d0(3, 1, 1);

    finalValue = bitFlag;
    if ((soundEnabled != 0) && (thisPtr[0xe7e] != 1)) {
        if ((thisPtr[0xebe] >> 4) & 1) {
            FUN_0042c700(0x400);  // Enable something
        }
        if ((thisPtr[0xebe] >> 3) & 1) {
            FUN_0042c700(0x200);  // Enable something else
        }
        if ((thisPtr[0xebe] >> 4) & 1) {
            goto LAB_0042cbdb;
        }
        finalValue = 0x400;
    }
    FUN_0042c700(finalValue);

LAB_0042cbdb:
    // Set various config values (possibly screen dimensions and flags)
    if (g_ResolutionWidth < 0x38) {
        g_ResolutionWidth = 0x38;
    }
    if (0x38 < g_ResolutionHeight) {
        g_ResolutionHeight = 0x38;
    }
    g_SomeFlag = 8;  // _DAT_011f3ab8

    if (g_ResolutionWidth < 0x39) {
        g_ResolutionWidth = 0x39;
    }
    if (0x39 < g_ResolutionHeight) {
        g_ResolutionHeight = 0x39;
    }
    g_AnotherFlag = 0;  // _DAT_011f3abc

    if (g_ResolutionWidth < 0x3a) {
        g_ResolutionWidth = 0x3a;
    }
    if (0x3a < g_ResolutionHeight) {
        g_ResolutionHeight = 0x3a;
    }
    g_SomeInt = 0xffffffff;  // _DAT_011f3ac0

    // Repeat clamping to minimum width again
    if (g_ResolutionWidth < 0x34) {
        g_ResolutionWidth = 0x34;
    }
    if (0x34 < g_ResolutionHeight) {
        g_ResolutionHeight = 0x34;
    }

    // Call graphics init again with (1,1,1)
    FUN_0041e4d0(1, 1, 1);

    if (g_ResolutionWidth < 0x34) {
        g_ResolutionWidth = 0x34;
    }
    if (0x34 < g_ResolutionHeight) {
        g_ResolutionHeight = 0x34;
    }
    g_SomeBufferFlag = 0;  // Clear flag

    // Call function with bitFlag (either 0 or 0x400)
    FUN_0042dae0(bitFlag);

    g_IsFullscreen = 0;  // Clear fullscreen flag
    if (g_SomePointer != 0) {
        // Call virtual function at vtable+0x20 (likely a finalize/apply)
        (*(code **)(*g_SomePointer + 0x20))(g_SomePointer);
    }

    // Set another config minimum
    if (g_ResolutionWidth < 0x16) {
        g_ResolutionWidth = 0x16;
    }
    g_LastFlag = 1;  // _DAT_011f3a30
    if (0x16 < g_ResolutionHeight) {
        g_ResolutionHeight = 0x16;
    }
    return;
}