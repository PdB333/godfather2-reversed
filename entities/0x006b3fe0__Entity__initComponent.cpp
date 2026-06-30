// FUNC_NAME: Entity::initComponent
void __thiscall Entity::initComponent(int this, int param_2, undefined4 param_3, undefined4 param_4, undefined4 param_5)
{
    int allocation;
    undefined4 subObject;

    // Allocate a 0x44-byte sub-component (size matches XInput controller slot)
    allocation = allocate(0x44);
    if (allocation == 0) {
        subObject = 0;
    } else {
        // Construct the sub-component using given parameters
        subObject = constructSubObject(this, param_2, param_3, param_4, param_5);
    }

    // Store pointer to the sub-component at offset +0xFC
    *(int *)(this + 0xFC) = subObject;

    // Copy a value from param_2's offset +0x54 to this+0x44 (likely a handle or ID)
    *(int *)(this + 0x44) = *(int *)(param_2 + 0x54);

    // Clear bit 23 (0x00800000) of flags at offset +0x34
    *(unsigned int *)(this + 0x34) &= 0xFF7FFFFF;

    // Call a general initialization/update function
    FUN_006b2f70();

    // If the object's class ID (stored at +0x40) matches a known constant (0x637b907)
    // and param_5 is false (byte zero), log a debug message
    if ((*(int *)(this + 0x40) == 0x637b907) && ((char)param_5 == '\0')) {
        FUN_007e7df0(0x19);  // Log message ID 0x19
        // Build formatted string using global DAT_0112a608
        undefined4 logBuffer[3];
        logBuffer[0] = DAT_0112a608;
        logBuffer[1] = 0;
        *(char *)&logBuffer[2] = (char)param_5;
        FUN_00408a00(&logBuffer, 0);
    }

    return;
}