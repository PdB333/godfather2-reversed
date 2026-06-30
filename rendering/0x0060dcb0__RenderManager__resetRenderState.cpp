// FUNC_NAME: RenderManager::resetRenderState
void __fastcall RenderManager::resetRenderState(uint param_1)
{
    uint uVar1;
    uint uVar2;
    
    uVar2 = DAT_011f3914;
    uVar1 = DAT_011f3910;
    DAT_011f3910 = DAT_012058a8; // Current render target
    DAT_011f3914 = 0;
    FUN_00609340(4, uVar1, uVar2, param_1); // SetRenderTarget(4, ...)
    FUN_0060dc10(); // ClearRenderState()
    uVar2 = DAT_011f3914;
    uVar1 = DAT_011f3910;
    DAT_011f3910 = DAT_012058a8;
    DAT_011f3914 = 0;
    FUN_00609340(4, uVar1, uVar2); // SetRenderTarget(4, ...)
    uVar2 = DAT_011f38f4;
    uVar1 = DAT_011f38f0;
    DAT_011f38f0 = DAT_012058a4; // Current depth/stencil buffer
    DAT_011f38f4 = 0;
    FUN_00609340(0, uVar1, uVar2); // SetDepthStencil(0, ...)
    FUN_0060db60(0, 0, 0, 0x3f800000, 0x3f800000); // SetViewport(0, 0, 0, 1.0f, 1.0f)
    return;
}