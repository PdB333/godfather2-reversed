// FUNC_NAME: GodfatherGameManager::init
// Address: 0x009201b0
// Initializes core game systems: registers resource types, allocates large game state objects,
// sets up the game manager's update function pointer, and marks initialization as complete.

void GodfatherGameManager::init(void)
{
    int allocResult;
    void* allocator;
    AllocationInfo allocInfo;
    void* paramPtr;

    // Register known resource/system types with their initialization data
    registerSystemType(2, &g_resourceData0);   // +0x00d86138
    registerSystemType(8, &g_resourceData1);   // +0x00d86134
    registerSystemType(0xe, &g_resourceData2); // +0x00d86130
    registerSystemType(4, &g_resourceData3);   // +0x00d8612c
    registerSystemType(0xd, &g_resourceData4); // +0x00d86128

    // If the singleton game manager exists, assign its main update function
    if (g_pGameManager != 0) {
        *(void**)(g_pGameManager + 0x50) = &GodfatherGameManager::update; // +0x50
    }

    // Initialize random number generator / seed
    initRandom();

    // Retrieve the global allocator
    allocator = getAllocator();

    // Prepare allocation descriptor for large object (size 0x2e50)
    allocInfo.size     = 2;       // Size category/type
    allocInfo.alignment = 0x10;   // 16-byte alignment
    allocInfo.flags    = 0;       // No special flags

    // Allocate memory for the large game state object
    allocResult = (*(int (__thiscall*)(void*, int, AllocationInfo*))(*allocator))(allocator, 0x2e50, &allocInfo);
    if (allocResult == 0) {
        g_pLargeGameState = 0;
    }
    else {
        g_pLargeGameState = constructLargeGameState(); // FUN_0091f200
    }

    // Second allocation attempt (always runs because allocInfo.flags remains 0)
    if (allocInfo.flags == 0) {
        allocator = getAllocator();
        paramPtr = &allocator; // Reuse variable as parameter pointer
        allocResult = (*(int (__thiscall*)(void*, int, void**))(*allocator))(allocator, 0x1dd0, &paramPtr);
        if (allocResult != 0) {
            g_pSecondGameState = constructSecondGameState(); // FUN_0091f920
            g_bGameInitComplete = 1;
            return;
        }
        g_pSecondGameState = 0;
    }
    g_bGameInitComplete = 1;
}