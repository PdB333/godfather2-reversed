// FUNC_NAME: RefPtr::operator=
// Function at 0x004f7810: Assignment operator for intrusive reference-counted smart pointer (RefPtr)
// The pointed-to object (RefCountedObject) has layout:
//   +0x00: vtable pointer
//   +0x04: refcount (int)
// Destructor is the second virtual function (vtable[1]).

struct RefCountedObject {
    void** vtable;  // +0x00
    int refCount;   // +0x04
};

class RefPtr {
    RefCountedObject* mPtr; // +0x00 in this class

public:
    RefPtr& __thiscall operator=(const RefPtr& other) {
        RefCountedObject* oldPtr = this->mPtr;
        if (oldPtr != nullptr) {
            // Decrement reference count
            oldPtr->refCount--;
            if (oldPtr->refCount == 0) {
                // Call destructor via vtable (second function)
                void (*destructor)(RefCountedObject*) = (void (*)(RefCountedObject*))(oldPtr->vtable[1]);
                destructor(oldPtr);
            }
        }
        // Copy pointer from other
        RefCountedObject* newPtr = other.mPtr;
        this->mPtr = newPtr;
        if (newPtr != nullptr) {
            // Increment reference count
            newPtr->refCount++;
        }
        return *this;
    }
};