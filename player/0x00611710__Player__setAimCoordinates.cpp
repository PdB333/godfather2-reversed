// FUNC_NAME: Player::setAimCoordinates
void __thiscall Player::setAimCoordinates(int* thisPtr, int param2, int param3)
{
    // +0xF4: target X (or yaw)
    // +0xF8: target Y (or pitch)
    *(int*)(thisPtr + 0xF4) = param2;
    *(int*)(thisPtr + 0xF8) = param3;

    // Global singleton check (g_pPlayer at 0x012058E8)
    if (g_pPlayer == thisPtr) {
        // Update aiming system: obj at +0x14, oldCoords at +0xF0, newCoords pointer at +0xF4
        FUN_0060ac80(*(int*)(thisPtr + 0x14), *(int*)(thisPtr + 0xF0), (int*)(thisPtr + 0xF4));
    }
}