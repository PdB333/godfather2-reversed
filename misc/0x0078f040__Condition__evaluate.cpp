// FUNC_NAME: Condition::evaluate
byte __thiscall Condition::evaluate(int* thisParam, int* entity) {
    byte result = 0;
    uint entityFlags = *(uint*)(entity + 0xd4); // +0xD4: bitmask flags (e.g., faction allegiance)
    uint requiredFlags = thisParam[8];
    uint forbiddenFlags = thisParam[9];
    if ((requiredFlags & entityFlags) == requiredFlags &&
        (~entityFlags & forbiddenFlags) == forbiddenFlags) {
        // Check first global condition pair
        int globalVal1 = getGlobalValue1(); // FUN_00791620 - returns current game state value
        if ((globalVal1 == thisParam[0]) || 
            ((globalVal1 != thisParam[1]) && (thisParam[0] == 4))) {
            int globalVal2 = getGlobalValue2(); // FUN_007914e0 - another global stat
            if ((globalVal2 == thisParam[2]) ||
                ((globalVal2 != thisParam[3]) && (thisParam[2] == 0))) {
                // Check item/entity comparison
                int entitySpecificValue = *(int*)(entity + 0xD8); // +0xD8: entity-specific ID/type
                if (((thisParam[4] == 0) && (thisParam[5] == 0)) ||
                    (entitySpecificValue == thisParam[4]) ||
                    ((thisParam[5] != 0) && (entitySpecificValue != thisParam[5]))) {
                    // Check a series of sub-conditions from entity fields
                    if (checkSubCondition1(*(void**)(entity + 0xDC)) &&   // +0xDC: pointer to sub-condition data
                        checkSubCondition2(getGlobalFuncResult()) &&       // FUN_00791750 -> FUN_0078eb20
                        checkSubCondition3(*(void**)(entity + 0x8C)) &&   // +0x8C
                        checkSubCondition4(*(void**)(entity + 0x90)) &&   // +0x90
                        checkSubCondition5(*(void**)(entity + 0x94)) &&   // +0x94
                        checkSubCondition6(*(void**)(entity + 0x98))) {   // +0x98
                        result = 1;
                        int additionalCheck = getAdditionalCheck(); // FUN_007912e0
                        if (additionalCheck != 0) {
                            byte extraResult = runExtraCheck(additionalCheck); // FUN_0078ef90
                            result = extraResult & 1;
                        }
                    }
                }
            }
        }
    }
    return result;
}