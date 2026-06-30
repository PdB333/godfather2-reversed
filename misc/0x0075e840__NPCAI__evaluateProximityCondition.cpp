// FUNC_NAME: NPCAI::evaluateProximityCondition
int __fastcall NPCAI::evaluateProximityCondition(void* thisPtr) {
    // Offsets: this+0x60 = self position x, this+0x68 = self position y (or z)
    // Get target entity position data (likely player or mission target)
    int targetData = FUN_00471610();
    
    // Compute delta Y: target->y - self->y
    float deltaY = *(float*)(targetData + 0x38) - *(float*)((int)thisPtr + 0x68);
    
    // Read target->x as a double (stored at targetData+0x30) and cast to float
    double targetXDouble = *(double*)(targetData + 0x30);
    float deltaX = (float)targetXDouble - *(float*)((int)thisPtr + 0x60);
    
    float sqDist = deltaX * deltaX + deltaY * deltaY;
    
    // Global threshold for squared distance (e.g., max engagement range)
    if (g_sqDistThreshold <= sqDist) {
        // If within range, check facing angle or line-of-sight via FUN_0046fd60
        float angle = FUN_0046fd60((int)thisPtr + 0x60);
        if (angle < g_angleThreshold) {
            return 0; // Condition satisfied (within range and angle)
        }
    }
    return 1; // Condition not satisfied
}