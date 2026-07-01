// FUNC_NAME: GodfatherGameManager::showPaydayMessage
void __thiscall GodfatherGameManager::showPaydayMessage(int this, int param2, int param3)
{
    undefined1 *puVar1;
    undefined1 *puVar2;
    undefined1 *puVar3;
    undefined2 *puVar4;
    undefined4 local_3c;
    undefined4 local_38;
    undefined1 local_34;
    undefined1 *local_30;
    undefined4 local_2c;
    undefined4 local_28;
    code *local_24;
    undefined1 *local_20;
    undefined4 local_1c;
    undefined4 local_18;
    code *local_14;
    undefined1 *local_10;
    undefined4 local_c;
    undefined4 local_8;
    code *local_4;
    
    local_10 = (undefined1 *)0x0;
    local_c = 0;
    local_8 = 0;
    local_4 = (code *)0x0;
    local_20 = (undefined1 *)0x0;
    local_1c = 0;
    local_18 = 0;
    local_14 = (code *)0x0;
    local_30 = (undefined1 *)0x0;
    local_2c = 0;
    local_28 = 0;
    local_24 = (code *)0x0;
    FUN_00604000(param2, &local_10, 1);  // Convert param2 to string
    FUN_00604000(param3, &local_20, 1);  // Convert param3 to string
    FUN_00604000(param2 - param3, &local_30, 1);  // Convert difference to string
    
    puVar1 = local_10;
    puVar2 = local_20;
    puVar3 = local_30;
    if (param2 - param3 < 0) {
        if (local_30 == (undefined1 *)0x0) {
            puVar3 = &DAT_0120546e;  // Default string for negative difference
        }
        if (local_20 == (undefined1 *)0x0) {
            puVar2 = &DAT_0120546e;
        }
        if (local_10 == (undefined1 *)0x0) {
            puVar1 = &DAT_0120546e;
        }
        puVar4 = &DAT_00d68478;  // Negative sign indicator
    }
    else {
        if (local_30 == (undefined1 *)0x0) {
            puVar3 = &DAT_0120546e;
        }
        if (local_20 == (undefined1 *)0x0) {
            puVar2 = &DAT_0120546e;
        }
        if (local_10 == (undefined1 *)0x0) {
            puVar1 = &DAT_0120546e;
        }
        puVar4 = (undefined2 *)&DAT_00d6847c;  // Positive sign indicator
    }
    FUN_005a04a0("ShowPaydayMessage", 0, &DAT_00d8a64c, 4, puVar1, puVar2, puVar3, puVar4);  // Show payday message UI
    
    *(uint *)(this + 0x5c) = *(uint *)(this + 0x5c) | 0x100000;  // Set flag at +0x5c
    
    local_3c = DAT_01130460;
    local_38 = 0;
    local_34 = 0;
    FUN_00408a00(&local_3c, 0);  // Play sound effect
    
    if (local_30 != (undefined1 *)0x0) {
        (*local_24)(local_30);  // Free string
    }
    if (local_20 != (undefined1 *)0x0) {
        (*local_14)(local_20);
    }
    if (local_10 != (undefined1 *)0x0) {
        (*local_4)(local_10);
    }
    return;
}