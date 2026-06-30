// FUNC_NAME: CollisionManager::getCollisionResult
uint __thiscall CollisionManager::getCollisionResult(uint param_2, uint param_3, int param_4) {
    // this+0x0C: m_overrideFlags (bit0: unused?, bit1: overrideValid, bits9-16: cachedCollisionType)
    uint flags = *(uint *)(this + 0x0C);
    
    // Check bit1 (overrideValid flag)
    if ((flags >> 1) & 1) {
        // Return cached collision type from bits9-16, shifted to bits8-15 (reserving low byte)
        return ((flags >> 9) << 8);
    }
    
    // First attempt: get base collision data from pair (param_2, param_3)
    uint result = FUN_00713960(param_2, param_3);
    
    // If no override requested (param_4 == 0) and base result is not TYPE_NORMAL(1) or TYPE_SPECIAL(2),
    // return base result with low byte cleared (maybe as a mask)
    if ((param_4 == 0) && (result != 1) && (result != 2)) {
        return result & 0xFFFFFF00;
    }
    
    // Otherwise, fallback to extended collision evaluation with additional data
    result = FUN_00715290(param_2, param_3, param_4, 0);
    return result;
}