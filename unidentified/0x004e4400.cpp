// FUNC_ADDRESS: 0x004e4400 - Simple wrapper that enables a game option (passes true to the underlying setter)
// FUNC_NAME: enableGameplayOption
void enableGameplayOption(void)
{
    int enabledFlag = 1; // true
    setGameplayOption(enabledFlag);
    return;
}