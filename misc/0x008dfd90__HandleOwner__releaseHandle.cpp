// FUNC_NAME: HandleOwner::releaseHandle
void __fastcall HandleOwner::releaseHandle(void* this) {
    // Call base cleanup or global function
    FUN_008dc670();

    // Check if we own a handle (flag at +0x244) and handle is non-null (+0x240)
    if (*(bool*)((uintptr_t)this + 0x244) && *(int*)((uintptr_t)this + 0x240) != 0) {
        // Release the handle
        FUN_00949e00(*(int*)((uintptr_t)this + 0x240));
        // Clear ownership flag
        *(bool*)((uintptr_t)this + 0x244) = false;
    }
}