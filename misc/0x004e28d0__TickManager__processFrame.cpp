// FUNC_NAME: TickManager::processFrame
class TickManager {
public:
    // Assumed structure offsets:
    // +0x00: vtable or unknown
    // +0x04: head pointer (Tickable*)
    // +0x0C: tail pointer (Tickable*)
    static TickManager* s_pInstance; // DAT_012234d0

    struct Tickable {
        Tickable* pNext; // +0x2C
    };

    Tickable* getHead() { return *(Tickable**)((uint8_t*)this + 0x04); }
    Tickable* getTail() { return *(Tickable**)((uint8_t*)this + 0x0C); }
    void setHead(Tickable* p) { *(Tickable**)((uint8_t*)this + 0x04) = p; }
    void setTail(Tickable* p) { *(Tickable**)((uint8_t*)this + 0x0C) = p; }
};

// Global flags (likely bool or int)
extern int g_bSomeFlag1; // DAT_01163cf6
extern int g_bSkipSecondLoop; // DAT_012054eb
extern uint32_t g_perfCounterLow; // DAT_01194b78
extern uint32_t g_perfCounterHigh; // DAT_01194b7c

// Forward declarations of helper functions
extern void processTickable(int param); // FUN_0051fc90
extern void handlePendingEvents();      // FUN_0051ead0
extern void postProcessTickable();      // FUN_0051fc40

void TickManager::processFrame() {
    TickManager* pMgr = s_pInstance; // DAT_012234d0
    LARGE_INTEGER perfCount;

    g_bSomeFlag1 = 0;
    QueryPerformanceCounter(&perfCount);
    g_perfCounterLow = perfCount.LowPart;
    g_perfCounterHigh = perfCount.HighPart;

    Tickable* pCurrent = pMgr->getHead();
    Tickable* pTail = pMgr->getTail();

    // First pass: update/render tickables?
    if (pCurrent != pTail) {
        do {
            processTickable(0);
            pCurrent = pCurrent->pNext;
        } while (pCurrent != pTail);
    }

    // If flag was set during first pass, handle deferred events
    if (g_bSomeFlag1 != 0) {
        handlePendingEvents();
    }

    // Second pass: additional processing (e.g., rendering) if not skipped
    if (g_bSkipSecondLoop == 0) {
        pCurrent = pMgr->getHead();
        if (pCurrent != pMgr->getTail()) {
            do {
                postProcessTickable();
                pCurrent = pCurrent->pNext;
            } while (pCurrent != pMgr->getTail());
        }
    }
}