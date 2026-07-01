// FUNC_NAME: Entity::checkCondition
// Function at 0x008712b0
// Evaluates a condition based on type (param4). Types: 10 = special, 11 = always true, 12 = distance check, default = generic handler.
__thiscall bool Entity::checkCondition(int param2, int param3, int conditionType, int param5)
{
    if (conditionType == 10) {
        return FUN_0086b860(); // Special condition handler
    }

    if (conditionType != 11) {
        if (conditionType != 12) {
            return FUN_0086b010(param2, param3, conditionType, param5); // Default condition handler
        }

        // Condition type 12: Check if distance from external point (from FUN_0086d5a0) to this entity's position (offset 0x60, 0x68) is within radius (offset 0x70)
        undefined8* targetPos = (undefined8*)FUN_0086d5a0(); // Returns pointer to a position (x, z?) packed in 8 bytes
        float dx = *(float*)(this + 0x60) - (float)*targetPos; // this->x - targetX
        // Note: Y difference is intentionally zero (both subtracted from same offset 0x64)
        float dy = 0.0f; // Always zero due to reassignment? Actually original code: fVar3 = *(float*)(this+100) - *(float*)(this+100); => 0
        float dz = *(float*)(this + 0x68) - *(float*)(targetPos + 1); // this->z - targetZ
        float sqDist = dx*dx + dy*dy + dz*dz;
        float radiusSq = *(float*)(this + 0x70); // this->collisionRadius (squared?)
        if (radiusSq <= sqDist) {
            return false;
        }
    }

    // For condition type 11, or if distance is within radius (type 12), return true
    return true;
}