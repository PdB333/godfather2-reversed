// FUNC_NAME: EARSObject::EARSObject (0x004b4d10)
void __thiscall EARSObject::EARSObject(void *this, void *param1, void *param2)
{
    // vtables for multiple inheritance (offset 0 and 4)
    *(void **)this = (void *)&PTR_FUN_00e35888;            // +0x00: primary vtable
    *(void **)((char *)this + 4) = (void *)&PTR_LAB_00e358a4; // +0x04: secondary vtable

    // Members at offsets 8, 12, 16, 20, 24
    *(int *)((char *)this + 8) = 1;                          // +0x08: some flag (initialized to 1)
    *(int *)((char *)this + 12) = 0;                         // +0x0C: will be overwritten later
    *(void **)((char *)this + 16) = param2;                  // +0x10: second parameter (unaff_EDI)
    *(void **)((char *)this + 20) = param1;                  // +0x14: first parameter (param_1)
    *(int *)((char *)this + 24) = 1;                         // +0x18: another flag

    // Critical section at offset 32 (0x20)
    InitializeCriticalSection((LPCRITICAL_SECTION)((char *)this + 32));

    // Call a global function returning a pointer, then invoke a method on it
    void *globalObj = FUN_009c8f80();
    int result = (*(int (**)(void))globalObj)();            // virtual call on global object
    *(int *)((char *)this + 12) = result;                   // +0x0C: store result

    // Call base class or additional initialization
    FUN_004b4c20(param2);                                   // param2 is likely a parent or this pointer
}