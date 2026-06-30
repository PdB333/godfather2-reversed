// FUNC_NAME: applyUnitConversion

float10 applyUnitConversion(float value, int conversionType, int conversionMode)
{
    double tempDouble;
    float selectedFactor;

    // conversionMode == 2 indicates a specific unit conversion branch
    if (conversionMode == 2) {
        // Select factor based on conversionType (1 => one factor, otherwise another)
        if (conversionType == 1) {
            selectedFactor = g_unitFactorB; // DAT_00e447ac
        } else {
            selectedFactor = g_unitFactorA; // DAT_00e447a8
        }

        // First scaling step
        tempDouble = (double)(value * g_scale1); // DAT_00e2cd54

        // Floating-point rounding / precision adjustment
        FUN_00b9c041();

        // Division then second scaling
        tempDouble = (double)(((float)tempDouble / selectedFactor) * g_scale2); // DAT_01205878

        // Another rounding / precision step
        FUN_00b9d99d();

        // Final scaling
        value = (float)tempDouble * g_scale3; // DAT_00e2b04c
    }

    return (float10)value;
}