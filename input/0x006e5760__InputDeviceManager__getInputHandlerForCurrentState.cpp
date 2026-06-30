// FUNC_NAME: InputDeviceManager::getInputHandlerForCurrentState
void InputDeviceManager::getInputHandlerForCurrentState(int *outHandler)
{
    int *deviceList = *(int **)(this + 0x100);
    bool isFirstKeyPressed = ((bool (__thiscall *)(int *, uint))deviceList->vtable->func0x10)(deviceList, 0x55859efa);
    InputDevice *currentDevice = nullptr;
    if (isFirstKeyPressed) {
        currentDevice = (InputDevice *)outHandler; // outHandler passed in as potential device pointer?
    }
    int deviceType = (*(int (__thiscall **)(int *))currentDevice->vtable[0x270])(currentDevice);
    switch(deviceType) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
            break;
    }
    int someCount = currentDevice->field_0x1d3;
    int adjustedCount = 0;
    if (someCount != 0) {
        adjustedCount = someCount - 0x48;
    }
    bool isSecondKeyPressed = ((bool (__thiscall *)(int *, uint))deviceList->vtable->func0x10)(deviceList, 0x383225a1);
    if (isSecondKeyPressed) {
        if (m_pSomeObject != nullptr) {
            if (m_pSomeObject->field_0x30c0 != 0 && m_pSomeObject->field_0x30c0 != 0x48) {
                // continue with secondKeyPressed true
            } else {
                isSecondKeyPressed = false;
            }
        } else {
            isSecondKeyPressed = false;
        }
    } else {
        // already false
    }
    if (adjustedCount != 0) {
        if (isSecondKeyPressed) {
            goto LAB_006e587a;
        }
        if ((adjustedCount->field_0x1d0 >> 2 & 1) == 0) {
            goto LAB_006e5891;
        }
        if ((((currentDevice->field_0x238 >> 10) & 1) != 0) || (((currentDevice->field_0x239 >> 5) & 1) != 0)) {
            goto LAB_006e587a;
        }
        if (m_pSomeObject != nullptr) {
            isSecondKeyPressed = FUN_00690210(0x1f);
        }
    }
    if (!isSecondKeyPressed) {
LAB_006e5891:
        *outHandler = (int)this; // return this
        return;
    }
LAB_006e587a:
    *outHandler = DAT_00d5779c; // some global
    return;
}