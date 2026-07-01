// FUNC_NAME: InputManager::processInputEvents
// Address: 0x00958810
// Role: Processes all controller input events (button presses, analog stick movements, button holds) and dispatches them to the UI/Lua system.
// Iterates over active controllers, reads event type, and handles button press (type 2), analog stick (type 3), and button enumeration (type 6).

void __thiscall InputManager::processInputEvents(void)
{
    int iVar1;
    undefined4 uVar2;
    uint uVar3;
    char *pcVar4;
    uint uVar5;
    float10 fVar6;
    undefined1 *puVar7;
    char *pcVar8;
    uint controllerIndex;
    char deviceName[128];       // local_80
    char actionName[128];       // local_100
    char buttonName[128];       // local_180

    // Initialize string buffers to empty
    deviceName[0] = '\0';
    _memset(deviceName + 1, 0, 0x7f);
    actionName[0] = '\0';
    _memset(actionName + 1, 0, 0x7f);
    buttonName[0] = '\0';
    _memset(buttonName + 1, 0, 0x7f);
    controllerIndex = 0;

    int numControllers = getNumControllers(); // FUN_009bf8f0
    if (numControllers != 0) {
        do {
            setActiveController(controllerIndex); // FUN_009bf900
            int eventType = getInputEventType(); // FUN_009bf470

            if (eventType == 2) {
                // Button press event
                getInputEventStrings(&deviceName, &actionName, &buttonName); // FUN_009bf4c0
                formatInputString(deviceName, actionName, buttonName); // FUN_00958230

                uVar2 = getInputEventValue(); // FUN_009bf4f0
                processButtonPress(uVar2); // FUN_009bf580

                uVar2 = getInputEventID(); // FUN_009bf490
                sendInputEventToUI(this + 0x214, 0x80, &PTR_LAB_00d83b5c, uVar2); // FUN_005c4630

                callLuaSetSelection("SetSelection", 0, &DAT_00d8c478, 3, &deviceName, &actionName, &buttonName); // FUN_005a04a0
            }
            else if (eventType == 3) {
                // Analog stick event
                getInputEventStrings(&deviceName, &actionName, &buttonName); // FUN_009bf4c0
                formatInputString(deviceName, actionName, buttonName); // FUN_00958230

                int analogType = getAnalogInputType(); // FUN_009bf590
                if (analogType == 2) {
                    // Check if the action or button name contains "stickl" (left stick)
                    if ((_strstr(&actionName, "stickl") == (char *)0x0) &&
                        (_strstr(&buttonName, "stickl") == (char *)0x0)) {
                        // Not left stick -> store as right stick or other axis
                        fVar6 = (float10)getAnalogValue(0); // FUN_009bf5c0
                        *(float *)(this + 0x2a4) = (float)fVar6;
                        fVar6 = (float10)getAnalogValue(1);
                        *(float *)(this + 0x2a8) = (float)fVar6;
                    }
                    else {
                        // Left stick detected
                        fVar6 = (float10)getAnalogValue(0);
                        *(float *)(this + 0x29c) = (float)fVar6;
                        fVar6 = (float10)getAnalogValue(1);
                        *(float *)(this + 0x2a0) = (float)fVar6;
                    }
                    callLuaSetSelection("SetSelection", 0, &DAT_00d8c478, 3, &deviceName, &actionName, &buttonName); // FUN_005a04a0
                }
            }
            else if (eventType == 6) {
                // Button enumeration event (e.g., for mapping or holding detection)
                uVar5 = 0;
                int numButtons = getNumButtonsForController(); // FUN_009bf9f0
                if (numButtons != 0) {
                    do {
                        int buttonState = getButtonState(uVar5); // FUN_009bf9a0
                        if (buttonState != 0) {
                            formatInputString(buttonState, &deviceName, &actionName, &buttonName); // FUN_00958230
                            uVar2 = getButtonID(uVar5); // FUN_009bfb70
                            *(undefined4 *)(this + 0x294) = uVar2; // Store current button ID
                            callLuaSetSelection("SetSelection", 0, &DAT_00d8c478, 3, &deviceName, &actionName, &buttonName); // FUN_005a04a0
                        }
                        uVar5 = uVar5 + 1;
                        uVar3 = getNumButtonsForController(); // FUN_009bf9f0 (re-fetch, maybe changes?)
                    } while (uVar5 < uVar3);
                }
            }

            controllerIndex = controllerIndex + 1;
            uVar5 = getNumControllers(); // FUN_009bf8f0
        } while (controllerIndex < uVar5);
    }
    return;
}