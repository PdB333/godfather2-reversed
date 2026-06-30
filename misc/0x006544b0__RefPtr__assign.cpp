// FUNC_NAME: RefPtr::assign
// Address: 0x006544b0
// Sets the internal pointer with proper reference counting.
// Decrements ref count of old object (at offset +0x8), calls destructor if zero,
// then assigns new pointer and increments its ref count.

void RefPtr::assign(RefCounted* newPtr) {
    RefCounted* oldPtr = this->ptr;          // dereference this to get current pointer
    if (oldPtr != nullptr) {
        oldPtr->refCount--;                  // refCount at +0x8
        if (oldPtr->refCount == 0) {
            oldPtr->destroy();               // vtable slot 2 (destructor)
        }
    }
    this->ptr = newPtr;
    if (newPtr != nullptr) {
        newPtr->refCount++;                  // refCount at +0x8
    }
}