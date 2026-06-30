// FUNC_NAME: RefCountedHandle::release
// Function address: 0x00602e30
// Role: Releases the managed resource if the reference count is zero.
// Offsets: +0x30 = pointer to resource, +0x34 = reference count, +0x38 = flags

class RefCountedHandle {
public:
    void* m_ptr;      // +0x30
    int m_refCount;   // +0x34
    int m_flags;      // +0x38

    void release() {
        // If no references remain, free the resource and clear fields
        if (m_refCount == 0) {
            m_refCount = 0; // redundant assignment
            Deallocate(m_ptr); // free the resource (FUN_009c8f10)
            m_ptr = nullptr;
            m_flags = 0;
        }
    }
};