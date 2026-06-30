// FUNC_NAME: initializeGlobalSettings
void initializeGlobalSettings(void)
{
    uint* pointerArray[2]; // +0x00: array of two pointers
    uint parameters;       // +0x08: parameter data (value from global)
    uint8 flag;            // +0x0C: flag (initialized to 0)

    pointerArray[0] = (uint*)&PTR_LAB_00d5dbb0; // Global pointer
    parameters = DAT_0112a5a4;                  // Global data value
    flag = 0;

    // Call initialization function with parameter struct and a zero argument
    FUN_00408a00(&parameters, 0);
    return;
}