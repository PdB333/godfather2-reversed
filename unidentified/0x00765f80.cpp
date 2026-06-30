// FUN_00765f80: PlayerActionableInfo::tryStartAction
bool __thiscall PlayerActionableInfo::tryStartAction(PlayerActionableInfo* this)
{
    char cVar1;
    int iVar2;

    // Dereference pointer at +0x5c (likely m_pSimManager or m_pGameManager)
    // then fetch a pointer from offset 0x24cc within that manager (maybe 
    // current vehicle or mission data)
    iVar2 = *(int*)(*(int*)((int)this + 0x5c) + 0x24cc);
    if (iVar2 == 0) {
        iVar2 = 0;
    }
    else {
        iVar2 = iVar2 + -0x48;  // Adjust pointer to get base of sub-struct (e.g., vehicle or mission object)
    }

    // Global check (e.g., is player alive or in control?)
    cVar1 = FUN_00717f40();
    if (((cVar1 != '\0') && (iVar2 != 0)) && ((*(byte*)(iVar2 + 0x8e0) & 1) != 0)) {
        // Already in an action (e.g., in vehicle, in mission) – consider as successful
        return true;
    }

    // Prepare action state machine located at this+0x70
    int actionSM = (int)this + 0x70;
    // Initialize action state machine with target data from manager +0x21dc and manager pointer
    FUN_0071a720(*(int*)(*(int*)((int)this + 0x5c) + 0x21dc), *(int*)((int)this + 0x5c), actionSM);
    // Process/update state machine
    FUN_00716420(actionSM);
    // Query result (returns 0 on success)
    cVar1 = FUN_00714770(actionSM);
    return cVar1 == '\0'; // true if success, false if failed
}