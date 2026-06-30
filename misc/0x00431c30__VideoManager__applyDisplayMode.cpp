// FUNC_NAME: VideoManager::applyDisplayMode

void __thiscall VideoManager::applyDisplayMode(int param2, int param3)
{
    int *ptr;
    int temp;
    bool toggle;

    FUN_00418360(param3, param2, *(int *)(this + 0x39f8) == 0);  // +0x39f8: isFullscreen flag

    (**(code **)(*(int *)gRenderDevice + 0x18))();  // vtable[0x18] - beginDisplayChange?

    temp = gResolutionWidth;  // DAT_01205440
    ptr = gRenderDevice;      // PTR_DAT_0110b430
    toggle = gResolutionWidth != *(int *)(gRenderDevice + 0x10); // +0x10: currentWidth
    gRenderDevice[0x1b8] = 1;  // +0x1b8: isChangingFlag

    if (toggle)
    {
        *(int *)(ptr + 0x10) = temp;       // +0x10: currentWidth
        *(int *)(ptr + 0x50) = 0;           // +0x50: currentHeight
        if (gRenderDevice == gDisplayDevice)  // DAT_012058e8
        {
            FUN_0060a460(temp);  // setDisplayDeviceWidth
        }
    }

    gIsApplying = 1;  // DAT_0110b438

    if (gResolutionMode < 7)       // DAT_012058d0
        gResolutionMode = 7;
    if (7 < gOtherResolutionMode)   // DAT_00f15988
        gOtherResolutionMode = 7;

    gFirstMode = 0;  // _DAT_011f39f4

    if (gResolutionMode < 22)
        gResolutionMode = 22;
    if (22 < gOtherResolutionMode)
        gOtherResolutionMode = 22;

    gSecondMode = 1;  // _DAT_011f3a30

    FUN_00417cf0(1, 1, 5);  // MessagePump or delay
    FUN_00418600();         // updateResolution?

    temp = gResolutionHeight;  // DAT_0120543c
    ptr = gRenderDevice;

    if (gResolutionMode < 22)
        gResolutionMode = 22;
    if (22 < gOtherResolutionMode)
        gOtherResolutionMode = 22;

    gSecondMode = 2;  // _DAT_011f3a30

    if (gResolutionMode < 7)
        gResolutionMode = 7;
    if (7 < gOtherResolutionMode)
        gOtherResolutionMode = 7;

    gFirstMode = 1;  // _DAT_011f39f4

    toggle = gResolutionHeight != *(int *)(gRenderDevice + 0x10);
    gRenderDevice[0x1b8] = 0;  // clear changing flag

    if (toggle)
    {
        *(int *)(ptr + 0x10) = temp;   // currentWidth = resolutionHeight (?)
        *(int *)(ptr + 0x50) = *(int *)(ptr + 0x1bc); // +0x1bc: maybe oldWidth
        if (gRenderDevice == gDisplayDevice)
        {
            FUN_0060a460(temp);
        }
    }

    gIsApplying = 0;  // DAT_0110b438

    (**(code **)(*(int *)gRenderDevice + 0x20))();  // vtable[0x20] - endDisplayChange?
    FUN_0041dfd0(0);  // finalize?
}