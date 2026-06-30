// FUNC_NAME: MathUtils::wrapAngle
float MathUtils::wrapAngle(float* anglePtr) {
    float result;
    double tempDouble;

    // If no input angle pointer, generate a random angle under certain conditions
    if (anglePtr == nullptr) {
        result = 0.0f;
        // Check a global flag (DAT_012233a0 + 4) to decide whether to generate a random angle
        // If the flag is non-zero and not equal to 0x1f30, we generate a random value
        if ((*(int**)(DAT_012233a0 + 4) != nullptr) && (*(int**)(DAT_012233a0 + 4) != (int*)0x1f30)) {
            float randomAngle = (float)FUN_00799230(); // possibly a random double generator
            result = randomAngle;
        }
    } else {
        // Read the angle value, call a debug/hook function, then apply a conversion factor
        tempDouble = (double)(*anglePtr);
        FUN_00b9a9fa(); // likely a debug hook
        result = (float)tempDouble * DAT_00e44748; // conversion factor (e.g., deg->rad or rad->deg)
    }

    // Wrap the angle to a symmetric range: [-kAngleRange, kAngleRange]
    // DAT_00e44600 is likely 180.0 or PI for degrees/radians
    if (result < 0.0f) {
        return result + DAT_00e44600;
    } else {
        return result - DAT_00e44600;
    }
}