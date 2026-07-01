// FUNC_NAME: GodfatherGameManager::initializeGameState
// Address: 0x008fd610
// Role: Initializes game state based on startup flags and configuration data.
// Uses global singleton at DAT_011299c4 (GodfatherGameManager instance).
// Parameters:
//   param_1: startupType (0 = initial launch, non-zero = restart/reload)
//   param_2: configData (pointer to configuration structure, can be null)
//   param_3: skipInit (0 = perform full init, non-zero = skip some steps)

void GodfatherGameManager::initializeGameState(int startupType, int configData, char skipInit)
{
    // If config data is provided, initialize audio and set configuration
    if (configData != 0) {
        initializeAudio();          // FUN_009823b0
        setAudioConfig(configData); // FUN_009c8eb0
    }

    int* gameManager = DAT_011299c4; // Global singleton pointer

    // If not skipping initialization, perform full startup sequence
    if (skipInit == '\0') {
        resetGameState();           // FUN_008fbcf0
        clearInputDevices();        // FUN_004511c0

        if (startupType == 0) {
            // Initial launch: send initialization message to subsystem
            // +0x1c: pointer to a subsystem (e.g., UI or game logic manager)
            // +0xec: offset within that subsystem for a message handler
            int* subsystemPtr = *(int**)(gameManager + 0x1c); // +0x1c
            int* handler = (int*)((char*)subsystemPtr + 0xec); // +0xec
            void* messageTarget = getSubsystemPointer(handler); // FUN_008fc140
            sendMessage(messageTarget, 0x209); // FUN_008fd000, 0x209 = MSG_INITIALIZE
            setSubsystemFlag(0);               // FUN_008fcb40
            update();                          // FUN_004df600
            render();                          // FUN_00912030
            return;
        }
        // Restart/reload: handle special case
        handleRestart(); // FUN_008fd4a0
    }

    // Common update/render for both paths
    update(); // FUN_004df600
    render(); // FUN_00912030
}