// FUNC_NAME: SimManager::updateEntityTimers
void __thiscall SimManager::updateEntityTimers(void* thisPtr)
{
    int entityIndex;
    int* entityPtr;
    int baseTimer;

    entityIndex = getNextActiveEntityIndex(&stackLocal); // FUN_00949380, returns index or -1
    if (entityIndex >= 0)
    {
        // thisPtr+0x60 points to an array of 8-byte entries; each entry's second DWORD is an entity pointer
        entityPtr = *(int**)(*(int*)((char*)thisPtr + 0x60) + 4 + entityIndex * 8);
        baseTimer = *(int*)((char*)entityPtr + 0x1a4); // base cooldown/timer value
        if (baseTimer != 0)
        {
            // Update next fire time by adding global frame delta
            *(int*)((char*)entityPtr + 0x1a8) = baseTimer + gFrameDeltaTime; // DAT_01205224
        }
    }
}