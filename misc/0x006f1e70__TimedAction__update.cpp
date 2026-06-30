// FUNC_NAME: TimedAction::update
// Function address: 0x006f1e70
// Role: Checks and updates a timer. If the timer expires (<=0), it clears the associated action;
// otherwise it calls an update function with the remaining time.

void __fastcall TimedAction::update() // thiscall; this in ecx
{
    int* pActionData = *(int**)(this + 0x20); // Pointer to related action data
    if (pActionData != nullptr)
    {
        float remainingTime = *(float*)(this + 0x1c); // Timer value (seconds or countdown)
        if (remainingTime <= 0.0f)
        {
            // Timer expired – clear/reset the action
            // Build a temporary structure: pActionData, zeros, and a zero byte
            int temp[2]; // stack buffer: 8 bytes
            temp[0] = (int)pActionData;
            temp[1] = 0;
            char extraZero = 0;
            // call engine routine to clear the action (likely resets flags, removes from update list)
            ClearEngineAction(temp, 0); // FUN_00408a00
        }
        else
        {
            // Timer still running – update the action with remaining time
            UpdateEngineAction(&this->mPointer, 0, remainingTime, 0, 4); // FUN_00440590
            // Parameters: address of pointer field, unknown (0), time, unknown (0), flag (4)
        }
    }
    // If pActionData is null, do nothing
}