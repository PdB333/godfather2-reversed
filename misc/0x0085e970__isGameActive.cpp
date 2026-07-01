// FUNC_NAME: isGameActive
bool isGameActive(void)
{
    char dummy; // unused stack variable, passed as argument to getGameStatePointer
    char* flagPtr = getGameStatePointer(&dummy); // returns pointer to a global flag
    return *flagPtr != '\0'; // check if flag is non-zero (true)
}