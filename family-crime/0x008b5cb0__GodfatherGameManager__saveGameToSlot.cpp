// FUNC_NAME: GodfatherGameManager::saveGameToSlot
bool __fastcall GodfatherGameManager::saveGameToSlot(int *this)
{
    int *piVar1;
    int iVar2;
    undefined4 uVar3;
    int iVar4;
    undefined1 auStack_424 [1060];
    
    iVar4 = -1;
    piVar1 = (int *)FUN_00ad8d40(); // Get GodfatherGameManager singleton
    if (piVar1 != (int *)0x0) {
        iVar2 = (**(code **)(*piVar1 + 0x34))(); // Get current game state
        if (iVar2 != 0) {
            piVar1 = (int *)(**(code **)(*piVar1 + 0x34))(); // Get game state again
            piVar1 = (int *)(**(code **)(*piVar1 + 0x24))(); // Get save manager
            if (piVar1 != (int *)0x0) {
                uVar3 = (**(code **)(*this + 0x10))(); // Get save slot index
                FUN_00b21d90(uVar3); // Prepare save data
                FUN_00b21ed0(this); // Write save data
                iVar4 = (**(code **)(*piVar1 + 0x30))(auStack_424,1,0); // Save to file
                FUN_00b19550(); // Cleanup
            }
        }
    }
    return -1 < iVar4;
}