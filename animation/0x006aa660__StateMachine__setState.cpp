// FUNC_NAME: StateMachine::setState

// State structure (used for each state in the state machine)
struct State {
    int* enterActionPtr;    // +0x28: pointer to enter action (or flag, non-zero if action exists)
    int exitActionPtr;      // +0x38: pointer to exit action (or flag)
    int enterTimer;         // +0x54: timer or flag cleared on enter
    int exitTimer;          // +0x5c: timer or flag cleared on exit
};

// State machine class
class StateMachine {
public:
    State** stateArray;     // +0x10: array of pointers to State objects (indexed by state index)
    int currentStateIndex;  // +0x1c: current state index, -1 for null
    int reentrancyCounter;  // +0x20: prevents reentrant calls during transition

    // External function: clears a timer/flag at the given address
    void clearTimer(int* addr, int value);  // FUN_00402050

    // Set the current state to newStateIndex, triggering enter/exit actions
    void setState(int newStateIndex);
};

void __thiscall StateMachine::setState(int newStateIndex)
{
    int prevStateIndex;
    State* prevState;
    State* newState;

    this->reentrancyCounter++;

    prevStateIndex = this->currentStateIndex;

    // If already in the requested state, nothing to do
    if (newStateIndex == prevStateIndex)
    {
        this->reentrancyCounter--;
        return;
    }

    // Get pointer to previous state object (if any)
    if (prevStateIndex == -1)
        prevState = nullptr;
    else
        prevState = this->stateArray[prevStateIndex];

    // Get pointer to new state object (if any)
    if (newStateIndex == -1)
        newState = nullptr;
    else
        newState = this->stateArray[newStateIndex];

    // Only perform the transition if we're not deeply nested (reentrancy guard)
    if (this->reentrancyCounter < 10)
    {
        this->currentStateIndex = newStateIndex;

        // Exit previous state: clear its exit timer if an exit action is present
        if (prevState != nullptr && prevState->exitActionPtr != 0)
        {
            clearTimer(&prevState->exitTimer, 0);
        }

        // Enter new state: clear its enter timer if an enter action is present
        // (The check newStateIndex == this->currentStateIndex is redundant after assignment,
        //  but ensures the state index hasn't been changed by a nested call)
        if (newStateIndex == this->currentStateIndex && newState != nullptr && newState->enterActionPtr != 0)
        {
            clearTimer(&newState->enterTimer, 0);
        }
    }

    this->reentrancyCounter--;
}