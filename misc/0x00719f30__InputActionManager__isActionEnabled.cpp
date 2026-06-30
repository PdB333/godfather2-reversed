// FUNC_NAME: InputActionManager::isActionEnabled
// Function at 0x00719f30: Checks if a specific action (by ID) is currently enabled.
// Action IDs 0-12 are mapped to global check functions; default case skips the check.
// A global override flag (bit 9 at +0x1f58 of manager at this+0x18) forces true.

unsigned char __thiscall InputActionManager::isActionEnabled(int this, int actionId)
{
    unsigned char result = 0;
    switch(actionId)
    {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
            // Group 0-7 uses one check function
            result = checkActionAllowed(gActionCheckFunc1);  // _DAT_00e51774
            break;
        case 8:
            result = checkActionAllowed(gActionCheckFunc2);  // _DAT_00e51778
            break;
        case 9:
            result = checkActionAllowed(gActionCheckFunc3);  // _DAT_00e5176c
            break;
        case 10:
        case 11:
        case 12:
            result = checkActionAllowed(gActionCheckFunc4);  // _DAT_00e51770
            break;
        default:
            goto checkOverride;
    }

checkOverride:
    // Global override: if bit 9 of the override flags is set, return 1 (enabled)
    // Override flags are stored in the manager referenced by this->inputManager (+0x18) at offset +0x1f58
    if ((*(unsigned int*)(*(int*)(this + 0x18) + 0x1f58) >> 9) & 1)
    {
        result = 1;
    }
    return result;
}