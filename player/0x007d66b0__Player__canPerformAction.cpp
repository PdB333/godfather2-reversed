// FUNC_NAME: Player::canPerformAction
bool __fastcall Player::canPerformAction(int thisPtr)
{
    int playerData = *(int *)(thisPtr + 0x58); // +0x58: mPlayerData
    int actionId = FUN_00798f50(0x41); // likely getActionIdFromInput or similar
    bool isActionBlocked = FUN_0079e920(actionId); // check if action is blocked/disabled
    if (isActionBlocked) {
        int blockReason = FUN_007ab420(0x200000); // get block reason flag
        return blockReason != 0;
    }
    bool isInCutscene = FUN_00481640(); // check if player is in cutscene
    if ((!isInCutscene) || (*(char *)(playerData + 0x2240) != '\0')) { // +0x2240: mForceAllowAction
        return false;
    }
    return true;
}