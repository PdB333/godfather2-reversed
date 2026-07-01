// FUNC_NAME: ControllerManager::updateLEDPatterns
void __fastcall ControllerManager::updateLEDPatterns(void *this)
{
    uint controllerCount;
    uint controllerIndex;
    uint buttonCount;
    uint buttonIndex;
    uint ledPartIndex;
    int deviceHandle;
    undefined4 ledPartValue;
    char colorName1[128]; // local_80, 128 bytes
    char colorName2[128]; // local_180
    char colorName3[128]; // local_100

    memset(colorName1, 0, 128);
    memset(colorName2, 0, 128);
    memset(colorName3, 0, 128);

    controllerCount = getControllerCount();
    if (controllerCount != 0) {
        for (controllerIndex = 0; controllerIndex < controllerCount; controllerIndex++) {
            initializeControllerLEDBuffer(controllerIndex);
            buttonCount = getControllerButtonCount();
            if (buttonCount != 0) {
                for (buttonIndex = 0; buttonIndex < buttonCount; buttonIndex++) {
                    ledPartIndex = getLEDPartCount(buttonIndex);
                    deviceHandle = getDeviceHandle(buttonIndex);
                    if (deviceHandle != 0) {
                        getLEDColorStrings(deviceHandle, colorName1, colorName2, colorName3);
                        if (ledPartIndex != 0) {
                            for (ledPartIndex = 0; ledPartIndex < ledPartIndex; ledPartIndex++) {
                                ledPartValue = getLEDPartValue(buttonIndex, ledPartIndex);
                                *(undefined4 *)((int)this + 0x298) = ledPartValue;
                                *(uint *)((int)this + 0x294) = ledPartIndex;
                                FUN_005a04a0("SetColor", 0, &DAT_00d8c478, 3, colorName1, colorName2, colorName3);
                            }
                        }
                    }
                }
            }
        }
    }
}