// FUNC_NAME: SomeClass::setRefCountedPtr
// Address: 0x00653fa0
// Role: Assigns a new pointer to a refcounted member (offset +0x1b0) with proper reference counting.
// Decrements old pointer's reference count (stored at +0x08) and deletes if count reaches zero,
// then stores new pointer and increments its reference count.

struct RefCountedObject {
    // +0x00: vtable pointer
    virtual void release() = 0; // typically vtable+0x08 is destructor/release
    // +0x04: (padding or other data)
    // +0x08: reference count
    int refCount;
};

struct SomeClass {
    // ... other members ...
    // +0x1b0: pointer to a refcounted object
    RefCountedObject* m_pRefCountedObject;
    // ... more members ...

    void setRefCountedPtr(RefCountedObject* newPtr) {
        RefCountedObject* oldPtr = m_pRefCountedObject;
        if (oldPtr) {
            oldPtr->refCount--;
            if (oldPtr->refCount == 0) {
                oldPtr->release(); // calls destructor via vtable
            }
        }
        m_pRefCountedObject = newPtr;
        if (newPtr) {
            newPtr->refCount++;
        }
    }
};