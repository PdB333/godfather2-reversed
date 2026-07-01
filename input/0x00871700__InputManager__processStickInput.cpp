// FUNC_NAME: InputManager::processStickInput
void InputManager::processStickInput(float *targetVector) {
    // Get pointer to global input manager singleton
    InputManager *inputMgr = reinterpret_cast<InputManager*>(FUN_00471610());
    
    // Dead zone threshold (likely 0.2f or similar)
    float deadZone = DAT_00d5ef84;
    // Mask to clear sign bit for absolute value comparison (0x7FFFFFFF)
    uint32_t absMask = DAT_00e44680;
    
    float leftStickX = *(float*)((uint8_t*)inputMgr + 0x20); // +0x20: left stick X
    float leftStickY = *(float*)((uint8_t*)inputMgr + 0x28); // +0x28: left stick Y
    float rightStickX = *(float*)((uint8_t*)inputMgr + 0x30); // +0x30: right stick X
    float rightStickY = *(float*)((uint8_t*)inputMgr + 0x38); // +0x38: right stick Y
    
    // Apply dead zone to left stick magnitude
    float leftMagnitude;
    if (deadZone <= reinterpret_cast<float>(reinterpret_cast<uint32_t&>(leftStickX) & absMask) ||
        deadZone <= reinterpret_cast<float>(reinterpret_cast<uint32_t&>(leftStickY) & absMask)) {
        // If either axis exceeds dead zone, take absolute value (via double conversion)
        double absX = static_cast<double>(leftStickX);
        FUN_00b9a9fa(); // likely fabs() - modifies the double on FP stack
        leftMagnitude = static_cast<float>(absX);
    } else {
        leftMagnitude = 0.0f;
    }
    
    // Compute difference between target and right stick
    float diffX = targetVector[0] - rightStickX; // target X - right stick X
    float diffY = targetVector[2] - rightStickY; // target Z (or Y) - right stick Y
    
    // Apply dead zone to difference
    float diffMagnitude;
    if (deadZone <= reinterpret_cast<float>(reinterpret_cast<uint32_t&>(diffX) & absMask) ||
        deadZone <= reinterpret_cast<float>(reinterpret_cast<uint32_t&>(diffY) & absMask)) {
        double absDiff = static_cast<double>(diffX);
        FUN_00b9a9fa(); // fabs
        diffMagnitude = static_cast<float>(absDiff);
    } else {
        diffMagnitude = 0.0f;
    }
    
    // Compute final input value (left magnitude minus difference magnitude)
    float finalInput = leftMagnitude - diffMagnitude;
    FUN_004a1580(finalInput); // Apply to movement/throttle system
}