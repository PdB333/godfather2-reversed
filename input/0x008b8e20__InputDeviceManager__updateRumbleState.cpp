// FUNC_NAME: InputDeviceManager::updateRumbleState
void __fastcall InputDeviceManager::updateRumbleState(int *this)
{
    float fVar1;
    int iVar2;
    float leftMotor;
    float rightMotor;
    float fVar5;

    // Get singleton (e.g., InputDeviceManager or GameManager)
    iVar2 = FUN_00471610();  // singleton getter
    this[0x66] = *(int *)(iVar2 + 0x30); // +0x198: store some state
    rightMotor = 0.0f;
    this[0x67] = *(int *)(iVar2 + 0x38); // +0x19c: store some state
    this[99] |= 0x20; // +0x18c: set flag

    // Check if controller slot is valid (0 = disconnected? 0x48 = specific type?)
    if ((this[0x1a] == 0) || (leftMotor = 50.0f, this[0x1a] == 0x48)) { // +0x68: slot index or device type
        // Call virtual function at vtable+0x58 (e.g., getDeviceType)
        iVar2 = (*(int (**)(void))(*this + 0x58))();
        leftMotor = 50.0f;
        if (iVar2 == 0x1ff) { // 511 = XInput device ID?
            if (this[0x65] == 0) { // +0x194: some flag (e.g., left motor active?)
                (*(void (**)(int))(*this + 0x54))(1); // vtable+0x54: setLeftMotorSpeed(1)
                rightMotor = 128.0f;  // rumble magnitude
                leftMotor = 114.0f;   // 0x72
            } else {
                (*(void (**)(int))(*this + 0x54))(2); // setRightMotorSpeed(2)
                rightMotor = 64.0f;   // rumble magnitude
                leftMotor = 178.0f;   // 0xb2
            }
        }
    }

    // Apply rumble
    FUN_0046f990(rightMotor, leftMotor); // setRumbleMotors(left, right)

    // Check if cumulative movement delta exceeds threshold for auto-aim/vibration cut?
    iVar2 = FUN_00471610(); // singleton again
    fVar1 = *(float *)(iVar2 + 0x14); // +0x14: some delta component
    iVar2 = FUN_00471610();
    fVar5 = *(float *)(iVar2 + 0x10) * _DAT_00d577a0; // +0x10: another delta, multiplied by global
    iVar2 = FUN_00471610();
    if (*(float *)(iVar2 + 0x18) * _DAT_00d577a0 + fVar5 + fVar1 < DAT_00d75cb4) { // threshold
        this[99] |= 0x200; // +0x18c: set another flag (e.g., auto-aim enabled)
    }
    return;
}