// FUNC_NAME: checkInputAndProcess
// Address: 0x0092ca90
// Role: Checks if a condition is met (likely input available) and performs a processing action.
// Calls: isControllerAvailable() at 0x00954860, processControllerInput() at 0x0092ca40

int checkInputAndProcess()
{
    char available = isControllerAvailable(); // 0x00954860
    if (available != '\0') {
        processControllerInput(); // 0x0092ca40
        return 1;
    }
    return 0;
}