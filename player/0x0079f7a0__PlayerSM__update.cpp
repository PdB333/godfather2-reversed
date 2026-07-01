// FUNC_NAME: PlayerSM::update
void __thiscall PlayerSM::update(int thisPtr, int param2) {
    int iVar1 = someGlobalCheck(); // FUN_007fd760 – probably checks state machine viability
    if (iVar1 == 0) {
        int* pSub = *(int**)(thisPtr + 0x3104); // +0x3104: pointer to a sub‑state tracking object
        if (pSub == 0) {
            iVar1 = 0;
        } else {
            // convert pointer to base of containing struct (field at +0x48)
            iVar1 = (int)pSub - 0x48;
        }
    }
    updateStateMachine(iVar1); // FUN_0079f690 – update the (sub) state machine
    handleSecondaryInput(param2); // FUN_008055e0 – process input/action from param2
}