// FUNC_NAME: ControllerManager::setVibration
bool ControllerManager::setVibration(int magnitude) {
    // +0x580: pointer to device or controller state
    Device* device = *(Device**)((uint)this + 0x580);
    if (device != nullptr) {
        // Check if vibration is enabled globally (0x005e9d10)
        if (isVibrationAllowed()) {
            // Enter vibration context (0x00c9eac0)
            beginVibration();
            // Local float array for left motor value
            float motorValues[2];
            motorValues[0] = static_cast<float>(magnitude);
            // Set left motor (action 0) with the array (only first element used?)
            setMotor(0, motorValues);
            // Compare a global threshold against a second float (likely right motor intensity)
            if (g_vibrationThreshold < motorValues[1]) {
                // Stop motor 5? (action 5 with zero pointer)
                setMotor(5, 0);
                // Set motors 1 and 4 from the second motor value
                setMotor(1, &motorValues[1]);
                setMotor(4, &motorValues[1]);
                // Store the magnitude for later use (offset +0x4)
                *(int*)((uint)this + 4) = magnitude;
                // Exit vibration context (0x00c9eae0)
                endVibration();
                return true;
            }
            // Exit vibration context (0x00c9eae0) – fallthrough if condition fails
            endVibration();
        }
    }
    return false;
}