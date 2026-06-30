// FUNC_NAME: ScreenSpaceEffect::init
void __fastcall ScreenSpaceEffect::init(void)
{
    // Call base class initialization (likely sets up vtable or default state)
    FUN_006127d0();

    // Load four effect/shader objects from global handles
    // Store them at known offsets in this object
    // +0xC4: effect for first pass (PTR_DAT_010bea20)
    *(undefined4 *)(this + 0xC4) = FUN_0060a2e0(&PTR_DAT_010bea20);

    // +0xC8 (200): effect for second pass (PTR_DAT_010bea30)
    *(undefined4 *)(this + 0xC8) = FUN_0060a2e0(&PTR_DAT_010bea30);

    // +0xCC: effect for third pass (PTR_DAT_010bea40)
    *(undefined4 *)(this + 0xCC) = FUN_0060a2e0(&PTR_DAT_010bea40);

    // +0xD0: effect for fourth pass (PTR_DAT_010bea50)
    *(undefined4 *)(this + 0xD0) = FUN_0060a2e0(&PTR_DAT_010bea50);

    // Retrieve parameter handles from the respective effects
    // +0xBC: screen_color parameter from the global render effect (DAT_012198f8)
    *(undefined4 *)(this + 0xBC) = FUN_0060a580(DAT_012198f8, "screen_color");

    // +0xA8: depth_texture parameter from the fourth effect (+0xD0)
    *(undefined4 *)(this + 0xA8) = FUN_0060a580(*(undefined4 *)(this + 0xD0), "depth_texture");

    // +0xAC: dof_params parameter from the fourth effect (+0xD0)
    *(undefined4 *)(this + 0xAC) = FUN_0060a580(*(undefined4 *)(this + 0xD0), "dof_params");

    // +0xB0: alphaScale1_alphaScale2_alphaDelta_notused parameter from the second effect (+0xC8)
    *(undefined4 *)(this + 0xB0) = FUN_0060a580(*(undefined4 *)(this + 0xC8), "alphaScale1_alphaScale2_alphaDelta_notused");

    // +0xB4: imageSizeXY_centerZoom parameter from the first effect (+0xC4)
    *(undefined4 *)(this + 0xB4) = FUN_0060a580(*(undefined4 *)(this + 0xC4), "imageSizeXY_centerZoom");

    // +0xB8: imageSizeXY_centerZoom parameter from the second effect (+0xC8)
    *(undefined4 *)(this + 0xB8) = FUN_0060a580(*(undefined4 *)(this + 0xC8), "imageSizeXY_centerZoom");

    return;
}