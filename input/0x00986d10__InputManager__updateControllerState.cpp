// FUNC_NAME: InputManager::updateControllerState
/*
 * Function: InputManager::updateControllerState (0x00986d10)
 * Updates controller state, vibration, and camera based on analog inputs.
 * Reads current analog values and compares with stored values,
 * toggles vibration/controller active flags as needed.
 */
void __fastcall InputManager::updateControllerState(InputManager* this)
{
    // Read current analog axes (likely X, Y, Z from left/right stick or trigger)
    uint16 currentAnalogX = getAnalogX();  // FUN_0060e9e0
    uint16 currentAnalogY = getAnalogY();  // FUN_0060e9f0
    uint16 currentAnalogZ = getAnalogZ();  // FUN_0060e9d0

    // Flags for controller activity and vibration state
    bool wasControllerInactive = (*(int*)((uintptr_t)this + 0x70) == 0);   // +0x70: m_bControllerActive
    bool wasVibrationEnabled  = (*(int*)((uintptr_t)this + 0x78) != 0);   // +0x78: m_bVibrationEnabled

    // Check if controller should be considered active
    char isControllerActive = isControllerActiveFunc();  // FUN_0060e860
    if (wasControllerInactive != (bool)isControllerActive) {
        setControllerActive(!wasControllerInactive);  // FUN_0060e970 - toggles activation
    }

    // Check if vibration should be enabled based on current state
    char isVibrationEnabledNow = isVibrationEnabledFunc();  // FUN_0060e690
    if ((bool)isVibrationEnabledNow != wasVibrationEnabled) {
        setVibrationEnabled(wasVibrationEnabled);  // FUN_0060e680 - sets to previous state? (contradicts logic? likely a bug in decomp or logic)
    }

    // If any analog axis value changed, update vibration settings and camera
    if (((currentAnalogX != *(uint16*)((uintptr_t)this + 0x114)) ||
         (currentAnalogY != *(uint16*)((uintptr_t)this + 0x110)) ||
         (currentAnalogZ != *(uint16*)((uintptr_t)this + 0x118)))
    {
        uint32 vibrationIntensity = isVibrationEnabledNow;  // FUN_0060e690 returns an int/uint used as intensity
        setVibration(*(uint16*)((uintptr_t)this + 0x114),  // stored analog X
                     *(uint16*)((uintptr_t)this + 0x110),  // stored analog Y
                     *(uint16*)((uintptr_t)this + 0x118),  // stored analog Z
                     wasControllerInactive,                 // flag indicating if controller was inactive
                     vibrationIntensity);                   // intensity from getter

        setCameraFromAnalogZ((float)*(int*)((uintptr_t)this + 0x118));  // FUN_00412bd0 - uses stored analog Z as float

        // Copy some previous value (e.g., last timestamp or previous analog float)
        *(uint32*)((uintptr_t)this + 0x6C) = *(uint32*)((uintptr_t)this + 0x5C);
    }

    return;
}