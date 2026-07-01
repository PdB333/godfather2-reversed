// FUNC_NAME: MinimapRenderer::renderMinimap
void MinimapRenderer::renderMinimap(int param_1, int param_2, int param_3, int param_4, int param_5)
{
    int iVar1;
    float local_a4;
    float local_a0;
    float local_9c;
    float local_98;
    float local_94;
    char local_90[64];
    char local_50[76];

    iVar1 = FUN_005c5aa0(); // Get some game object (likely player or camera)
    local_98 = *(float *)(iVar1 + 0x30); // +0x30: x position
    local_9c = *(float *)(iVar1 + 0x34); // +0x34: y position
    local_a0 = 0.0;
    FUN_0059fa10("mmap/minimap._xscale", &local_a0); // Get minimap x scale
    local_a4 = 0.0;
    FUN_0059fa10("mmap/minimap._width", &local_a4); // Get minimap width
    if ((0.0 < local_a0) && (0.0 < local_a4)) {
        FUN_00614440(*(undefined4 *)(param_3 + 0x20), *(undefined4 *)(param_3 + 0x24),
                     *(undefined4 *)(param_3 + 0x2c), *(undefined4 *)(param_3 + 0x28), local_90, 0);
        FUN_0093fac0(local_50); // Initialize some structure
        local_94 = (local_a4 / local_a0) * DAT_00d5efa4; // Calculate scale factor
        FUN_0094baf0(local_50, param_2, local_94 + local_98, local_94 + local_9c, local_94, param_4, param_5,
                     DAT_01130618, DAT_01130614);
    }
    return;
}