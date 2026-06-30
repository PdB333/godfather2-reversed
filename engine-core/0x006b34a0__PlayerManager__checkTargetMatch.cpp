// FUNC_NAME: PlayerManager::checkTargetMatch
bool __fastcall PlayerManager::checkTargetMatch(void* thisPtr)
{
    // Global pointer to player manager singleton (DAT_012233a0)
    // Offset +0x4 holds a pointer to the player's data block (pPlayerData)
    int* pPlayerData = *(int**)(*(int*)0x012233a0 + 4);

    // Return false if no player data or if the pointer equals a sentinel value (0x1f30)
    if (pPlayerData == nullptr || pPlayerData == (int*)0x1f30)
        return false;

    // Compare the player's target ID (at offset -0x48 from pPlayerData) with this object's ID (at +0x38)
    if (*(int*)(pPlayerData - 0x48) == *(int*)((char*)thisPtr + 0x38))
        return true;

    // If player has no target and this object has a valid target flag (at +0xd4), try to acquire it
    if (*(int*)(pPlayerData - 0x48) == 0 && *(int*)((char*)thisPtr + 0xd4) != 0)
    {
        // Call target acquisition function with base player pointer, global target list, and flag
        return FUN_006aecf0(pPlayerData - 0x1f30, DAT_00d5e20c, 1);
    }

    return false;
}