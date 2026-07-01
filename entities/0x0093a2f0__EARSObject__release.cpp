// FUNC_NAME: EARSObject::release

extern void performGlobalCleanup();     // FUN_005c1b40
extern void releaseDialogTreeManager(); // FUN_0094da20
extern void releasePresentationManager(); // FUN_00928440
extern void releaseStreamManager();      // FUN_0093de90

extern int   g_globalCleanupEnabled;     // DAT_0112af90
extern void* g_someManagerBase;          // DAT_01223484 (base of some manager block)
extern void* g_dialogTreeManager;        // DAT_0112b9b8
extern void* g_presentationManager;      // DAT_0112a87c
extern void* g_streamManager;            // DAT_0112a67c

struct EARSObject {
    // +0x00: vtable pointer
    // ...
    int   m_flags;      // +0x5c
    int   m_refCount;   // +0x60
};

void __thiscall EARSObject::release() {
    this->m_refCount--;

    if (this->m_refCount == 0) {
        performGlobalCleanup();

        // Second cleanup if ref count is still zero, certain flags are clear,
        // and the global cleanup flag is set
        if (this->m_refCount == 0 &&
            ((this->m_flags & 0x40000008) == 0) &&
            g_globalCleanupEnabled != 0) {
            performGlobalCleanup();
        }

        // If a subsystem manager (stored at g_someManagerBase+0xC) exists
        if (*((int**)((char*)g_someManagerBase + 0xC)) != 0) {
            if (g_dialogTreeManager != 0) {
                releaseDialogTreeManager();
            }
            // Check bit 4 of flags (0x10) for presentation manager release
            if (((this->m_flags >> 4) & 1) != 0 && g_presentationManager != 0) {
                releasePresentationManager();
            }
        }

        // If stream manager is active, release it and return immediately
        if (g_streamManager != 0) {
            releaseStreamManager();
            return;
        }
    }
}