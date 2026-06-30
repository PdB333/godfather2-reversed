// Xbox PDB: void __cdecl luaG_aritherror(struct lua_State *,struct lua_TObject const *,struct lua_TObject const *)
// FUNC_NAME: debugArithmeticCheck

// Function at 0x00633790: Evaluates a state pointer and conditionally invokes an arithmetic operation, then logs a debug message.
// Likely part of internal EARS debugging or test infrastructure.
void debugArithmeticCheck(int* statePtr)
{
    // The condition *statePtr != 3 && *statePtr == 4 is equivalent to *statePtr == 4
    if (*statePtr == 4)
    {
        // Local buffer for arithmetic result (size 4, possibly int or float)
        char resultBuffer[4];
        // Perform arithmetic operation and store result in buffer
        performArithmeticOperation(resultBuffer);
    }
    // Log a debug string indicating that arithmetic is being performed
    debugLogMessage("perform arithmetic on");
}