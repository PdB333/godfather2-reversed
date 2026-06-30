// FUNC_NAME: GodfatherGameManager::cleanup
// Address: 0x0072f790
// Role: Releases sub-components and shuts down major engine subsystems.
void __thiscall GodfatherGameManager::cleanup(int thisPtr) {
    // +0x1c78: pointer to a resource manager or similar component
    int* resourceComponent = (int*)(thisPtr + 0x1c78);
    if (*resourceComponent != 0) {
        safeDelete((void**)resourceComponent); // nullifies after release
    }
    if (thisPtr != 0) {
        // Unregister this from the global singleton manager
        genericUnregister(DAT_01131018);
    }
    // Shutdown core subsystems
    AudioDataManager::shutdown();
    InputDeviceManager::shutdown();
    StreamManager::shutdown();
    Presentation::shutdown();
}