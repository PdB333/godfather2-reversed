// FUNC_NAME: getCurrentPlayerStat
// Address: 0x0065d3a0
// Role: Retrieves an integer value from the active player by chaining three virtual getters:
//   globalSingleton->getManager()->getComponent()->getValue().
// Returns 0 if any pointer in the chain is null.

int getCurrentPlayerStat()
{
    // Retrieve global game manager singleton (e.g., GodfatherGameManager or SimManager)
    void* gameManager = FUN_00ad8d40();
    if (gameManager == nullptr)
        return 0;

    // Virtual call at vtable+0x34: get a manager (e.g., PlayerManager)
    typedef void* (__thiscall* GetManagerFunc)(void*);
    void* playerManager = ((GetManagerFunc)(*(uint32_t*)gameManager + 0x34))(gameManager);
    if (playerManager == nullptr)
        return 0;

    // Virtual call at vtable+0x24: get a player or component (e.g., Player)
    typedef void* (__thiscall* GetComponentFunc)(void*);
    void* player = ((GetComponentFunc)(*(uint32_t*)playerManager + 0x24))(playerManager);
    if (player == nullptr)
        return 0;

    // Virtual call at vtable+0x18: get the integer value (e.g., health, reputation, ammo)
    typedef int (__thiscall* GetValueFunc)(void*);
    int value = ((GetValueFunc)(*(uint32_t*)player + 0x18))(player);

    return value;
}