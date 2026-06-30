// FUNC_NAME: setSystemMode
// Address: 0x004df560
// Role: Wrapper function that calls a subsystem setter with a constant mode parameter (1).
// Game logic: This likely enables or initializes a specific game subsystem (e.g., debug rendering, audio, or input). The callee (0x0051aa50) takes an integer to configure the subsystem's state.
void setSystemMode(void)
{
    setSubsystemState(1);
    return;
}