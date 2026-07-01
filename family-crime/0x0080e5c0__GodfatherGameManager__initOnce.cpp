// FUNC_NAME: GodfatherGameManager::initOnce
// Address: 0x0080e5c0
// Role: One-time initialization guard that calls subsystem initializers only if the m_flags bit 0 is unset.

struct GodfatherGameManager {
    // Unknown fields before +0x54
    uint32_t m_flags; // +0x54
};

// Forward declarations of the two subsystem initializers called from this function
extern void __cdecl initSubsystemA();       // 0x007f62b0
extern void __cdecl initSubsystemB(int arg); // 0x007f6db0

void __thiscall GodfatherGameManager::initOnce() {
    if (!(this->m_flags & 1)) {
        initSubsystemA();
        initSubsystemB(0);
        this->m_flags |= 1;
    }
}