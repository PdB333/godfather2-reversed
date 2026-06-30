// FUNC_NAME: EARSObject::releaseHandle
// Function address: 0x004f98d0
// Role: Releasing a handle by zeroing the first word of the pointed-to object and nullifying the stored pointer.

class EARSObject {
public:
    // +0x8: m_handle (uint32_t*) - pointer to some resource or object
    void __thiscall releaseHandle();
};

void __thiscall EARSObject::releaseHandle() {
    if (m_handle != nullptr) {
        *m_handle = 0;   // Zero the first word of the target (e.g., reference count, vtable, or state)
        m_handle = nullptr; // Clear the handle
    }
}