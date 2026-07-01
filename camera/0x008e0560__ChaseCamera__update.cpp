// FUNC_NAME: ChaseCamera::update
void __fastcall ChaseCamera::update() {
    bool gameActive = isGameModeActive(); // FUN_00481620
    if (gameActive && (this->pTargetData != nullptr)) {
        // Copy target pitch from target data structure at offset 0x1ef4
        this->targetPitch = *(float*)((char*)this->pTargetData + 0x1ef4);
        
        // Get smoothed interpolation factor from time-dependent function
        float smoothAngle = getSmoothedAngle(); // FUN_008dab60
        
        // Calculate desired rotation from global offset and current pitch
        // DAT_00e44564 is a global target reference angle
        float desiredYaw = DAT_00e44564 - this->currentPitch;
        float desiredPitch = -smoothAngle;
        setCameraRotation(desiredYaw, desiredPitch); // FUN_008de620
        
        // Set camera mode via vtable: offset 0x28 in vtable at +0x58
        void (*setCameraMode)(int) = (void (*)(int))this->vtable[0x28 / 4];
        setCameraMode(0x80); // argument 0x80 likely a mode enum
        
        applyCameraPostEffects(); // FUN_008dfd20
    }
    baseCameraUpdate(); // FUN_008dc5a0
}