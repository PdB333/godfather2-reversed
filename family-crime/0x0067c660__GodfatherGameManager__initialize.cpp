// FUNC_NAME: GodfatherGameManager::initialize
void GodfatherGameManager::initialize()
{
    // 20-byte buffer for stream manager initialization parameters
    char streamInitBuffer[20];

    // Initialize the heap/memory manager for the EARS engine
    initializeHeapManager();

    // Seed random number generator used by the game
    initializeRandomSeed();

    // Initialize the stream manager with an empty buffer and flag 0
    initializeStreamManager(streamInitBuffer, 0);

    // Initialize the input device manager (controller/keyboard/mouse support)
    initializeInputDeviceManager();

    // Initialize the building manager (manages building data and states)
    initializeBuildingManager();
}