//FUNC_NAME: PlayerStateMachine::updateState
void __thiscall PlayerStateMachine::updateState(int this) {
    char cVar1;
    int* piVar3;

    switch (*(int*)(this + 0xDC)) { // current state ID
    case 2:
    case 3:
        piVar3 = (int*)(this + 0x508); // pointer to sub-object (e.g., behavior component)
        break;
    case 4:
        if (*(char*)(this + 0x220) == '\0') { // some flag (e.g., isActive)
            return;
        }
        if (DAT_01223484 == 0) { // global flag (e.g., game paused)
            return;
        }
        cVar1 = (**(code**)(*(int*)(this + 0x508) + 0x88))(); // virtual call: subObject->canTransition()
        if (cVar1 != '\0') {
            FUN_00402050(&DAT_011304d8, 0); // clear buffer or reset something
            *(char*)(this + 0x6F1) = 0; // flag1
            *(char*)(this + 0x6F0) = 0; // flag2
            FUN_005a04a0("SetReadyState", 0, &DAT_00d8cdec, 0); // debug/log
            int uVar2 = FUN_00962eb0(); // get some time value
            FUN_009643f0(*(int*)(this + 0xD4) + *(int*)(this + 0xC4), uVar2); // update animation or position
            return;
        }
        goto LAB_0096b97d;
    case 5:
        FUN_009654f0(1); // enter state 5
        return;
    default:
        goto switchD_0096b951_caseD_6;
    case 7:
        FUN_009653f0(1); // enter state 7
        return;
    case 8:
        piVar3 = (int*)(this + 0x63C); // another sub-object pointer
        break;
    case 9:
        piVar3 = (int*)(this + 0x590); // another sub-object pointer
        break;
    case 0xB:
        FUN_0096a870(); // handle state 0xB
        return;
    }

    cVar1 = (**(code**)(*piVar3 + 0x88))(); // virtual call on selected sub-object
    if (cVar1 == '\0') {
LAB_0096b97d:
        FUN_00402050(&DAT_011302c0, 0); // clear buffer or reset
        return;
    }
    FUN_00402050(&DAT_011304d8, 0); // clear buffer
switchD_0096b951_caseD_6:
    return;
}