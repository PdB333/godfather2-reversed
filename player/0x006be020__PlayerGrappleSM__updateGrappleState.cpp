// FUNC_NAME: PlayerGrappleSM::updateGrappleState
void __thiscall PlayerGrappleSM::updateGrappleState(void)
{
    // Offsets:
    // +0x54: m_pCombatComponent (Component pointer)
    // +0x88: m_currentActionID (some ID compared to 0)

    bool bVar1;
    int iActionCheck;
    int iGameState;
    int iCombatComp;
    uint uGrappleFlags;

    // Check conditions for continuing/starting grapple action
    if (( (*(int*)(this + 0x54) == 0) ||
         ( (iCombatComp = FUN_006b0ee0(*(int*)(this + 0x54)), iCombatComp != 0 &&
           (bVar1 = FUN_006b4440(), bVar1) && (iCombatComp = FUN_006b4860(), iCombatComp == 0) ) ) ) &&
        ( (iActionCheck = FUN_00446100(this + 0x88, 0), iActionCheck != 0 &&
          (iGameState = FUN_007915b0(), iGameState != 0) &&
          ((~(byte)(*(uint*)(iGameState + 0x84) >> 5) & 1) != 0) ) ) &&
        ( ( (bVar1 = FUN_007900b0(), !bVar1) ||
            (iGameState = FUN_008bf2f0(iActionCheck), iGameState == 1) ) ||
          ( (iGameState == 3) &&
            (iCombatComp = *(int*)(this + 0x54), iCombatComp != 0 &&
             (iActionCheck = FUN_00790d90(), iCombatComp == iActionCheck) ) ) ) )
    {
        // Extract grapple-related flags from combat component (offset +0x5c, bit 21)
        uGrappleFlags = *(uint*)(iActionCheck + 0x5c) >> 0x15;
        if ((uGrappleFlags & 1) != 0) {
            FUN_00792560(iActionCheck); // Begin grapple action
        }

        // Handle potential target interaction
        iGameState = FUN_00791300(); // Get current target
        if ((iGameState != 0) && (bVar1 = FUN_0083e6a0(iGameState), bVar1)) {
            FUN_0083de30(iGameState); // Apply damage/hit
            FUN_006bd3a0(iGameState); // Apply knockback or animation
        }

        bVar1 = FUN_00791230(); // Check for input (e.g., attack button)
        if (bVar1) {
            FUN_00791250(this, 0xffffffff); // Transition to idle/cancel state
            return;
        }

        if ((uGrappleFlags & 1) != 0) {
            FUN_00792d80(iActionCheck); // End grapple action
        }
    }
    return;
}