// FUNC_NAME: EffectManager::drawQuadEffect
// Address: 0x00938c40
// Draws a full-screen quad effect using the SM_QuadEffectClass shader.
// Likely part of the post-processing or transition effect system.

void EffectManager::drawQuadEffect(uint64_t* param_1)
{
    // Extract two 2D coordinates from the 128-bit input.
    // Each 64-bit element holds a packed 32-bit x,y.
    float x1 = (float)(uint64_t)*param_1;                    // low 32 bits of param_1[0]
    float y1 = (float)((uint64_t)*param_1 >> 32);            // high 32 bits of param_1[0]
    float x2 = (float)param_1[1];                            // low 32 bits of param_1[1]
    float y2 = (float)((uint64_t)param_1[1] >> 32);          // high 32 bits of param_1[1]

    // Set up rendering state for the quad effect.
    // The function call likely prepares the vertex buffer or sets up a quad.
    FUN_0060ddf0((int)x1, (int)y1, (int)x2, (int)y2, 0, 0x3f800000); // 0x3f800000 = 1.0f (alpha?)

    // Set render target or depth buffer flags.
    // These globals likely control render target indices (e.g., RT0, RT1).
    if (DAT_012058d0 < 14) {
        DAT_012058d0 = 14;
    }
    if (14 < DAT_00f15988) {
        DAT_00f15988 = 14;
    }
    _DAT_011f3a10 = 0;  // disable something

    if (DAT_012058d0 < 7) {
        DAT_012058d0 = 7;
    }
    if (7 < DAT_00f15988) {
        DAT_00f15988 = 7;
    }
    _DAT_011f39f4 = 0;  // disable another thing

    // Get the quad effect class and its vtable.
    uint32_t effectID = FUN_0060d740("SM_QuadEffectClass"); // possible string hashing or lookup
    int* vtablePtr = (int*)FUN_00611d30(effectID);          // get instance or class pointer

    // Set render state (e.g., disable depth, set blending mode)
    FUN_00611b50(6);  // 6 might be a state index

    // Bind something (shader? texture?) from global data.
    FUN_00611750(*(uint32_t*)(DAT_011298a0 + 0x90)); // +0x90 is likely a resource handle

    // Call virtual function at vtable offset 0x18 (likely "preRender" or "activate")
    (*(void (**)(void))(*vtablePtr + 0x18))();

    // Set transformation or color using global constants.
    FUN_006105e0(_DAT_00e56790, _DAT_00e56794, _DAT_00e56798, _DAT_00e5679c); // color/position

    // Call virtual function at vtable offset 0x20 (likely "render" or "draw")
    (*(void (**)(void))(*vtablePtr + 0x20))();

    // Unbind resources.
    FUN_00611750(0);

    // Restore render target flags to previous values.
    if (DAT_012058d0 < 14) {
        DAT_012058d0 = 14;
    }
    if (14 < DAT_00f15988) {
        DAT_00f15988 = 14;
    }
    _DAT_011f3a10 = 1;  // re-enable

    if (DAT_012058d0 < 7) {
        DAT_012058d0 = 7;
    }
    if (7 < DAT_00f15988) {
        DAT_00f15988 = 7;
    }
    _DAT_011f39f4 = 1;  // re-enable

    // Draw the quad (full-screen) with identity transform and white color.
    FUN_0060db60(0, 0, 0, 0x3f800000, 0x3f800000); // last two are 1.0f (scale/alpha)
}