// FUNC_NAME: checkAndPrintNumberDebug
void checkAndPrintNumberDebug(void)
{
    int conditionResult;
    float10 flagValue;

    flagValue = (float10)getSomeFlag();  // FUN_006259b0 - returns a flag as float? Possibly a debug flag
    if (flagValue == (float10)0) {
        conditionResult = getSomeCondition();  // FUN_006257d0 - returns 0 if something is false
        if (conditionResult == 0) {
            printDebugString("number");  // FUN_00627ac0 - prints the debug string "number"
        }
    }
    return;
}