// FUNC_NAME: ConditionHandler::processCondition
void __thiscall ConditionHandler::processCondition(void* this, uint param_2, uint param_3)
{
    // this+0x8: float field (e.g., currentValue)
    float* currentValue = (float*)((char*)this + 8);
    uint maskedValue = *(uint*)currentValue & DAT_00e44680; // mask applied to integer bits of float
    float leftSide = DAT_00e2b1a4 - DAT_00e2b1a4 / (float)(param_3 & 0xFF);
    bool condition = leftSide <= (float)maskedValue;

    uint result = FUN_0064bb50(condition); // returns status code (low byte = flag, next byte = sub-status)

    if ((result & 0xFF) == 0) {
        // Cleanup path
        FUN_0064be30(param_3);
        FUN_00b9a9fa(param_2);
        FUN_0064be30(param_2);
        return;
    }

    uint subStatus = (result >> 8) & 0xFF; // second byte of result
    if (*currentValue <= 0.0f && *currentValue != 0.0f) {
        FUN_0064bb50((subStatus << 8) | 1); // set low byte to 1
        return;
    }
    FUN_0064bb50(subStatus << 8); // keep low byte zero
}