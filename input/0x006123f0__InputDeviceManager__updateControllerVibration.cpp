// FUNC_NAME: InputDeviceManager::updateControllerVibration
void __fastcall InputDeviceManager::updateControllerVibration(int controllerIndex)
{
    // DAT_012058e8 is the singleton InputDeviceManager instance
    InputDeviceManager* manager = (InputDeviceManager*)DAT_012058e8;
    if (manager == nullptr) {
        return;
    }

    if (controllerIndex == 0) {
        // Check if vibration is enabled (offset +0x9c)
        if (*(char*)((char*)manager + 0x9c) != '\0') {
            // Call vibration callback: subobject at +0x98, vtable index 3 (offset 0xc)
            // Likely sets vibration to a neutral state
            (**(code**)(**(int**)((char*)manager + 0x98) + 0xc))();
        }

        // Check if a vibration device pointer exists (offset +0x70)
        if (*(int*)((char*)manager + 0x70) != 0) {
            // Apply vibration with scaled parameters from global structs
            // DAT_00e2b04c is a master vibration scale
            float scale = DAT_00e2b04c;
            // DAT_012233a4 is a global vibration parameter block (e.g., for left/right motors)
            // Offsets 0x40,0x44,0x48,0x4c define left motor, right motor, etc.
            float param1 = scale * *(float*)(DAT_012233a4 + 0x40);
            float param2 = scale * *(float*)(DAT_012233a4 + 0x44);
            float param3 = scale * *(float*)(DAT_012233a4 + 0x48);
            float param4 = scale * *(float*)(DAT_012233a4 + 0x4c);
            FUN_006125c0(param1, param2, param3, param4);
        }
    } else if (controllerIndex != DAT_012058f0) {
        // Update the last used controller index
        DAT_012058f0 = controllerIndex;

        // If vibration is enabled, set the active controller
        if (*(char*)((char*)manager + 0x9c) != '\0') {
            // Vtable index 2 (offset 0x8) – likely sets the controller index
            (**(code**)(**(int**)((char*)manager + 0x98) + 8))(controllerIndex, 4);
        }

        // If vibration device exists, reset and apply new vibration
        if (*(int*)((char*)manager + 0x70) != 0) {
            FUN_0066d2e0(); // Reset/stop current vibration
            FUN_006125c0(); // Apply vibration with default parameters
        }
    }
}