// FUNC_NAME: Player::canPerformAction
// Address: 0x0078a7d0
// Checks if the player can perform an action based on state flags, game state, and a virtual function result.

int __fastcall Player::canPerformAction(Player* this) {
    int iVar2;
    char cVar1;

    // Check if the player's state machine/component pointer is null
    if (*(int*)((int)this + 0x5c) == 0) {
        iVar2 = 0;
    } else {
        // Query global game state (e.g., input mode, cutscene flag)
        iVar2 = FUN_0043b870(DAT_0112af58);
    }

    // Condition: if state machine exists and flags at +0x1f98 have certain bits set,
    // and not in a specific state (FUN_00898330 with param 2), and game is not paused (FUN_0071fa50),
    // OR if global condition is true and another condition (FUN_00782ce0) is true,
    // and finally the player is controllable (FUN_00730210 returns 0).
    if ((((((*(uint*)(*(int*)((int)this + 0x5c) + 0x1f98) & 0xd1c) != 0) &&
          (cVar1 = FUN_00898330(*(int*)((int)this + 0x5c), 2), cVar1 == '\0')) &&
         (cVar1 = FUN_0071fa50(), cVar1 == '\0')) ||
        ((iVar2 != 0 && (cVar1 = FUN_00782ce0(), cVar1 != '\0')))) &&
       (cVar1 = FUN_00730210(), cVar1 == '\0')) {
        // Call virtual function at vtable+0xc0 (likely returns a float like cooldown or progress)
        (**(code**)(**(int**)((int)this + 0x5c) + 0xc0))();
        if ((float10)0 < extraout_ST0) {
            return 1;
        }
    }
    return 0;
}