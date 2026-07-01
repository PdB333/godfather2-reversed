// FUNC_NAME: MissionManager::createMission
void __thiscall MissionManager::createMission(int thisPtr, undefined4 param2, undefined4 param3, int *factoryInterface)
{
    int in_EAX;
    int newMission;
    char *sourceString;
    undefined4 uVar2;
    int *piVar3;
    char uVar4;
    int unaff_EBX;
    bool in_ZF;
    size_t copyCount;

    // in_ZF is the zero flag from a previous comparison; if not zero, skip creation
    if (!in_ZF) {
        param2 = in_EAX;  // param2 gets the value from EAX (likely a mission type or ID)
        newMission = FUN_009c8e50(0x60);  // allocate 96 bytes for a new mission object
        uVar4 = (char)unaff_EBX;  // unaff_EBX is likely 0
        if (newMission == unaff_EBX) {
            newMission = 0;  // allocation failed
        }
        else {
            // Initialize the new mission object
            FUN_008a2dd0(unaff_EBX, 3, unaff_EBX, unaff_EBX, 0);  // likely memset or init
            *(int *)(newMission + 0x50) = unaff_EBX;  // +0x50: some pointer, set to 0
            *(int *)(newMission + 0x54) = unaff_EBX;  // +0x54: another pointer, set to 0
            *(char *)(newMission + 0x58) = uVar4;     // +0x58: byte, set to 0
            *(char *)(newMission + 0x59) = uVar4;     // +0x59: byte, set to 0
            *(int *)(newMission + 0x5c) = unaff_EBX;  // +0x5c: int, set to 0
        }
        copyCount = 0x30;  // 48 bytes
        // Get a string from the factory interface (vtable offset +4)
        sourceString = (char *)(**(code **)(*factoryInterface + 4))();
        _strncpy((char *)(newMission + 0x20), sourceString, copyCount);  // copy name to +0x20
        *(char *)(newMission + 0x4f) = uVar4;   // +0x4f: byte, set to 0
        *(char *)(newMission + 0x58) = uVar4;   // +0x58: byte, set to 0 (again)
        *(int *)(newMission + 0x10) = 2;        // +0x10: type field, set to 2
        // Get another value from factory interface (vtable offset +0xc)
        uVar2 = (**(code **)(*factoryInterface + 0xc))();
        *(int *)(newMission + 0x5c) = uVar2;    // +0x5c: set to that value
        // Check if param2+8 is zero (param2 is likely a pointer to some object)
        if (*(int *)(param2 + 8) == unaff_EBX) {
            // Call a method on thisPtr+0x378 (likely a sub-manager)
            (**(code **)(*(int *)(thisPtr + 0x378) + 0x88))(newMission);
        }
        else {
            // Call a method on thisPtr+0x2ec (another sub-manager)
            (**(code **)(*(int *)(thisPtr + 0x2ec) + 0x88))();
            uVar2 = (**(code **)(*factoryInterface + 0xc))();
            FUN_009646b0(uVar2);  // some function
        }
        // Switch on the mission type stored at thisPtr+0xdc
        switch(*(int *)(thisPtr + 0xdc)) {
        case 1:  // Mission type 1
            *(int *)(thisPtr + 0x1e4) = 3;  // set some state
            FUN_008a3be0(thisPtr + 0x1a8);  // start a timer or state machine
            *(int *)(newMission + 0x14) = 1;  // mission state = 1 (active?)
            FUN_00967d70(1);  // set something
            FUN_00962d80();   // start mission logic
            FUN_00970f10();   // update UI or something
            break;
        case 3:  // Mission type 3
            *(int *)(newMission + 0x14) = 4;  // mission state = 4 (completed?)
            return;
        case 0xc:  // Mission type 12
            FUN_00967c80(*(int *)(thisPtr + 0x6e8));  // handle mission complete with parameter
        case 5:
        case 7:
        case 0xb:  // Fall through for types 5,7,11
            *(int *)(newMission + 0x14) = 4;  // mission state = 4
            newMission = FUN_00965910();  // get current mission or active mission
            if (newMission != 0) {
                piVar3 = (int *)FUN_00965910();  // get again? maybe different
                (**(code **)(*piVar3 + 0x94))();  // call virtual function on that mission
                return;
            }
        }
    }
    return;
}