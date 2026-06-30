// FUNC_NAME: PlayerMissionState::checkObjectiveTrigger
void __thiscall PlayerMissionState::checkObjectiveTrigger(int this) {
    int iVar1;
    
    // Check if state flag at +0xc4 is zero (e.g., objective not yet triggered)
    if (*(int *)(this + 0xc4) == 0) {
        // Dispatch first event/hash (likely objective activation)
        FUN_00894c90(0x8441d639);
        
        // Lookup an entity or component by hash 0x637b907 (e.g., a specific target)
        iVar1 = FUN_008c74d0(0x637b907);
        
        // If found and its owner matches current player (global +0x40)
        if ((iVar1 != 0) && (*(int *)(iVar1 + 0x118) == *(int *)(DAT_0112a558 + 0x40))) {
            // Dispatch second event/hash (e.g., objective completed)
            FUN_00894c90(0xdfa40562);
        }
    }
    return;
}