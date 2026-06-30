// FUNC_NAME: Presentation::initDebug
void Presentation::initDebug(void)
{
    int iVar1;
    char isDebug;
    char isVerbose;
    undefined4 renderDevice;
    undefined4 msgId;

    iVar1 = g_pPresentation; // DAT_012233b4
    if ((g_bDebugInit == 0) && (g_pPresentation != 0)) {
        msgId = 6;
        if (g_bExtraDebug != 0) {
            msgId = 0x16;
        }
        renderDevice = FUN_0069d500(); // likely Presentation::getRenderDeviceHandle
        *(undefined4 *)(iVar1 + 0x540) = renderDevice; // store render device handle at offset 0x540
        FUN_0040f900(3, msgId); // debugPrint(3, msgId) - maybe print initialization message
        isDebug = FUN_00496940(); // likely Presentation::isDebugMode
        isVerbose = FUN_004969c0(); // likely Presentation::isVerboseMode
        // Compute flags: (isVerbose ? 4 : 8) | (2 - isDebug)
        // Result: 5 if both true, 6 if debug only, 9 if verbose only, 10 if none
        FUN_0040f900(2, ((-(uint)(isVerbose != 0) & 0xFFFFFFFC) + 8) | (2 - (isDebug != 0)));
        g_bDebugInit = 1;
    }
    return;
}