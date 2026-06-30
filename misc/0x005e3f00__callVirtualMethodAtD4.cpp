// FUNC_NAME: callVirtualMethodAtD4
void callVirtualMethodAtD4(void* instance)
{
    // The global DAT_01223510 holds a pointer to a vtable base (or a structure containing it).
    // This function calls the virtual method located at offset 0xd4 (212 bytes) from that base.
    // The method is invoked on the given instance (param_1) as the 'this' pointer.
    void* vtableBase = *(void**)DAT_01223510;
    void* funcPtr = *(void**)((char*)vtableBase + 0xd4);
    ((void (__thiscall*)(void*))funcPtr)(instance);
}