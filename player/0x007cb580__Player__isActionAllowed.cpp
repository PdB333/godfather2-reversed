// FUNC_NAME: Player::isActionAllowed
bool __fastcall Player::isActionAllowed(int this_) // param_1 is this pointer
{
    bool bVar1;
    int iVar2;
    float fVar3;

    // Try to allocate 44 bytes (0x2c) for some internal object
    iVar2 = FUN_00798f50(0x2c);
    bVar1 = FUN_0079e970(iVar2);
    if (!bVar1) {
        return false;
    }

    // Check global game manager flag at offset +0x5c, bit 0xf (0x8000)
    // If set (e.g., loading, cutscene?), disallow action
    if ((*(uint *)(DAT_01129c4c + 0x5c) >> 0xf & 1) != 0) {
        return false;
    }

    // Check two cheat/debug flags
    bVar1 = FUN_007ab420(0x1000); // e.g., cheatFlag1
    if (bVar1) {
        return true;
    }
    bVar1 = FUN_007ab420(0x40000000); // e.g., cheatFlag2
    if (bVar1) {
        return true;
    }

    // Check player-specific flag at this+0x1d0, bit 9 (0x200)
    if (((*(uint *)(this_ + 0x1d0) >> 9 & 1) != 0) &&
        // Additional condition: some float from game time/distance
        // FUN_0040aa10 returns a float, compared with a global threshold
        (fVar3 = FUN_0040aa10(), fVar3 <= (float)DAT_00e44598)) {
        return true;
    }

    return false;
}