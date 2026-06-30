// FUNC_NAME: PlayerInputHandler::processComponentInput
bool __thiscall PlayerInputHandler::processComponentInput(int thisPtr, int* componentPtr)
{
    char isActive;
    
    if (componentPtr == (int*)0x0) {
        componentPtr = (int*)FUN_006bca80(thisPtr + 0x60);  // get component from member at +0x60
        if (componentPtr == (int*)0x0) goto returnFalse;
    }
    
    isActive = FUN_006bdb50();  // check if component is active
    if (isActive != '\0') {
        (**(code**)(*componentPtr + 0x1c))(thisPtr);  // call virtual method at vtable+0x1c (e.g., update)
    }
    
returnFalse:
    return componentPtr != (int*)0x0;
}