// FUNC_NAME: InputManager::processAndCheckActiveControllers
bool __thiscall InputManager::processAndCheckActiveControllers(int thisPtr, int param2, int param3)
{
    // Call internal update functions
    FUN_004470c0(thisPtr);             // likely InputManager::updateControllerState()
    FUN_00447500(param2, param3);      // likely processInputSlot(param2, param3)

    // Check if either controller slot 0 or slot 1 is active (pointers at +0x90 and +0x98)
    // +0x90: first active controller pointer
    // +0x98: second active controller pointer
    if (*(int *)(thisPtr + 0x90) == 0 && *(int *)(thisPtr + 0x98) == 0)
        return false;

    return true;
}