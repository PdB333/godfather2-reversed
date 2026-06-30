// FUNC_NAME: VTableForwarder::callMethodAt18
void __thiscall VTableForwarder::callMethodAt18()
{
    // Dereference this+4 to get a pointer to an object with a vtable
    // Then call the function at vtable offset 0x18 (the 6th entry)
    (*(void (__thiscall**)(void*))(*(int**)(*(int*)this + 4)) + 0x18 / 4)();
}