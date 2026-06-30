// FUNC_NAME: PlayerManager::updateEntityList
void __thiscall PlayerManager::updateEntityList(int entityList[2]) // entityList[0] = array of entity pointers, entityList[1] = count
{
    int count = entityList[1];
    while (count-- > 0)
    {
        int entity = entityList[0][count]; // +0x00

        // Get the local player or game state object (global singleton)
        int localPlayer = FUN_00791300(); // possibly PlayerManager::getLocalPlayer or GameState::get()

        // If no local player OR local player has bit 0x19 (bit 25) set at +0x1f58 (e.g., isDead or isInactive)
        if (localPlayer == 0 || ((*(uint*)(localPlayer + 0x1f58) >> 0x19) & 1) != 0)
        {
            // Check entity state flags at +0x5c
            if ((*(uint*)(entity + 0x5c) & 0x60000) == 0) // bits 17,18 NOT set (e.g., not under special control)
            {
                // If local player is valid and has the "inactive" flag set
                if (localPlayer != 0 && ((*(uint*)(localPlayer + 0x1f58) >> 0x19) & 1) != 0)
                {
                    // Call something on localPlayer + 0x3c (maybe a mutex or state transition)
                    FUN_004088c0(localPlayer + 0x3c); // likely localPlayer->lock() or localPlayer->activate()
                }

                // If this->field_0xfc is non-zero (maybe pointer to a sub-system)
                if (*(int*)(this + 0xfc) != 0)
                {
                    FUN_006bf230(entity); // e.g., processEntityAction(entity)
                }

                // Get another global singleton (e.g., NetworkManager or ScenarioManager)
                int scenario = FUN_007915b0(); // possibly ScenarioManager::get()

                // Compare scenario's field +0x54 with this->field_0x40 (e.g., mission ID or scenario state)
                if (*(int*)(scenario + 0x54) == *(int*)(this + 0x40))
                {
                    FUN_008c2ab0(this, entity); // handle matched scenario
                }
                else
                {
                    FUN_008c29f0(this, entity); // handle non-matched scenario
                }
            }
            else
            {
                // Entity has 0x60000 bits set -> mark it with 0x40000000 (bit 30) as "to be removed" or "pending"
                *(uint*)(entity + 0x5c) |= 0x40000000;
            }
        }
    }
}