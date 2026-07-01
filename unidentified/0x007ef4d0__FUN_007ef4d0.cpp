// FUNC_NAME: UnknownClass::CallChainedDelegates
// Function at 0x007ef4d0: Sequence of callbacks stored in the object.
// Each offset points to a function pointer (with double indirection), called with no arguments.
void __thiscall CallChainedDelegates(void* thisptr) {
    // +0x2c: first callback pointer (pointer to pointer to function)
    (**(void (__fastcall**)(void))((char*)thisptr + 0x2c))();
    // +0x48: second callback
    (**(void (__fastcall**)(void))((char*)thisptr + 0x48))();
    // +0x64: third callback (offset 100 decimal)
    (**(void (__fastcall**)(void))((char*)thisptr + 100))();
    // +0x80: fourth callback
    (**(void (__fastcall**)(void))((char*)thisptr + 0x80))();
    // +0x9c: fifth callback
    (**(void (__fastcall**)(void))((char*)thisptr + 0x9c))();
    // +0xb8: sixth callback
    (**(void (__fastcall**)(void))((char*)thisptr + 0xb8))();
    return;
}