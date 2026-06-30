// FUNC_NAME: GameManager::updateActiveComponents

extern float g_currentGameTime;  // 0x00e44598
extern float g_lastUpdateTime;   // 0x012067e8
extern float g_timeScaleFactor;  // 0x00e2b1a4

void __thiscall GameManager::updateActiveComponents(void) {
    if (g_currentGameTime <= g_lastUpdateTime) {
        // Array descriptor: pointer to { int* data; int count; }
        int* arrayBase = **(int**)((char*)this + 4);
        int elementCount = *((int*)(*(int**)((char*)this + 4)) + 1);
        int currentEntry = (int)arrayBase;
        int endEntry = (int)arrayBase + elementCount * 0x70;
        float timeStep = g_timeScaleFactor / g_lastUpdateTime;

        while (currentEntry != endEntry) {
            // At offset 0x40: pointer to a component object
            int* componentPtr = *(int**)(currentEntry + 0x40);
            // +0x8 of component: non-zero indicates active/needs update
            if (*(int*)(componentPtr + 8) != 0) {
                FUN_005570a0(componentPtr, timeStep);
            }
            currentEntry += 0x70;
        }
    }
}