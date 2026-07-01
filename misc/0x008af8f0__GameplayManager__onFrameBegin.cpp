// FUNC_NAME: GameplayManager::onFrameBegin
void __fastcall GameplayManager::onFrameBegin(GameplayManager* this) {
    char canUpdate;
    int newSubObject; // Actually handles, but for now int
    int subObjectHandle; // Handle to sub-object

    // Check if gameplay is active (e.g., game loaded, not in menu)
    canUpdate = isGameplayActive(); // FUN_00481660
    if (canUpdate != 0) {
        // Allocate memory for a sub-component (size 0x38 = 56 bytes)
        newSubObject = gameAlloc(0x38); // FUN_009c8e50
        if (newSubObject == 0) {
            subObjectHandle = 0;
        } else {
            // Construct the sub-object, passing 'this' as parent
            subObjectHandle = constructSubObject(this); // FUN_008a9090
        }
        // Store/register the handle
        setSubObjectHandle(subObjectHandle); // FUN_00481690
    }
    // Mark this frame as active/updated
    this->m_activeFlags[0x36] = 1; // +0xD8, 7th bit? Actually index 0x36 = +0xD8
    // Perform generic update tasks
    updateGlobalSystems(); // FUN_004baec0
    initializeFrameComponents(); // FUN_008ab6a0
    // Reset some field
    this->m_frameCounter = 0; // +0x10C (index 0x43)
    // Initialize a local timer from a global constant
    TimerFrame localTimer;
    localTimer.m_time = DAT_0112f1dc; // Global constant
    localTimer.m_unknown1 = 0;
    localTimer.m_unknown2 = 0;
    resetTimer(&localTimer, 0); // FUN_00408a00, likely clears or starts timer
    // If the system is ready, call the virtual update (vtable offset 0xB0)
    if (isFrameReady()) { // FUN_008ae1d0
        // Virtual call at offset 0xB0 from vtable pointer
        (this->vtable[0x2C])(); // 0xB0/4 = 44 -> 44th entry (0-indexed 0x2C)
        return;
    }
}