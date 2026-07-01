//FUNC_NAME: InputManager::handleControllerDisconnectReconnect
bool __thiscall InputManager::handleControllerDisconnectReconnect(void* this)
{
    char cVar1;
    int iVar2;
    char* pcVar3;
    undefined4 local_24;
    undefined4 local_20;
    undefined4 local_1c;
    undefined8 local_c;
    undefined4 local_4;

    // Check if controller is connected and certain flags are clear/set
    cVar1 = isControllerConnected(); // FUN_00481620
    if ((((cVar1 != '\0') && ((*(uint*)(*(int*)((char*)this + 0x58) + 0x24a0) >> 0x14 & 1) == 0)) &&
         (cVar1 = isControllerActive(), cVar1 != '\0')) && // FUN_007d8aa0
        (((*(uint*)(*(int*)((char*)this + 0x58) + 0x249c) >> 0x11 & 1) != 0 &&
          (cVar1 = isVibrationEnabled(), cVar1 != '\0')))) // FUN_00705b40
    {
        cVar1 = isKeyboardActive(); // FUN_00481660
        if (cVar1 == '\0') {
            return 1; // No keyboard active, handled
        }
        iVar2 = *(int*)(*(int*)((char*)this + 0x58) + 0x74c);
        if ((iVar2 == 0) || (iVar2 == 0x48)) {
            iVar2 = 0;
        }
        else {
            iVar2 = iVar2 + 0x10;
        }
        playControllerVibration(iVar2); // FUN_004a8ec0
        local_1c = CONCAT31(local_1c._1_3_, 1);
        debugPrintMessage(2, CONCAT44(5, local_1c), CONCAT44(local_20, local_24), local_c, local_4); // FUN_0079fb90
        return 1;
    }

    // Check for controller disconnection
    cVar1 = isControllerDisconnected(); // FUN_00481640
    if ((((cVar1 != '\0') && (pcVar3 = (char*)(*(int*)((char*)this + 0x58) + 0x21d0), *pcVar3 == '\0')) &&
         (iVar2 = getControllerHandle(), iVar2 != 0)) && (iVar2 + -0x58 != 0)) // FUN_004a8f00
    {
        // Call virtual function at offset 600 (0x258) on the object at this+0x58
        (**(code**)(**(int**)((char*)this + 0x58) + 600))(iVar2 + -0x58);
        *pcVar3 = '\x01'; // Set flag at offset 0x21d0
        return 1;
    }
    return 0;
}