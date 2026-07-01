// FUNC_NAME: MissionManager::displayObjective
void __thiscall MissionManager::displayObjective(MissionManager* thisPtr, MissionObjectiveData* objectiveData)
{
    int iVar1;
    int iVar2;
    
    iVar1 = **(int**)(objectiveData + 4); // dereference pointer at +0x4 -> maybe mission ID
    iVar2 = getCurrentMissionID(); // FUN_0099c490 -> global or static current mission ID
    if ((iVar1 == iVar2) && (*(int*)(objectiveData + 0x24) == 0)) // check mission ID matches and objective not completed
    {
        if (*(char*)(thisPtr + 0x14) != '\0') // if flag at this+0x14 is true (alternate display mode?)
        {
            showObjectiveWithIcon( // FUN_00953990
                objectiveData,
                *(uint32_t*)(thisPtr + 4),   // title text ID
                *(uint32_t*)(thisPtr + 8),   // description text ID
                *(uint32_t*)(thisPtr + 0xc), // icon ID
                *(uint32_t*)(thisPtr + 0x10),// optional param
                *(char*)(thisPtr + 0x14),    // bool flag
                *(uint32_t*)(thisPtr + 0x18),// subtext ID
                *(uint32_t*)(thisPtr + 0x1c) // timer/duration
            );
            return;
        }
        showObjectivePlain( // FUN_009539f0
            objectiveData,
            *(uint32_t*)(thisPtr + 4),
            *(uint32_t*)(thisPtr + 8),
            *(uint32_t*)(thisPtr + 0xc),
            *(uint32_t*)(thisPtr + 0x10),
            0,                               // bool flag forced to false
            *(uint32_t*)(thisPtr + 0x18),
            *(uint32_t*)(thisPtr + 0x1c)
        );
    }
    return;
}