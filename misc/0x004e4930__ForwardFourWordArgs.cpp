// FUNC_NAME: ForwardFourWordArgs
// Function at 0x004e4930: Unpacks a pointer to an array of 4 DWORDs and forwards each as an individual argument to another function (a simple thunk).
void __fastcall ForwardFourWordArgs(uint32_t* pArgs)
{
    // Calls the target function at 0x005277b0 with the four extracted values.
    FUN_005277b0(pArgs[0], pArgs[1], pArgs[2], pArgs[3]);
}