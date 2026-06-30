// FUNC_NAME: DelegateCallback::release
void DelegateCallback::release() {
    // Decrement reference count
    if (--refCount == 0) {
        // If the "cleanup needed" flag is set, perform additional cleanup
        if (flags & 0x1) {
            FUN_004218d0();             // e.g., finalizeData()
            flags &= ~0x1;              // Clear the flag
        }
        // Release any extra resource (e.g., timer handle)
        if (extraResource != nullptr) {
            FUN_00420ee0();             // e.g., releaseResource()
        }
        // Invoke callback's virtual methods if callbackTarget is set
        if (callbackTarget != nullptr) {
            // Call the second virtual function (vtable+4) with stored arguments
            (*(void (**)(void*, int, int))(*(int*)callbackTarget + 4))(callbackArg1, callbackArg2);
            // Call the fourth virtual function (vtable+12) with no arguments (e.g., reset or destroy)
            (*(void (**)(void*))(*(int*)callbackTarget + 12))();
        }
        // Free this object's memory
        FUN_009c8eb0(this);             // operator delete or custom deallocator
    }
}
// Struct layout (offsets in bytes from this):
// +0x00: int refCount
// +0x06: unsigned short flags (only bit0 used)
// +0x08: int callbackArg1 (passed to callbackTarget->vtable+4)
// +0x0C: int callbackArg2
// +0x10: void* callbackTarget (object with vtable)
// +0x14: void* extraResource (e.g., timer or memory handle)