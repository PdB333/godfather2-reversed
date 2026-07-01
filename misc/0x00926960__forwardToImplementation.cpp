// FUNC_NAME: forwardToImplementation
// Address: 0x00926960
// Role: Thin wrapper that forwards all parameters to the function at 0x00928080.
// Likely a virtual dispatcher or platform abstraction in EARS engine.
void forwardToImplementation(int param1, int param2, int param3, int param4, int param5, int param6)
{
    // Delegate to the actual implementation at 0x00928080
    FUN_00928080(param1, param2, param3, param4, param5, param6);
}