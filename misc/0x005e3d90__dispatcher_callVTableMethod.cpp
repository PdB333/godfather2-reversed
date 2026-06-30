// FUNC_NAME: dispatcher_callVTableMethod
// Address: 0x005e3d90
// This function is a trampoline that retrieves a function pointer from a global structure's vtable-like table at offset 0xBC and calls it with two arguments.
// The first parameter (param_1 in decompiler) is ignored; likely a leftover from __fastcall convention or unused 'this'.

void __fastcall dispatcher_callVTableMethod(void* param_1, void* param_2, void* param_3)
{
    // DAT_01223510 is a global pointer to some engine object (e.g., EARS singleton).
    // *DAT_01223510 is the vtable pointer. Offset 0xBC corresponds to a method that takes two parameters.
    typedef void (__fastcall *EngineMethod)(void* arg0, void* arg1);
    EngineMethod method = *(EngineMethod*)(*(uintptr_t*)DAT_01223510 + 0xBC);
    method(param_2, param_3);
}