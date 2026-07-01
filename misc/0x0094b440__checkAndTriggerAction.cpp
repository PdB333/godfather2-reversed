// FUNC_NAME: checkAndTriggerAction
// Address: 0x0094b440
// Role: Checks a global flag and if set, retrieves a value and calls a setter function with constant first argument (1).
// Likely part of input/audio subsystem: possibly vibration or volume control.
// Global pointer DAT_0112af70 is assumed to be a singleton manager instance (e.g., InputDeviceManager or AudioManager).
// Offset +0x48 is a boolean flag enabling/disabling the action.

void checkAndTriggerAction(void)
{
    // Accesses a global manager instance (e.g., gInputDeviceManager or gSoundManager)
    // Check if the flag at offset 0x48 is non-zero (e.g., mVibrationEnabled, mSoundEnabled)
    if (*(char *)(DAT_0112af70 + 0x48) != '\0') {
        // Retrieve a value from some subsystem (e.g., current vibration intensity, volume level)
        int value = FUN_00977420(); // getCurrentIntensity() or getCurrentVolume()
        // Call an action function with first parameter 1 (e.g., controller index 1, or enable flag)
        // and the retrieved value as second parameter
        FUN_0094ae10(1, value); // setVibration(1, value) or setVolume(1, value)
    }
}