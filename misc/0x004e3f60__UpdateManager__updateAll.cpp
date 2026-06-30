// FUNC_NAME: UpdateManager::updateAll
void UpdateManager::updateAll(void)
{
    int i;
    
    i = 0;
    if (0 < g_updateCount) {
        do {
            // Call virtual update method at vtable offset 0x20
            (**(code **)(g_updateList[i] + 0x20))();
            i = i + 1;
        } while (i < g_updateCount);
    }
    // Additional update for another subsystem
    FUN_0052e5f0();
    return;
}