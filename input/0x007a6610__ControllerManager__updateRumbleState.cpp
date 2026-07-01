// FUNC_NAME: ControllerManager::updateRumbleState
void __fastcall ControllerManager::updateRumbleState(int *this)
{
    float rumbleTimer;
    float deltaTime;
    float timerThreshold;
    float timerWithDelta;
    int rumbleStrength;
    int motorFlags;
    int localStrengthBuffer;
    bool bVar;
    int iVar;
    int playerIndex;
    bool buttonPressed;

    timerThreshold = _DAT_00d6a7c8; // global rumble duration threshold
    deltaTime = DAT_012067e8; // frame delta time (seconds)
    timerWithDelta = deltaTime + (float)this[0xc4c]; // rumble timer + delta
    this[0xc4c] = (int)timerWithDelta; // update timer as integer (truncated)

    if (timerThreshold < timerWithDelta) {
        this[0xc4c] = 0; // reset timer
        localStrengthBuffer = 0;
        rumbleStrength = 0;
        bVar = getRumbleStrength(&localStrengthBuffer, 0); // get random intensity?
        if (bVar) {
            motorFlags = 0x80; // default: left motor? (low frequency)
            bVar = this->vtable[0x28c](); // virtual: isControllerActive?
            if (bVar && (FUN_007a5fe0(0), ((uint)this[0x23b] >> 1 & 1) == 0)) {
                motorFlags = 0x40; // right motor? (high frequency)
                if (this[0x7ba] != 0) {
                    iVar = FUN_006b07e0(this[0x7ba]); // isDeviceConnected?
                    if (iVar != 0) {
                        playerIndex = FUN_00471610(); // get local player index
                        buttonPressed = FUN_00798010(playerIndex + 0x30,
                                                     this[0xb1e],
                                                     this[0xb1f]); // is specific action active?
                        if (buttonPressed) {
                            motorFlags = 0xc0; // both motors
                        }
                    }
                }
            }
            setControllerRumble(localStrengthBuffer, motorFlags); // apply rumble
        }
    }
}