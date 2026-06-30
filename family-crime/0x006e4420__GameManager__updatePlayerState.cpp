// FUNC_NAME: GameManager::updatePlayerState
void __thiscall GameManager::updatePlayerState(void)
{
    int iVar1;
    void **outPtr;
    int local_ESI;

    // +0x100: pointer to some data manager (e.g., EntityDataManager)
    void *pManager = *(void **)((int)this + 0x100);
    outPtr = (void **)0x0;
    // Virtual function at +0x10 on the manager; presumably a "getObjectByHash" call
    // Using hash 0x383225a1 (likely hash for 'playerState' or similar)
    bool bFound = (**(bool (__thiscall **)(void *, int, void ***))pManager)(0x383225a1, &outPtr);
    if ((bFound) && (local_ESI != 0)) {
        // local_ESI likely a global (e.g., the active player object)
        *outPtr = *(void **)(local_ESI + 0x28d0);
    } else {
        // Fallback: use default state from the manager at offset 0x1f90
        *outPtr = *(void **)((int)pManager + 0x1f90);
    }
    return;
}