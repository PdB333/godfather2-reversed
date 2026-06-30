// FUNC_NAME: ManagedObject::destroy

// Reconstructed C++ for function at 0x0060ba00
// Role: Releases resources and removes the object from a global list.

#include <windows.h> // for CRITICAL_SECTION

// Forward declaration of global objects (defined elsewhere)
extern void* g_pObjectVtable;      // DAT_01205868 - pointer to function table (vtable)
extern CRITICAL_SECTION g_listCritSec; // DAT_012224c0
extern int g_objectCount;          // DAT_01205850
extern void* g_objectList[];       // DAT_011da8f0

// Helper function (defined at 0x0060b4c0)
void cleanupObject(); // Implemented elsewhere

class ManagedObject {
public:
    // Offsets within the class structure:
    // +0x10 : m_pResource (pointer to a resource with own vtable)
    // +0x14 : m_resourceReleaseParam (parameter for resource release)
    // +0x1c : m_bActive (byte flag, 0 = inactive, 1 = active)
    // +0x20 : m_pLinkedObject (pointer to another object, possibly self)

    void* m_pResource;             // 0x10
    int m_resourceReleaseParam;    // 0x14
    char m_bActive;                // 0x1c
    void* m_pLinkedObject;         // 0x20

    void destroy() {
        if (m_bActive == 0) {
            // Not active: release resource if present
            if (m_pResource != 0) {
                // Call the second virtual function (release) on m_pResource
                // g_pObjectVtable points to a struct with function pointers at offsets 0,4,8,...
                (*(void (**)(void*, int))(*(int*)g_pObjectVtable + 4))(m_pResource, m_resourceReleaseParam);
                m_pResource = 0;
            }
            // Remove this object from the global list (thread-safe)
            EnterCriticalSection(&g_listCritSec);
            for (int i = 0; i < g_objectCount; i++) {
                if (g_objectList[i] == this) {
                    g_objectCount--;
                    if (g_objectCount > 0) {
                        // Move last element to fill the gap
                        g_objectList[i] = g_objectList[g_objectCount];
                    }
                    break;
                }
            }
            LeaveCriticalSection(&g_listCritSec);
        } else {
            // Active: call cleanup function
            cleanupObject();

            // Handle linked object
            void* pLinked = m_pLinkedObject;
            if (pLinked != 0) {
                if (g_pObjectVtable != 0) {
                    // Call the same release function on the linked object with param 0
                    (*(void (**)(void*, int))(*(int*)g_pObjectVtable + 4))(pLinked, 0);
                }
                if (this != pLinked) {
                    // If linked object is not itself, clear the pointer
                    m_pLinkedObject = 0;
                    return;
                }
                // If linked object is itself, do not clear (self-linking? Usually not)
            }
        }
    }
};