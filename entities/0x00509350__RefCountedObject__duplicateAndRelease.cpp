// FUNC_NAME: RefCountedObject::duplicateAndRelease
void RefCountedObject::duplicateAndRelease() {
    // This function appears to be a reference-counted duplication operation.
    // It increments the current object's reference count, clones the object via
    // a helper function (FUN_004e8550), then decrements and potentially deletes
    // both the original and the cloned object based on their updated reference counts.
    // Note: The decompilation is ambiguous; piVar3[1] assignment is likely a missed
    // decRef operation on the clone.

    if (this != nullptr) {
        this->refCount++; // +0x04: ref count increment
    }

    // Call to a cloning/duplication utility (FUN_004e8550)
    RefCountedObject* clone = static_cast<RefCountedObject*>(
        SomeGlobalCloneFunction(this) // FUN_004e8550 returns a new or shared pointer
    );

    if (this != nullptr) {
        // Release original reference
        this->refCount--; // +0x04
        if (this->refCount == 0) {
            // vtable+0x04: virtual destructor
            (this->vtable->destructor)(); // (**(code **)(*this + 4))()
        }
    }

    if (clone != nullptr) {
        // Release clone reference (likely decRef on clone)
        clone->refCount--; // +0x04
        if (clone->refCount == 0) {
            (clone->vtable->destructor)();
        }
    }
}