// FUNC_NAME: SimObject::shutdown
// Function at 0x0073f060: Performs multi-stage cleanup and deinitialization.
// Calls three internal detach functions, then checks a flag at +0x60 bit0.
// If the flag is set, it optionally (if +0x58 is non-null) calls FUN_007fbe50
// (likely unregister from a global list) and clears the flag.
// This pattern is typical for removing an object from various managers.

// Forward declarations of helper functions – actual names unknown.
extern void __fastcall detachFromUpdateManager();   // 0x00722330
extern void __fastcall detachFromRenderManager();   // 0x00722310
extern void __fastcall detachFromCollisionManager(); // 0x007223d0
extern void __fastcall unregisterFromGlobalList();   // 0x007fbe50

class SimObject {
public:
    // Offset +0x58: pointer to parent or next link in a chain
    // If non-null, object is registered in some global list
    void* m_pLinkOrParent;  // +0x58

    // Offset +0x60: flags (ushort); bit0 = alive/active marker
    unsigned short m_flags; // +0x60

    // Shutdown sequence: detach from active systems and unregister if needed
    void __thiscall shutdown();
};

void __thiscall SimObject::shutdown() {
    // Step 1: Remove from three core engine list/update loops
    detachFromUpdateManager();
    detachFromRenderManager();
    detachFromCollisionManager();

    // Step 2: If the object is currently marked as active (bit0 set)
    if ((m_flags & 1) != 0) {
        // If the object is linked into a global list (pointer non-null)
        if (m_pLinkOrParent != nullptr) {
            unregisterFromGlobalList();
        }
        // Clear the active flag (bit0)
        m_flags &= 0xFFFE;
    }
}