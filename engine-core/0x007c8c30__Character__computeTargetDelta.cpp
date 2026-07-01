// FUNC_NAME: Character::computeTargetDelta
void __thiscall Character::computeTargetDelta(uint targetHandle, Vector3* outDelta)
{
    // Get this character's current position (likely from a global transform manager)
    int selfPosPtr = FUN_00471610();
    
    // Resolve target handle using the character controller
    FUN_007c6f70(targetHandle, *(int*)(this + 0x58));
    
    // Get pointer to character controller (e.g., AimController, MovementController)
    int controllerPtr = *(int*)(this + 0x58);
    int state = *(int*)(controllerPtr + 0x31a8);
    
    // If in a special state (not idle, not state 0x48)
    if (state != 0 && state != 0x48) {
        // Get the target's current position (second call to the same manager)
        int targetPosPtr = FUN_00471610();
        // Compute delta: target - self
        outDelta->x = *(float*)(targetPosPtr + 0x30) - *(float*)(selfPosPtr + 0x30);
        outDelta->y = *(float*)(targetPosPtr + 0x34) - *(float*)(selfPosPtr + 0x34);
        outDelta->z = *(float*)(targetPosPtr + 0x38) - *(float*)(selfPosPtr + 0x38);
        return;
    }
    
    // Check if the "stored position" flag is set (bit 2 of controller flags at +0x8e8)
    if ((*(uint*)(controllerPtr + 0x8e8) >> 2 & 1) != 0) {
        // Use the controller's stored aim position
        outDelta->x = *(float*)(controllerPtr + 0x8f0) - *(float*)(selfPosPtr + 0x30);
        outDelta->y = *(float*)(controllerPtr + 0x8f4) - *(float*)(selfPosPtr + 0x34);
        outDelta->z = *(float*)(controllerPtr + 0x8f8) - *(float*)(selfPosPtr + 0x38);
        return;
    }
    
    // Default: use a hardcoded offset from the character itself (e.g., aiming straight ahead)
    // +0x80 is likely a default aim direction (e.g., along local forward)
    *(Vector3*)outDelta = *(Vector3*)(this + 0x80);
}