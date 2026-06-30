// FUNC_NAME: CleanableObject::~CleanableObject
// Destructor: calls a cleanup function pointer (at +0x10) with data at +0x04, then sets vtable to purecall to prevent further virtual calls, and optionally deletes memory.
CleanableObject::~CleanableObject() {
    // If cleanup data present, invoke the cleanup function
    if (this->cleanupData != nullptr) {
        this->cleanupFunc(this->cleanupData);
    }
    // Reset vtable to purecall base to block virtual dispatch
    this->vtable = &purecall_vtable; // PTR___purecall_00e3a9d0
    // If the scalar delete flag is set, deallocate this object
    if ((this->deleteFlag & 1) != 0) {
        operator delete(this); // calls FUN_009c8eb0 (operator delete)
    }
}