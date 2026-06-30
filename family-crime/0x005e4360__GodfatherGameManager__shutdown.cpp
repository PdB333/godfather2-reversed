// FUNC_NAME: GodfatherGameManager::shutdown
// Address: 0x005e4360
// Role: Cleanup/shutdown method for the game manager. Releases subsystems and sets global flag.

// Forward declarations for external functions and globals
extern void MemoryManager::free(void* ptr); // FUN_009c8f10 - custom deallocation
extern int g_gameRunning; // DAT_012234bc - global game running flag

// Vtable pointers (symbols from data section)
extern void* g_vtableShutdown; // PTR_FUN_00e3f6a4
extern void* g_vtableDestroyed; // PTR_LAB_00e3f6a8

class GodfatherGameManager {
public:
    // Member offsets (in bytes from this):
    // +0x6010: m_pSubsystemA (pointer to object with virtual shutdown at vtable+0xc)
    // +0x6014: m_pSubsystemB
    // +0x6020: m_pSubsystemC
    // +0x602c: m_pSubsystemD

    void* m_pSubsystemA;      // offset 0x6010
    void* m_pSubsystemB;      // offset 0x6014
    void* m_pSubsystemC;      // offset 0x6020
    void* m_pSubsystemD;      // offset 0x602c

    void shutdown() {
        // Set vtable to shutdown vtable (first phase of destruction)
        this->vtable = &g_vtableShutdown;

        // Shutdown subsystem A if present (virtual call at vtable+0xc)
        if (this->m_pSubsystemA != nullptr) {
            // Call the third virtual method (offset 0xc) - assumed to be shutdown
            (*(void (**)(void*))(*(int*)this->m_pSubsystemA + 0xc))(this->m_pSubsystemA);
        }

        // Release subsystem D (offset 0x602c)
        if (this->m_pSubsystemD != nullptr) {
            MemoryManager::free(this->m_pSubsystemD);
        }

        // Release subsystem C (offset 0x6020)
        if (this->m_pSubsystemC != nullptr) {
            MemoryManager::free(this->m_pSubsystemC);
        }

        // Release subsystem B (offset 0x6014)
        if (this->m_pSubsystemB != nullptr) {
            MemoryManager::free(this->m_pSubsystemB);
        }

        // Set global shutdown flag to false
        g_gameRunning = 0;

        // Set vtable to destroyed vtable (final phase)
        this->vtable = &g_vtableDestroyed;
    }
};