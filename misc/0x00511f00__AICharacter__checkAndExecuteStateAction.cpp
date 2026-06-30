// FUNC_NAME: AICharacter::checkAndExecuteStateAction

// Function address: 0x00511f00
// Role: State-driven AI action check and execution.
// Uses EA EARS engine object model, member accessed via this (in EAX).
// Offsets: +0x30 (active flag, short), +0x70 (state byte), +0x5c (some object pointer, int),
//          +0x40 (float threshold), +0x32 (action parameter, short), +0x50 (some int).

void __thiscall AICharacter::checkAndExecuteStateAction(void* this, int param_1)
{
    short activeFlag = *(short*)((int)this + 0x30);
    if (activeFlag == 0) {
        return;
    }

    uint state = (uint)*(byte*)((int)this + 0x70);
    if (state == 4) {
        // State 4: check if the pointer at +0x5c is valid and global time (DAT_00e2af44)
        // is less than the stored time threshold
        if (*(int*)((int)this + 0x5c) != 0 && DAT_00e2af44 < *(float*)((int)this + 0x40)) {
            // Execute state-specific function with multiple parameters
            FUN_00512870(
                this,
                param_1,
                *(undefined2*)((int)this + 0x32),  // action parameter at +0x32
                *(short*)((int)this + 0x30)        // active flag again
            );
        }
    }
    else if (state == 6) {
        // State 6: check if the value at +0x50 is not equal to (state - 6) i.e. not 0,
        // and global time condition
        if (*(int*)((int)this + 0x50) != (int)(state - 6) && DAT_00e2af44 < *(float*)((int)this + 0x40)) {
            // Execute a different state function with only action parameter
            FUN_005118f0(*(undefined2*)((int)this + 0x32));
            return; // early return after this call
        }
    }
    // implicit return if no condition matched
}