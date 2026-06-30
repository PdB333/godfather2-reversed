// FUNC_NAME: Character::isTargetInRange
// Address: 0x004f7a00
// This function checks if a target position is within a given range (squared distance test).
// It uses the object's base range (offset 0x28) plus an additional modifier.
// Position is stored as three consecutive floats starting at offset 0x70.
bool __thiscall Character::isTargetInRange(const float* targetPos, float rangeModifier)
{
    // Compute delta from target position to this object's position
    float dx = targetPos[0] - *(float*)((int)this + 0x70); // position.x
    float dy = targetPos[1] - *(float*)((int)this + 0x74); // position.y
    float dz = targetPos[2] - *(float*)((int)this + 0x78); // position.z

    // Effective range = base range + modifier
    float effectiveRange = *(float*)((int)this + 0x28) + rangeModifier; // baseRange

    // Squared distance check
    if (dx*dx + dy*dy + dz*dz < effectiveRange * effectiveRange)
    {
        return true;
    }
    return false;
}