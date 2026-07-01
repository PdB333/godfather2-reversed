// FUNC_NAME: SomeClass::validateState
void __thiscall SomeClass::validateState(int thisPtr, int desiredState)
{
    int currentStateIndex;
    int currentStatePtr = *(int *)(thisPtr + 0x30); // +0x30: pointer to current state object or state ID

    // If currentStatePtr is non-zero and not equal to 0x48 (a sentinel value)
    if ((currentStatePtr != 0) && (currentStatePtr != 0x48)) {
        // Compute index: if currentStatePtr is 0, index is 0; otherwise subtract 0x48 (size of state struct?)
        if (currentStatePtr == 0) {
            currentStateIndex = 0;
        } else {
            currentStateIndex = currentStatePtr - 0x48;
        }
        // If the computed index does not match the desired state, trigger a state change or error
        if (currentStateIndex != desiredState) {
            FUN_0090ea10(); // likely a state transition or error handler
            return;
        }
    }
    // If currentStatePtr is 0 or 0x48, no action needed (state is considered valid or uninitialized)
}