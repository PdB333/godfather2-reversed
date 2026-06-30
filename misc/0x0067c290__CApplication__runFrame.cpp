// FUNC_NAME: CApplication::runFrame
undefined4 __thiscall CApplication::runFrame(int *this)
{
    char isActive;
    undefined4 result;

    isActive = checkInputState(); // FUN_0069d700
    if (isActive == '\0') {
        handleNoInput(); // FUN_0068ac30
    }
    beginFrameProfiling(1); // FUN_0068baf0
    result = (**(code **)(*this + 0x2c))(); // virtual call to update/tick
    endFrameProfiling(1); // FUN_0068bcd0
    return result;
}