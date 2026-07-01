// FUNC_NAME: VehicleStateMachine::updateState
void __fastcall VehicleStateMachine::updateState(int thisPtr)
{
    bool isDriverNull = *(int *)(thisPtr + 0x1c) == 0;
    switch(*(int *)(thisPtr + 8)) // currentState
    {
    case 0: // STATE_IDLE
        VehicleStateMachine::handleIdleState(isDriverNull);
        return;
    case 1: // STATE_DRIVING
    case 4: // STATE_BOOSTING
    case 5: // STATE_TURNING
    case 6: // STATE_SLIDING
        VehicleStateMachine::handleDrivingState(isDriverNull);
        return;
    case 2: // STATE_BRAKING
        VehicleStateMachine::handleBrakingState(isDriverNull);
        return;
    case 3: // STATE_STOPPED
        VehicleStateMachine::handleStoppedState(isDriverNull);
    }
    return;
}