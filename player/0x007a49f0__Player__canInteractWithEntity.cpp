// FUNC_NAME: Player::canInteractWithEntity
// Address: 0x007a49f0
// Returns 1 if the player can interact with the specified target entity, 0 otherwise.
bool __thiscall Player::canInteractWithEntity(int targetEntity)
{
    char result = 0;

    Player* localPlayer = (Player*)FUN_0079d7c0(); // getLocalPlayer()
    if (localPlayer != nullptr && targetEntity != -0x3ac) // -0x3ac is sentinel for no target
    {
        void* interactionConfig = (void*)FUN_00625050(0xb47bb605, 0); // hash for interaction config/manager
        if (interactionConfig != nullptr)
        {
            char relationship = FUN_007cbcd0(targetEntity, localPlayer, 1, 0); // check target-player relation
            if (relationship != 0)
            {
                char deadState = FUN_00898330(localPlayer, 2); // player state check (e.g., dead = 2)
                if (deadState == 0)
                {
                    result = 1;
                    // Check player flags at offset 0x1f98 (e.g., driving, in conversation)
                    if ((*(uint*)((int)localPlayer + 0x1f98) & 0x110c) != 0)
                    {
                        char globalBlock = FUN_0071fa50(); // e.g., menu open, cinematic
                        if (globalBlock != 0)
                            return 0;
                    }
                }
            }
        }
    }
    return result;
}