// FUNC_NAME: PlayerStateMachine::updateState
void PlayerStateMachine::updateState(void)
{
    // Check if the sub-state machine pointer is null
    if (*(int *)(this + 0xc) == 0) {
        // Set flag to 1 and state to 9 (likely idle or default state)
        *(byte *)(this + 0x14) = 1;
        *(int *)(this + 0x10) = 9;
    } else {
        // Read global game mode (offset +4 from global pointer)
        int gameMode = *(int *)(DAT_012234d8 + 4);
        if (gameMode != 5) { // 5 might be a special mode (e.g., loading, cutscene)
            int param = *(int *)(this + 0x11c);
            // Determine action type: 0 if param != 0, 2 if param == 0
            int actionType = (param != 0) ? 0 : 2;
            // Call virtual function at +0x4c (likely getAction or processInput)
            int result = (*(code **)(this + 0x4c))(actionType, gameMode, param);
            // Process the result
            FUN_00b11f00(result, actionType, gameMode, param);
            // Call virtual function on the sub-state machine object (at +0xc) with a stack buffer
            char buffer[1116];
            (**(code **)(**(int **)(this + 0xc) + 0x18))(buffer);
            return;
        }
    }
    return;
}