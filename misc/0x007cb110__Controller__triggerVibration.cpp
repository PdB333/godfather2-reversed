// FUNC_NAME: Controller::triggerVibration
void __thiscall Controller::triggerVibration(Controller* this, bool enable) {
    uint flags;
    uint* pFlags;
    VibrationInterface* vibInterface;

    if (enable && 
        ((*(uint*)(this + 0x1d0) >> 7 & 1) == 0) &&
        ((*(uint*)(*(int*)(this + 0x58) + 0x8e4) >> 0x12 & 1) == 0)) {
        
        // Get vibration interface and set motors
        vibInterface = (VibrationInterface*)FUN_007ab160();
        vibInterface->setMotor(8);       // e.g., left motor
        vibInterface = (VibrationInterface*)FUN_007ab160();
        vibInterface->setMotor(2);       // e.g., right motor
        vibInterface = (VibrationInterface*)FUN_007ab160();
        vibInterface->setMotor(0x20);    // e.g., trigger rumble

        // Mark vibration as active
        *(uint*)(this + 0x1d0) |= 8;
    }
}