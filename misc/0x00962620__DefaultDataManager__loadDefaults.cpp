// FUNC_NAME: DefaultDataManager::loadDefaults
void __fastcall DefaultDataManager::loadDefaults(DefaultDataManager* this)
{
    // Get pointer to the global default data (20 dwords = 80 bytes)
    uint32* globalDefaults = (uint32*)GetGlobalDefaultData(); // FUN_008a2d90

    // Copy the default data to this object
    for (int i = 0; i < 20; i++)
    {
        *(uint32*)((char*)this + i * 4) = globalDefaults[i];
    }
    return;
}