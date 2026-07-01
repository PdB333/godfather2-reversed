// FUNC_NAME: isTimerConditionMet
int isTimerConditionMet(void) {
    char status;
    int result;
    uint timerValue;
    char buffer1[4];
    char buffer2[4];

    status = getStateInfo(buffer1, &timerValue, buffer2);
    // If the query failed (status == 0) or the masked timer value (as float) is below threshold, return false.
    if ((status == '\0') || ((float)(timerValue & STATE_MASK) <= STATE_THRESHOLD)) {
        result = 0;
    } else {
        result = 1;
    }
    return result;
}