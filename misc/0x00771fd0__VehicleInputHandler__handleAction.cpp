// FUNC_NAME: VehicleInputHandler::handleAction
undefined1 __thiscall VehicleInputHandler::handleAction(int this, int inputValue, undefined4 param3, undefined4 param4, int actionId, undefined4 param6)
{
    char cVar1;
    undefined1 uVar2;
    uint uVar3;
    uint *puVar4;
    float10 fVar5;
    float10 fVar6;
    float10 fVar7;

    uVar2 = 1;
    // Action IDs: 0x12=18, 0x13=19, 0x14=20, 0x15=21, 0x16=22, 0x17=23, 0x18=24, 0x19=25
    switch(actionId) {
    case 0x12: // Toggle bit off (e.g., handbrake release)
        uVar3 = FUN_006252f0(); // Returns controller bitmask
        puVar4 = (uint *)(*(int *)(this + 0x58) + 0x1b94); // +0x58: pointer to internal state, +0x1b94: flags
        *puVar4 = *puVar4 & ~uVar3;
        return 1;
    case 0x13: // Toggle bit on (e.g., handbrake set)
        uVar3 = FUN_006252f0();
        puVar4 = (uint *)(*(int *)(this + 0x58) + 0x1b94);
        *puVar4 = *puVar4 | uVar3;
        return 1;
    case 0x14: // Steering analog input
        fVar6 = (float10)(**(code **)(**(int **)(this + 0x58) + 0x208))(); // Virtual function: get steering base value?
        fVar7 = (float10)inputValue;
        if (inputValue < 0) {
            // Compensate for negative values (e.g., joystick axis)
            fVar7 = fVar7 + (float10)DAT_00e44578; // Possibly 65536 (2^16) to handle signed short?
        }
        *(float *)(this + 0x60) = (float)(fVar7 * (float10)DAT_00d5efb8 + fVar6); // +0x60 = m_steering
        return 1;
    case 0x15: // Throttle analog input
        if (((uint)(*(int **)(this + 0x58))[0x6e5] >> 7 & 1) == 0) { // Check bit 7 of some flag (invert?)
            fVar6 = (float10)(**(code **)(**(int **)(this + 0x58) + 0x204))(); // Get throttle base value
            fVar7 = (float10)inputValue;
            if (inputValue < 0) {
                fVar7 = fVar7 + (float10)DAT_00e44578;
            }
            *(float *)(this + 0x64) = (float)(fVar7 * (float10)DAT_00d5efb8 + fVar6); // +0x64 = m_throttle
            return 1;
        }
        // Invert mode: add extra value from another source
        fVar6 = (float10)FUN_007340c0(); // Get some additional input (e.g., keyboard throttle?)
        if (fVar6 <= (float10)0) {
            *(undefined4 *)(this + 0x64) = 0;
        }
        fVar7 = (float10)(**(code **)(**(int **)(this + 0x58) + 0x204))(); // Base throttle
        fVar5 = (float10)inputValue;
        if (inputValue < 0) {
            fVar5 = fVar5 + (float10)DAT_00e44578;
        }
        *(float *)(this + 0x64) = (float)(fVar5 * (float10)DAT_00d5efb8 + fVar7 + (float10)(float)fVar6);
        return 1;
    case 0x16: // Brake analog input
        fVar6 = (float10)(**(code **)(**(int **)(this + 0x58) + 0x200))(); // Get brake base value
        fVar7 = (float10)inputValue;
        if (inputValue < 0) {
            fVar7 = fVar7 + (float10)DAT_00e44578;
        }
        *(float *)(this + 0x68) = (float)(fVar7 * (float10)DAT_00d5efb8 + fVar6); // +0x68 = m_brake
        FUN_007f9540(); // Update something (e.g., brake lights?)
        return 1;
    case 0x17: // Enable specific feature (ID 0x11)
        FUN_007f63e0(0x11);
        return 1;
    case 0x18: // Disable specific feature (ID 0x11)
        FUN_007f6420(0x11);
        return 1;
    case 0x19: // Action (e.g., exit vehicle, interact)
        cVar1 = FUN_007f47a0(); // Check if something is active (menu/dialogue?)
        if (cVar1 == '\0') {
            if (*(int *)(*(int *)(this + 0x58) + 0x1e70) != 0) { // Check some pointer
                FUN_004df600(); // Call exit/interact function
            }
            if (*(int *)(*(int *)(this + 0x58) + 0x1e84) != 0) {
                FUN_004df600();
                return 1;
            }
        }
        break;
    default:
        // Forward unknown actions to another handler
        uVar2 = FUN_0080e8e0(inputValue, param3, param4, actionId, param6);
    }
    return uVar2;
}