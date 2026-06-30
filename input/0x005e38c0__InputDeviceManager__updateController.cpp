// FUNC_NAME: InputDeviceManager::updateController
bool __fastcall InputDeviceManager::updateController(int currentTime, ControllerState* state)
{
    // Constants for timer conversion (assumed: 32-bit wrap and tick-to-seconds scale)
    const float kTimerWrapOffset = 4294967296.0f; // 2^32 for unsigned wrap compensation
    const float kTickToSeconds   = 1.0f / 1000.0f; // assuming millisecond ticks
    const float kAbsFixOffset    = 0.0f;          // used to compute absolute value

    // Externals: manager singletons likely initialized elsewhere
    extern void*  gLeftMotorManager;    // DAT_01223508
    extern void*  gRightMotorManager;   // DAT_012234bc
    extern void*  gInputManager;        // DAT_0122350c  (InputDeviceManager*)
    extern bool   FUN_005dc9b0(void* manager, float delta);
    extern bool   FUN_005e4700(void* manager, float delta);
    extern void   FUN_005e86e0();       // feedback update

    // Compute delta time with overflow handling (timer wrap)
    int ticksDelta = currentTime - state->previousTime;          // offset +0x08
    float deltaTime = static_cast<float>(ticksDelta);
    if (ticksDelta < 0) {
        deltaTime += kTimerWrapOffset;
    }
    deltaTime *= kTickToSeconds;
    // Absolute value for negative drift (should be positive in normal flow)
    if (deltaTime < 0.0f) {
        deltaTime = kAbsFixOffset - deltaTime;
    }

    state->previousTime = currentTime;                           // store new timestamp

    // Update left/right motor vibration based on elapsed time
    bool leftMotorActive  = FUN_005dc9b0(gLeftMotorManager, deltaTime);
    bool rightMotorActive = FUN_005e4700(gRightMotorManager, deltaTime);

    // Check if vibration/force-feedback is enabled (flag at +0x1744)
    if (gInputManager != nullptr && *(byte*)((uintptr_t)gInputManager + 0x1744) != 0) {
        // Update force‑feedback multiple times (pattern iteration)
        for (int i = 0; i < 5; i++) {
            FUN_005e86e0();
        }
        return (rightMotorActive && leftMotorActive);
    }
    return false;
}