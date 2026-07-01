// FUNC_NAME: PlayerController::updateMovementInput
void __thiscall PlayerController::updateMovementInput(int thisPtr, int* analogState, int* moveState, char* updated)
{
    int* pState;
    int iVar2;
    char cVar3;
    int iVar4;
    int iVar5;

    pState = analogState;
    iVar4 = thisPtr;
    *updated = 0;

    // Check if current state is some specific mode (0x9 = maybe in cover or climbing?)
    if (*(int*)(thisPtr + 0xC4) == 9) // +0xC4: currentCharacterState
    {
        iVar4 = FUN_008FF310(*(undefined4*)(thisPtr + 0x38)); // +0x38: some object pointer
        if (iVar4 != 0)
        {
            iVar4 = FUN_008FDFD0(); // Get something global?
            if (iVar4 != 0)
            {
                iVar5 = FUN_00791540(); // Get something else
                if (iVar5 != 0)
                {
                    iVar4 = FUN_008C1250(iVar4); // Lookup from manager?
                    if (iVar4 != 0)
                    {
                        cVar3 = FUN_008FE3D0(); // Check a condition? (bool)
                        if ((cVar3 != '\0') || (*(int*)(iVar4 + 4) == 1)) // +0x04: some flag
                        {
                            iVar4 = FUN_00791750(); // Get a direction index?
                            if (iVar4 == 3)
                            {
                                analogState[2] = 1; // Right?
                                return;
                            }
                            if (iVar4 == 4)
                            {
                                analogState[1] = 1; // Up?
                                return;
                            }
                            if (iVar4 == 5)
                            {
                                analogState[0] = 1; // Left? Down?
                                return;
                            }
                        }
                    }
                }
            }
        }
    }
    else
    {
        // Normal movement path (not in state 9)
        FUN_00992660(thisPtr, analogState); // Some update function
        if (*(int*)(iVar4 + 0x40) == 0x637B907) // +0x40: objectTypeId, compare to "cover" type?
        {
            cVar3 = FUN_006B34A0(); // Is player in cover?
            if (cVar3 != '\0')
            {
                thisPtr = 0; // Reset local
                FUN_00992590(iVar4, pState, pState + 1, pState + 2, &thisPtr); // Pass direction flags?
                *(undefined1*)(pState + 4) = 1; // Set a flag
            }
        }
        iVar2 = moveState;
        iVar5 = *(int*)(iVar4 + 0xFC); // +0xFC: movingTarget or other object
        if (iVar5 != 0)
        {
            // Decompose moveState into components (X, Y, Z?) and offsets
            FUN_00992500(iVar4, iVar4 + 0x84, moveState, moveState + 4, moveState + 8, moveState + 0xC);
            // Check if target is a specific type and self is not that type
            if ((*(int*)(*(int*)(iVar5 + 0x14) + 0x54) == 0x637B907) && // target type?
                (*(int*)(iVar4 + 0x40) != 0x637B907)) // self not that type
            {
                cVar3 = FUN_006B34A0();
                if (cVar3 != '\0')
                {
                    FUN_00992590(iVar4, iVar2, iVar2 + 4, iVar2 + 8, iVar2 + 0xC);
                    *(undefined1*)(iVar2 + 0x10) = 1;
                }
            }
            *updated = 1;
        }
    }
    return;
}