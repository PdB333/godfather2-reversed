// FUNC_NAME: Player::updateStateChange
void __thiscall Player::updateStateChange(int param_2) {
    int iVar1;
    int iVar2;
    undefined4 uVar3;
    char cVar4;
    bool bVar5;

    // Check if current state pointer and its base are valid
    if ((*(int *)(this + 0x33c) != 0) && (**(int **)(this + 0x338) != 0)) {
        // Get current state ID from the state object at +0x10
        iVar1 = *(int *)(**(int **)(this + 0x338) + 0x10);
        // Get target state ID via vtable call (method at vtable offset 0x9c)
        iVar2 = (**(code **)(*(int *)(this + 0x2ec) + 0x9c))(param_2, 0);
        if ((iVar1 != iVar2) && ((DAT_01223484 != 0 && (*(int *)(DAT_01223484 + 0xc) != 0)))) {
            // Determine change direction based on param_2 (0 = forward? 1 = backward?)
            if ((char)param_2 == '\0') {
                cVar4 = (iVar1 != 1) + '\x02';   // -> 2 if not in state 1, else 1?
                bVar5 = iVar1 == 3;              // true if current state is 3
            } else {
                cVar4 = (iVar1 == 3) + '\x01';   // -> 1 if in state 3, else 0?
                bVar5 = iVar1 == 1;              // true if current state is 1
            }
            if (bVar5) {
                // If specific state, just log and return
                FUN_00402050(&DAT_011302c0, 0);  // Debug log
                return;
            }
            // Otherwise log twice and perform the actual transition
            FUN_00402050(&DAT_011304d8, 0);
            FUN_00402050(&DAT_011304d8, 0);
            uVar3 = FUN_0079b4f0();             // Some global getter (perhaps current time or ID)
            FUN_009642e0(cVar4, uVar3);         // Apply state change with direction and value
        }
    }
    return;
}