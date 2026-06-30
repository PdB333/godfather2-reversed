// FUNC_NAME: NPC::checkForAction
// Address: 0x00753d80
// Checks if the NPC can perform an autonomous action.
// If the NPC is not dead/disabled (bit0 of flags at +0xA4 clear) and
// the behavior component (pointer at +0x50) has its "scripted" flag (byte at +0x1B8C) as zero,
// then calls the action function.
void __thiscall NPC::checkForAction(NPC* this) {
    // +0xA4: flags byte (bit0 = dead/disabled?)
    bool isActive = (*(uint8_t*)((uint8_t*)this + 0xA4) & 1) == 0;
    // +0x50: pointer to behavior component (e.g., AIBrain, BehaviorState)
    uint8_t* behaviorPtr = *(uint8_t**)((uint8_t*)this + 0x50);
    // +0x1B8C: offset within behavior component for a scripted flag
    bool isScripted = *(char*)(behaviorPtr + 0x1B8C) != '\0';

    if (isActive && !isScripted) {
        // Perform the actual autonomous action (decompiled as FUN_00752f70)
        NPC::performAutonomousAction(this);
    }
}