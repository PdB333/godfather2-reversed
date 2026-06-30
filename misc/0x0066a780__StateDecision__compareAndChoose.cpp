// FUNC_NAME: StateDecision::compareAndChoose
// Address: 0x0066a780
// Compares two state objects (pointers) by their value at offset +0x8.
// Sets this object's own value at +0x8 based on the comparison and optional random/condition check.
// Calls helper functions to finalize the transition.

void StateDecision::compareAndChoose(int stateA, int stateB) {
    // Read the comparison value from each state object (offset +0x8 is likely a state ID or priority)
    int valA = *(int*)(stateA + 8);
    int valB = *(int*)(stateB + 8);

    if (valA != valB) {
        // Values differ – prefer stateA's value.
        // Write stateA's value into this object's comparison field.
        *(int*)(this + 8) = valA;
        // Process both states (e.g., blend or consider both)
        FUN_0066bb40(stateA, stateB); // likely "applyTwoStates(stateA, stateB)"
        return;
    }

    // Values are identical – check a condition via external function.
    int conditionResult = FUN_00665c30(); // likely "randomCheck()" or "timeCheck()" returning -1 on fail
    if (conditionResult != -1) {
        // Condition succeeded: use stateA's value.
        *(int*)(this + 8) = valA;
        FUN_0066c8d0(stateA); // likely "applySingleState(stateA)"
        return;
    }

    // Condition failed: set this object's value to the boolean negation of valA (0/1).
    *(uint*)(this + 8) = (uint)(valA == 0);
    FUN_0066c8d0(stateB); // apply the other state
    return;
}