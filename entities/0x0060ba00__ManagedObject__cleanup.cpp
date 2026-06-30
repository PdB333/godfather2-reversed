// FUNC_NAME: ManagedObject::cleanup
// Address: 0x0060ba00
// Role: Releases resources and removes object from global list. Two paths based on flag at +0x1c.

#include <windows.h> // For CRITICAL_SECTION

// Forward declaration of the global manager structure
struct GlobalManager;

// Global variables (from Ghidra data)
extern GlobalManager* g_pGlobalManager;          // DAT_01205868
extern CRITICAL_SECTION g_csObjectList;          // DAT_012224c0
extern ManagedObject** g_ppObjectList;           // DAT_011da8f0
extern int g_nObjectCount;                       // DAT_01205850

// Forward declaration of helper function (FUN_0060b4c0)
void releaseChildren(ManagedObject* pThis);

class ManagedObject {
public:
    // Offsets (relative to this):
    // +0x00: vtable pointer
    // +0x10: void* m_pResource1
    // +0x14: int m_nResourceParam
    // +0x1c: bool m_bFlag
    // +0x20: void* m_pResource2

    void cleanup() {
        if (!m_bFlag) {
            // Path 1: Normal cleanup
            if (m_pResource1) {
                // Call global manager's release function (vtable offset 4)
                // Signature: void release(void* resource, int param)
                typedef void (*ReleaseFunc)(void*, int);
                ReleaseFunc release = *(ReleaseFunc*)(*(int*)g_pGlobalManager + 4);
                release(m_pResource1, m_nResourceParam);
                m_pResource1 = nullptr;
            }

            // Remove this object from the global list
            EnterCriticalSection(&g_csObjectList);
            for (int i = 0; i < g_nObjectCount; i++) {
                if (g_ppObjectList[i] == this) {
                    g_nObjectCount--;
                    if (g_nObjectCount > 0) {
                        g_ppObjectList[i] = g_ppObjectList[g_nObjectCount];
                    }
                    break;
                }
            }
            LeaveCriticalSection(&g_csObjectList);
        } else {
            // Path 2: Flag set – additional cleanup
            releaseChildren(this); // FUN_0060b4c0

            if (m_pResource2) {
                if (g_pGlobalManager) {
                    typedef void (*ReleaseFunc)(void*, int);
                    ReleaseFunc release = *(ReleaseFunc*)(*(int*)g_pGlobalManager + 4);
                    release(m_pResource2, 0);
                }
                // If resource2 is not the same as this, clear it and return early
                if (this != m_pResource2) {
                    m_pResource2 = nullptr;
                    return;
                }
            }
        }
    }

private:
    // Fields (order and sizes assumed from offsets)
    void* m_pResource1;      // +0x10
    int m_nResourceParam;    // +0x14
    bool m_bFlag;            // +0x1c
    void* m_pResource2;      // +0x20
    // Other fields may follow
};