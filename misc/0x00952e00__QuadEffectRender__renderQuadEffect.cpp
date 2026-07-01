// FUNC_NAME: QuadEffectRender::renderQuadEffect
// Function address: 0x00952e00
// This function renders a screen-space quad effect (e.g., a fullscreen overlay or UI element).
// It temporarily reduces rendering quality limits (global thresholds) to 0xe (14) and 7,
// then restores them after drawing the effect. The effect class is identified by "SM_QuadEffectClass".

void QuadEffectRender::renderQuadEffect(int32_t renderState)
{
    int32_t* vtablePtr;

    // Clamp global detail limits to 0xe (14) and 7
    if (DAT_012058d0 < 0xe) {
        DAT_012058d0 = 0xe;
    }
    if (0xe < DAT_00f15988) {
        DAT_00f15988 = 0xe;
    }
    _DAT_011f3a10 = 0; // Disable high-detail rendering

    if (DAT_012058d0 < 7) {
        DAT_012058d0 = 7;
    }
    if (7 < DAT_00f15988) {
        DAT_00f15988 = 7;
    }
    _DAT_011f39f4 = 0; // Disable low-detail rendering

    // Lookup the quad effect class instance
    undefined4 classId = FUN_0060d740("SM_QuadEffectClass");
    vtablePtr = (int32_t*)FUN_00611d30(classId); // vtable pointer of the effect object

    // Set up rendering state and call virtual functions
    FUN_00611b50(6); // Possibly set render order or depth
    FUN_00611750(renderState); // Set rendering flags

    // Call virtual method at offset 0x18 (likely "begin" or "start")
    (*(void (**)(void))(*vtablePtr + 0x18))();

    // Set projection/viewport parameters (x, y, width, height)
    FUN_006105e0(_DAT_00e57400, _DAT_00e57404, _DAT_00e57408, _DAT_00e5740c);

    // Call virtual method at offset 0x20 (likely "end" or "render")
    (*(void (**)(void))(*vtablePtr + 0x20))();

    // Restore rendering state
    FUN_00611750(0);

    // Restore global detail limits
    if (DAT_012058d0 < 0xe) {
        DAT_012058d0 = 0xe;
    }
    if (0xe < DAT_00f15988) {
        DAT_00f15988 = 0xe;
    }
    _DAT_011f3a10 = 1; // Re-enable high-detail

    if (DAT_012058d0 < 7) {
        DAT_012058d0 = 7;
    }
    _DAT_011f39f4 = 1; // Re-enable low-detail
    if (7 < DAT_00f15988) {
        DAT_00f15988 = 7;
    }
}