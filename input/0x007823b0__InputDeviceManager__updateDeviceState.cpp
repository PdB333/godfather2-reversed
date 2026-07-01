// FUNC_NAME: InputDeviceManager::updateDeviceState
uint __thiscall InputDeviceManager::updateDeviceState(InputDeviceManager *this, int *outState)
{
    uint uVar1;
    // offset 0x84: m_deviceType (1-8 for gamepad, keyboard, etc.)
    uVar1 = *(int *)((char *)this + 0x84) - 1;
    if (uVar1 < 8) {
        if (*outState != 0) {
            // try to get state from specific device object
            uVar1 = getDeviceState(*outState); // FUN_007822d0
            if (uVar1 != 0) goto LAB_007823db;
        }
        // return high byte flags on success (deviceType in upper 8 bits?)
        return uVar1 & 0xffffff00;
    }
LAB_007823db:
    // fallback to generic polling
    uVar1 = pollDevice(outState); // FUN_0077e850
    return uVar1;
}