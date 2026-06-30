// FUNC_NAME: processRumbleEffect
void processRumbleEffect(void) {
    // Get an integer from some subsystem (e.g., time, random, or input state)
    int result = FUN_0072f370(1); // Possibly getElapsedTime or getRandomValue with seed 1
    
    // Read a global pointer to the active controller/device object (DAT_012233a0 + 0x4)
    int* controllerPtr = *(int**)(DAT_012233a0 + 4);
    
    if (controllerPtr != nullptr && controllerPtr != (int*)0x1f30) {
        // Check a field at offset -0x5c from the controller pointer (e.g., m_rumbleEnabled or m_active)
        int offsetField = *(int*)((char*)controllerPtr - 0x5c);
        if (FUN_008c74d0(offsetField) != 0) {
            // Convert result to float, negate, and possibly add a constant if negative
            float floatVal = (float)result;
            if (result < 0) {
                floatVal = floatVal + DAT_00e44578; // Possibly adjust range
            }
            // Apply rumble/effect with the negated float value and parameter 5 (motor index or effect type)
            FUN_008c09a0(-floatVal, 5);
        }
    }
}