// FUNC_NAME: applyScalingAndClamp
float applyScalingAndClamp(float value, int scalingType)
{
    double temp; // used for double conversion
    float result;

    switch (scalingType)
    {
    case 0:
        goto clampToMax; // direct to final clamp
    default:
        break;
    case 2:
    case 6:
    case 7:
        // Scale by DAT_00e2afac and subtract from max, then scale by DAT_00e2cd54
        temp = (double)(value * DAT_00e2afac);
        FUN_00b99e20(); // likely a rounding or conversion function
        value = (DAT_00e2b1a4 - (float)temp) * DAT_00e2cd54;
        break;
    case 3:
    case 8:
    case 9:
        // Scale by DAT_00e2a850, then subtract from max
        temp = (double)(value * DAT_00e2a850);
        FUN_00b99fcb(); // another conversion
        temp = (double)(DAT_00e2b1a4 - (float)temp);
        FUN_00b9af10(); // maybe floor/ceil
        value = (float)temp;
        // Invert relative to max
        value = DAT_00e2b1a4 - value;
        break;
    case 5:
        // Special case: if less than DAT_00e2cd54, scale linearly; else invert and scale
        if (DAT_00e2cd54 < value) {
            temp = (double)(DAT_00e2b1a4 - value);
            FUN_00b9af10();
            value = (float)temp * DAT_00e2b04c;
            value = DAT_00e2b1a4 - value;
        } else {
            value = value * DAT_00e2b1a0;
        }
        break;
    }

    // Clamp to [0.0, DAT_00e2b1a4]
    if (value <= 0.0f) {
        return 0.0f;
    }
    result = value;
    if (DAT_00e2b1a4 <= value) {
clampToMax:
        result = DAT_00e2b1a4;
    }
    return result;
}