// FUNC_NAME: AnimationStateMachine::updateStateTransitions
void AnimationStateMachine::updateStateTransitions(void)
{
    uint flags;
    int param;
    
    flags = *(uint *)(*(int *)(this + 0x68)); // +0x68: state flags pointer
    if ((flags & 0x10) == 0) {
        if (((flags & 0x20) != 0) && (0 < (short)(*(uint *)(this + 0x68))[1])) {
            if ((flags & 0x200) == 0) {
                param = *(int *)(this + 0x1c) + 1; // +0x1c: transition param A
                FUN_00589450(0, param, param); // enter state A
            }
            else {
                param = *(int *)(this + 0xc) + 1; // +0x0c: transition param B
                FUN_00589360(0, param, param); // enter state B
            }
        }
    }
    else {
        FUN_00589a90(*(int *)(this + 0x24) + 1); // +0x24: transition param C
    }
    flags = *(uint *)(*(int *)(this + 0x68));
    if ((flags & 0x40) == 0) {
        if ((char)flags < '\0') {
            param = *(int *)(this + 0x44) + 1; // +0x44: transition param D
            FUN_00589ef0(param, param); // enter state D
        }
        else if ((flags & 0x100) == 0) {
            FUN_0058a290(); // enter state E (no param)
        }
        else {
            param = *(int *)(this + 0x34) + 1; // +0x34: transition param F
            FUN_00589bf0(param, param); // enter state F
        }
    }
    else {
        FUN_0058a1f0(); // enter state G (no param)
    }
    if ((*(uint *)(*(int *)(this + 0x68)) & 0x800) != 0) {
        param = *(int *)(this + 100) + 1; // +0x64: transition param H
        FUN_0058a330(param, param); // enter state H
    }
    *(int *)(this + 0x68) = *(int *)(this + 0x68) + 8; // advance state flags pointer
    return;
}