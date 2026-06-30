// FUNC_NAME: BaseBehavior::resetState
void __thiscall BaseBehavior::resetState(uint flags)
{
    // Reconstructed from Ghidra decompilation (function 0x00674d40)
    // This appears to be a base class method for resetting state flags and calling an optional callback.
    // The 'this' pointer is passed in ESI (unaff_ESI), and the first (and only) stack parameter is param_1.

    // Stack variable: output pointer (set to 0, likely unused or for debug)
    undefined4 *outPtr = in_stack_00000010;  // Actually a pointer stored on stack, set to 0
    *outPtr = 0;

    // Access sub-object at offset +0x180 (likely a properties/state block)
    uint *stateBlock = *(uint **)((int)this + 0x180);
    // +0x9c: store bit 7 of flags (0x80) - possibly a 'loading' or 'streaming' flag
    stateBlock[0x9c / 4] = flags & 0x80;
    // +0xa4: store low byte of in_EAX (the return value of a previous function? Possibly an extra parameter)
    // The decompiler uses 'in_EAX' as a register passed from caller; here we treat it as a second parameter.
    stateBlock[0xa4 / 4] = (uint)in_EAX & 0xff;

    // Decision logic for setting the 'enabled' flag at +0x28
    // Conditions: 
    // - If this+0x24 is non-zero (some state) OR this+0x40 (callback pointer) is non-zero OR bit 8 (0x100) of flags is set -> disable
    // - Otherwise enable
    if ( (*(int *)((int)this + 0x24) == 0) && (*(int *)((int)this + 0x40) == 0) && ((flags & 0x100) == 0) )
    {
        *(undefined4 *)((int)this + 0x28) = 1;  // enable
    }
    else
    {
        *(undefined4 *)((int)this + 0x28) = 0;  // disable
    }

    // +0x2c: inverted bit 8 (upper byte second bit) of flags masked to 0 or 1
    *(uint *)((int)this + 0x2c) = ~((flags >> 8) & 0xff) & 1;

    // +0x120: clear some pointer/flag
    *(undefined4 *)((int)this + 0x120) = 0;

    // Call an internal setup function (likely resets other state)
    FUN_00673b60();

    // +0xcc: set to 1 (probably a 'ready' flag)
    *(undefined4 *)((int)this + 0xcc) = 1;
    // +0xe8: clear some update timer or flag
    *(undefined4 *)((int)this + 0xe8) = 0;

    // If callback pointer at +0x40 is non-null, invoke it
    if (*(code **)((int)this + 0x40) != (code *)0x0)
    {
        (**(code **)((int)this + 0x40))();
    }

    return;
}