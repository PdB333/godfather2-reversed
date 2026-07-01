// FUNC_NAME: SimNpc::updateCombatState

void __fastcall SimNpc::updateCombatState(SimNpc* this)
{
    char cVar1;
    uint uVar2;
    int* piVar3;
    float10 fVar4;

    cVar1 = isInCombatAction(); // 0x00778fd0 - checks if currently in combat action
    if ((*(uint*)(this + 0x90) >> 4 & 1) == 0) { // +0x90: combatStateFlags
        *(uint*)(this + 0x90) = *(uint*)(this + 0x90) | 0x22; // Set bits 1 and 5 (0x02=hasTarget, 0x20=unknown)
        return;
    }
    // Check if we have a current target
    if ((*(int*)(this + 0x88) != 0) && (*(int*)(this + 0x88) != 0x48)) { // +0x88: currentTarget pointer
        // Get the target's type/class pointer (offset -0x48 for vtable)
        if (*(int*)(this + 0x88) == 0) {
            piVar3 = (int*)0x0;
        } else {
            piVar3 = (int*)(*(int*)(this + 0x88) + -0x48);
        }
        fVar4 = (float10)(**(code**)(*piVar3 + 0x1a8))(); // vtable+0x1a8 - likely getDistanceToTarget()
        if ((float10)_DAT_00d6835c < fVar4) { // _DAT_00d6835c = some combat range threshold
            *(uint*)(this + 0x90) = *(uint*)(this + 0x90) | 4; // Set bit 2 (0x04 = tooFarFromTarget)
            if (cVar1 == '\0') {
                return;
            }
            DAT_012054b4 = DAT_012054b4 + 1; // Combat action counter
            return;
        }
    }
    // In range or no target - clear tooFar flag
    *(uint*)(this + 0x90) = *(uint*)(this + 0x90) | 2; // Set bit 1 (0x02 = hasTarget)
    uVar2 = DAT_010c2678 & DAT_012054b4; // Some combat state index
    DAT_012054b4 = DAT_012054b4 + 1;
    if (DAT_00d68368 < *(float*)(&DAT_010c2680 + uVar2 * 4) || // Check if combat timer exceeds threshold
        DAT_00d68368 == *(float*)(&DAT_010c2680 + uVar2 * 4)) {
        if (*(int*)(this + 0x88) == 0) {
            piVar3 = (int*)0x0;
        } else {
            piVar3 = (int*)(*(int*)(this + 0x88) + -0x48);
        }
        (**(code**)(*piVar3 + 0x298))(); // vtable+0x298 - fire weapon or attack
        return;
    }
    *(uint*)(this + 0x90) = *(uint*)(this + 0x90) | 0x20; // Set bit 5 (0x20 = waitingForCombatAction)
    return;
}