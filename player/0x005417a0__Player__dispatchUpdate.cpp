// FUNC_NAME: Player::dispatchUpdate
void __thiscall Player::dispatchUpdate(void* this, uint32_t arg0, uint32_t arg1) {
    // Profile marker? Possibly a nullsub in release builds.
    FUN_009f2000();

    // Call virtual function at index 0x58 (vtable offset 0x58) on the object
    // stored at this+0xd0 (likely a state machine or handler).
    // The function receives arg0 and arg1 as parameters.
    void* handler = *(void**)((uintptr_t)this + 0xd0); // +0xd0: pointer to sub-object
    void (*vfunc)(uint32_t, uint32_t) = *(void (**)(uint32_t, uint32_t))((uintptr_t)handler + 0x58);
    vfunc(arg0, arg1);
}