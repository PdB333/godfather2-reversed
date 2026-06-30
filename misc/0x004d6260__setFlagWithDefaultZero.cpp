// FUNC_NAME: setFlagWithDefaultZero
void setFlagWithDefaultZero(uint param1, uint param2, uint param3, uint param4)
{
    // Forward to internal function with third parameter hardcoded to 0
    // param3 is ignored; inner function expects a flag that is set to 0 here
    FUN_004d6160(param1, param2, 0, param4);
    return;
}