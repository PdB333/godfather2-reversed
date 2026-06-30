// FUNC_NAME: initializeGlobalSystemsAndComponents
void __cdecl initializeGlobalSystemsAndComponents(void)
{
    // Allocate object of size 0x1c (28 bytes) – likely a small component
    void* primaryComponent = allocateMemory(0x1c);      // FUN_009c8e50(0x1c)
    if (primaryComponent == nullptr) {
        primaryComponent = nullptr;
    }
    else {
        primaryComponent = constructPrimaryComponent(); // FUN_006a16d0()
    }

    // Allocate second object of size 0x28 (40 bytes)
    void* secondaryContainer = allocateMemory(0x28);    // FUN_009c8e50(0x28)
    if (secondaryContainer == nullptr) {
        g_secondaryObject = 0;                           // DAT_01129bc0
    }
    else if (primaryComponent == nullptr) {
        g_secondaryObject = createDerivedObject(0);      // FUN_00497910(0)
    }
    else {
        // Use pointer at offset +4 from primaryComponent
        g_secondaryObject = createDerivedObject((int)primaryComponent + 4); // FUN_00497910(primaryComponent + 4)
    }

    // Finish setup of both objects
    finalizePrimarySetup();                              // FUN_00692340
    finalizeSecondarySetup();                            // FUN_00497ad0

    // Store reference to primary component (offset +4) in global manager structure
    if (primaryComponent != nullptr) {
        *(int*)(g_gameManager + 0x570) = (int)primaryComponent + 4; // +0x570: m_primaryComponentOffset
    }
    else {
        *(int*)(g_gameManager + 0x570) = 0;
    }
}