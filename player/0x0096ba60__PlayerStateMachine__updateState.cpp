// FUNC_NAME: PlayerStateMachine::updateState

void __fastcall PlayerStateMachine::updateState(int thisPtr)
{
    char cVar1;
    uint uVar2;
    int *piVar3;

    switch(*(undefined4 *)(thisPtr + 0xdc)) // state enum
    {
    case 2: // eReadyState_Standby?
    case 3: // eReadyState_Active?
        piVar3 = (int *)(thisPtr + 0x508); // +0x508: vtable for IStateBehavior?
        break;

    case 4: // eReadyState_Transition?
        if (*(char *)(thisPtr + 0x220) == '\0') { // bool: isTransitionAllowed?
            return;
        }
        if (g_globalBool == 0) { // some global condition
            return;
        }
        cVar1 = (**(code **)(*(int *)(thisPtr + 0x508) + 0x8c))(); // vcall at +0x8c (e.g. canTransition())
        if (cVar1 != '\0') {
            setTimer(g_defaultTimer, 0); // clear timer
            *(undefined1 *)(thisPtr + 0x6f1) = 0; // flag byte
            *(undefined1 *)(thisPtr + 0x6f0) = 0; // another flag byte
            scriptCall("SetReadyState", 0, g_readyStateData, 0); // trigger scripting event
            uVar2 = getPlayerPosition(); // might return a coordinate
            setPlayerActionTarget(*(int *)(thisPtr + 0xd4) + *(int *)(thisPtr + 0xc4), uVar2); // adjust target based on offset
            return;
        }
        goto LAB_0096ba9d;

    case 5: // eReadyState_Exit?
        setCameraState(0); // disable camera
        return;

    default:
        goto switchD_0096ba71_caseD_6;

    case 7: // eReadyState_Enter?
        setCharacterAnimation(0); // stop animation?
        return;

    case 8: // eReadyState_Post?
        piVar3 = (int *)(thisPtr + 0x63c); // +0x63c: vtable for another behavior
        break;

    case 9: // eReadyState_Complete?
        piVar3 = (int *)(thisPtr + 0x590); // +0x590: vtable for another behavior
        break;

    case 0xb: // eReadyState_Abort?
        abortStateMachine();
        return;
    }

    cVar1 = (**(code **)(*piVar3 + 0x8c))(); // virtual function at vtable+0x8c
    if (cVar1 == '\0') {
LAB_0096ba9d:
        setTimer(g_altTimer, 0); // set alternative timer
        return;
    }
    setTimer(g_defaultTimer, 0); // clear timer
switchD_0096ba71_caseD_6:
    return;
}