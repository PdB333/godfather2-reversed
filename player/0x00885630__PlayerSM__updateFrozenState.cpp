// FUNC_NAME: PlayerSM::updateFrozenState
void __fastcall PlayerSM::updateFrozenState(PlayerSM* thisPtr)

{
    uint* puVar1;
    int iVar2;
    int iVar3;
    undefined4 uVar4;
    int* piVar5;
    undefined4 local_c;
    float fStack_8;
    undefined4 local_4;
    
    // Get the game manager instance
    iVar3 = GameManager::getInstance(); // FUN_00471610
    
    // Copy game time data into local struct (likely time of day or game timer)
    local_4 = *(undefined4*)(iVar3 + 0x38); // +0x38: game time fractional part
    fStack_8 = (float)((ulonglong)*(undefined8*)(iVar3 + 0x30) >> 0x20); // +0x30: game time high part
    local_c = CONCAT44(fStack_8 + DAT_00d5ca18, (int)*(undefined8*)(iVar3 + 0x30));
    
    // Call some method on the player state object (likely updateTimer or similar)
    (**(code**)(**(int**)(thisPtr + 0x58) + 0x1c))(&local_c);
    
    // Clear/update some global data
    FUN_007f89d0(&DAT_00d77000);
    
    // Check if certain flags are set on the player -> 0x1b94 bit 0x15 (bit 21)
    if ((*(uint*)(*(int*)(thisPtr + 0x58) + 0x1b94) >> 0x15 & 1) == 0) {
        FUN_007f9340(1, 1);
    }
    
    // Dereference thisPtr+0x50 to get some object, subtract 0x48 (likely offset to parent struct)
    if (*(int*)(thisPtr + 0x50) == 0) {
        iVar3 = 0;
    }
    else {
        iVar3 = *(int*)(thisPtr + 0x50) - 0x48;
    }
    
    iVar2 = *(int*)(thisPtr + 0x58);
    piVar5 = (int*)(iVar2 + 0x1e90); // +0x1e90: some linked list node or pointer
    
    if (iVar3 == 0) {
        iVar3 = 0;
    }
    else {
        iVar3 = iVar3 + 0x48;
    }
    
    if (*piVar5 != iVar3) {
        if (*piVar5 != 0) {
            FUN_004daf90(piVar5); // Remove from list
        }
        *piVar5 = iVar3;
        if (iVar3 != 0) {
            *(undefined4*)(iVar2 + 0x1e94) = *(undefined4*)(iVar3 + 4);
            *(int**)(iVar3 + 4) = piVar5; // Insert into linked list
        }
    }
    
    // Get object from thisPtr+0x50 again, subtract 0x48
    if (*(int*)(thisPtr + 0x50) == 0) {
        piVar5 = (int*)0x0;
    }
    else {
        piVar5 = (int*)(*(int*)(thisPtr + 0x50) - 0x48);
    }
    
    // Call virtual method at offset 0x26c on the player state object with the player as arg
    (**(code**)(*piVar5 + 0x26c))(*(undefined4*)(thisPtr + 0x58));
    
    // Same pattern for method at offset 0x204
    if (*(int*)(thisPtr + 0x50) == 0) {
        piVar5 = (int*)0x0;
    }
    else {
        piVar5 = (int*)(*(int*)(thisPtr + 0x50) - 0x48);
    }
    (**(code**)(*piVar5 + 0x204))(*(undefined4*)(thisPtr + 0x58), thisPtr + 0x5c);
    
    FUN_007f6420(4);
    
    puVar1 = (uint*)(*(int*)(thisPtr + 0x58) + 0x1b94);
    *puVar1 = *puVar1 & 0xf7ffffff; // Clear bit 27 (frozen state flag?)
    
    if ((*(byte*)(thisPtr + 0x70) & 1) == 0) {
        piVar5 = *(int**)(thisPtr + 0x58);
        FUN_00737e60(); // Reset some animation state
        iVar3 = *piVar5;
        uVar4 = FUN_007347e0(0, 1); // Get some object
        (**(code**)(iVar3 + 0x14c))(uVar4); // Call method on the object
        puVar1 = (uint*)(piVar5 + 0x7d6);
        *puVar1 = *puVar1 & 0xffffdfff; // Clear bit 13
    }
    
    (**(code**)(**(int**)(thisPtr + 0x58) + 0x70))(); // Call update method on player
    FUN_005512c0(3); // Set some global state
    
    *(uint*)(thisPtr + 0x70) = *(uint*)(thisPtr + 0x70) | 0x10; // Set flag bit 4
    return;
}