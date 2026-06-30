// FUNC_NAME: EngineManager::shutdown

class Engine {
public:
    virtual void release(int param) = 0; // vtable+0x04
};

extern Engine* g_pEngine;         // DAT_01163ee0
extern int* g_pEngineVTable;      // DAT_01163ed4 (pointer to vtable pointer)
extern int g_nSomeFlag;           // _DAT_01163ed8
extern int g_nSomeOtherFlag;      // DAT_01163edc

void releaseMemoryPools();        // FUN_0042c550
void closeNetworkConnections();   // FUN_00433d90
void processFrameCleanup();       // FUN_004c44e0

void EngineManager::shutdown() {
    // Call virtual release on the engine singleton (vtable+0x04)
    if (g_pEngine) {
        g_pEngine->release(0);
    }

    // Null out engine and vtable pointers
    g_pEngine = nullptr;
    g_pEngineVTable = nullptr;
    g_nSomeFlag = 0;
    g_nSomeOtherFlag = 0;

    // Clean up subsystems
    releaseMemoryPools();
    closeNetworkConnections();

    // Run garbage collection 6 times to finalize pending removals
    int loopCount = 5;
    do {
        processFrameCleanup();
        loopCount--;
    } while (loopCount >= 0);
}