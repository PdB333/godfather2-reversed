// FUNC_NAME: isStateActionable
// Returns true if the integer value at *statePtr is one of the action-allowing states (8, 9, 12, 13).
// These constants likely correspond to specific state machine states (e.g., combat, movement, or building states).
bool isStateActionable(int* statePtr)
{
    int state = *statePtr;
    bool result = false;
    if (state == 8 || state == 9 || state == 12 || state == 13)
    {
        result = true;
    }
    return result;
}