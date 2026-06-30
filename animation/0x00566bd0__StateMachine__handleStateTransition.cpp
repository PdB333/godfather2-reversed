// FUNC_NAME: StateMachine::handleStateTransition

void __thiscall StateMachine::handleStateTransition(void *this) {
    int *piVar1;
    undefined4 *puVar2;

    int state = *(int *)((char *)this + 0x10);
    if (state != 1) {
        if (state == 7) {
            piVar1 = (int *)FUN_00ad8d40(); // Get singleton manager
            puVar2 = (undefined4 *)(**(code **)(*piVar1 + 4))(); // Get manager's child object
            if (puVar2 != (undefined4 *)0x0) {
                piVar1 = (int *)(**(code **)*puVar2)(); // Get manager's manager
                if (piVar1 != (int *)0x0) {
                    (**(code **)(*piVar1 + 0x20))(*(undefined4 *)((char *)this + 0x100)); // Call method with parameter at +0x100
                }
            }
        }
        // Transition to state 0
        *(int *)((char *)this + 0x10) = 0;
        *(int *)((char *)this + 0x14) = 2; // Sub-state set to 2
    }
    // Clear flags: bit 2 (0x04) and bit 7 (0x80)
    *(unsigned int *)((char *)this + 0x2c) &= 0xffffff7b;
}