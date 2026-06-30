// FUNC_NAME: StateMachineController::update
void __thiscall StateMachineController::update(int thisPtr, undefined4 param_2)
{
    int *currentStatePtr; // piVar1 (reused)
    char conditionResult;

    // Check if current state pointer is non-zero and not a special sentinel value (0x48)
    if (*(int *)(thisPtr + 300) != 0 && *(int *)(thisPtr + 300) != 0x48)
    {
        // Check if state behavior object at +0x128 can transition (vtable+0x10 and +0x14)
        conditionResult = (**(code (__thiscall **)(int))(**(int **)(thisPtr + 0x128) + 0x10))(thisPtr);
        if (conditionResult == '\0')
        {
            conditionResult = (**(code (__thiscall **)(int))(**(int **)(thisPtr + 0x128) + 0x14))(thisPtr);
            if (conditionResult == '\0')
            {
                // Destroy current state and clear state behavior pointer
                currentStatePtr = (int *)(thisPtr + 300);
                *(undefined4 *)(thisPtr + 0x128) = 0;
                if (*currentStatePtr != 0)
                {
                    FUN_004daf90(currentStatePtr); // likely destruction/free
                    *currentStatePtr = 0;
                }
            }
        }
    }

    // Check if current state is null or sentinel, and another condition (FUN_00725c80) is false
    // and bit 0 of +0x120 flags is clear
    if ((*(int *)(thisPtr + 300) == 0 || *(int *)(thisPtr + 300) == 0x48) &&
        (conditionResult = FUN_00725c80(), conditionResult == '\0' && (*(byte *)(thisPtr + 0x120) & 1) == 0))
    {
        // Reset something at +0x3c (likely a timer)
        FUN_004088c0(thisPtr + 0x3c);
    }

    // If state is active and not sentinel, and lower 2 bits of +0xe8 are clear, call main virtual update
    if (*(int *)(thisPtr + 300) != 0 && *(int *)(thisPtr + 300) != 0x48 &&
        (*(byte *)(thisPtr + 0xe8) & 3) == 0)
    {
        (**(code (__thiscall **)(int, undefined4))(**(int **)(thisPtr + 0x128) + 4))(thisPtr, param_2);
    }
    return;
}