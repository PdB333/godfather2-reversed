// FUNC_NAME: GodfatherGameManager::shutdown

#include <cstdint>

// Forward declarations for callees
void releaseObject(void* obj);
void debugLog(uint32_t* global);
void clearInternalState(int* thisAddr);
void memoryCollector(int, int);
void globalShutdownStep();
void deleteTypeA(void* ctx, void* item);
void deleteTypeB(void* ctx, void* item);
void prepareForDeletion(void* ctx);

struct ListContainer {
    void** arrayTypeB;    // +0x08
    uint32_t countTypeB;  // +0x0c
    void** arrayTypeA;    // +0x14
    uint32_t countTypeA;  // +0x18
};

struct VTableWithNotify {
    void* vtable[4]; // assume at least 4 slots
};

class GodfatherGameManager {
public:
    void __fastcall shutdown();

private:
    // Offsets relative to this
    void* m_pSomeObject;       // +0x90
    uint32_t m_nSomeCount;     // +0x94
    uint32_t m_flags;          // +0x4c
    VTableWithNotify* m_pAnotherObject; // +0x0c
    ListContainer* m_pListContainer;    // +0x20
    void* m_someContext;       // +0x9c
};

void GodfatherGameManager::shutdown() {
    // Release optional object if present
    if (m_pSomeObject) {
        releaseObject(m_pSomeObject);
        m_pSomeObject = nullptr;
    }
    m_nSomeCount = 0;

    // Debug logging
    debugLog(&DAT_012069d4);

    // Internal state clearing (likely resets timers or flags)
    int thisAddr = reinterpret_cast<int>(this);
    clearInternalState(&thisAddr);

    // Clear bit 1 of flags (0x2)
    m_flags &= ~0x2u;

    // Notify another system of shutdown (event ID 0xae986323)
    int result = 0;
    // vtable entry at offset 0x10 -> index 4
    reinterpret_cast<void (__thiscall*)(void*, uint32_t, int*)>(
        m_pAnotherObject->vtable[4]
    )(m_pAnotherObject, 0xae986323, &result);

    // General memory cleanup
    memoryCollector(0, 0);

    // Global shutdown hook
    globalShutdownStep();

    // Temporary context passed to item deletion functions
    int context = 0;

    // Delete all Type A items
    uint32_t countA = m_pListContainer->countTypeA;
    void** arrayA = m_pListContainer->arrayTypeA;
    for (uint32_t i = 0; i < countA; ++i) {
        deleteTypeA(&context, arrayA[i]);
    }

    // Delete all Type B items
    uint32_t countB = m_pListContainer->countTypeB;
    void** arrayB = m_pListContainer->arrayTypeB;
    for (uint32_t j = 0; j < countB; ++j) {
        prepareForDeletion(m_someContext);
        deleteTypeB(&context, arrayB[j]);
    }
}