// FUNC_NAME: EARSBaseObject::cleanupTarget
// Function at 0x00426690: Releases a target object via a manager, then performs final cleanup on the manager.
// The object contains two members: m_pTarget (offset 0) and m_pManager (offset 4).
// m_pManager points to an object with a vtable; vtable[1] (offset 4) takes a pointer and an int,
// vtable[3] (offset 12) takes no arguments.

class EARSBaseObject {
public:
    int* m_pTarget;    // +0x00: pointer to the target object (null if none)
    int* m_pManager;   // +0x04: pointer to a manager object with vtable

    void __thiscall cleanupTarget() {
        if (m_pTarget != 0) {
            // Call manager->someRelease(m_pTarget, 0)
            // The manager's vtable[1] is a method that expects a pointer and an int.
            ((void (__thiscall*)(int*, int))(*((int**)m_pManager)[1]))(m_pTarget, 0);
        }
        // Call manager->someFinalCleanup()
        ((void (__thiscall*)(int*))(*((int**)m_pManager)[3]))(m_pManager);
    }
};