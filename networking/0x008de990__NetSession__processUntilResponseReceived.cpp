// FUNC_NAME: NetSession::processUntilResponseReceived
void __thiscall NetSession::processUntilResponseReceived(int thisPtr, int param)
{
    bool isDone;
    int result;

    FUN_008dab90(param);                         // Initialize the command/parameter object
    FUN_0043aff0(param, 0x6bb6c2f9);             // Register/identify with specific hash (likely packet type or session ID)

    isDone = (bool)FUN_0043b120();               // Check if event processing is complete
    while (!isDone)
    {
        FUN_0043b210();                          // Process next event/poll
        result = FUN_0043ab70();                 // Query result/status
        if (result == 0)
        {
            // If status indicates a specific condition, get another result and store pointer
            result = FUN_0043b210();             // Process again (or get data)
            *(int*)(thisPtr + 0x210) = *(int*)(result + 8);  // Store a pointer from result (likely event data)
        }
        FUN_0043b1a0();                          // Cleanup/advance state
        isDone = (bool)FUN_0043b120();           // Re-check completion
    }
}