// FUNC_NAME: Player::processFlaggedAction
void __thiscall Player::processFlaggedAction(void) {
    int targetValid;
    // +0x1f98: flag byte, bit 2 and 3 indicate some combined state (e.g. in cover + aiming)
    if ((*(unsigned char *)(this + 0x1f98) & 0xC) != 0) {
        // +0x2134: handle/pointer to target object (e.g. enemy, interactable)
        targetValid = FUN_006b0ee0(*(unsigned int *)(this + 0x2134));
        if (targetValid != 0) {
            // Hash 0x637b907 likely corresponds to a script event (e.g. "attack_initiated" or "cover_break")
            FUN_006b68c0(0x637b907, 1, 0, 0);
        }
        {
            struct {
                unsigned int id; // from global DAT_0112a5f8 (e.g. script function ID)
                int zero1;
                int zero2;
            } localData = { DAT_0112a5f8, 0, 0 };
            // Call script engine with this ID and flag 0 (maybe execute immediately)
            FUN_00408a00(&localData, 0);
        }
    }
}