// FUNC_NAME: CallbackDispatcher::dispatchCallback
void CallbackDispatcher::dispatchCallback(void* param_2) // param_1 is this, param_2 is eventData
{
    int iVar1;
    code* callbackPtr; // local_4
    int callbackArray[3]; // local_10

    // Possibly enter critical section or reference count increment
    FUN_004d3bc0(this);

    iVar1 = FUN_00699ff0(); // Check if game is in a certain state (e.g., not paused)
    if ((iVar1 != 0) || 
        ((-1 < DAT_00e506ac) && (DAT_00e506ac < ((DAT_01129f90 - DAT_01129f8c) >> 2)))) 
    {
        // Re-enter critical section (or increment reference again)
        FUN_004d3bc0(this);

        // Extract callback info from event data (param_2)
        FUN_0069b510(callbackArray, param_2);

        // If a valid callback was found, execute it
        if (callbackArray[0] != 0) 
        {
            callbackPtr = (code*)callbackArray[0]; // local_4 was uninitialized; treat first array element as function pointer
            (*callbackPtr)(callbackArray[0]); // Call the callback with itself? Unclear but follow decompiled logic
        }
    }
    return;
}