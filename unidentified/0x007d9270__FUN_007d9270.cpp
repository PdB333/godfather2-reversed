// FUNC_NAME: SomeClass::handleAllowedStateTransition
bool __fastcall SomeClass::handleAllowedStateTransition(void* this) {
    char cVar1;
    int iVar2;
    char* pcVar3;
    int local_24, local_20, local_1c, local_c, local_4;

    cVar1 = IsGameActive(); // FUN_00481620
    if (cVar1 != '\0' && 
       ((*(uint*)(*(int*)((char*)this + 0x58) + 0x24a0) >> 0x14 & 1) == 0)) {
        cVar1 = IsMenuAllowed(); // FUN_007d9200
        if (cVar1 != '\0') {
            iVar2 = GetCurrentGameMode(); // FUN_007a5f40
            if ((iVar2 != 1 && iVar2 != 2) ||
               ((*(uint*)(*(int*)((char*)this + 0x58) + 0x24a0) >> 0x13 & 1) != 0)) {
                cVar1 = IsCutsceneActive(); // FUN_007d89f0
                if (cVar1 != '\0') {
                    iVar2 = GetSomethingElse(); // FUN_007ab1f0
                    if (iVar2 != 0) {
                        cVar1 = IsAnotherConditionMet(); // FUN_00701820
                        if (cVar1 != '\0') {
                            iVar2 = CheckConditionA(); // FUN_007013c0
                            if (iVar2 == 0) {
                                iVar2 = CheckConditionB(); // FUN_007057c0
                                if (iVar2 == 0) {
                                    cVar1 = IsGameActive(); // FUN_00481620
                                    if (cVar1 == '\0') {
                                        return 1;
                                    }
                                    ShowMessage(0); // FUN_004a8ec0
                                    local_1c = 1; // simplified from CONCAT31
                                    // original: FUN_0079fb90(2, CONCAT44(5,local_1c?), CONCAT44(local_20,local_24), local_c, local_4);
                                    SendUICommand(2, 5, local_1c, local_20, local_24, local_c, local_4); // FUN_0079fb90
                                    return 1;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    cVar1 = IsPauseMenuAllowed(); // FUN_00481640
    if (cVar1 != '\0') {
        pcVar3 = (char*)(*(int*)((char*)this + 0x58) + 0x21d0);
        if (*pcVar3 == '\0') {
            iVar2 = IsMenuOpen(); // FUN_004a8f00
            if (iVar2 == 0) {
                *pcVar3 = '\x01';
                return 1;
            }
        }
    }
    return 0;
}