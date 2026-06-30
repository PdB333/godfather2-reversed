// FUNC_NAME: RefCountedObject::release

class RefCountedObject;
class SomeManager;
class ResourceManager;

// Global variables
extern SomeManager* g_pReleaseManager; // 0x012234c4
extern ResourceManager* g_pResourceManager; // 0x012233a4
extern int g_iGlobalRefCount; // 0x012054f4

void RefCountedObject::release() {
    // Check if the "has callback" flag is set (bit 0 of flags at +0x3c)
    if (m_flags & 1) {
        // If a release callback is registered in the global manager
        if (g_pReleaseManager->m_pReleaseCallback != nullptr) {
            // Call the callback with this object's target pointer and extra byte
            g_pReleaseManager->m_pReleaseCallback(m_pTarget, m_extraByte);
        }
        // Clear the flag
        m_flags &= ~1u;
    }

    // Decrement reference on the target object
    RefCountedObject* pTarget = m_pTarget; // +0x28
    if (pTarget != nullptr) {
        // Decrement reference count (at target +0x14)
        pTarget->m_refCount--;
        if (pTarget->m_refCount == 0) {
            // Notify resource manager to clean up
            FUN_0044f130(g_pResourceManager, 0);
        }
        // Decrement global reference counter
        g_iGlobalRefCount--;
    }
    // Clear the target pointer
    m_pTarget = nullptr;
}