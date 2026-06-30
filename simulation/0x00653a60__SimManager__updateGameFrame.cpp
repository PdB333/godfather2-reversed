// FUNC_NAME: SimManager::updateGameFrame
void __thiscall SimManager::updateGameFrame(void) {
    // in_EAX is 'this' pointer
    int* thisPtr = (int*)this; // Avoid ghidra's in_EAX

    // Process subsystem with flag 2 (possibly delta time or update type)
    processSubsystem(thisPtr, 2);

    // Check if there's an active entity pointer at +0x1b0
    int* pActiveEntity = *(int**)(thisPtr + 0x1b0); // +0x1b0: pointer to spawned entity
    if (pActiveEntity != 0) {
        // Spawn/reposition entity at stored coordinates (offsets +0x90, +0x98)
        // Likely position x and z or x and y
        spawnEntity(pActiveEntity, 
                    *(float*)(thisPtr + 0x98),  // +0x98: spawn coordinate X
                    *(float*)(thisPtr + 0x90),  // +0x90: spawn coordinate Z (or Y)
                    2);                         // param: entity type or flag
        // Log event with severity 3
        logEvent(3, pActiveEntity);
    }

    // Finalize simulation update
    updateRendering();
    finalizeFrame();
}

void processSubsystem(int* thisPtr, int param);
void spawnEntity(int* entityPtr, float x, float z, int flag);
void logEvent(int severity, int* entityPtr);
void updateRendering(void);
void finalizeFrame(void);