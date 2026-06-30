// FUNC_NAME: PlayerStateMachine::pushStateTo_0x11f
undefined4 __fastcall PlayerStateMachine::pushStateTo_0x11f(undefined4 param_1)
{
    uint uVar1;
    
    // +0x08 = +0x04  (save previous field)
    *(uint *)(this + 0x8) = *(uint *)(this + 0x4);
    
    // Check if current state (at +0x14) is already the target state (0x11f = 287)
    if (*(int *)(this + 0x14) != 0x11f) {
        uVar1 = *(uint *)(this + 0x14);          // save current state
        *(uint *)(this + 0x14) = 0x11f;          // set new state
        *(uint *)(this + 0xC) = uVar1;           // store previous state at +0x0C
        *(uint *)(this + 0x10) = *(uint *)(this + 0x18); // copy data from +0x18 to state data (+0x10)
        return 1;
    }
    
    // Already in target state: call sub-function on sub-object at this+0x10
    uVar1 = FUN_00639c70(this + 0x10, param_1);
    *(uint *)(this + 0x0C) = uVar1;             // store result as previous state
    return 1;
}