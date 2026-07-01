// FUNC_NAME: EntityBase::synchronizeGameTime
// 0x008808c0 - Synchronizes game time scale and pause state from global simulation manager to this entity.
// The function queries the simulation manager singleton for current time scale and pause flag,
// then applies them to the entity via setTimeScale and setPaused. Returns 2 to indicate success.

// External global: pointer to a manager singleton struct (e.g., SimulationManager)
// Offset +0x4 is the actual manager pointer (checked for non-null and not 0x1f30 magic)
extern int* g_simManagerStruct; // actually DAT_012233a0

// Virtual function offsets for the simulation manager object
// vtable[0x1a8] -> float getTimeScale()
// vtable[?] -> bool isPaused()

// External functions
extern void* FUN_007ff880(); // returns pointer to simulation manager singleton (?) -> actually SimulationManager::instance()
extern char* FUN_00549a40(char* buffer); // checks a global pause state, returns pointer to status string (non-empty = paused)
extern void FUN_00625c40(void* entity, float timeScale); // set time scale
extern void FUN_00625df0(void* entity, int isPaused);   // set paused flag

// Reconstructed function
int EntityBase::synchronizeGameTime(void* thisObject) {
    int* managerPtr;        // piVar1
    char pauseFlagBuffer[1]; // uStack_5
    float timeScale = 0.0f; // local_4
    int isPaused = 0;       // uVar3

    // Check if the global simulation manager pointer is valid and not a sentinel value (0x1f30)
    if ( *(int**)((int)g_simManagerStruct + 4) != 0 &&
         *(int**)((int)g_simManagerStruct + 4) != (int*)0x1f30 ) {

        managerPtr = (int*)FUN_007ff880(); // get instance of simulation manager
        if (managerPtr != 0) {
            // Call virtual function at vtable+0x1a8 to get current time scale
            timeScale = (*(float (__thiscall**)(int*))(managerPtr[0] + 0x1a8))(managerPtr);

            // Check pause state
            char* pauseStatus = FUN_00549a40(pauseFlagBuffer);
            if (pauseStatus[0] != '\0') {
                isPaused = 1;
            }
        }
    }

    // Apply time scale and pause state to the entity
    FUN_00625c40(thisObject, timeScale);
    FUN_00625df0(thisObject, isPaused);

    return 2;
}