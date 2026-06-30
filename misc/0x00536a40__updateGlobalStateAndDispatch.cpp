// FUNC_NAME: updateGlobalStateAndDispatch
// Function address: 0x00536a40
// Stores four integer parameters and one float (via XMM0) into global state,
// then conditionally dispatches two processing calls when a state condition is met.

void updateGlobalStateAndDispatch(int arg0, int arg1, int arg2, int arg3, float arg4_float) // float passed in XMM0
{
    /* Global state pointers (offsets unknown) */
    // _DAT_0121a2f4, _DAT_0121a2f8, _DAT_0121a2fc, _DAT_0121a2c0, _DAT_0121a2f0
    gState.param0 = arg0;          // +0x00?  
    gState.param1 = arg1;          // +0x04?
    gState.param2 = arg2;          // +0x08?
    gState.param3 = arg3;          // +0x0C? (stored at different location: _DAT_0121a2c0)
    gState.param4_float = arg4_float; // +0x10? (stored at _DAT_0121a2f0)

    // Check if the state machine is in a particular mode
    // DAT_012058e8 is possibly a pointer to current state identifier; 
    // gState.currentStateId and gState.someOtherState are compared.
    if ((gState.currentStatePtr == &gState.targetStateStruct) && 
        (gState.someStateA == gState.someStateB)) 
    {
        // Process using the stored parameters
        FUN_0060add0(gState.someStateB, gState.somePointer, &gState.param4_float);
        FUN_0060add0(gState.someStateB, gState.anotherPointer, &gState.param3);
    }
    return;
}