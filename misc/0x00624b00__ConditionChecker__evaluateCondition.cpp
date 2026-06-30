// FUNC_NAME: ConditionChecker::evaluateCondition
bool __thiscall ConditionChecker::evaluateCondition(int this, undefined4 param_2, undefined4 param_3, int conditionType, int param_5)
{
    bool result = false;
    
    switch(conditionType) {
    case 1: // Check if some object is null/not active
        // +0x20 likely holds a pointer or state flag
        return *(int *)(this + 0x20) == 0;
        
    case 2: // Compare float with parameter
        // +0x30 likely holds a current value
        // param_5 points to a structure with a threshold at offset +0x4
        if (*(float *)(this + 0x30) < *(float *)(param_5 + 4) ||
            *(float *)(this + 0x30) == *(float *)(param_5 + 4)) {
            return false;
        }
        break;
        
    case 3: // Compare float with global constant
        // DAT_00e2b05c is likely a global constant/threshold
        if (*(float *)(this + 0x30) <= DAT_00e2b05c) {
            return false;
        }
        break;
        
    case 4: // Always true
        break;
        
    default:
        goto end;
    }
    result = true;
    
end:
    return result;
}