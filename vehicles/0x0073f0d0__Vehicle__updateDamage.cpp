// FUNC_NAME: Vehicle::updateDamage

void __thiscall Vehicle::updateDamage(void)
{
    char cVar1;
    int iVar2;
    int iVar3;
    int iVar4;

    iVar2 = getGameState(); // FUN_00806440
    if (iVar2 == 3) // In-game state?
    {
        // +0x58 likely a pointer to a base/parent object
        if (*(int *)(this + 0x58) == 0)
        {
            iVar2 = 0;
        }
        else
        {
            iVar2 = *(int *)(this + 0x58) - 0x48; // Adjust to get container structure
        }
        // Check class ID at +0x1ed4 (likely vehicle ID constant)
        if (*(int *)(iVar2 + 0x1ed4) != 0x637b907)
        {
            // Second check with same pattern
            if (*(int *)(this + 0x58) == 0)
            {
                iVar2 = 0;
            }
            else
            {
                iVar2 = *(int *)(this + 0x58) - 0x48;
            }
            if (*(int *)(iVar2 + 0x2134) != 0) // Pointer to some component or entity
            {
                if (*(int *)(this + 0x58) == 0)
                {
                    iVar2 = 0;
                }
                else
                {
                    iVar2 = *(int *)(this + 0x58) - 0x48;
                }
                // Get entity from +0x2134
                iVar2 = getEntity(*(undefined4 *)(iVar2 + 0x2134)); // FUN_006b07e0
                if (((((iVar2 != 0) &&
                      (iVar3 = *(int *)(iVar2 + 0x180), // Pointer to damage/effect system
                       *(int *)(iVar3 + 0x40) != 0x637b907)) && // Another class ID check
                     (cVar1 = isPlayerInControl(), cVar1 != '\0')) && // FUN_0073ec80
                    ((*(int *)(iVar3 + 0xfc) == 0 && ((*(uint *)(iVar3 + 0x34) >> 0x1c & 1) == 0)))) && // Flag checks
                   (iVar3 = isCutsceneActive(), iVar3 == 0)) // FUN_006b4860
                {
                    if (*(int *)(this + 0x58) == 0)
                    {
                        iVar3 = 0;
                    }
                    else
                    {
                        iVar3 = *(int *)(this + 0x58) - 0x48;
                    }
                    iVar3 = *(int *)(iVar3 + 0x2230); // Linked list head
                    if (iVar3 != 0)
                    {
                        while ((iVar4 = getNextEntityIterator(), // FUN_0071c120 (maybe global iterator)
                                iVar4 == 0 || (*(int *)(iVar4 + 0x1ed4) != 0x637b907)))
                        {
LAB_0073f1e7:
                            iVar3 = *(int *)(iVar3 + 4); // Next in linked list
                            if (iVar3 == 0)
                            {
                                return;
                            }
                        }
                        if (*(int *)(iVar4 + 0x1ee8) != *(int *)(iVar2 + 0x184)) // Compare some IDs
                        {
                            iVar4 = getLocalPlayer(); // FUN_00471610
                            cVar1 = isAlive(iVar4 + 0x30); // FUN_006aed40
                            if (cVar1 == '\0') goto LAB_0073f1e7;
                        }
                        applyDamageToVehicle(*(undefined4 *)(iVar2 + 0x180)); // FUN_008c7e30
                    }
                }
            }
        }
    }
    return;
}