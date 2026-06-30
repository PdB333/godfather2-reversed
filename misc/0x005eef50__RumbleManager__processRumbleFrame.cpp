// FUNC_NAME: RumbleManager::processRumbleFrame
void RumbleManager::processRumbleFrame() {
    // Check if rumble system is active (non-null pointer at +0x3FC)
    if (*(int*)(this + 0x3FC) != 0) {
        // Query pending rumble events (probably input/controller state)
        int rumbleEvent1 = FUN_005e9d10();  // bool? e.g., isRumbleSource1Active
        int rumbleEvent2 = FUN_005e9d10();  // isRumbleSource2Active
        int rumbleEvent3 = FUN_005e9d10();  // isRumbleSource3Active

        // Begin rumble frame (e.g., start writing vibration)
        FUN_00c9eac0();  // beginRumbleFrame()

        // Apply rumble based on event flags
        if (rumbleEvent1 != 0) {
            // Set left motor using value at +0x90A0 (intensity?)
            FUN_00ca4e90(0, *(int*)(this + 0x90A0));  // setMotor(0, leftIntensity)
        }

        if (rumbleEvent2 != 0) {
            // Set left motor from +0x9094
            FUN_00ca4e90(0, *(int*)(this + 0x9094));
            // Set right motor from +0x9098
            FUN_00ca4e90(1, *(int*)(this + 0x9098));
            // Set trigger motor (?) from +0x909C
            FUN_00ca4e90(2, *(int*)(this + 0x909C));
        }

        if (rumbleEvent3 != 0) {
            // Set left motor from +0x908C
            FUN_00ca4e90(0, *(int*)(this + 0x908C));
        }

        // End rumble frame (commit changes)
        FUN_00c9eae0();  // endRumbleFrame()
    }
}