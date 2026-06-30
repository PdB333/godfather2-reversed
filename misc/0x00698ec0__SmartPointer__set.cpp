// FUNC_NAME: SmartPointer::set
// Function at 0x00698ec0: Assigns a new pointer to this smart pointer, managing reference counting and release.
// Structure fields:
//   +0x00: m_ptr (int*) - pointed-to object
//   +0x04: m_refCount (int) - reference count or related state
//   +0x08: m_unknown (int) - unknown field, zeroed on release
//   +0x0C: m_releaseFunc (void (*)(int*)) - function to release the pointed object

// External helper functions (likely reference counting)
extern int refCountGet(int* ptr);          // FUN_004dbef0
extern void refCountSet(int* ptr, int oldCount, int newCount); // FUN_004dbb10

class SmartPointer {
public:
    int* m_ptr;                // +0x00
    int m_refCount;            // +0x04
    int m_unknown;             // +0x08
    void (*m_releaseFunc)(int*); // +0x0C

    // Sets the pointer. If newPtr is null, releases current and zeros fields.
    // If newPtr is non-null and different from current, adjusts reference counts.
    SmartPointer* set(int* newPtr) {
        if (newPtr == nullptr) {
            // Release current object if it exists
            if (m_ptr != nullptr) {
                m_releaseFunc(m_ptr);
            }
            m_ptr = nullptr;
            m_unknown = 0;
            m_refCount = 0;
            return this;
        }

        // If new pointer is different from current, update reference counts
        if (newPtr != m_ptr) {
            int oldRefCount = refCountGet(newPtr);
            refCountSet(newPtr, 0, oldRefCount); // Possibly increment or adjust
        }
        return this;
    }
};