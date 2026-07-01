// FUNC_NAME: ActionNode::shouldExecute
undefined4 __fastcall ActionNode::shouldExecute(int this) {
    char cVar1;
    undefined4 uVar2;
    int iVar3;
    int *piVar4;
    undefined4 coords[2]; // local_10, local_c (xy pair)
    undefined4 velocity; // local_8
    undefined4 distSquared; // local_4

    // Check if action is complete (bit0 set) OR time is zero OR time == 0x48 (72 seconds?)
    if ((((*(byte *)(this + 0x70) & 1) != 0) || (*(int *)(this + 0x50) == 0)) ||
       (*(int *)(this + 0x50) == 0x48)) {
        return 1; // Should not execute
    }

    // Get position from either base alignment or offset alignment
    if ((*(uint *)(this + 0x70) >> 7 & 1) == 0) {
        // Use base position
        coords[0] = *(undefined4 *)(this + 0x5c);
        coords[1] = *(undefined4 *)(this + 0x60);
    } else {
        // Use offset position (this + 0x64, this + 0x68)
        coords[0] = *(undefined4 *)(this + 100); // 0x64
        coords[1] = *(undefined4 *)(this + 0x68);
    }

    uVar2 = FUN_00875b40(&coords); // Some vector/point conversion
    cVar1 = FUN_0045ef10(uVar2);   // Check if point is valid/loaded? (related to navigation/pathing)
    
    if (cVar1 == '\0') {
        // Point is valid, check distance to player/item
        velocity = 0;
        distSquared = 0;
        
        // Get player controller pointer (+0x50 points to some object - likely BSSPlayer?)
        if (*(int *)(this + 0x50) == 0) {
            piVar4 = (int *)0x0;
        } else {
            piVar4 = (int *)(*(int *)(this + 0x50) + -0x48); // Cast from BSSPlayer or similar
        }
        
        // Call virtual function at vtable offset 0x1ec (getCharacterPosition?)
        (**(code **)(*piVar4 + 0x1ec))(&coords, &velocity);
        
        // Get distance from player to action position
        if (*(int *)(this + 0x50) == 0) {
            piVar4 = (int *)0x0;
        } else {
            piVar4 = (int *)(*(int *)(this + 0x50) + -0x48);
        }
        
        iVar3 = (**(code **)(*piVar4 + 500))(&coords); // Compute squared distance (0x1F4 = 500)
        
        if (iVar3 == 0) {
            return 1; // Too close? Can't execute
        }
        
        if (iVar3 == *(int *)(this + 0x58)) {
            return 1; // At exact range, don't execute again
        }
    }
    
    return 0; // Should execute
}