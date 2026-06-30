// FUNC_NAME: initializeDebugOverlay
// Address: 0x0069d2d0
// Role: One-time initialization of debug overlay system; sets overlay type and mode based on flags, stores overlay handle at offset 0x540 in manager object.

void initializeDebugOverlay(void)
{
    int iOverlayType;
    char cFlagA, cFlagB;
    int iOverlayHandle, iMode;

    // Static globals from Ghidra data imports
    // DAT_012233b4 -> s_pDebugOverlayManager (pointer to manager object)
    // DAT_01129faf -> s_bDebugOverlayInitialized (bool, non-zero if already done)
    // DAT_01129fad -> s_bUseAdvancedOverlay (bool, selects advanced overlay type)

    iVar1 = DAT_012233b4;
    if ((DAT_01129faf == '\0') && (DAT_012233b4 != 0))
    {
        // Determine overlay type: 6 (normal) or 0x16 (advanced) if flag set
        iOverlayType = 6;
        if (DAT_01129fad != '\0')
        {
            iOverlayType = 0x16;
        }

        // Get some handle (likely renderer ID or allocation) and store at offset 0x540 in manager
        iOverlayHandle = FUN_0069d500(); // getOverlayHandle()
        *(int *)(iVar1 + 0x540) = iOverlayHandle; // +0x540: overlayHandle

        // Set primary overlay state with type
        FUN_0040f900(3, iOverlayType); // setOverlayState(3, overlayType)

        // Query two boolean flags from external modules
        cFlagA = FUN_00496940(); // isDebugFeatureAEnabled()
        cFlagB = FUN_004969c0(); // isDebugFeatureBEnabled()

        // Compute mode: bitwise combination of flags
        // ( ( -FlagB & 0xFFFFFFFC ) + 8 ) | ( 2 - FlagA )
        // This forms a mode value for secondary overlay state
        iMode = ((-(uint)(cFlagB != '\0')) & 0xfffffffc) + 8 | (2 - (cFlagA != '\0'));
        FUN_0040f900(2, iMode); // setOverlayState(2, mode)

        // Mark as initialized
        DAT_01129faf = '\x01';
    }
    return;
}