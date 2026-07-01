// FUNC_NAME: PlayerInputHandler::canUsePDT_Assault
__fastcall uint8_t PlayerInputHandler::canUsePDT_Assault(int32_t this)
{
    char cVar1;
    uint8_t bVar2;
    int32_t iVar3;
    uint32_t uVar4;
    uint8_t local_1d;
    uint32_t local_1c;
    uint32_t uStack_10;
    uint64_t local_c;
    int32_t local_4;

    local_1d = 0;
    // Check global flag and player state pointer
    if ((DAT_0112a838 != 0) && (*(int32_t *)(DAT_0112a838 + 0x5c) != 0)) {
        return 0;
    }
    // Get player controller data
    iVar3 = getPlayerController(); // FUN_007ab140
    // Check player state flags: isPaused? Other conditions
    if ((((*(uint8_t *)(iVar3 + 4) & 0x10) != 0) &&
        // Check if player is in a cutscene or weapon restriction
        (((iVar3 = isCutsceneActive(), iVar3 == 0 || // FUN_00800a90
          ((*(uint32_t *)(*(int32_t *)(this + 0x58) + 0x8e0) >> 10 & 1) == 0)) &&
         // Check if player is not in a specific state (e.g., climbing)
         (cVar1 = isPlayerOnGround(), cVar1 != '\0')))) && // FUN_007ab560
        // Check some other condition (maybe currently in animation)
        ((cVar1 = isPlayerDoingAction(), cVar1 == '\0' && // FUN_007abd90
         (*(int32_t *)(*(int32_t *)(this + 0x58) + 0x8e8) < 0))))
    {
        // Check weapon availability for slots 5 and 6?
        uVar4 = getWeaponAtSlot(5); // FUN_00798f50
        bVar2 = isWeaponEquipped(uVar4); // FUN_0079e970
        uVar4 = getWeaponAtSlot(6); // FUN_00798f50
        cVar1 = isWeaponEquipped(uVar4); // FUN_0079e970
        if ((bVar2 == 0) && (cVar1 == '\0')) {
            return 0;
        }
        local_1d = 1;
        // Optionally log the action
        cVar1 = isDebugModeActive(); // FUN_00481660
        if (cVar1 != '\0') {
            local_1c = (local_1c & 0x00FFFFFF) | 0x01000000;
            logWeaponSwitch(0x10, // FUN_0079fb90
                            (2 << 16) | local_1c,
                            uStack_10,
                            local_c,
                            local_4);
        }
    }
    return local_1d;
}