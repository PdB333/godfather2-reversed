// FUNC_NAME: RefCountedPointer::assign

// Function at 0x004f7940: Assigns a new reference-counted pointer, releasing the old one.
// This is a __thiscall member function where 'this' is passed in ESI.
// The member at offset +0x20 holds a pointer to a reference-counted object.
// The object's structure (at the pointer) has:
//   +0x00: vtable pointer (used to call destructor via (*(this+0x20)->vtable[1]))
//   +0x04: reference count (int32)

class RefCountedPointer {
public:
    void assign(int* newPtr); // param_1 is the new raw pointer to assign
};

// Helper structure for ref-counted objects
struct RefCountedObject {
    int* vtable;       // +0x00
    int refCount;      // +0x04
};

void __thiscall RefCountedPointer::assign(int* newPtr) {
    // Release old pointer if it exists
    if (this->m_ptr != nullptr) {  // *(this+0x20)
        RefCountedObject* oldObj = reinterpret_cast<RefCountedObject*>(this->m_ptr);
        oldObj->refCount--;        // decrement ref count at +0x04
        if (oldObj->refCount == 0) {
            // Call the destructor function from vtable (offset +0x04 in vtable is typically second entry)
            // vtable[1] corresponds to (*(oldObj->vtable + 4))
            (void (*)())(oldObj->vtable[1])();
        }
        this->m_ptr = nullptr;     // clear old pointer at +0x20
    }
    // Assign new pointer
    this->m_ptr = newPtr;          // *(this+0x20) = newPtr
    if (newPtr != nullptr) {
        RefCountedObject* newObj = reinterpret_cast<RefCountedObject*>(newPtr);
        newObj->refCount++;        // increment new object's ref count
    }
}