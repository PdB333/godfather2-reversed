// FUNC_NAME: EARS::SharedPtr::assign
void __thiscall EARS::SharedPtr::assign(int *newPtr) {
    // Save this pointer (the smart pointer object)
    int *self = this;

    // vtable+0x8: Get internal reference block (likely a control block with ref counts and back pointers)
    int *refBlock = (int *)(this->vtable->getRefBlock(this));

    // If new pointer is non-null, increase its reference count and get a handle
    int newHandle = (newPtr != 0) ? FUN_004265d0(newPtr, self) : 0;

    // Store the new handle (releases previous one internally)
    FUN_005e1480(self, newHandle);

    // Link the reference block back to this smart pointer
    refBlock[0x3] = (int)self;  // offset +0x0C: back pointer to smart pointer

    // vtable+0x8 called again (likely a post-update hook)
    this->vtable->postUpdate();

    if (newPtr != 0) {
        // Re-fetch the back pointer from reference block (should be self)
        int *backPtr = (int *)refBlock[0x3];
        // Obtain another handle from the new pointer using the back pointer
        newHandle = FUN_004265d0(newPtr, backPtr);
        refBlock[0x4] = newHandle;  // offset +0x10: store secondary handle

        // vtable+0x4: Release previous reference (old pointer)
        this->vtable->release(newPtr, 0);

        // vtable+0x0C: Finalize the assignment (e.g., decrement weak refs)
        this->vtable->finalize();
    } else {
        refBlock[0x4] = 0;
        this->vtable->finalize();
    }
}