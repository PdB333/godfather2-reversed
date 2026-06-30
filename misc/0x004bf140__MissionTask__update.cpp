// FUNC_NAME: MissionTask::update
void __fastcall MissionTask::update(int thisPtr)
{
    int *piVar1;
    char cVar2;
    undefined4 uVar3;
    int iVar4;
    undefined4 local_c;
    undefined4 local_8;
    undefined1 local_4;

    // Get timer value from state machine vtable (index 0x24 = getTimer?)
    uVar3 = (**(code **)(**(int **)(thisPtr + 0x34) + 0x24))();
    *(undefined4 *)(thisPtr + 0xc) = uVar3;

    // Check if state machine needs to transition (vtable index 0x3c = checkTransition?)
    iVar4 = (**(code **)(**(int **)(thisPtr + 0x34) + 0x3c))();
    if (iVar4 != 0) {
        FUN_005683c0(); // likely mission event or callback
    }

    if (*(int *)(thisPtr + 0xc) == 0) {
        // Timer expired
        if ((*(int *)(thisPtr + 0x36c) != 0) && (DAT_0122344c != (undefined4 *)0x0)) {
            (**(code **)*DAT_0122344c)(1); // notify global game interface
        }
        *(undefined4 *)(thisPtr + 0x36c) = 0; // clear task data pointer
    }
    else {
        // Timer still running: decrement a sub-counter
        piVar1 = (int *)(*(int *)(thisPtr + 0x36c) + 100);
        *piVar1 = *piVar1 + -1;
        if ((*piVar1 == 0) && (DAT_01206940 != 0)) {
            cVar2 = FUN_00402080(&DAT_01206940); // acquire lock?
            if (cVar2 == '\0') {
                _DAT_01206944 = _DAT_01206944 + 1;
                FUN_004084d0(&DAT_01206940, 0x8000); // allocate resource?
            }
        }

        if (*(int *)(thisPtr + 8) != 0) {
            FUN_00453eb0(); // send network update?
        }

        FUN_004cb900(*(undefined4 *)(*(int *)(thisPtr + 0x36c) + 0x14)); // perform task action
    }

    // Cleanup stack local (actually just some global data reset)
    local_c = DAT_01218060;
    local_8 = 0;
    local_4 = 0;
    FUN_00408a00(&local_c, 0); // reset timer or state
    return;
}