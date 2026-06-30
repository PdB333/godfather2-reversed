// Xbox PDB: void __cdecl TX_InitCompressionThreads(void)
// FUNC_NAME: TextureWorkerThreadManager::initWorkerThreads
void initTextureWorkerThread(void)
{
    int i;
    undefined4 *pMutex;
    undefined4 mutex;
    undefined4 threadParams[4];
    char threadName[16];
    char *namePtr;
    
    // Reset global flags and buffer
    g_textureWorkerThreadActive = 0;
    memset(&g_textureWorkerThreadData, 0, 0xBB8); // 3000 bytes, likely array of worker slot data
    
    // Initialize mutexes for each worker slot (0x18 = 24 bytes per slot)
    pMutex = &g_workerSlotMutexes; // starting at DAT_0122257c
    do {
        i = operator_new(0x10); // allocate a lock object
        if (i == 0) {
            mutex = 0;
        }
        else {
            mutex = createMutex(0, 1); // FUN_00ab64e0(0,1) likely creates a mutex
        }
        *pMutex = mutex;
        pMutex += 6; // step 6 * 4 = 24 bytes
    } while ((int)pMutex < 0x1223134); // until end of array
    
    // Initialize threading subsystem
    initThreadSystem(); // FUN_00ab5450
    
    // Prepare thread parameters
    threadParams[0] = 0;           // thread ID or handle
    threadParams[1] = 0x2000;      // stack size
    threadParams[2] = 0xffffff80;  // flags or priority? (signed -128)
    threadParams[3] = 0xffffffff;  // creation flags? (INVALID_HANDLE)
    threadName[0] = 0;             // clear
    namePtr = "TextureWorkerThread";
    
    // Create the worker thread with entry point at FUN_006155e0
    createThread(workerThreadEntry, 0, threadParams, getThreadContext()); // FUN_00ab7410
}