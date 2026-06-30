// FUNC_NAME: EARSObject::dispatchUpdate

void __fastcall EARSObject::dispatchUpdate(void)
{
    // Global engine pre-update (e.g., FrameTime, InputPoll, or Manager step)
    // Address: 0x009f2000
    globalUpdateFunction();

    // Retrieve function table pointer at this+0xd0
    void* functionTable = *(void**)((uint)this + 0xd0);

    // Call virtual function at offset 0x48 in the table (index 18)
    // This dispatch pattern is typical for EARS update callbacks
    void (*updateCallback)() = (void (*)())(*(int*)((uint)functionTable + 0x48));
    updateCallback();
}