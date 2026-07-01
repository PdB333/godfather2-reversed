// FUNC_NAME: PlayerSM::updateStateMachine
void PlayerSM::updateStateMachine()
{
    int state = *(int *)(this + 0xC4); // current state offset +0xC4
    char someFlag;
    int targetObj;

    switch(state)
    {
    case 0:
    case 2:
    case 3:
    case 4:
    case 5:
    case 7:
    case 8:
        // Generic state handling: set some animation state to 5, then do default update with zero flags
        setAnimationState(5);
        defaultUpdate(this, 0, 0);
        break;
    case 1:
        // Special case for state 1: set animation to 4, then alternate update
        setAnimationState(4);
        alternateUpdate(this, 0);
        break;
    case 9:
        // State 9: check attached object via target pointer at +0x38
        targetObj = getTargetFromPointer(*(int *)(this + 0x38)); // +0x38 is target handle or pointer
        if (targetObj != 0)
        {
            someFlag = checkTargetCondition(targetObj);
            if (someFlag != 0)
            {
                // If condition met, set animation 1 and do final update
                setAnimationState(1);
                finalStateUpdate(this);
            }
        }
        break;
    }
}