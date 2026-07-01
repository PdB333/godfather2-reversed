// FUNC_NAME: StateMachine::setState
void __thiscall StateMachine::setState(void* this, int stateParam, int stateId)
{
    switch (stateId) {
    case 0:
    case 3:
    case 4:
        *(char*)((int)this + 0xc) = 0;           // +0xc: some flag (byte)
        *(int*)((int)this + 0x18) = -1;           // +0x18: timeout or reference
        *(int*)((int)this + 0x8) = stateId;       // +0x8: current state
        return;
    case 5:
        *(int*)((int)this + 0x18) = 0;            // +0x18
        *(int*)((int)this + 0x1c) = 0;            // +0x1c
        *(int*)((int)this + 0x20) = 8;            // +0x20
        // Fall through to case 1,2,8,9
    case 1:
    case 2:
    case 8:
    case 9:
        *(int*)((int)this + 0x14) = stateParam;   // +0x14: parameter associated with state
        // Fall through to default
    default:
        *(int*)((int)this + 0x8) = stateId;       // +0x8: set current state
        return;
    }
}