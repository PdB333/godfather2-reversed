// FUNC_NAME: SmartPointer::attach
// Function address: 0x005f9e00
// This appears to be a member function of a smart pointer or reference-counted wrapper class.
// It handles attaching a new target object, performing reference counting operations.
// Offsets:
//   this+0x8: Pointer to the target object (vtable-based)
//   this+0xC: Some reference count/identifier (uint)
// The target object's vtable layout (offsets from target's vtable pointer):
//   vtable[0x4/4] (offset 0x4): Some method, likely release/decrement ref
//   vtable[0x8/4] (offset 0x8): Some method, likely addref/increment ref
//   vtable[0xC/4] (offset 0xC): Some method, possibly finalize/cleanup

void __thiscall SmartPointer::attach(int *this, int *pNewTarget, int param2) {
    int *piVar2;
    uint uVar1;
    
    piVar2 = pNewTarget;
    // Call virtual method at offset 8 on the new target (addref?)
    (*(code **)(*pNewTarget + 8))(pNewTarget);
    
    if (param2 == 0) {
        uVar1 = 0;
    } else {
        // param2 is non-zero, treat as a pointer/source for reference counting
        uVar1 = FUN_004265d0(param2, piVar2); // likely a copy or AddRef from source
    }
    
    // Initialize the wrapper (maybe assign internal ref count)
    FUN_005fa2e0(piVar2, uVar1);
    
    // Store the target pointer
    *(int **)(this + 8) = pNewTarget;
    
    // Call virtual method at offset 8 again (duplicate addref?)
    (*(code **)(*pNewTarget + 8))(); // note: missing this arg? Actually it's same as earlier but no explicit param; likely a bug in decompilation, still passes pNewTarget
    
    if (param2 != 0) {
        uVar1 = FUN_004265d0(param2, *(int **)(this + 8)); // re-get reference from source
        *(uint *)(this + 0xC) = uVar1;
        // Call virtual methods on the target: offset 4 (release?) and offset 12 (finalize?)
        (*(code **)(*pNewTarget + 4))(param2, 0); // release with extra arg
        (*(code **)(*pNewTarget + 0xC))(); // finalize
        return;
    }
    
    // If param2 is null, just set the second field to zero
    *(uint *)(this + 0xC) = 0;
    (*(code **)(*pNewTarget + 0xC))(); // finalize without release
    return;
}