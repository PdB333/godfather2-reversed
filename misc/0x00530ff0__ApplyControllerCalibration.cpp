// FUNC_NAME: ApplyControllerCalibration
void ApplyControllerCalibration(uint controllerIndex, float analogValue)
{
    // [0x00530ff0] Applies calibration/scaling to an analog input using a per-controller lookup table.
    // Then dispatches to a type-specific calibration function based on controller type.
    
    // Global array of calibration data (size 0x38 per entry)
    // DAT_011a0f28 is likely a pointer to an array of ControllerCalibration structs
    ControllerCalibration* calibrationEntry = nullptr;
    if (controllerIndex < 0x1000)
    {
        calibrationEntry = (ControllerCalibration*)((uint)DAT_011a0f28 + controllerIndex * 0x38);
    }
    else
    {
        calibrationEntry = nullptr;
    }
    
    // Get calibration factors from the table (unsigned short at offsets +2 and +4)
    // Presumably these are deadzone/range scaling values read from device calibration data.
    float factor1 = (float)(calibrationEntry->decay);    // +0x02
    float factor2 = (float)(calibrationEntry->sensitivity); // +0x04
    
    // Compute scaled analog value
    float scaledValue1 = analogValue / factor1;   // local_20
    float scaledValue2 = analogValue / factor2;   // local_1c (unused after compute? Seems leftover)
    
    // Subtract from a global constant (maybe hardware neutral value)
    float neutralValue = DAT_00e44564 - scaledValue1; // local_18 (unused after compute)
    float temp = scaledValue2; // local_14 (unused)
    
    // Now dispatch to type-specific calibration based on current controller type (DAT_01219954)
    // These global constants represent different controller connection types (e.g., wired, wireless, etc.)
    // The callee (FUN_0060add0) applies final deadzone/curve and stores result somewhere.
    
    if (DAT_01219954 == DAT_01219a4c) // Type A
    {
        FUN_0060add0(DAT_01219954, DAT_01219a28, &scaledValue1);
    }
    else if (DAT_01219954 == DAT_01219a50) // Type B
    {
        FUN_0060add0(DAT_01219954, DAT_01219a24, &scaledValue1);
    }
    else if (DAT_01219954 == DAT_01219a58) // Type C
    {
        FUN_0060add0(DAT_01219954, DAT_01219a2c, &scaledValue1);
    }
    else if (DAT_01219954 == DAT_01219a68 && DAT_01219a5c != 0) // Type D, with additional flag
    {
        FUN_0060add0(DAT_01219954, DAT_01219a5c, &scaledValue1);
    }
}