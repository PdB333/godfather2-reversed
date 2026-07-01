// FUNC_NAME: InputManager::processInputAction
undefined4 InputManager::processInputAction(int this, undefined4 actionId)
{
    char result;
    int *singletonPtr;
    int controllerPtr;
    int *inputHandlerPtr;
    undefined4 returnValue;
    int localResult;

    localResult = 0;
    returnValue = 0;
    if (this != 0) {
        singletonPtr = (int *)InputDeviceManager::getInstance(); // FUN_0043b870
        if (singletonPtr == (int *)0x0) {
            return localResult;
        }
        controllerPtr = (**(code **)(*singletonPtr + 0x34))(); // getCurrentController()
        if (*(int *)(controllerPtr + 0xc) == 0) {
            inputHandlerPtr = (int *)0x0;
        }
        else {
            inputHandlerPtr = (int *)(*(int *)(controllerPtr + 0xc) + -0x48); // container_of to InputHandler
        }
        int controllerType = *(int *)(controllerPtr + 0x30); // controller type (e.g., 3 = keyboard)
        if (inputHandlerPtr == (int *)0x0) {
            return localResult;
        }
        result = (**(code **)(*inputHandlerPtr + 0x10))(actionId, &localResult); // handleAction
        returnValue = unaff_EDI; // likely a register holding previous return value
        if ((result == '\0') && (controllerType == 3)) {
            FUN_0084da50(inputHandlerPtr, actionId, &localResult); // fallback handler for keyboard
        }
    }
    return returnValue;
}