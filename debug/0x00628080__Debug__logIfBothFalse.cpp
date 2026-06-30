// FUNC_NAME: Debug::logIfBothFalse
// Address: 0x00628080
// Purpose: Checks two conditions; if both are false, logs the string "number".
void Debug::logIfBothFalse() {
    float someFloat = getSomeFloat(); // FUN_006259b0
    if (someFloat == 0.0f) {
        int someFlag = getSomeFlag(); // FUN_006257d0
        if (someFlag == 0) {
            logDebugMessage("number"); // FUN_00627ac0 with PTR_s_number_00e2a8a8
        }
    }
}