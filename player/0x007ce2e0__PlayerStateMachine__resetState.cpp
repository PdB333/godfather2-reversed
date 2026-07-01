// FUNC_NAME: PlayerStateMachine::resetState

void __fastcall PlayerStateMachine::resetState(void *this)
{
    int *piVar1;
    int iVar2;
    char cVar3;
    undefined4 *puVar4;
    int iVar5;
    
    // Offset +0x58: pointer to GameManager or World object
    iVar2 = *(int *)((int)this + 0x58);
    
    // Start timer 0x30 (48 ticks?) — possibly a cooldown or delay
    FUN_007f63e0(0x30);
    
    // Set bit 0x800 (bit 11) in World flags at +0x24a0
    *(uint *)(iVar2 + 0x24a0) |= 0x800;
    
    // Update some global state (maybe input or rendering)
    FUN_006fd730();
    
    // If global multiplayer flag is set, render something
    if (DAT_01129944 != 0) {
        FUN_0081f300();
    }
    
    // Check if some condition is active, and if so handle it
    cVar3 = FUN_007fd720();
    if (cVar3 != '\0') {
        FUN_007fcd60();
    }
    
    // Get a pointer to an interface/object
    puVar4 = (undefined4 *)FUN_007ab160();
    // Call virtual functions on that object with magic constants
    (**(code **)*puVar4)(0x10);
    (**(code **)*puVar4)(0x20);
    (**(code **)*puVar4)(0x100);
    
    // Reset global state variables
    DAT_0112ba54 = 0;
    DAT_0112ba58 = 0;
    
    // Reset fields on the current object
    *(undefined4 *)((int)this + 0x1dc) = 0;
    *(undefined4 *)((int)this + 0x1e0) = 0;
    DAT_0112ba5c = 0;
    *(undefined4 *)((int)this + 0x1cc) = 0;
    *(uint *)((int)this + 0x1d0) &= 0xfffdffff;  // Clear some flags
    *(uint *)((int)this + 0x1d0) |= 0x100000;     // Set another flag
    
    // Set more flags on the World object
    *(uint *)(iVar2 + 0x970) |= 0x800;
    *(uint *)(iVar2 + 0x974) |= 0x800;
    
    // Call a function with parameter 0 (maybe reset something)
    FUN_009c4ea0(0);
    
    // Handle a pointer at +0x1b4 (actionable target?)
    piVar1 = (int *)((int)this + 0x1b4);
    if ((*(int *)((int)this + 0x1b4) != 0) && (*(int *)((int)this + 0x1b4) != 0x48)) {
        if (*piVar1 == 0) {
            iVar5 = 0;
        }
        else {
            iVar5 = *piVar1 - 0x48;  // Convert to base pointer
        }
        // Compare ID/owner at +0x1ed4 with the World's ID
        if (*(int *)(iVar5 + 0x1ed4) == *(int *)(*(int *)((int)this + 0x58) + 0x1ed4)) {
            FUN_007f6420(0x3c);  // Stop timer 0x3c
        }
        else {
            FUN_007f63e0(0x3c);  // Start timer 0x3c
        }
    }
    
    // Process a pointer from World at +0x30c0
    iVar2 = *(int *)(iVar2 + 0x30c0);
    if ((iVar2 != 0) && (iVar2 != 0x48)) {
        FUN_004088c0(iVar2 - 0xc);  // Release or reset object
    }
    
    // Zero out more fields
    *(undefined4 *)((int)this + 0x1a0) = 0;
    *(undefined4 *)((int)this + 0x1bc) = 0;
    *(undefined4 *)((int)this + 0x1c0) = 0;
    
    // Free the pointer at +0x1b4 if non-null
    if (*piVar1 != 0) {
        FUN_004daf90(piVar1);
        *piVar1 = 0;
    }
    
    // Set a field from a global constant
    *(undefined4 *)((int)this + 0x1c4) = _DAT_00d5780c;
    
    // Clear specific bits in flags, set a short to 1
    *(uint *)((int)this + 0x1d0) &= 0xfffe6ac1;
    *(undefined4 *)((int)this + 0x1e4) = 0;
    *(undefined4 *)((int)this + 0x1e8) = 0;
    *(undefined2 *)((int)this + 0x1d8) = 1;
    
    // Call final initialization functions
    FUN_007ce090();
    FUN_007ca8a0();
    return;
}