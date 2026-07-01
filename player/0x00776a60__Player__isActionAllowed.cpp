// FUNC_NAME: Player::isActionAllowed
bool __thiscall Player::isActionAllowed() {
    char cVar1;
    int iVar2;
    int iVar3;
    byte bVar4;

    // Check bit 6 of flags at +0xAC: if clear, allow by default
    bVar4 = ~(*(uint *)(this + 0xAC) >> 6) & 1;
    iVar3 = *(int *)(this + 0x5C); // some pointer, possibly a sound or effect handle

    // If bit 10 is set, override with more complex logic
    if ((*(uint *)(this + 0xAC) >> 10 & 1) != 0) {
        bVar4 = 0;
        // Check target pointer at +0x70; 0x48 might be a sentinel value
        if ((*(int *)(this + 0x70) != 0) && (*(int *)(this + 0x70) != 0x48)) {
            // Compute base pointer by subtracting 0x48 (size of some structure?)
            if (*(int *)(this + 0x70) == 0) {
                iVar2 = 0;
            } else {
                iVar2 = *(int *)(this + 0x70) - 0x48;
            }
            // Check a flag at +0xA9C in the target's base and a global ability check
            if ((*(int *)(iVar2 + 0xA9C) != 0) && (FUN_0085e090(10) != '\0')) {
                bVar4 = 1;
            }
        }
        if (bVar4 == 0) {
            // Action not allowed: stop sound if pointer is valid
            if (iVar3 != 0) {
                FUN_0043b870(DAT_0113105c); // likely gSoundManager
            }
            // Check two global conditions; if both true, return 0 (blocked)
            iVar3 = FUN_009b2910();
            if ((iVar3 != 0) && (iVar3 = FUN_007ff880(), iVar3 != 0)) {
                return 0;
            }
            return 1;
        }
    }
    return bVar4;
}