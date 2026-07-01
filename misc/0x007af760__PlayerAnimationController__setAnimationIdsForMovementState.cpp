// FUNC_NAME: PlayerAnimationController::setAnimationIdsForMovementState

void __thiscall PlayerAnimationController::setAnimationIdsForMovementState(int thisPtr, int movementState)
{
    // +0x78: currentAnimationId (int)
    // +0x7c: nextAnimationId (int)
    switch (movementState)
    {
    case 2: // eMovementState_Walk
    case 3: // eMovementState_Run
    case 8: // eMovementState_Sprint
        *(int*)(thisPtr + 0x78) = 0x57; // AnimationId_WalkRun
        *(int*)(thisPtr + 0x7c) = 0x58; // AnimationId_WalkRunTransition
        break;
    case 6: // eMovementState_Idle
    case 7: // eMovementState_Idle2
    case 10: // eMovementState_Stand
        *(int*)(thisPtr + 0x78) = 0x53; // AnimationId_Idle
        *(int*)(thisPtr + 0x7c) = 0x54; // AnimationId_IdleTransition
        break;
    case 0x14: // 20 - eMovementState_CombatWalk
    case 0x15: // 21 - eMovementState_CombatRun
    case 0x1a: // 26 - eMovementState_CombatSprint
        *(int*)(thisPtr + 0x78) = 0x59; // AnimationId_CombatWalk
        *(int*)(thisPtr + 0x7c) = 0x5a; // AnimationId_CombatRun
        break;
    case 0x18: // 24 - eMovementState_CrouchWalk
    case 0x19: // 25 - eMovementState_CrouchRun
    case 0x1c: // 28 - eMovementState_CrouchSprint
        *(int*)(thisPtr + 0x78) = 0x55; // AnimationId_CrouchWalk
        *(int*)(thisPtr + 0x7c) = 0x56; // AnimationId_CrouchRun
        break;
    }
}