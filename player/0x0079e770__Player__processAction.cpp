//FUNC_NAME: Player::processAction
void __thiscall Player::processAction(int thisPtr, uint actionFlags)
{
    char isGameActive;
    bool bVar3;
    int iVar2;

    isGameActive = FUN_00481660(); // likely isGameActive()
    if (isGameActive != '\0') {
        if ((actionFlags & 2) != 0) {
            bVar3 = false;
            // Check if this player is alive and not in a special state
            if ((*(char *)(thisPtr + 0x109) != '\0') && // +0x109: isAlive
                (bVar3 = (bool)(*(byte *)(thisPtr + 0x2447) & 1), bVar3 == false) && // +0x2447: bit0 = isInVehicle? isStunned?
                (thisPtr != -0x354) && // sentinel check (invalid pointer?)
                (iVar2 = FUN_00625050(0x12f25c12, 0), iVar2 != 0)) // get global object by hash
            {
                bVar3 = (*(byte *)(iVar2 + 0xc4) & 6) != 0; // +0xc4: bit1 and bit2 set = some condition
            }
            // Conditions that block the action (clear bit 1)
            if (((((*(int *)(thisPtr + 0x10) != 0) && (*(int *)(thisPtr + 0x10) != 0x48)) || // +0x10: state, 0x48 = STATE_DEAD?
                 ((cVar1 = FUN_007f47a0(), cVar1 != '\0' || // isCutscenePlaying?
                  ((*(char *)(thisPtr + 0x2418) == '\0' || (*(char *)(thisPtr + 0x23fc) == '\0')))))) || // +0x2418, +0x23fc: flags
                ((*(char *)(thisPtr + 0x109) != '\0' && (bVar3 == false)))) || // alive but condition not met
               ((cVar1 = FUN_00690210(5), cVar1 != '\0' || // isTutorialActive?
                (cVar1 = FUN_00690150(0x17), cVar1 != '\0')))) // isMissionActive?
            {
                actionFlags = actionFlags & 0xfffffffd; // clear bit 1 (disallow action)
            }
        }
        if (actionFlags != 0) {
            FUN_007f9970(actionFlags); // dispatch action
        }
    }
    return;
}