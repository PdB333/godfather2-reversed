// FUNC_NAME: PlayerSM::deactivateState
void __fastcall PlayerSM::deactivateState(int* this_) {
    // Clear the active flag at offset 0x1C1 (likely a boolean indicating state is running)
    *reinterpret_cast<char*>(reinterpret_cast<int>(this_) + 0x1C1) = 0;

    // Call a global function with argument 3 (possibly debug logging or state transition notification)
    FUN_00957780(3); // someDebugFunc(3)

    // Invoke virtual function at vtable offset 0x28 (index 10)
    // This is likely a virtual method like 'onDeactivate' or 'update'
    typedef void (__thiscall *VirtualMemberFunc)(void*);
    VirtualMemberFunc vfunc = *reinterpret_cast<VirtualMemberFunc*>(*reinterpret_cast<int*>(this_) + 0x28);
    vfunc(this_);
}