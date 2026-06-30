//FUNC_NAME: ActionHandler::processAction
// Function address: 0x006cf290
// This function processes an action command from param_2.
// It checks if the action ID matches stored IDs and performs state changes.

void __thiscall ActionHandler::processAction(int* param_2) // param_1 = this
{
    int iVar1;
    char cVar2;
    int iVar3;
    // Stack structure passed to virtual function at vtable+0x24
    struct {
        char data[4]; // local_20
        int extra;    // uStack_1c
    } stackBuf;

    // Initialize action data (param_2 might be an action structure)
    initializeActionData(param_2); // FUN_0046c6a0

    iVar1 = g_globalFlag; // DAT_0112a834

    // Check if the action ID matches either of the two stored action IDs
    if ((*param_2 == this->actionId1) || (*param_2 == this->actionId2)) // +0x78, +0x80
    {
        if (g_globalFlag != 0)
        {
            cVar2 = isGameActive(); // FUN_00481640
            if (cVar2 != '\0')
            {
                cVar2 = isCutsceneActive(); // FUN_0089c630
                if ((cVar2 == '\0') && (param_2[1] != 0))
                {
                    iVar3 = *(int *)(param_2[1] + 4);
                    if (iVar3 == 0)
                    {
                        iVar3 = 0;
                    }
                    else
                    {
                        iVar3 = iVar3 - 0x48;
                    }
                    cVar2 = isPlayerAlive(); // FUN_00481620
                    if (cVar2 != '\0')
                    {
                        // Call virtual function at vtable offset 0x24
                        // vtable is at this - 0x3c (derived class start)
                        (**(code **)(*(int *)((char*)this - 0x3c) + 0x24))(&stackBuf);

                        if (*param_2 == this->actionId1) // +0x78
                        {
                            // Handle action 1
                            triggerEffect(*(int *)(iVar3 + 0x1ef4)); // FUN_006ceda0
                            setActionState(*(char *)(iVar3 + 0x1ef4), iVar1, stackBuf.extra); // FUN_0089bdf0
                            return;
                        }
                        // Handle action 2
                        this->state = 2; // +0x88
                        setActionState(0xff, iVar1, stackBuf.extra); // FUN_0089bdf0
                    }
                }
            }
        }
    }
    return;
}