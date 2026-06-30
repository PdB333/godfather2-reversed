// FUNC_NAME: RefCountedOwner::setPointer

// Structure for reference-counted objects with vtable
struct RefCountedObject {
    void (**vtable)(); // +0x00: vtable pointer (array of function pointers)
    int refCount;      // +0x04: reference count
};

// Class that holds a reference-counted pointer at offset 0x20
class RefCountedOwner {
    RefCountedObject* m_refCountedObj; // +0x20: owned ref-counted pointer

public:
    // Releases old pointer (decrements ref count, calls vtable[1] if zero)
    // and assigns new pointer (increments its ref count)
    void setPointer(RefCountedObject* newObj) {
        // Release old pointer if it exists
        if (m_refCountedObj != nullptr) {
            // Decrement reference count at +0x04
            m_refCountedObj->refCount--;
            if (m_refCountedObj->refCount == 0) {
                // Call Release method (vtable index 1)
                m_refCountedObj->vtable[1]();
            }
            m_refCountedObj = nullptr; // Clear old pointer
        }

        // Assign new pointer
        m_refCountedObj = newObj;
        if (newObj != nullptr) {
            // Increment new object's reference count at +0x04
            newObj->refCount++;
        }
    }
};