// FUNC_NAME: InputDeviceManager::UpdateRumbleState
void __fastcall InputDeviceManager::UpdateRumbleState(InputDeviceManager* thisPtr)
{
    // Pre-update hook (e.g., synchronize with hardware)
    somePreUpdateFunction();

    // Copy 4-byte rumble value from controller slot (offset +0x50) to global rumble buffer
    // Global DAT_00d87900 is the shared rumble data for output to XInput
    copyToGlobalRumbleBuffer(&g_rumbleOutput, (uint8_t*)thisPtr + 0x50, 4, 0, 0, 1);
}