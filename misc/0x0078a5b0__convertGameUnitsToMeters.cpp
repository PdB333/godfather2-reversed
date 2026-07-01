// FUNC_NAME: convertGameUnitsToMeters
float convertGameUnitsToMeters(float gameUnits)
{
    // DAT_012067e8 is likely a global conversion factor (e.g., 0.01f for cm to m)
    // _DAT_00d5f560 is another global scale factor (e.g., 1.0f or engine-specific)
    return (float)DAT_012067e8 * gameUnits * (float)_DAT_00d5f560;
}