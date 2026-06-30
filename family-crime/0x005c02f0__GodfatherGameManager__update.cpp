// FUNC_NAME: GodfatherGameManager::update
// Address: 0x005c02f0
// Lazy singleton initialization and per-frame update.

extern GodfatherGameManager* g_theGodfatherGameManager; // global DAT_01205664

void GodfatherGameManager::update()
{
    // First-time initialization
    if (g_theGodfatherGameManager == NULL)
    {
        int allocResult = FUN_005c4410(200, 0); // allocate manager memory block (200 bytes)
        if (allocResult != 0)
        {
            g_theGodfatherGameManager = (GodfatherGameManager*)FUN_005c3070(); // construct manager instance
        }
        FUN_005c31d0(); // post-construction initialization
    }

    // Per-frame update
    FUN_005c28c0(); // update game logic
}