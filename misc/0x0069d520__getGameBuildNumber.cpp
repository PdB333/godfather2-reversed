// FUNC_NAME: getGameBuildNumber
// Address: 0x0069d520
// Returns a 16-bit build/version number stored in global variable.
uint16 getGameBuildNumber(void)
{
    return *reinterpret_cast<uint16*>(0x0112a038); // gBuildNumber
}