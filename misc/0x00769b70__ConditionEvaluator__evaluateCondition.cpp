// FUNC_NAME: ConditionEvaluator::evaluateCondition
// Function address: 0x00769b70
// Evaluates various condition types based on a condition ID (param_4 - 0x12).
// Returns true/false depending on the condition.

bool __thiscall ConditionEvaluator::evaluateCondition(int param_2, int param_3, int param_4, int param_5) {
    int iVar4;
    int iVar3;
    double dVar5;
    bool bResult;

    switch (param_4 - 0x12) {
    case 0: { // param_4 == 0x12
        // Compare two pointer-derived offsets
        int* ptr70 = *(int**)(this + 0x70); // +0x70: pointer to some object
        if (ptr70 == 0) {
            iVar4 = 0;
        } else {
            iVar4 = *(int*)(ptr70 + 0x1c78) - 0x48; // offset 0x1c78 within that object
        }
        int* ptr74 = *(int**)(this + 0x74); // +0x74: another pointer or offset container
        if (ptr74 == 0) {
            iVar3 = 0;
        } else {
            iVar3 = *(int*)(ptr74 + 0x48); // note: offset is +0x48 from the pointer? Actually dereference then subtract 0x48? No, original: iVar3 = *(int*)(this+0x74) + -0x48; so it's *ptr74 - 0x48. But Ghidra shows pointer add: + -0x48 means minus 0x48, so (int*)(this+0x74) is address, subtract 0x48 yields new pointer, then dereference? Wait: The decompiler shows: if (*(int *)(param_1 + 0x74) == 0) { iVar3 = 0; } else { iVar3 = *(int *)(param_1 + 0x74) + -0x48; } That means it takes the value at param_1+0x74 (which is an int), checks if it's 0, then iVar3 = that int minus 0x48. So it's not a pointer; it's an integer offset. Let me re-express: int val74 = *(int*)(this+0x74); if (val74 == 0) iVar3 = 0; else iVar3 = val74 - 0x48; That's different from the other case.
        }
        // Compare the two computed values
        if (iVar4 == iVar3 && iVar4 != 0) {
            return false;
        }
        break;
    }
    case 1: // param_4 == 0x13: check bit 0 of flags at +0x7c
        return (*(byte*)(this + 0x7c) & 1) != 0;
    case 2: // bit 1
        return (*(uint*)(this + 0x7c) >> 1) & 1;
    case 3: // bit 2
        return (*(uint*)(this + 0x7c) >> 2) & 1;
    case 4: // bit 3
        return (*(uint*)(this + 0x7c) >> 3) & 1;
    case 5: // param_4 == 0x17: check global condition negation
        return !isGlobalConditionA(); // FUN_007eeab0 returns 0 means true?
    case 6: // param_4 == 0x18: another global condition
        return !isGlobalConditionB(); // FUN_007eeb00
    case 7: // param_4 == 0x19: check condition involving a float
        dVar5 = getSomeFloat(); // FUN_00769620
        return !checkConditionA((float)dVar5); // FUN_00769740
    case 8: // param_4 == 0x1A
        dVar5 = getSomeFloat();
        return !checkConditionB((float)dVar5); // FUN_00769800
    case 9: { // param_4 == 0x1B: call a vtable method on the object at +0x70
        int* obj = *(int**)(this + 0x70); // Pointer to some object
        if (obj) {
            // Call method at offset 0x1c0 in the vtable (object method)
            double dResult = ((double (*)())(*(int*)(*obj + 0x1c0)))();
            if (dResult <= g_fGlobalFloat) { // _DAT_00d65bd0
                return false;
            }
        }
        bResult = evaluateState(); // FUN_00721190
        return bResult;
    }
    case 10: { // param_4 == 0x1C: check additional conditions
        int val74 = *(int*)(this + 0x74);
        if (val74 != 0 && val74 != 0x48) {
            dVar5 = getSomeFloat();
            bool cond1 = checkConditionC((float)dVar5); // FUN_007696e0
            bool cond2 = checkConditionD((float)dVar5); // FUN_007697a0
            if (!cond1 && !cond2) { // Both false
                return false;
            }
        }
        break; // Fall through to return true
    }
    case 0xB: // param_4 == 0x1D: compare two floats
        if (*(float*)(this + 0x30) <= *(float*)(this + 0x80)) {
            return false;
        }
        return true;
    default:
        return otherConditionEvaluator(param_2, param_3, param_4, param_5); // FUN_0073e300
    }
    return true;
}