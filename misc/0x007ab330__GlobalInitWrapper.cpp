// FUNC_NAME: GlobalInitWrapper
// Address: 0x007ab330
// Role: Wrapper function delegating to 0x007e0ca0 (likely part of engine initialization chain). Called from multiple points in the binary.
void GlobalInitWrapper(void)
{
    FUN_007e0ca0();
}