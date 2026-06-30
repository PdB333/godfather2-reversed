// FUNC_NAME: EARSObject::update
void __fastcall EARSObject::update(int this) // __fastcall due to Ghidra convention; actual __thiscall with this in ECX
{
    // Likely profiler / timing hook
    FUN_009f2000();

    // Virtual dispatch: get pointer at +0xd0 (likely a component or base class vtable pointer)
    // Then call function at vtable offset 0x44 (e.g., virtual Update)
    int* vtablePtr = *(int**)(this + 0xd0);
    (**(code**)(vtablePtr + 0x44))();
}