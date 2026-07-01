// FUNC_NAME: InputManager::isDeviceValid
// Function address: 0x007b9f80
// Checks if the given device (param_2) matches three conditions:
// - It is the correct device type (via m_deviceTypeTable + offset 0x1fc8)
// - It is connected/active (via FUN_007f80e0)
// - It matches a specific global constant (DAT_00d58cbc)
// Returns 1 if all conditions true, else 0.

undefined1 __thiscall InputManager::isDeviceValid(int this, undefined4 deviceParam)
{
    undefined4 deviceTypeCheck;
    char result1, result2, result3;

    // m_pInputManager is at this+0x58, then we access two fields at offsets 0x1fc8 and 0x1fcc
    int* pInputManager = *(int**)(this + 0x58);
    deviceTypeCheck = *(undefined4*)(*(int*)(pInputManager + 0x1fc8));
    result1 = FUN_007f81c0(deviceParam, *(undefined4*)(*(int*)(pInputManager + 0x1fcc)));
    if (result1 != 0)
    {
        result2 = FUN_007f80e0(deviceParam, deviceTypeCheck);
        if (result2 != 0)
        {
            result3 = FUN_007f8240(deviceParam, DAT_00d58cbc);
            if (result3 != 0)
            {
                return 1;
            }
        }
    }
    return 0;
}